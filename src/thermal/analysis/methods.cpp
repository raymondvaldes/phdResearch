/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#include <vector>
#include <string>
#include <functional>
#include <boost/property_tree/ptree.hpp>

#include "thermal/analysis/kernal.hpp"
#include "thermal/analysis/methods.hpp"
#include "thermal/analysis/pie.hpp"
#include "math/estimation/parameterestimation.hpp"
#include "math/algorithms/combinations.hpp"
#include "math/utility.hpp"

namespace thermal{
namespace analysis{

methods::methods(
    const math::estimation::settings &Settings_in,
    const math::estimation::unknownList &unknownParameters_in,
    const ThermalData& thermalData_in ,
    const math::estimation::unknownList &thermalSweepSearch ,
    const std::vector<thermal::model::labels> &sweepOptimizationGoal,
    const sensible::layer coating,
    const size_t iter, const double lmin, const double lmax ) noexcept
  : bestfitMethod( new LMA( Settings_in, unknownParameters_in,
                            thermalData_in.size() ) ),
    intervalEstimates( new PIE() ),
    lthermalSweepOptimizer(
      new ThermalSweepOptimizer( Settings_in,
                                 thermalData_in,
                                 unknownParameters_in,
                                 bestfitMethod,
                                 intervalEstimates ,
                                 thermalSweepSearch,
                                 sweepOptimizationGoal,
                                 coating, iter, lmin, lmax ) ),
    taylor_uncertainty( new Taylor_uncertainty() )
{
}

methods& methods::operator=( const methods& that ) noexcept
{
  if(this != &that)
  {
     bestfitMethod = that.bestfitMethod;
     intervalEstimates = that.intervalEstimates;
     lthermalSweepOptimizer = that.lthermalSweepOptimizer;
  }
  return *this;
}

double methods::bestFit(
    const std::shared_ptr< math::estimation::unknownList > &list_in,
    const std::shared_ptr< ThermalData > &thermalData_in,
    const std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in ) noexcept
{
  bestfitMethod->solve( list_in, thermalData_in, coreSystem_in );
  return thermalData_in->MSE;
}

PIE::PIEAnalysisOutput
methods::parameterIntervalEstimates(
    const std::shared_ptr< math::estimation::unknownList > &list_in,
    const std::shared_ptr< ThermalData > &thermalData_in,
    const std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in ) noexcept
{
  return intervalEstimates->solve( list_in, thermalData_in, coreSystem_in,
                            bestfitMethod );
}

ThermalSweepOptimizer::OptimizerOutput methods::optimization(
    const std::shared_ptr< math::estimation::unknownList > &list_in,
    const std::shared_ptr< ThermalData > &thermalData_in,
    const std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in ) noexcept
{
  return lthermalSweepOptimizer->solve( list_in, thermalData_in, coreSystem_in,
                                        bestfitMethod, intervalEstimates ) ;

}

std::string methods::contourMapping() noexcept
{
  return lthermalSweepOptimizer->contourMappingwithOrderedPointUsingGrid() ;
}

void methods::GUM_uncertainty(
    const std::shared_ptr< math::estimation::unknownList > &list_in,
    const std::shared_ptr< ThermalData > &thermalData_in,
    const std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in ) noexcept{
  
  taylor_uncertainty->solve( list_in, thermalData_in, coreSystem_in );
  
  return;
}



methods
loadMethodsfromFile( const boost::property_tree::ptree &mybranch,
                     const math::estimation::unknownList &parameterEstimation,
                     const ThermalData &thermData,
                     const sensible::layer &coating ) noexcept
{
  using math::estimation::unknownList;
  using math::estimation::settings;
  using boost::property_tree::ptree;

  const ptree ptchild2 = mybranch.get_child( "ParaEstSettings" ) ;
  const settings estSettings( settings::loadConfigfromXML( ptchild2 ) ) ;


  const unknownList thermalSweep( unknownList::loadConfigfromXML( mybranch ) ) ;

  std::vector< thermal::model::labels > sweepOptimizationGoal ;
  for( const ptree::value_type &v : mybranch.get_child( "parameters" ) )
  {
    //retrieve subtree
    const ptree& child = v.second ;

    //access members of subtree
    thermal::model::labels labelmaker ;
    const std::string nameLabel = child.get< std::string >( "label" ) ;
    enum thermal::model::labels::Name mylabel ;
    try
    {
      mylabel = labelmaker.nameMap.right.at( nameLabel ) ;
    }
    catch( std::exception& e )
    {
      std::cerr << "Error with mylabel in poptea.xml labelmaker\n";
      exit( 1 ) ;
    }
    const thermal::model::labels output( mylabel ) ;
    sweepOptimizationGoal.push_back( output ) ;
  }

  const ptree ptchild3 = mybranch.get_child( "mapping" ) ;
  const size_t iter_m = ptchild3.get< size_t >( "Iterations" ) ;
  const double lthermal_min = ptchild3.get< double >( "lthermal_min" ) ;
  const double lthermal_max = ptchild3.get< double >( "lthermal_max" ) ;


  const methods analysis( estSettings, parameterEstimation, thermData,
                          thermalSweep, sweepOptimizationGoal,
                          coating, iter_m, lthermal_min, lthermal_max   ) ;
  return analysis;
}

}}
