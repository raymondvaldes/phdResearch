//
//  temperature.h
//  tat
//
//  Created by Raymond Valdes on 4/29/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_oneLayer2D_complex_temperature___
#define __tat_thermal_model_oneLayer2D_complex_temperature___

#include "units.h"
#include <complex>

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace complex{

auto temperature
(
  units::quantity< units::si::dimensionless > const z,
  units::quantity< units::si::dimensionless > const r,
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::dimensionless > const l,
  units::quantity< units::si::heat_flux > const I,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_conductivity > const k
) noexcept -> units::quantity< units::si::temperature, std::complex<double> >;

} // namespace complex
} // namespace oneLayer2D
} // namespace model
} // namespace thermal

#endif /* defined(__tat__temperature__) */
