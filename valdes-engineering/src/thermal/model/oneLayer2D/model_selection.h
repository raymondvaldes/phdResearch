//
//  model_selection.h
//  tat
//
//  Created by Raymond Valdes on 10/14/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef model_selection_h_101415
#define model_selection_h_101415

#include <exception>

namespace thermal{
namespace model{
namespace oneLayer2D{



enum class Conduction_model {
  infinite_disk,
  finite_disk
};

enum class Detector_model {
  center_point,
  center_with_view,
  offset_point,
  offset_with_view
};


class Detector_model_not_available: public std::exception
{
public:
  Detector_model detector_model;
  
  Detector_model_not_available( Detector_model const & detector_model )
  noexcept: detector_model( detector_model ){};

  virtual const char* what() const throw()
  {
    return "Detector model not available.";
  }

};

class Conduction_model_not_available: public std::exception
{
public:
  Conduction_model model;
  
  Conduction_model_not_available( Conduction_model const & model )
  noexcept: model( model ){};

  virtual const char* what() const throw()
  {
    return "Conduction model not available.";
  }
  
};

struct Parameter_selection {
  bool beam_radius = false;
  bool thermal_conductivity = false;
  bool thermal_diffusivity = false;
  bool specimen_radius = false;
  bool detector_offset = false;
  bool detector_view_radius = false;
};


} // namespace oneLayer2D
} // namespace model
} // namespace thermal

#endif /* model_selection_h */
