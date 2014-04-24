/*----------------------------------------------------------------------------*\
 ========               |
    || 	 T Thermal      | TAT: Thermal Analysis Toolbox
    ||   A Analysis     |
    || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	        	|
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

#include "num_method2014.h"
#include "thermal/analysis/poptea.hpp"
#include "thermal/analysis/poptea_initialize.h"
#include "thermal/emission/phase99.hpp"

namespace investigations{
  namespace num_method{
    
using namespace thermal::analysis;

void run( const filesystem::directory &dir )
{
  using std::string;
  using thermal::define::construct;
  using thermal::define::HeatX;
  using thermal::define::EmissionX;
  using thermal::emission::phase99;

  /// setup output
  Poptea poptea = initializePopTeawithNominalEmission( dir ) ;
  construct theoreticalModel = poptea.coreSystem->thermalsys.Construct ;
  
  
  // prepare models
  theoreticalModel.update( HeatX::OneDimAnalytical, EmissionX::OneDimNonLin ) ;
  poptea.reloadThermalModel( theoreticalModel) ;
  std::vector<double> heat1 =
  phase99( *(poptea.coreSystem) , poptea.thermalData->omegas ) ;

  
  theoreticalModel.update( HeatX::OneDimNumLin, EmissionX::OneDimNonLin ) ;
  poptea.reloadThermalModel( theoreticalModel) ;
  std::vector<double> heat2 =
  phase99( *(poptea.coreSystem) , poptea.thermalData->omegas ) ;
  
  for(size_t i = 0 ; i < poptea.thermalData->size() ; ++i )
    std::cout << heat1[i] << "\t" <<  heat2[i] << "\n";
  
  
  /// Part test
  // poptea.bestFit() ;
  std::cout << poptea.ppUnknownParameters() ;
  
  
  return;
}
    
}}