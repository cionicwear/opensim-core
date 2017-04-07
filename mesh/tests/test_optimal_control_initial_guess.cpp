
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "testing.h"

#include <mesh.h>

using Eigen::Ref;
using Eigen::VectorXd;
using Eigen::RowVectorXd;
using Eigen::Vector2d;
using Eigen::MatrixXd;
using Eigen::Matrix2d;

using namespace mesh;
using namespace Catch;

// This test ensures that user-specified initial guesses for an optimal
// control problem are used correctly.

/// This problem seeks to move a point mass to a specified final position with
/// minimum effort. There are two final positions (+/- 1/sqrt(2)) that are
/// equally desirable; the initial guess should determine which final position
/// the optimizer finds.
template<typename T>
class FinalPositionLocalOptima : public mesh::OptimalControlProblemNamed<T> {
public:
    FinalPositionLocalOptima()
    {
        this->set_time(0, 1);
        this->add_state("x", {-1.5, 1.5}, {0});
        this->add_state("v", {-10, 10}, {0}, {0});
        this->add_control("F", {-50, 50});
    }
    void dynamics(const VectorX<T>& states, const VectorX<T>& controls,
                  Ref<VectorX<T>> derivatives) const override
    {
        derivatives[0] = states[1];
        derivatives[1] = controls[0];
    }
    void integral_cost(const T& /*time*/,
                       const VectorX<T>& /*states*/,
                       const VectorX<T>& controls,
                       T& integrand) const override {
        integrand = 0.001 * pow(controls[0], 2);
    }
    /// This function has minima at `x = \pm 1/\sqrt(2)`.
    static T two_minima(const T& x) {
        // Root at -1, double root at 0, and root at 1.
        // These roots cause two minima, one between -1 and 0, and another
        // between 0 and 1.
        return (x - 1) * (x + 1) * x*x;
    }
    void endpoint_cost(const T& /*final_time*/,
                       const VectorX<T>& final_states,
                       T& cost) const override
    {
        cost = 100.0 * two_minima(final_states[0]);
    }
};

TEST_CASE("Final position cost with two local optima", "[initial_guess]") {

    // Guess low.
    {
        auto ocp = std::make_shared<FinalPositionLocalOptima<adouble>>();
        const int N = 20;
        DirectCollocationSolver<adouble> dircol(ocp, "trapezoidal", "ipopt", N);

        // TODO allow getting a guess template, so that we don't need to
        // manually fill in all parts of the guess.
        OptimalControlIterate guess;
        guess.time.setLinSpaced(N, 0, 1);
        ocp->set_state_guess(guess, "x", RowVectorXd::LinSpaced(N, 0, -1));
        ocp->set_state_guess(guess, "v", RowVectorXd::Zero(N));
        ocp->set_control_guess(guess, "F", RowVectorXd::Zero(N));
        OptimalControlSolution solution = dircol.solve(guess);
        solution.write("final_position_local_optima_low_solution.csv");
        REQUIRE(Approx(solution.states.rightCols<1>()[0]).epsilon(1e-4)
                        == -1/sqrt(2));
    }
    // Guess high.
    {
        auto ocp = std::make_shared<FinalPositionLocalOptima<adouble>>();
        const int N = 20;
        DirectCollocationSolver<adouble> dircol(ocp, "trapezoidal", "ipopt", N);

        // TODO allow getting a guess template, so that we don't need to
        // manually fill in all parts of the guess.
        OptimalControlIterate guess;
        guess.time.setLinSpaced(N, 0, 1);
        ocp->set_state_guess(guess, "x", RowVectorXd::LinSpaced(N, 0, +1));
        ocp->set_state_guess(guess, "v", RowVectorXd::Zero(N));
        ocp->set_control_guess(guess, "F", RowVectorXd::Zero(N));
        OptimalControlSolution solution = dircol.solve(guess);
        solution.write("final_position_local_optima_high_solution.csv");
        REQUIRE(Approx(solution.states.rightCols<1>()[0]).epsilon(1e-4)
                        == +1/sqrt(2));
    }
}

TEST_CASE("Exceptions for setting optimal control guess", "[initial_guess]") {
    auto ocp = std::make_shared<FinalPositionLocalOptima<adouble>>();
    int N = 15;
    DirectCollocationSolver<adouble> dircol(ocp, "trapezoidal", "ipopt", N);

    OptimalControlIterate guess;

    // Check for exceptions with OptimalControlProblem set_*_guess().
    // --------------------------------------------------------------
    // Must set guess.time first.
    REQUIRE_THROWS_WITH(ocp->set_state_guess(guess, "x", RowVectorXd::Zero(1)),
                        Contains("guess.time is empty"));
    REQUIRE_THROWS_WITH(
            ocp->set_control_guess(guess, "x", RowVectorXd::Zero(1)),
            Contains("guess.time is empty"));
    guess.time.setLinSpaced(N, 0, 1);

    // Wrong number of elements.
    REQUIRE_THROWS_WITH(ocp->set_state_guess(guess, "x", RowVectorXd::Zero(1)),
                        Contains("Expected value to have 15"));
    REQUIRE_THROWS_WITH(
            ocp->set_control_guess(guess, "F", RowVectorXd::Zero(1)),
            Contains("Expected value to have 15"));

    // Wrong state name.
    REQUIRE_THROWS_WITH(ocp->set_state_guess(guess, "H", RowVectorXd::Zero(N)),
                        Contains("State H does not exist"));
    REQUIRE_THROWS_WITH(
            ocp->set_control_guess(guess, "H", RowVectorXd::Zero(N)),
            Contains("Control H does not exist"));

    guess.states.resize(10, N - 1);
    guess.controls.resize(9, N - 2);
    // guess.states has the wrong size.
    REQUIRE_THROWS_WITH(ocp->set_state_guess(guess, "x", RowVectorXd::Zero(N)),
                        Contains("Expected guess.states to have "));
    REQUIRE_THROWS_WITH(
            ocp->set_control_guess(guess, "F", RowVectorXd::Zero(N)),
            Contains("Expected guess.controls to have "));

    // Test for more exceptions when calling solve().
    // ----------------------------------------------
    // TODO when we are able to interpolate the guess, the checks should just
    // be that the number of columns is consistent (and that the number of
    // state and control rows is correct).
    guess.time.resize(N - 10);   // incorrect.
    guess.states.resize(2, N);   // correct.
    guess.controls.resize(1, N); // correct.
    REQUIRE_THROWS_WITH(dircol.solve(guess),
                        Contains("Expected time to have 15 elements"));

    guess.time.resize(N);        // correct.
    guess.states.resize(6, N);   // incorrect.
    guess.controls.resize(1, N); // correct.
    REQUIRE_THROWS_WITH(dircol.solve(guess),
                        Contains("Expected states to have dimensions 2 x 15"));

    guess.states.resize(2, N + 1); // incorrect.
    REQUIRE_THROWS_WITH(dircol.solve(guess),
                        Contains("Expected states to have dimensions 2 x 15"));

    guess.states.resize(2, N);   // correct.
    guess.controls.resize(4, N); // incorrect
    REQUIRE_THROWS_WITH(dircol.solve(guess),
            Contains("Expected controls to have dimensions 1 x 15"));

    guess.controls.resize(1, N - 3); // incorrect
    REQUIRE_THROWS_WITH(dircol.solve(guess),
            Contains("Expected controls to have dimensions 1 x 15"));

}





