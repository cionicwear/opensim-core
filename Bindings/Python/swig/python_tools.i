%module(directors="1") tools
#pragma SWIG nowarn=822,451,503,516,325
// 401 is "Nothing known about base class *some-class*.
//         Maybe you forgot to instantiate *some-template* using %template."
// When wrapping new classes it's good to uncomment the line below to make sure
// you've wrapped your new class properly. However, SWIG generates lots of 401
// errors that are very difficult to resolve.
#pragma SWIG nowarn=401

%{
#define SWIG_FILE_WITH_INIT
#include <Bindings/OpenSimHeaders.h>
#include <Bindings/OpenSimToolsHeaders.h>
%}

%{
using namespace OpenSim;
using namespace SimTK;
%}


%include "python_preliminaries.i"

// Tell SWIG about the opensim module.
%import "python_opensim.i"

// Relay exceptions to the target language.
// This causes substantial code bloat and possibly hurts performance.
// Without these try-catch block, a SimTK or OpenSim exception causes the
// program to crash.
%include "exception.i"
// Delete any previous exception handlers.
%exception; 
%exception {
    try {
        $action
    } catch (const std::exception& e) {
        std::string str("std::exception in '$fulldecl': ");
        std::string what(e.what());
        SWIG_exception_fail(SWIG_RuntimeError, (str + what).c_str());
    }
}

// Typemaps
// ========
// None.


// Include all the OpenSim code.
// =============================
%include <Bindings/preliminaries.i>
%include <Bindings/tools.i>


// Memory management
// =================
SET_ADOPT_HELPER(IKTask);
SET_ADOPT_HELPER(Measurement);
SET_ADOPT_HELPER(MarkerPair);
