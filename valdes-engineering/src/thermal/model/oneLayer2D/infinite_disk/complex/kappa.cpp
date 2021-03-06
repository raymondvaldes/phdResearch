//
//  kappa.cpp
//  tat
//
//  Created by Raymond Valdes on 4/23/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/infinite_disk/complex/kappa.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace complex{

using namespace std::literals;
using namespace units;
using std::sqrt;
using std::complex;

auto kappa
(
  units::quantity< units::si::dimensionless > const nu,
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::dimensionless > const l
) noexcept -> units::quantity< units::si::dimensionless, std::complex<double> >
{
  assert( nu >= 0 ) ;
  assert( b > 0 ) ;
  assert( l > 0 ) ;
  
  auto const i_non = quantity< si::dimensionless, complex<double > >( 0. + 1i );
  auto const k = sqrt( pow<2>( nu ) + i_non * pow<2>( b / l ) ) ;

  assert( isfinite( k.value().real() ) ) ;
  assert( isfinite( k.value().imag() ) ) ;

  return  k;
}


} // namespace complex
} // namespace oneLayer2D
} // namespace model
} // namespace thermal

