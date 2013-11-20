#ifndef POPTEA_HPP
#define POPTEA_HPP

enum XParaNames
{
    gammaEff,
    asub,
    E1,
    R1,
    lambda,
    R0
};

namespace thermalAnalysisMethod
{
  class PopTea
  {
  public:
    enum XParaNames *xParameters95Names;  //MUST BE REMOVEd
    enum XParaNames *xParametersNames;    // MUST BE REMOVED
    size_t N95;                           //MUST BE REMOVED

    class expEquipment::setup expSetup;
    class physicalModel::TBCsystem TBCsystem;
    class thermal::ThermalModelSelection thermalModel;
    class parameterEstimation::LMA LMA;
    std::string dir;

    PopTea(class expEquipment::setup expSetup_,
           class physicalModel::TBCsystem TBCsystem_,
           class thermal::ThermalModelSelection thermalModel_,
           class parameterEstimation::settings Settings_,
           class parameterEstimation::unknownList unknownParameters_);
    ~PopTea(void);


  void thermalSetup(const double lmin_, const double lmax_,
                    const size_t LendMin); //MUST BE REMOVED
  double bEval(void) const; //MUST BE REMOVED
  };
}

#endif // POPTEA_HPP
