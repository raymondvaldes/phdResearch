//
//  fit.hpp
//  tat
//
//  Created by Raymond Valdes on 9/8/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef fit_cpp_fitab3RC_090815
#define fit_cpp_fitab3RC_090815

#include "units.h"
#include "thermal/model/slab/slab.h"
#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/Best_fit.h"
#include "thermal/experimental/observations/slab/slab.hpp"

namespace thermal{
namespace analysis {
namespace oneLayer2D {
namespace estimate_parameters{
namespace phase_analysis{
namespace fit_a_b3_RC{
namespace fit_all{

auto fit
(
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  std::vector< units::quantity< units::si::plane_angle > > const & observations,
  thermal::model::slab::Slab const slab_initial,
  units::quantity< units::si::length> const beam_radius,
  units::quantity< units::si::length > const detector_offset_point
)
noexcept -> Best_fit;


auto fit
(
  thermal::experimental::observations::Slab const & initial_slab,
  units::quantity< units::si::length > const detector_offset_point
)
noexcept -> Best_fit;

} // namespace fit_all
} // namespace fit_a_b3_RC
} // namespace phase_analysis
} // namespace estimate_parameters
} // namespace oneLayer2D
} // namespace analysis
} // namespace thermal

#endif /* fit_cpp */
