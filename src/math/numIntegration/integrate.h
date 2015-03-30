//
//  integrate.h
//  tat
//
//  Created by Raymond Valdes on 3/27/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_math_numIntegration_integrate__
#define __tat_math_numIntegration_integrate__

#include "units.h"
#include "algorithm/algorithm.h"
#include "statistics/signal_processing/average.h"
#include <vector>
#include <cassert>
#include <boost/numeric/odeint/config.hpp>
#include <boost/numeric/odeint.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <iterator>

namespace math{
namespace numIntegration{

using statistics::signal_processing::average;
using algorithm::for_each;

/* The rhs of x' = f(x) */

///The function type takes all by const except the state_type is taken by
// reference and this is used to modify.
template< typename type >
void harmonic_oscillator
(
  std::vector< type > const & y ,
  std::vector< type > & dydx ,
  type const x
)
{
    dydx[0] = y[0] * x ;
}

//[ integrate_observer
template< typename type >
struct push_back_state_and_time
{
    std::vector< std::vector< type > > & m_states;
    std::vector< type > & m_xPoints;

    push_back_state_and_time
    (
      std::vector< std::vector< type > > & states ,
      std::vector< type > & xPoints
    )
    : m_states( states ) , m_xPoints( xPoints ) { }

    void operator()
    (
      std::vector< type > const & y ,
      type x
    )
    {
        m_states.push_back( y ) ;
        m_xPoints.push_back( x ) ;
    }
};
//]

template< typename func_type, typename type >
auto integrate
(
  func_type const & func  ,
  std::vector< type > const f_x0,
  type const x0,
  type const x1,
  type const dx_intial_step
)
noexcept -> decltype( f_x0.front() * dx_intial_step )
{
  using namespace boost::numeric::odeint;
  using std::vector;
  assert( !f_x0.empty() );

  /* The type of container used to hold the state vector */
  using state_type = vector< type  > ;

  //[ state_initialization
  auto y = f_x0;
  //]

  // create stepper (use the RK-4 because of it's controlled steps
//  using boost::numeric::odeint::runge_kutta4;
//  using boost::numeric::odeint::make_dense_output;
//  typedef runge_kutta4<state_type> stepper_type;
//  
  
  auto const tol_relative = 1E-9;
  auto const tol_absolute = 1E-9;
  
  typedef runge_kutta_dopri5< state_type > dopri5_type;
  typedef controlled_runge_kutta< dopri5_type > controlled_dopri5_type;
  typedef dense_output_runge_kutta< controlled_dopri5_type > dense_output_dopri5_type;
  dense_output_dopri5_type dopri5 = make_controlled( 1E-9 , 1E-9 , dopri5_type() );


  auto y_vec = vector< state_type >() ;
  auto x_points = vector< type >() ;

  //This function integrates dy/dx from x0 to x1
  auto const n_steps = integrate_adaptive(
    dopri5,
    func , y , x0 , x1 , dx_intial_step,
    push_back_state_and_time< type >( y_vec, x_points) );

//  decltype( f_x0.front() * x0 ) area;
//  using std::next;
//  using std::begin;
//  using std::end;
//  
//  auto i = size_t(1);
//  for_each( next( begin( y_vec ) ) , end( y_vec ) ,
//  [ & ]( auto const & y_state ) noexcept
//  {
//    auto const y = y_vec[ i ].front()  ;
//    auto const y_ = y_vec[ i - 1 ].front() ;
//
//    auto const dx_i = x_points[ i ] - x_points[ i-1 ];
//    auto const y_i =  ( y +  y_ ) / 2. ;
//    
//    auto const dA = y_i * dx_i;
//    area += dA ;
//    
//    std::cout << "( " << dx_i << " , " << y_i << " )\t" << dA <<"\t"<< area <<  "\t";
//    std::cout << "( " << x_points[ i ] << " , " << y << " )\n" ;
//    ++i;
//  } ) ;

  return y_vec.back().front() - y_vec.front().front();
}

} // namespace numIntegration
} // namespace math

#endif /* defined(__tat__integrate__) */