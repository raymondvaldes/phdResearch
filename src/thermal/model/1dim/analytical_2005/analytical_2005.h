/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
 -------------------------------------------------------------------------------
 License
 This file is part of Thermal Analysis Toolbox.
 
 Thermal Analysis Toolbox is free software: you can redistribute it and/or
 modify it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or (at your
 option) any later version.
 
 Thermal Analysis Toolbox is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License along with
 Thermal Analysis Toolbox.  If not, see <http://www.gnu.org/licenses/>.
 
\*----------------------------------------------------------------------------*/

#ifndef __tat_onedim_analytical_2005__
#define __tat_onedim_analytical_2005__

#include <iostream>
#include <complex>
#include "sensible/TBCsystem.h"
#include "thermal/equipment/laser.h"
#include "math/algorithms/spline_cplx.h"

namespace thermal{ namespace model { namespace one_dim{
  
  using std::complex;
  
class analytical_2005
{
private:
  struct layer
  {
    const double k;
    const double psi;
    const double L;
    const double Lambda;
    
    explicit layer( const double k_in, const double psi_in, const double L_in,
                    const double Lambda_in)
    : k( k_in ), psi( psi_in ), L( L_in ), Lambda( Lambda_in ) {}
  };
  
  const layer coat;
  const double I_intensity_ss;
  const double I_intensity_tt;

  const double Temperature_interface;
  const double gamma;
  const double R1;
  const double Emit1;
  const std::complex<double> eye;


  double Lambda_hat ( const double lthermal ) const;
  complex<double> F_tilde( const double lthermal ) const;
  complex<double> eta ( const double Lambda_hat ) const;
  complex<double> M_tilde( const complex<double> x_in, const double l ) const;
  complex<double> N_tilde( const complex<double> x_in, const double l ) const;
  
          double  T_ss_R1eq1_eval( const double omega, const double z ) const ;
  complex<double> T_tt_R1eq1_eval( const double omega, const double z ) const ;

public:
  explicit analytical_2005( const sensible::layer &coating_in,
                            const sensible::radiativeSysProp &radiative_prop_in,
                            const thermal::equipment::Laser &laser_in,
                            const double temp_in,
                            const double gamma_in ) ;
  ~analytical_2005( void ) ;
  
  complex<double> T_tt_eval_cplx( const double omega, const double z ) const;
  
  double phase_linear( const double omega ) const ;
  double phase_nonlinear( const double omega ) const;
  
  //sweeps
  math::algorithms::spline_cplx T_tt_R1eq1_cplx_sweep( const double omega ) ;
};
  
}}}
#endif /* defined(__tat_onedim_analytical_2005__) */