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

#ifndef __tat__kinematics__
#define __tat__kinematics__

#include "units.h"

namespace physics{

namespace classical_mechanics{

double period_to_angularFrequency( const double period ) noexcept;

double angularFrequency_to_period( const double angularFrequency ) noexcept;

auto
frequency_to_angularFrequency(
  units::quantity< units::si::frequency > const &  frequency )
noexcept -> units::quantity< units::si::angular_frequency >;

} // namespace classical_mechanics

} // physics


#endif /* defined(__tat__kinematics__) */
