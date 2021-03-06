/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#include "math/estimation/cosfit.hpp"
#include "math/estimation/constrained.hpp"
#include "math/estimation/lmdiff.hpp"
#include "math/functions/periodic.h"

namespace math{
  namespace estimation{


void cosfit( const double *dependent, const std::vector<double> &independent,
             double *x, const size_t Nend) noexcept
{
  BOOST_ASSERT( dependent != nullptr ) ;
  BOOST_ASSERT( x != nullptr ) ;


  constexpr size_t N = 3; // number  of constants to be fitted
  const size_t P = Nend-1;
  //number of datapoints to be used in the fitting process

///Transform input into offset, amplitude, phase
  /*
  The offset is limited to positive values.
  The amplitude if limited to positive values.  This is accomplished
  by reparameterization (Bates and Watts, 1988). See pg 163 Englezos
  (applied parameter estimation)
  ex. k_i = exp(kappa_i)

  By conducting our search over kappa regardless of its value, exp(kappa)
  and hence k is always positive.

  The phase is bounded from -pi to +pi.
  */
  //x[0] = kx_limiter1(x[0]);
  x[1] = kx_limiter1(x[1]);
  x[2] = kx_limiter2(x[2], -M_PI, M_PI );

///Fitting in kappa space
  /*
  loop is run for each time
  newdependent is the temperature data
  newindependent sets B and B to corresponding values (time)
  */
  {
      double *fjac = new double[P*N];
      double *wa5 = new double[P*N];

      double *fvec = new double[P];
      double *wa4 = new double[P];
      double *newdependent = new double[P];//dependent array for fits
      double *newindependent = new double[P]; //independent array for fits

      double *qtf     = new double[N];
      double *wa1     = new double[N];
      double *wa2     = new double[N];
      double *wa3     = new double[N];
      double *diag    = new double[N]();
      int *ipvt       = new int[N];

      for(size_t i = 0 ; i < N ; ++i )
        ipvt[i] = 9;
        
      int nfev;
      int info=0;

      for (size_t g = 0; g <P; g++)
      {
          newdependent[g]   = dependent[g];
          newindependent[g] = g*(independent[1]-independent[0]);
      }


      double *variables[3];
      for( size_t a=0; a<=2 ; ++a )
          variables[a]=new double [P];

      for( size_t g = 0; g <P; g++ )
      {
          variables[0][g] =   newdependent[g];
          variables[1][g] =   newindependent[g];
      }
      variables[2][0]=0;

      constexpr double ftol = 1.e-10;
      constexpr double xtol = 1.e-10;
      constexpr double gtol = 1.e-10;
      constexpr int maxfev = 1e8;
      constexpr double epsfcn = 1.e-12;
      constexpr double factor = 1;
      constexpr int mode = 1;
      constexpr int nprint = 0;

      lmdif( &cosfcn1, static_cast<int>(P), N, x, fvec, variables, ftol, xtol,
             gtol, maxfev, epsfcn, diag, mode, factor, nprint, &info, &nfev,
             fjac, static_cast<int>(P), ipvt, qtf, wa1, wa2, wa3, wa4, wa5 ) ;

      ///Clean Up
      for(size_t a=0; a<=2 ; ++a)
      {
          delete[] variables[a];
      }
      delete [] fvec;    delete [] qtf;
      delete [] wa1;      delete [] wa2;
      delete [] wa3;     delete [] wa4;
      delete [] fjac;    delete [] wa5;
      delete [] ipvt;     delete [] diag;

      delete [] newdependent;
      delete [] newindependent;
  }

///Transform output back to offset, amplitude, phase
  //x[0] = x_limiter1(x[0]);
  x[1] = x_limiter1(x[1]);
  x[2] = x_limiter2(x[2],-M_PI,M_PI);

  return;
}

void cosfcn1( int P, int /*N*/, double *x, double *fvec, int */*iflag*/,
              double **variables ) noexcept
{  // function to be fitted:
   // dependent[i] = x[0] + x[1] * cos( independent[i]*2*PI + x[2] )
   // constants to be found by the fit are: x[0],x[1],x[2] which respectively
   // are offset, amplitude, phase
  
  const double phase = x_limiter2( x[2], -M_PI, M_PI ) ;
  const double ampli = x_limiter1( x[1] ) ;
  const double offset = x[0] ;

  using std::cos;
  for( int g=0 ; g<P ; ++g )
  {
      fvec[g] = cos( variables[1][g] * 2 * M_PI + phase );
      fvec[g] *= ampli ;
      fvec[g] += offset;  //x_limiter1(x[0]);

      fvec[g] *= -1;
      fvec[g] += variables[0][g];
  }
  
  return;
}


  }
}
