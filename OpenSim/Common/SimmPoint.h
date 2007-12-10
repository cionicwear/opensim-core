#ifndef __SimmPoint_h__
#define __SimmPoint_h__

// SimmPoint.h
// Author: Peter Loan
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


// INCLUDE
#include <iostream>
#include <string>
#include "osimCommonDLL.h"
#include "Object.h"

namespace OpenSim {

//=============================================================================
//=============================================================================
/**
 * A class implementing a 3D point.
 *
 * @author Peter Loan
 * @version 1.0
 */
class OSIMCOMMON_API SimmPoint : public Object
{

//=============================================================================
// DATA
//=============================================================================
private:
	double _location[3];

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	SimmPoint();
	SimmPoint(double coords[3]);
	SimmPoint(const SimmPoint& aPoint);
	virtual ~SimmPoint();
	virtual Object* copy() const;
#ifndef SWIG
	SimmPoint& operator=(const SimmPoint &aPoint);
	SimmPoint& operator+=(const SimmPoint &aPoint);
	SimmPoint& operator/=(double factor);
#endif
	void set(double x, double y, double z);
	double* get() { return _location; }
	void scale(double aScaleFactor);
	bool isVisible() const;

private:
	void setNull();

//=============================================================================
};	// END of class SimmPoint
//=============================================================================
//=============================================================================

} // end of namespace OpenSim

#endif // __SimmPoint_h__


