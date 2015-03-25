//
//  conductivity_from_phases.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/10/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//
#include <iostream>
#include <iterator>
#include <cassert>

#include "thermal/analysis/bulkSpeciman/temperature/conductivity_from_phases.h"
#include "thermal/define/lthermal.h"
#include "math/estimation/lmdiff.hpp"
#include "math/estimation/settings.h"
#include "algorithm/algorithm.h"
#include "physics/classical_mechanics/kinematics.h"
#include "plot/gnuplot.h"
#include "investigations/twoColorPyrometery/plot/phase_exp_model.h"
#include "units.h"

namespace thermal {

namespace analysis {

namespace bulkSpeciman {

namespace temperature {

fitting_result::fitting_result
(
  std::vector< units::quantity<units::si::frequency> > const  frequencies_,

  thermal::model::slab::Slab const initial_slab_,
  thermal::model::slab::Slab const fitted_slab_,
 
  std::vector< units::quantity< units::si::plane_angle > > const experimenta_phases_,
  std::vector< units::quantity< units::si::plane_angle > > const bestFit_phases_
)
: frequencies( frequencies_ ),
  initial_slab( initial_slab_ ),
  fitted_slab( fitted_slab_ ),
  experimenta_phases( experimenta_phases_ ),
  bestFit_phases( bestFit_phases_ )
{
  assert( frequencies.size() > 0 );
  assert( experimenta_phases.size() > 0 );
  assert( bestFit_phases.size() > 0 );
}

inline auto updateRear( const double * x )
noexcept -> std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> >
{
  using namespace units;
  auto const temperature = quantity<dimensionless>( x[1] );
  auto const phase = quantity<plane_angle>::from_value( x[2] ) ;
  return std::make_pair( temperature, phase );
}

inline auto updateSlab
(
  const double* x ,
  thermal::model::slab::Slab const & mySlab
) noexcept -> thermal::model::slab::Slab
{
  using units::quantity;
  using units::si::length;
  using units::si::thermal_diffusivity;
  using thermal::model::slab::Slab;

  auto const fittedDiffusivity =
  quantity< thermal_diffusivity >::from_value( x[0] ) ;
  
  auto const fitted_length = mySlab.characteristic_length ;

  auto const fittedSpeciman =
  Slab( fitted_length , fittedDiffusivity , mySlab.rhoCp ) ;
  
  return fittedSpeciman ;
}

auto
diffusivity_from_phases
(
  std::vector< units::quantity< units::si::angular_frequency > > const & omegas,
  std::vector< units::quantity< units::si::plane_angle > > const & observations,
  thermal::model::slab::Slab const & slab_initial,
  enum thermal::model::slab::back_boundary_condition const BC )
-> fitting_result
{
  using std::vector;
  using std::generate;
  using math::estimation::settings;
  using thermal::model::slab::surface_temperature_phases;
  using namespace units;
  
  using physics::classical_mechanics::frequencies_from_angularFrequencies;
  auto const frequencies = frequencies_from_angularFrequencies(omegas);
  assert( frequencies.size() > 0 );
  
  auto const numberPoints2Fit = omegas.size();

  auto const minimizationEquation =
  [ &omegas, &observations, &slab_initial, &numberPoints2Fit, &BC, &frequencies]
  ( const double *x, double *fvec ) noexcept
  {
    auto const slabCurrent = updateSlab( x, slab_initial );
    
    auto rear_bc = std::pair< quantity<dimensionless>, quantity<plane_angle> >();
    if( BC == thermal::model::slab::back_boundary_condition::T_unknown ) {
      rear_bc = updateRear( x );
    std::cout << rear_bc.first << "\t" << rear_bc.second << "\n" ;
    }
    auto const predictions = surface_temperature_phases( omegas, slabCurrent, BC, rear_bc ) ;
    
    //std::cout << slabCurrent.get_diffusivity() << "\n";
    //investigations::twoColorPyrometery::plot::phase_exp_model( frequencies, observations, predictions );
    
    auto const residual = [ & ]( const int i ) noexcept
    {
      return ( predictions[i]  -  observations[i] ).value() ;
    } ;

    auto i = 0;
    generate( fvec, fvec + numberPoints2Fit , [&]() noexcept
    {
      return residual(i++);
    } ) ;
  };

  auto const myDiffusivity = slab_initial.get_diffusivity();
  //auto const myL = slab_initial.characteristic_length;
  auto unknownParameters = vector<double>{ myDiffusivity.value() } ;
  
  if( BC == thermal::model::slab::back_boundary_condition::T_unknown )
  {
    unknownParameters.push_back(1);
    unknownParameters.push_back(0);
  }
  
  lmdif( minimizationEquation, numberPoints2Fit, unknownParameters, settings{});

  auto const model_slab = updateSlab( unknownParameters.data(), slab_initial );
  auto const model_observations = surface_temperature_phases( omegas, model_slab, BC ) ;


  auto const results =  fitting_result
  (
    frequencies,
    slab_initial, model_slab,
    observations ,model_observations
  );

  return results;
}

auto
diffusivity_from_phases
(
  std::pair<
    std::vector< units::quantity< units::si::angular_frequency > >,
    std::vector< units::quantity< units::si::plane_angle > >
  > const & observations,
  thermal::model::slab::Slab const & slab_initial,
  enum thermal::model::slab::back_boundary_condition const BC
 
)
-> fitting_result
{
  auto const results = diffusivity_from_phases(
  observations.first, observations.second, slab_initial, BC ) ;

  return results ;
}

} // namespace temperature

} // namespace bulkSpeciman
  
} // namespace analysis

} // namespace thermal
