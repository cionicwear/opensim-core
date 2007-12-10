// SdfastSpeed.cpp
// Author: Peter Loan, Frank C. Anderson
/*
 * Copyright (c)  2006, Stanford University. All rights reserved. 
* Use of the OpenSim software in source form is permitted provided that the following
* conditions are met:
* 	1. The software is used only for non-commercial research and education. It may not
*     be used in relation to any commercial activity.
* 	2. The software is not distributed or redistributed.  Software distribution is allowed 
*     only through https://simtk.org/home/opensim.
* 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
*      presentations, or documents describing work in which OpenSim or derivatives are used.
* 	4. Credits to developers may not be removed from executables
*     created from modifications of the source.
* 	5. Modifications of source code must retain the above copyright notice, this list of
*     conditions and the following disclaimer. 
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
*  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
*  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
*  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
*  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
*  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
*  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//=============================================================================
// INCLUDES
//=============================================================================
#include "SdfastSpeed.h"
#include "SdfastEngine.h"
#include <OpenSim/Simulation/Model/Model.h>
#include <OpenSim/Simulation/Model/CoordinateSet.h>
#include <OpenSim/Common/SimmMacros.h>

//=============================================================================
// STATICS
//=============================================================================
using namespace std;
using namespace OpenSim;

//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor.
 */
