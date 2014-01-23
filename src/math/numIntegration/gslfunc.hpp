/*----------------------------------------------------------------------------*\
  ========                      |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||   	  		|
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

#ifndef GSLFUNC_HPP
#define GSLFUNC_HPP

#include <gsl/gsl_spline.h>
#include <gsl/gsl_integration.h>
#include <iostream>
#include <iomanip>

namespace math{
  namespace numIntegration{




struct funcClass
{
public:
  /*
  F:          the gsl_function which is the integrand
  xlow:       lower integration limit
  xhigh:      higher integration limit
  abstol:     absolute tolerance
  reltol:     relative tolerance
  result:     a pointer to a gdouble in which stores the result
  error:      a pointer to a gdobuel in which the function stores the
              estimed error
  */

  const double* xvar;
  const double* func;
  const size_t  N;

  size_t neval;
  double epsabs = 1e-8;
  double epsrel = 1e-8;

  double result, error;
  int code;
  const size_t limit = 1001;    //defines size of workspace

  ///Allocate pointer to interpolation iterator
  gsl_interp_accel *acc   = gsl_interp_accel_alloc();

  ///Declare pointer to interpolations
  gsl_spline *spline      = nullptr;

  ///Declare pointer to workspace
  gsl_integration_workspace * workspace  = nullptr;

  explicit funcClass(double* a, double* b, size_t c): xvar(a), func(b), N(c)
  {
      /*The arguments include two arrays where
          a ...independent array
          b ...dependent array
          c ...size of array */
      ///alloc space for the spline anbd assign to pointer
      spline = gsl_spline_alloc(gsl_interp_cspline, N);
      gsl_spline_init(spline, xvar, func, N);
      workspace = gsl_integration_workspace_alloc (limit);
  }
  ~funcClass(void)
  {
    cleanup();
  }

  double eval(const double xpos) const
  {
      if( xpos < xvar[0] || xpos > xvar[N-1] )
      {
          std::cout << "outside range!!\n\n"
          <<xpos<<" is outside of range "<<xvar[0]<<"\t"<<xvar[N-1]<<"\n";

          exit(-71);
          return 0;
      }

      return gsl_spline_eval(spline, xpos, acc);
  }

  static double CCallback(double d, void*params)
  {
      return static_cast<funcClass*>(params)->eval(d);
  }

  double integrate_a_b(const double xlow, const double xhigh,
                       const double epsabs_, const double epsrel_)
  {
      //http://www.bnikolic.co.uk/nqm/1dinteg/gslgk.html
      if( (xlow < xvar[0]) || (xhigh > xvar[N-1]) || (xlow > xhigh) )
      {
          std::cout << "\n\n" << std::setprecision(4) << (xlow < xvar[0]);
          std::cout << "\t" << (xhigh > xvar[N-1]) << "\t" << (xlow > xhigh);
          std::cout << "\t" << xlow <<"\t"<< xhigh << "\t" << xvar[0] << "\t";
          std::cout << xvar[N-1] << "\n";
          std::cout << "error - redefine integration domain"; exit(64);
      }

      gsl_function F;
      F.function = &funcClass::CCallback;
      F.params = this;

      code = gsl_integration_qng(&F, xlow, xhigh, epsabs_, epsrel_, &result,
                                 &error, &neval);
      return result;
  }

private:
  void cleanup(void)
  {
    gsl_spline_free(spline);
    gsl_interp_accel_free(acc);
    gsl_integration_workspace_free(workspace);
  }
};


double fintegrate(double x, void *p);
double integrate(struct funcClass *Func, double xlow, double xhigh);


  }
}
#endif // GSLFUNC_HPP