//
//  c.h
//  tat
//
//  Created by Raymond Valdes on 3/26/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_tbc2009_dimensionless_c__
#define __tat_thermal_model_tbc2009_dimensionless_c__

#include "units.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace dimensionless{

auto c
(
  units::quantity< units::si::thermal_conductivity > const k_radial_r,
  units::quantity< units::si::thermal_conductivity > const k_axial_z
) noexcept -> units::quantity< units::si::dimensionless >;

} // namespace dimensionless
} // namespace tbc2009
} // namespace model
} // namespace thermal

#endif /* defined(__tat_thermal_model_tbc2009_dimensionless_c__) */
