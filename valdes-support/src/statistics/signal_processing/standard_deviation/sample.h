//
//  sample.h
//  tat
//
//  Created by Raymond Valdes_New on 3/16/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_sample_h
#define tat_sample_h

#include <vector>

#include "statistics/signal_processing/sum_residuals_square.h"

#include "units.h"

namespace statistics {

namespace signal_processing {

namespace corrected_sample  {

template< typename T >
auto standard_deviation( std::vector< units::quantity<T> > const & signals )
-> units::quantity<T>
{
  using units::quantity;
  using units::si::dimensionless;
  
  auto const sum_residuals_square_val = sum_residuals_square( signals );
  auto const corrected_count = signals.size() - 1 ;
  
  auto const std_dev = sum_residuals_square_val / quantity<dimensionless>( corrected_count )

  return std_dev;
}

} // namespace standard_deviation
  
} // namespace signal_processing
  
} // namespace statistics

#endif
