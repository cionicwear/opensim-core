#ifndef _StateVector_h_
#define _StateVector_h_
// StateVector.h: interface for the StateVector class.
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
* Copyright (c) 2005, Stanford University. All rights reserved. 
* Redistribution and use in source and binary forms, with or without 
* modification, are permitted provided that the following conditions
* are met: 
*  - Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer. 
*  - Redistributions in binary form must reproduce the above copyright 
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the distribution. 
*  - Neither the name of the Stanford University nor the names of its 
*    contributors may be used to endorse or promote products derived 
*    from this software without specific prior written permission. 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
* POSSIBILITY OF SUCH DAMAGE. 
*/

/* Note: This code was originally developed by Realistic Dynamics Inc. 
 * Author: Frank C. Anderson 
 */


#include "osimCommon.h"
#include "Array.h"


//template class OSIMCOMMON_API Array<double>;


//=============================================================================
//=============================================================================
/**
 * A class which stores a vector of states or data at a specified time.
 * Generally, it is used to store the time histories of the states during
 * an integration.
 *
 * The format of the numerical output for this class is specified by the
 * settings in IO.
 *
 * @author Frank C. Anderson
 * @version 1.0
 * @see IO
 */
namespace OpenSim { 

class OSIMCOMMON_API StateVector
{
//=============================================================================


//=============================================================================
// DATA
//=============================================================================
private:
	/** Time stamp of the statevector. */
	double _t;
	/** Array of states. */
	Array<double> _data;

//=============================================================================
// METHODS
//=============================================================================
public:
	StateVector(double aT=0.0,int aN=0,const double *aData=NULL);
	StateVector(const StateVector &aVector);
	virtual ~StateVector();

	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
private:
	void setNull();

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
#ifndef SWIG
	StateVector& operator=(const StateVector &aStateVector);
	bool operator==(const StateVector &aStateVector) const;
	bool operator<(const StateVector &aStateVector) const;
	friend std::ostream& operator<<(std::ostream &aOut,
									const StateVector &aStateVector) {
		aOut<<"StateVector: t="<<aStateVector._t<<", "<<aStateVector._data;
		return(aOut);
	};
#endif
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	void setStates(double aT,int aN,const double aY[]);
	int getSize() const;
	void setTime(double aT);
	double  getTime() const;
	int getDataValue(int aIndex,double &rValue);
	void setDataValue(int aIndex,double &aValue);
	Array<double>& getData();
#ifndef SWIG
	const Array<double>& getData() const;
#endif
	//--------------------------------------------------------------------------
	// OPERATIONS
	//--------------------------------------------------------------------------
	void shiftTime(double aValue);
	void scaleTime(double aValue);
	void add(double aValue);
	void add(int aN,double aY[]);
	void add(int aN,double aValue);
	void add(StateVector *aStateVector);
	void subtract(double aValue);
	void subtract(int aN,double aY[]);
	void subtract(StateVector *aStateVector);
	void multiply(double aValue);
	void multiply(int aN,double aY[]);
	void multiply(StateVector *aStateVector);
	void divide(double aValue);
	void divide(int aN,double aY[]);
	void divide(StateVector *aStateVector);

	//--------------------------------------------------------------------------
	// IO
	//--------------------------------------------------------------------------
	void print() const;
	int print(FILE *fp) const;


//=============================================================================
};	// END of class StateVector

}; //namespace
//=============================================================================
//=============================================================================

#endif //__StateVector_h__
