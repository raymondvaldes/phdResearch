//
//  measurements.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/equipment/detector/measurements.h"
#include "algorithm/algorithm.h"
#include "assert/assertExtensions.h"
#include "plot/gnuplot.h"

namespace thermal {

namespace equipment {

namespace detector {

using std::vector;
using units::quantity;
using units::si::time;
using units::si::electric_potential;
using algorithm::generate;
using algorithm::transform;
using algorithm::vector::quantityTodouble;

Measurements::Measurements(
  units::quantity<units::si::wavelength> const & wavelengthIn,
  std::vector< units::quantity< units::si::time> > const & referenceTime,
  std::vector< units::quantity< units::si::electric_potential > > const & signals )
  : wavelength( wavelengthIn), measurements( signals.size() )
{
  assert_gt_zero( wavelengthIn );
  assert_equal( referenceTime.size(), signals.size() );
  
  size_t i = 0u;
  generate( measurements, [&referenceTime, &signals, &i]() noexcept
  {
    auto const melissa = Measurement{ referenceTime[i], signals[i] };
    ++i;
    return melissa;
  } );
  
};

auto Measurements::size( void )
const noexcept -> size_t
{
  return measurements.size();
};

auto Measurements::referenceTimes( void )
const noexcept-> std::vector< units::quantity<units::si::time> >
{
  auto const count = size();
  
  auto const myMeasurements = measurements;
  auto times = vector< quantity< time > >{ count };
  auto i = 0;

  generate( times, [ &myMeasurements, &i]() noexcept
  {
    auto const time = myMeasurements[i].reference_time;
    ++i;
    return time ;
  } );

  return times;
}

auto Measurements::signals_electical_potential( void )
const noexcept-> std::vector< units::quantity<units::si::electric_potential> >
{
  auto const count = size();
  
  auto const myMeasurements = measurements;
  auto signals = vector< quantity< electric_potential > >{ count };

  transform( myMeasurements, signals.begin(), []( auto const measurement ){
    auto const signal = measurement.signal;
    return signal ;
  } );
  
  return signals;
}

auto Measurements::plot_measurements( void ) const noexcept -> void
{
	Gnuplot gp("/usr/local/bin/gnuplot --persist");
  
  gp << "set xlabel 'time (s)'" << "\n";
  gp << "set ylabel 'detector (V)'" << "\n";
  
  auto const x_pts = quantityTodouble( referenceTimes() );
  auto const y1_pts = quantityTodouble( signals_electical_potential() );
  
  auto const xy1_pts = make_pair( x_pts, y1_pts );

  gp << "plot"
  << gp.file1d( xy1_pts ) << "with points title 'thermal detector measurements',"
  << std::endl;
}
  
} // namespace detector

} // namespace equipment

} // namespace thermal
