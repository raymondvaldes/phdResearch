//
//  frequency_sweep.cpp
//  tat
//
//  Created by Raymond Valdes on 6/3/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/infinite_disk/thermal_emission/offset_point/frequency_sweep.h"
#include <cassert>
#include "algorithm/algorithm.h"
#include "thermal/model/oneLayer2D/infinite_disk/dimensionless/thermal_penetration.h"
#include "thermal/model/oneLayer2D/infinite_disk/thermal_emission/point_measurement.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace thermal_emission {
namespace offset_point{

using namespace units;
using std::vector;
using math::complex::properties;
using algorithm::transform;

auto
frequency_sweep
(
  units::quantity< units::si::dimensionless > const b ,
  units::quantity< units::si::temperature > const deltaT ,
  units::quantity< units::si::dimensionless > const r_offset ,
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity > const alpha
)
noexcept -> std::vector< math::complex::properties< units::si::temperature > >
{
  assert( b > 0 ) ;
  assert( deltaT > 0 * kelvin   );
  assert( !frequencies.empty() );
  assert( L > 0 * meters ) ;
  assert( alpha.value() > 0  ) ;

  auto results =
  vector< properties< si::temperature > >( frequencies.size()  );
  
  transform( frequencies, results.begin(), [&]( auto const f ) noexcept
  {
    auto const l = dimensionless::thermal_penetration( f, L, alpha ) ;
    auto const p = point_measurement( b, l, deltaT, r_offset );
    return p;
  } );
  
  return results;
}

} // namespace offset_point
} // namespace thermal_emission
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
