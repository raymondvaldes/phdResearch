/*----------------------------------------------------------------------------*\
  ========                  |
     ||     T Thermal       | TAT: Thermal Analysis Toolbox
     ||     A Analysis      |
     ||     T Toolbox       | Copyright (C) 2013 Raymond Valdes
     ||                     |
--------------------------------------------------------------------------------
License                                                                         
    This file is part of Thermal Analysis Toolbox.

    Thermal Analysis Toolbox is free software: you can redistribute it and/or 
    modify it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or (at your 
    option) any later version.

    Thermal Analysis Toolbox is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
    Public License for more details.

    You should have received a copy of the GNU General Public License along with 
    Thermal Analysis Toolbox.  If not, see <http://www.gnu.org/licenses/>.

\*----------------------------------------------------------------------------*/
#include "Header.h"

int main( int /*argc*/, char** /*argv[]*/ )
{
  std::cout << "Welcome back, Raymond!\n\n";
  class stopwatch globalStopWatch;

  /// Figure out working directory
  namespace bf = boost::filesystem;
  std::string path("/home/raymond/code/tat/bin");
  const bf::path pProgram(path);
  class filesystem::directory dir(pProgram.string());

  /// Run investigations
  investigations::sensitivityvaldes2013::run( dir );

  /// Test investigation
  investigations::manyfit::run( dir );

//  //Prepare figures and data for paper Sensitivity
////    SensitivityValdes2013::CC_APS2(poptea);
////    SensitivityValdes2013::figureSensitivityIntro(poptea);

  /// end
  globalStopWatch.displayTime();
  return 0;
}
