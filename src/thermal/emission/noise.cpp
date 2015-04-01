/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#include <cmath>
#include "thermal/emission/noise.hpp"
#include "math/utility.hpp"
#include "math/random/random.h"
#include "tools/interface/xml.h"

namespace thermal{
  namespace emission{


ExpNoiseSetting::ExpNoiseSetting( const double a1_, const double b1_,
                                  const bool d1_, const bool d2_,
                                  const int s1_, const double noiseRandom_) noexcept
  : a(a1_), b(b1_), noiseRandom(noiseRandom_), d1(d1_), d2(d2_), s1(s1_)
{}

std::vector<double>
addNoise( const std::vector<double> &emissionNominal_,
          const std::vector<double> &lthermal,
          const thermal::emission::ExpNoiseSetting &para ) noexcept

{
  const double lmin = lthermal.front();
  const double lmax = lthermal.back();
  const double a = para.a;
  const double b = para.b;
  const bool d1 = para.d1;
  const bool d2 = para.d2;
  const int s1 = para.s1;
  const double noiseRandom = para.noiseRandom;

  using std::tan;
  using std::abs;

  if( (a < 0) || (b < 1) || (b > M_PI) )
  {
    using std::cerr;
    cerr << "parameters (a,b) out of range";
    exit(-99);
  }
  
  using std::vector;
  vector<double> output( emissionNominal_ ) ;
  for( size_t i=0 ; i < lthermal.size() ; ++i )
  {
    constexpr double c = 0.5;
    using math::percentilelog10;
    const double
        lthermalPercentile = percentilelog10( lmin, lmax, lthermal[i] );

    ///Determine biased noise
    const double cotbc = tan( M_PI_2 - ( b * c ) );
    double noiseBias = -a * cotbc * tan( b * ( c - lthermalPercentile ) );

    if( !d2 ) { noiseBias = abs( noiseBias ) ; }
    if( !d1 ) { noiseBias *= -1 ; }

    switch(s1)
    {
      case -1:
          if( lthermalPercentile > 0.5 ) { noiseBias = 0 ; }
          break;
      case 0:
          break;
      case 1:
          if( lthermalPercentile < 0.5 ) { noiseBias = 0 ; }
          break;
      default:
          std::cout << "\n\nerror in symmetry options\n\n"; exit(-1);
    }

    ///Determine random noise
    using math::x_normal;
    const double noiseRandomGen = x_normal( 0, noiseRandom ) ;

    output[i] += M_PI_2 * noiseBias ;
    output[i] += M_PI_2 * noiseRandomGen ;
  }
  return output;
}


ExpNoiseSetting
ExpNoiseSetting::initializeObj(const boost::property_tree::ptree &pt ) noexcept
{
  //initialize parameter estimation settings
  const double a1_     = pt.get<double>( "bias-noise" );
  const double b1_     = pt.get<double>( "stretching-parameter" );
  const bool d1_     = pt.get<int>( "positive" );
  const bool d2_   = pt.get<int>( "monotonic" );
  const int s1_   = pt.get<int>( "bias-side" );
  const double noiseRandom_   = pt.get<double>( "random-noise" );

  const ExpNoiseSetting output( a1_, b1_, d1_, d2_, s1_, noiseRandom_ ) ;

  return output;
}

ExpNoiseSetting
ExpNoiseSetting::loadExpNoiseFile( const class filesystem::directory &dir ) noexcept
{
  using std::string;
  const string filename = "EmissionNoise.xml";
  const string absPath = dir.abs( filename );

  using boost::property_tree::ptree;
  ptree pt = tools::interface::getTreefromFile( absPath ) ;

  //pass child to settings object
  const string conjunto = "simulated-emission." ;
  const ptree ptchild1 = pt.get_child( conjunto + "settings");


  return initializeObj( ptchild1 ) ;
}
}}
