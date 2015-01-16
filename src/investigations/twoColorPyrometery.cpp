//
//  2colorPyrometery.cpp
//  tat
//
//  Created by Raymond Valdes on 12/18/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#include "investigations/twoColorPyrometery.h"
#include "thermal/analysis/poptea.hpp"
#include "thermal/analysis/poptea_initialize.h"

namespace investigations{
namespace twoColorPyrometery{
  
void run( const filesystem::directory &dir ) noexcept {
  using thermal::analysis::Poptea;

  {
  using thermal::analysis::initializePopTeawithExperimentalEmission;
  auto poptea = Poptea{
    initializePopTeawithExperimentalEmission( dir ) };
    
  }
  
  
  
  
  

  {
    using thermal::analysis::initializePopTeaAndLoadSimuEmission;
    auto poptea = Poptea{
      initializePopTeaAndLoadSimuEmission( dir ) };
    poptea.bestFit() ;
    std::cout << poptea.ppUnknownParameters() << "\n";
  }
}
}}
