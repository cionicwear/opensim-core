#ifndef _XMLParsingException_h_
#define _XMLParsingException_h_
// XMLParsingException.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
* Copyright (c) 2007, Stanford University. All rights reserved. 
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


// INCLUDES
#include "Exception.h"

// Only the necessary Xerces includes/defines
#include <xercesc/util/XercesDefs.hpp>
XERCES_CPP_NAMESPACE_BEGIN
class DOMNode;
XERCES_CPP_NAMESPACE_END
XERCES_CPP_NAMESPACE_USE


//=============================================================================
//=============================================================================
/**
 * A class for XML parsing exceptions (derives from Exception).
 *
 * @version 1.0
 * @author Eran Guendelman
 */
#ifdef SWIG
	#ifdef OSIMCOMMON_API
		#undef OSIMCOMMON_API
		#define OSIMCOMMON_API
	#endif
#endif

namespace OpenSim { 

class OSIMCOMMON_API XMLParsingException : public Exception {

//=============================================================================
// DATA
//=============================================================================
protected:
	/** Textual description of where in the XML file the error occured. */
	std::string _xmlContextString;

//=============================================================================
// METHODS
//=============================================================================
public:
	// CONSTRUCTORS
	XMLParsingException(const std::string &aMsg="",const DOMNode *aNode=0,const std::string &aFile="",int aLine=-1);

public:
	// PRINT
	void print(std::ostream &aOut);

//=============================================================================
};	// END CLASS XMLParsingException

}; //namespace
//=============================================================================
//=============================================================================

#endif // __XMLParsingException_h__
