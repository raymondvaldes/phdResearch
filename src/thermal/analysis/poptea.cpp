/*----------------------------------------------------------------------------*\
  ========                |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||                   |
-------------------------------------------------------------------------------
License
    This file is part of Thermal Analysis Toolbox.

    Thermal Analysis Toolbox is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    Thermal Analysis Toolbox is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with
    Thermal Analysis Toolbox.  If not, see <http://www.gnu.org/licenses/>.

\*----------------------------------------------------------------------------*/
#include <boost/foreach.hpp>
#include <vector>
#include "thermal/analysis/solution.hpp"
#include "thermal/analysis/poptea.hpp"
#include "thermal/analysis/kernal.hpp"
#include "thermal/emission/phase99.hpp"
#include "thermal/analysis/lmdiff_poptea.hpp"
#include "thermal/analysis/lmdiff_poptea_help.hpp"


#include "math/estimation/parameterestimation.hpp"
#include "math/estimation/lmdiff.hpp"
#include "math/estimation/lmdiff_helper.hpp"
#include "math/estimation/utils.hpp"
#include "math/utility.hpp"
#include "math/estimation/constrained.hpp"
#include "algorithms/ThermalProp_Analysis.h"

namespace thermal {
namespace analysis{  

Poptea::Poptea( const class Kernal &coreSystem_ ,
                const class ThermalData &thermaldata_,
                const class math::estimation::settings &Settings_,
                const class math::estimation::unknownList &unknownParameters_)
  : coreSystem( coreSystem_ ), thermalData( thermaldata_ ),
    LMA( Settings_, unknownParameters_, thermalData.omegas.size(), thermalData ),
    SA( thermalData.omegas.size() )
{}

class Poptea
Poptea::loadConfig( const class Kernal &coreSystem_,
                    const boost::property_tree::ptree &pt )
{
  using boost::property_tree::ptree;
  const std::string conjunto = "poptea.";

  const ptree ptchild1 = pt.get_child( conjunto + "sweep");
  const class ThermalData Obj1(
        ThermalData::loadConfigfromXML( ptchild1 ,
                                        coreSystem_.TBCsystem.coating) );

  const ptree ptchild2 = pt.get_child( conjunto + "ParaEstSettings" );
  const class math::estimation::settings
    Obj2( math::estimation::settings::loadConfigfromXML( ptchild2 ) );

  const ptree ptchild3 = pt.get_child( conjunto );
  const class math::estimation::unknownList
    Obj3( math::estimation::unknownList::loadConfigfromXML( ptchild3 ) );


  //Load class object from previous objects
  class Poptea poptea( coreSystem_, Obj1, Obj2, Obj3 ) ;

  return poptea;
}

void Poptea::updatelthermal( const double lmin, const double lmax,
                             const double lminperDecade)
{
  const size_t Lend =
  thermalData.thermalSetup( lmin, lmax, lminperDecade,
                            coreSystem.TBCsystem.coating ) ;

  LMA.updateWorkSpace( Lend, LMA.unknownParameters.Nsize() );
}

class Poptea Poptea::loadConfigfromFile( const class filesystem::directory &dir )
{
  ///Initiate poptea kernal
  const std::string filename1 = "kernal.xml";
  boost::property_tree::ptree pt;
  try
  {
    boost::property_tree::read_xml( dir.abs( filename1 ), pt );
  }
  catch (std::exception& e)
  {
    std::cout << "file " << dir.abs( filename1 ) << " not found! See --help\n";
    exit(-2);
  }
  const class Kernal popteaCore = Kernal::loadConfig( pt , dir );

  ///bring full poptea object online
  const std::string filename = "poptea.xml";
  boost::property_tree::ptree pt1;
  try
  {
    boost::property_tree::read_xml( dir.abs( filename ), pt1 );
  }
  catch (std::exception& e)
  {
    std::cout << "file " << dir.abs( filename ) << " not found! See --help\n";
    exit(-2);
  }

  ///return this object
  return Poptea::loadConfig( popteaCore, pt1 );
}

Poptea::~Poptea(void){}

void Poptea::loadExperimentalData( const std::vector<double> data )
{}

//void Poptea::setParameterstoFit( class math::estimation::unknownList parameters )
//{
////  unknownParameters = parameters;
//}
//void Poptea::setParametertoHoldX( enum physicalModel::labels::Name currentParameterX_)
//{
////  currentParameterX = currentParameterX_;
////  currentParameter = unknownParameterswithBFdata.getParameter( currentParameterX_ );
//  return;
//}
//double Poptea::Gfunc( const double x )
//{
//  ///Gfunc must work by updating kernal with unknown parameters
//  ///updating experimental with predicted values;

////  unknownParameterswithBFdata.

//  double val = x * 1;


////  TBCsystem::updateVal( currentParameterX , val );


////  current_PHASE_BF


//  return meanError( current_PHASE_BF , ref_PHASE_BF );

//}
//std::pair< double, double >
//Poptea::Gsolve( enum physicalModel::labels::Name currentParameterX_ )
//{
//  double lowerLimit(1);
//  double upperLimit(2);

//  std::pair <double,double> limits (lowerLimit, upperLimit);
//  return limits;
//}
//void Poptea::saveBestFitParameters( void )
//{

//}
//void Poptea::setG1(void)
//{

//}
//double Poptea::meanError( const std::vector<double> curveBF,
//                          const std::vector<double> curveRef )
//{
//  const size_t N = curveBF.size();
//  double error = 0;


//  for(size_t n=0 ; n < N ;  ++n)
//  {
//      error += pow( ( curveBF[n] / curveRef[n] - 1 ), 2);
//  }

//  return sqrt(error / N );
//}
//double Poptea::bestFit( class Kernal core )
//{
//  int nfev;
//  int info = 0;

//  core.LMA.xpredicted = paramter_estimation( core, &info, &nfev );
//  current_PHASE_BF = core.LMA.LMA_workspace.emissionCurrent;
//  S1_current = meanError( current_PHASE_BF , ref_PHASE_BF );

//  return S1_current;
//}
//std::pair< double, double >
//Poptea::parameterInterval(const enum physicalModel::labels::Name currentPx ,
//                          std::vector<double> emissionExperimental)
//{
//  //Step 1
//  loadExperimentalData( emissionExperimental );

//  //Step 2
//  bestFit( coreSystem );

//  //Step 3 Rebuild Core
//  //rebuild unknown list;

////  class kernal coreRebuild( coreSystem.expSetup ,
////                            coreSystem.TBCsystem,
////                            coreSystem.thermalsys,
////                            coreSystem.LMA.Settings,
////                            rebuiltSubSystem,
////                            coreSystem.DataDirectory
////                            )

////      Kernal( class equipment::setup expSetup_,
////              class physicalModel::TBCsystem TBCsystem_,
////              class thermal::model thermalsys_,
////              class math::estimation::settings Settings_,
////              class math::estimation::unknownList unknownParameters_,
////              class filesystem::directory DataDirectory_ ) ;


//  double lowerLimit(1);
//  double upperLimit(2);
//  std::pair <double,double> limits (lowerLimit, upperLimit);
//  return limits;
//}



}}
