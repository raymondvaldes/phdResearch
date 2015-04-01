/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef __tat__one_dim__
#define __tat__one_dim__

#include <iostream>
#include <complex>
#include "sensible/TBCsystem.h"
#include "thermal/equipment/laser.h"

namespace thermal{ namespace model {namespace one_dim{

class one_dim
{
  protected:
  
  struct layer
  {
    const double k;
    const double psi;
    const double L;
    const double Lambda;
    
    explicit layer( const double k_in, const double psi_in, const double L_in,
                    const double Lambda_in ) noexcept
    : k( k_in ), psi( psi_in ), L( L_in ), Lambda( Lambda_in ) {}
  };
  
  const layer coat;
  const sensible::layer coat_full ;
  const sensible::layer sub_full ;
  const double I_intensity_ss;
  const double I_intensity_tt;

  const double Temperature_interface;
  const double gamma;
  const double R1;
  const double Emit1;

  explicit one_dim( const sensible::layer &coating_in,
                    const sensible::layer &substrate_in,
                    const sensible::radiativeSysProp &radiative_prop_in,
                    const thermal::equipment::Laser &laser_in,
                    const double temp_in, const double gamma_in ) noexcept;
  ~one_dim( void ) noexcept;
};

}}}

#endif /* defined(__tat__one_dim__) */
