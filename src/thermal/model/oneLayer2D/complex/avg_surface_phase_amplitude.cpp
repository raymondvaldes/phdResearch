//
//  avg_surface_phase_amplitude.cpp
//  tat
//
//  Created by Raymond Valdes on 4/29/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/complex/avg_surface_phase_amplitude.h"
#include "thermal/model/oneLayer2D/complex/surface_phase_amplitude.h"
#include "math/calculus/mean_value/circle/circle_complex.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace complex{

using math::calculus::mean_value::circle_complex;
using math::complex::properties;

auto avg_surface_phase_amplitude
(
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::dimensionless > const l,
  units::quantity< units::si::temperature > const deltaT,
  units::quantity< units::si::dimensionless> const view_radius
) noexcept -> math::complex::properties< units::si::temperature >
{
  using std::make_pair;
  using namespace units;
  
  auto const f_r =
  [ &b, &l, &deltaT ]
  ( double const r ) noexcept -> std::pair< double, double >
  {
    auto const r_dim = quantity<si::dimensionless>( r );
    auto const p = surface_phase_amplitude( r_dim, b, l, deltaT );
    return make_pair( p.phase.value(), p.amplitude.value() ) ;
  };

  auto const view_radius_d = double( view_radius.value() );
  auto const dr = double( 0.001 );
  auto const mean = circle_complex( f_r, view_radius_d, dr );
  
  auto const mean_phase = quantity< plane_angle >::from_value( mean.first );
  auto const mean_amplitude = quantity< si::temperature >::from_value( mean.second );
  return properties< si::temperature >( mean_phase, mean_amplitude );
}

} // namespace complex
} // namespace oneLayer2D
} // namespace model
} // namespace thermal