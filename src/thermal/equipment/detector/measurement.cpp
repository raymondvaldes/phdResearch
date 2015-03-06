//
//  measurement.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/equipment/detector/measurement.h"
#include "assert/assertExtensions.h"

namespace thermal {

namespace equipment {

namespace detector {

Measurement::Measurement(
  units::quantity< units::si::time > const & timestamp_In,
  units::quantity< units::si::electric_potential > const & signal_In )
: reference_time( timestamp_In ), signal( signal_In )
{
  assert_ge_zero( timestamp_In );
  assert_gt_zero( signal_In );
};

} // namespace detector

} // namespace equipment

} // namespace thermal