
/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#include "sensible/TBCsystem.h"

namespace sensible{
  
  
TBCsystem::TBCsystem( const layer &coating_,
                      const layer &substrate_,
                      const temperatureScale &Temp_,
                      const radiativeSysProp &optical_,
                      const double radius_ ) noexcept
: coating(coating_), truecoating( coating_ ), substrate(substrate_),
  Temp(Temp_), optical(optical_), radius(radius_)
{
  gamma = gammaEval();
  a_sub = a_subEval();
}
  
TBCsystem::~TBCsystem(void) noexcept{}

TBCsystem TBCsystem::loadConfig(const boost::property_tree::ptree &pt) noexcept
{
  using boost::property_tree::ptree;
  
  const ptree pcoat = pt.get_child( "coating" );
  const layer coating_( layer::loadConfigfromXMLTree( pcoat ) );
  
  const ptree psub = pt.get_child( "substrate" );
  const layer substrate_( layer::loadConfigfromXMLTree( psub ) );
  
  const ptree ptmp = pt.get_child( "TemperatureScale" );
  const temperatureScale Temp_( temperatureScale::loadConfigfromXML( ptmp ) );
  
  const ptree prad = pt.get_child( "RadiationProperties" );
  const radiativeSysProp optical_( radiativeSysProp::loadConfig( prad ) );
  
  const double radius_ = pt.get< double >( "radialDomain" );
  
  const TBCsystem TBCsystemObj( coating_, substrate_, Temp_, optical_,
                                     radius_ );
  return  TBCsystemObj;
}

void TBCsystem::updateVal( const enum labels::Name mylabel , const double val ) noexcept
{
  switch( mylabel )
  {
    case labels::Name::asub :
      a_sub = val;
      break;
    case labels::Name::E1 :
      optical.Emit1 = val;
      break;
    case labels::Name::gammaEff :
      gamma = val;
      break;
    case labels::Name::R1 :
      optical.R1 = val;
      break;
    case labels::Name::lambda :
      coating.setLambda( val ) ;
      break;
    case labels::Name::length :
      coating.setDepth( val ) ;
      break;
//    case labels::Name::thermalCenter:
//      std::cout << "not yet implemented, error!!"; exit(-68);
//      break;
//    case labels::Name::thermalRange:
//      std::cout << "not yet implemented, error!!"; exit(-68);
//      break;      
    default:
      std::cout << "\nSwitch Error!!\n";
      exit(-68);
      break;
  }
}




double TBCsystem::returnVal( const enum labels::Name mylabel ) const noexcept
{
  double val( 0 ) ;
  
  switch ( mylabel )
  {
    case labels::Name::asub :
      val = a_sub ;
      break;
    case labels::Name::E1 :
      val = optical.Emit1 ;
      break;
    case labels::Name::gammaEff :
      val = gamma;
      break;
    case labels::Name::R1 :
      val = optical.R1;
      break;
    case labels::Name::lambda :
      val = coating.getLambda();
      break;
    case labels::Name::thermalCenter:
      std::cout << "not yet implemented, error!!"; exit(-68);
      break;
    case labels::Name::thermalRange:
      std::cout << "not yet implemented, error!!"; exit(-68);
      break;
    default:
      std::cout << "\nSwitch Error!!\n";
      exit(-69);
      break;
  }
  return val;
}

double TBCsystem::gammaEval(void) const noexcept
{
  return substrate.thermalEffusivity() / coating.thermalEffusivity();
}

double TBCsystem::a_subEval(void) const noexcept
{
  using std::sqrt;
  return sqrt(substrate.thermalDiffusivity() / coating.thermalDiffusivity());
}

void TBCsystem::updateCoat(void) noexcept
{
  using std::pow;
  using std::sqrt;

  const double effusivity_coat = substrate.thermalEffusivity() / gamma;
  const double diffusivty_coat = substrate.thermalDiffusivity() / pow(a_sub,2);
  
  coating.psithermal.offset = effusivity_coat / sqrt(diffusivty_coat);
  coating.kthermal.offset = coating.psithermal.offset * diffusivty_coat;
  
  
  return;
}
  
  
}