SdfastSpeed::SdfastSpeed() :
   _defaultValue(_defaultValueProp.getValueDbl()),
	_index(_indexProp.getValueInt()),
	_coordinateName(_coordinateNameProp.getValueStr())
{
	setNull();
	setupProperties();
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
SdfastSpeed::~SdfastSpeed()
{
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aSpeed SdfastSpeed to be copied.
 */
SdfastSpeed::SdfastSpeed(const SdfastSpeed &aSpeed) :
   AbstractSpeed(aSpeed),
   _defaultValue(_defaultValueProp.getValueDbl()),
	_index(_indexProp.getValueInt()),
	_coordinateName(_coordinateNameProp.getValueStr())
{
	setNull();
	setupProperties();
	copyData(aSpeed);
}

//_____________________________________________________________________________
/**
 * Copy constructor from an AbstractSpeed.
 *
 * @param aSpeed SdfastSpeed to be copied.
 */
SdfastSpeed::SdfastSpeed(const AbstractSpeed &aSpeed) :
   AbstractSpeed(aSpeed),
   _defaultValue(_defaultValueProp.getValueDbl()),
	_index(_indexProp.getValueInt()),
	_coordinateName(_coordinateNameProp.getValueStr())
{
	setNull();
	setupProperties();
	copyData(aSpeed);
}

//_____________________________________________________________________________
/**
 * Copy this speed and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this SdfastSpeed.
 */
Object* SdfastSpeed::copy() const
{
	SdfastSpeed *gc = new SdfastSpeed(*this);
	return(gc);
}

//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Copy data members from one SdfastSpeed to another.
 *
 * @param aSpeed SdfastSpeed to be copied.
 */
void SdfastSpeed::copyData(const SdfastSpeed &aSpeed)
{
	_defaultValue = aSpeed.getDefaultValue();
	_index = aSpeed._index;
	_coordinateName = aSpeed._coordinateName;
	_SdfastEngine = aSpeed._SdfastEngine;
}

//_____________________________________________________________________________
/**
 * Copy data members from an AbstractSpeed to an SdfastSpeed.
 *
 * @param aSpeed AbstractSpeed to be copied.
 */
void SdfastSpeed::copyData(const AbstractSpeed &aSpeed)
{
	_defaultValue = aSpeed.getDefaultValue();
	_coordinate = aSpeed.getCoordinate(); // TODO: should we be copying pointers?
	if (_coordinate)
		_coordinateName = _coordinate->getName();
	else
		_coordinateName = "Unassigned";
}

//_____________________________________________________________________________
/**
 * Set the data members of this SdfastSpeed to their null values.
 */
void SdfastSpeed::setNull(void)
{
	setType("SdfastSpeed");

	_coordinate = NULL;
	_SdfastEngine = NULL;
}

//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void SdfastSpeed::setupProperties(void)
{
	_defaultValueProp.setName("default_value");
	_defaultValueProp.setValue(0.0);
	_propertySet.append(&_defaultValueProp);

	_indexProp.setName("index");
	_propertySet.append(&_indexProp);

	_coordinateNameProp.setName("coordinate");
	_propertySet.append(&_coordinateNameProp);
}

//_____________________________________________________________________________
/**
 * Perform some set up functions that happen after the
 * object has been deserialized or copied.
 *
 * @param aEngine dynamics engine containing this SdfastSpeed.
 */
void SdfastSpeed::setup(AbstractDynamicsEngine* aEngine)
{
	// Base class;
	AbstractSpeed::setup(aEngine);

	_SdfastEngine = dynamic_cast<SdfastEngine*>(aEngine);

	_coordinate = _SdfastEngine->getCoordinateSet()->get(_coordinateName);

	// If the user specified a default value, set the
	// current value to the default value.
	if (!_defaultValueProp.getUseDefault())
		setValue(_defaultValue);
}

//=============================================================================
// OPERATORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Assignment operator.
 *
 * @return Reference to this object.
 */
SdfastSpeed& SdfastSpeed::operator=(const SdfastSpeed &aSpeed)
{
	// BASE CLASS
	AbstractSpeed::operator=(aSpeed);

	copyData(aSpeed);

	return(*this);
}


//=============================================================================
// COORDINATE
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the coordinate that this speed corresponds to.
 *
 * @param Pointer to the coordinate.
 * @return Whether or not the coordinate was set.
 */
bool SdfastSpeed::setCoordinate(AbstractCoordinate *aCoordinate)
{
	_coordinate = aCoordinate;
	return true;
}
//_____________________________________________________________________________
/**
 * Set the name of the coordinate that this speed corresponds to. When creating
 * a new SdfastSpeed object, this method should be used rather than setCoordinate,
 * because setup() will use _coordinateName to set _coordinate (which needs
 * to be done when deserializing SdfastSpeed objects).
 *
 * @param Name of the coordinate.
 * @return Whether or not the coordinate was set.
 */
bool SdfastSpeed::setCoordinateName(const string& aCoordName)
{
	_coordinateName = aCoordName;
	return true;
}


//=============================================================================
// DEFAULT VALUE
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the default value.
 *
 * @param aDefaultValue default value to change to.
 * @return Whether or not the default value was changed.
 */
bool SdfastSpeed::setDefaultValue(double aDefaultValue)
{
	_defaultValue = aDefaultValue;

	return true;
}


//=============================================================================
// VALUE
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the value.
 *
 * @param aValue value to change to.
 * @return Whether or not the value was changed.
 */
bool SdfastSpeed::setValue(double aValue)
{
	double *y = _SdfastEngine->getConfiguration();
	if(y) {
		y[_SdfastEngine->getNumCoordinates() + _index] = aValue;
		_SdfastEngine->setConfiguration(y);
	}
	return true;
}

//_____________________________________________________________________________
/**
 * Get the value.
 *
 * @return The current value of the speed.
 */
double SdfastSpeed::getValue() const
{
	double* y = _SdfastEngine->getConfiguration();
	return y[_SdfastEngine->getNumCoordinates() + _index];
}


//=============================================================================
// ACCELERATION
//=============================================================================
//_____________________________________________________________________________
/**
 * Get the acceleration of this speed.  Note that the accelerations must
 * have been computed by the dynamics engine by calling computeDerivatives()
 * for this method to return a valid result.
 *
 * @return The current value of the acceleration.
 */
double SdfastSpeed::getAcceleration() const
{
	double* dy = _SdfastEngine->getDerivatives();
	return dy[_SdfastEngine->getNumCoordinates() + _index];
}
