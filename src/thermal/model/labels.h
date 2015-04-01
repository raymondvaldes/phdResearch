/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef __tat__labels__thermal_model
#define __tat__labels__thermal_model

#include <iostream>
#include <cstddef>
#include <string>

#include "tools/bimap/bimap.h"


namespace thermal{
  namespace model{

class labels
{
private:

public:
  static size_t numberOfLabels(void) noexcept { return 10; };

  enum class Name
  {
    gammaEff,           //1
    asub,               //2
    E1,                 //3
    R1,                 //4
    lambda,             //5
    length,             //6
    acoat,              //7
    gammaSub,           //8
    omega,              //9
    experimentalData,   //10
    
    thermalCenter,
    thermalRange,
  };

  static std::vector< enum Name > getEnumList( void ) noexcept {
    std::vector< enum Name > output( numberOfLabels() ) ;
    output[0] = Name::gammaEff;
    output[1] = Name::asub;
    output[2] = Name::E1;
    output[3] = Name::R1;
    output[4] = Name::lambda;
    output[5] = Name::length;
    output[6] = Name::acoat;
    output[7] = Name::gammaSub;
    output[8] = Name::omega;
    output[9] = Name::experimentalData;
    
    return output;
  };

  
  
  typedef boost::bimap< enum Name , std::string > NameBiTYPE;
  const NameBiTYPE nameMap =
  boost::assign::list_of < NameBiTYPE::relation >
  ( Name::gammaEff , "gammaEff")
  ( Name::asub     , "asub")
  ( Name::E1       , "E1")
  ( Name::R1       , "R1")
  ( Name::lambda   , "lambda" )
  
  ( Name::length   , "length" )
  ( Name::thermalCenter, "thermalCenter")
  ( Name::thermalRange, "thermalRange")
  ( Name::experimentalData, "experimentalData")
  ( Name::omega, "omega" )
  ( Name::acoat, "acoat" )
  ( Name::gammaSub, "gammaSub") ;
  
  explicit labels(void) noexcept;
  explicit labels(const enum Name name_) noexcept;
  Name getName(void) const noexcept;
  std::string getNameString(void) const noexcept;
  
  
  labels& operator=( const labels& that ) noexcept;
  
private:
  enum Name name;
};

  }
}
#endif /* defined(__tat__labels__thermal_model) */
