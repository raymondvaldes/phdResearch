#-------------------------------------------------
#
# Project created by QtCreator 2015-03-13T17:10:20
#
#-------------------------------------------------

QT       -= core gui

TARGET = tat-lib
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++14

QMAKE_CXXFLAGS += -std=c++14
QMAKE_CXXFLAGS += -march=native
QMAKE_CXXFLAGS += -stdlib=libc++

SOURCES += \
    algorithm/stream/resetInputBeginning.cpp \
    algorithm/string/split.cpp \
    algorithm/string/starts_with.cpp \
    algorithm/vector/doubleToString.cpp \
    algorithm/vector/ifzero.cpp \
    algorithm/vector/stdVector2ublasVector.cpp \
    algorithm/vector/stringToDouble.cpp \
    algorithm/vector/vector2cstringArray.cpp \
    filesystem/path.cpp \
    gTBC/gMeasure/find_all_files_with.cpp \
    gTBC/gMeasure/find_unique_frequencies_in_files.cpp \
    gTBC/gMeasure/find_unique_labels_in_files.cpp \
    gTBC/gMeasure/find_unique_lambdas_in_files.cpp \
    gTBC/gMeasure/find_unique_measurements.cpp \
    gTBC/gMeasure/get_pair_measurements_at_frequency.cpp \
    gTBC/gMeasure/get_signal_from_scope_file.cpp \
    gTBC/gMeasure/is_scope_file.cpp \
    gTBC/gMeasure/read_scope_file.cpp \
    gTBC/gMeasure/scopeFile.cpp \
    gTBC/gMeasure/scopeFiles_from_datafiles.cpp \
    gTBC/gMeasure/total_calibrated_emission_pairs.cpp \
    gTBC/gMeasure/unique_measurement_pair.cpp \
    gTBC/gMeasure/Unique_scope_measurement.cpp \
    investigations/twoColorPyrometery/calculateCalibrationCoefficients.cpp \
    investigations/twoColorPyrometery/importExperimentalData.cpp \
    investigations/twoColorPyrometery/phase_fitting.cpp \
    investigations/twoColorPyrometery/temperature_prediction.cpp \
    investigations/execute.cpp \
    investigations/main-app.cpp \
    investigations/num_method2014.cpp \
    investigations/sensitivityvaldes2013.cpp \
    investigations/taylor_uncertainty.cpp \
    investigations/twoColorPyrometery.cpp \
    math/algorithms/combinations.cpp \
    math/algorithms/complex.cpp \
    math/algorithms/spline.cpp \
    math/algorithms/spline_cplx.cpp \
    math/construct/periodic_time_distribution.cpp \
    math/estimation/constrained.cpp \
    math/estimation/cosfit.cpp \
    math/estimation/lmdiff.cpp \
    math/estimation/parameterestimation.cpp \
    math/estimation/settings.cpp \
    math/estimation/utils.cpp \
    math/functions/wrap2pi.cpp \
    math/geometry/interval.cpp \
    math/numIntegration/gslfunc.cpp \
    math/numIntegration/simpsons_3_8.cpp \
    math/random/random.cpp \
    math/solvers/sor.cpp \
    math/solvers/tma.cpp \
    math/bisection.cpp \
    math/utility.cpp \
    physics/classical_mechanics/kinematics.cpp \
    sensible/layer.cpp \
    sensible/property.cpp \
    sensible/radiativeSysProp.cpp \
    sensible/TBCsystem.cpp \
    sensible/temperature_scale.cpp \
    thermal/analysis/bulkSpeciman/temperature/conductivity_from_phases.cpp \
    thermal/analysis/cmplx_combination/cmplx_combination.cpp \
    thermal/analysis/sweep/temp_cmplx.cpp \
    thermal/analysis/sweep/temp_ss.cpp \
    thermal/analysis/gum_uncertainty.cpp \
    thermal/analysis/kernal.cpp \
    thermal/analysis/lmdiff_poptea.cpp \
    thermal/analysis/lmdiff_poptea_help.cpp \
    thermal/analysis/methods.cpp \
    thermal/analysis/pie.cpp \
    thermal/analysis/poptea.cpp \
    thermal/analysis/poptea_initialize.cpp \
    thermal/analysis/thermalData.cpp \
    thermal/analysis/thermalsweepoptimizer.cpp \
    thermal/define/conductivity.cpp \
    thermal/define/construct.cpp \
    thermal/define/diffusivity.cpp \
    thermal/define/effusivity.cpp \
    thermal/define/lthermal.cpp \
    thermal/define/model.cpp \
    thermal/define/omega.cpp \
    thermal/define/temperature.cpp \
    thermal/define/volumetricHeatCapacity.cpp \
    thermal/emission/blackBody/planckWienApprox.cpp \
    thermal/emission/emission.cpp \
    thermal/emission/noise.cpp \
    thermal/emission/phase99.cpp \
    thermal/emission/signalRatio.cpp \
    thermal/equipment/detector/detector.cpp \
    thermal/equipment/detector/measurement.cpp \
    thermal/equipment/detector/measurements.cpp \
    thermal/equipment/laser.cpp \
    thermal/equipment/setup.cpp \
    thermal/model/one_dim/analytical_2005/analytical_2005.cpp \
    thermal/model/one_dim/numerical_2011/mesh.cpp \
    thermal/model/one_dim/numerical_2011/numerical_2011.cpp \
    thermal/model/one_dim/numerical_2011/Numerical_Setup.cpp \
    thermal/model/one_dim/numerical_2011/Numerical_Temperature.cpp \
    thermal/model/one_dim/one_dim.cpp \
    thermal/model/one_dim/Tss_ana.cpp \
    thermal/model/slab/slab.cpp \
    thermal/model/two_dim/analytical_2009/heat2DAna.cpp \
    thermal/model/utilities/heat_generation/Iheat.cpp \
    thermal/model/utilities/nondimensional/tau_0.cpp \
    thermal/model/labels.cpp \
    thermal/pyrometry/twoColor/calibratedSignalRatio.cpp \
    thermal/pyrometry/twoColor/normalizedDetectorMeasurements.cpp \
    thermal/pyrometry/twoColor/normalizedSignalRatio.cpp \
    thermal/pyrometry/twoColor/normalizedSignalRatio_from_measurement.cpp \
    thermal/pyrometry/twoColor/pyrometery_settings_file.cpp \
    thermal/pyrometry/twoColor/signalRatio.cpp \
    thermal/pyrometry/twoColor/temperatureSteady.cpp \
    thermal/pyrometry/twoColor/transient_analysis.cpp \
    thermal/simulations/Numerical_PhaseOfEmission.cpp \
    tools/interface/import/columnData.cpp \
    tools/interface/exportfile.cpp \
    tools/interface/filesystem.cpp \
    tools/interface/xml.cpp \
    tools/programoptions/programoptions.cpp \
    tools/timing.cpp

HEADERS += \
    algorithm/stream/eof.h \
    algorithm/stream/getline.h \
    algorithm/stream/is_open.h \
    algorithm/stream/resetInputBeginning.h \
    algorithm/stream/validateOpenStream.h \
    algorithm/string/split.h \
    algorithm/string/starts_with.h \
    algorithm/string/trim.h \
    algorithm/string/trim_all.h \
    algorithm/valarray/valarray_to_vector.h \
    algorithm/valarray/vector_to_valarray.h \
    algorithm/vector/add.h \
    algorithm/vector/doubleToQuantity.h \
    algorithm/vector/doubleToString.h \
    algorithm/vector/fill_with_list_values_as_constructor_arg.h \
    algorithm/vector/find_all.h \
    algorithm/vector/ifzero.h \
    algorithm/vector/operator_overloads.h \
    algorithm/vector/quantityTodouble.h \
    algorithm/vector/repeatElements.h \
    algorithm/vector/stdVector2ublasVector.h \
    algorithm/vector/stringToDouble.h \
    algorithm/vector/stringToQuantity.h \
    algorithm/vector/subtract.h \
    algorithm/vector/sum.h \
    algorithm/vector/vector2cstringArray.h \
    algorithm/algorithm.h \
    assert/assertExtensions.h \
    filesystem/path.h \
    gTBC/gMeasure/find_all_files_with.h \
    gTBC/gMeasure/find_unique_frequencies_in_files.h \
    gTBC/gMeasure/find_unique_labels_in_files.h \
    gTBC/gMeasure/find_unique_lambdas_in_files.h \
    gTBC/gMeasure/find_unique_measurements.h \
    gTBC/gMeasure/get_pair_measurements_at_frequency.h \
    gTBC/gMeasure/get_signal_from_scope_file.h \
    gTBC/gMeasure/is_scope_file.h \
    gTBC/gMeasure/read_scope_file.h \
    gTBC/gMeasure/scopeFile.h \
    gTBC/gMeasure/scopeFiles_from_datafiles.h \
    gTBC/gMeasure/total_calibrated_emission_pairs.h \
    gTBC/gMeasure/unique_measurement_pair.h \
    gTBC/gMeasure/Unique_scope_measurement.h \
    investigations/twoColorPyrometery/calculateCalibrationCoefficients.h \
    investigations/twoColorPyrometery/importExperimentalData.h \
    investigations/twoColorPyrometery/phase_fitting.h \
    investigations/twoColorPyrometery/temperature_prediction.h \
    investigations/execute.h \
    investigations/main-app.h \
    investigations/num_method2014.h \
    investigations/sensitivityvaldes2013.hpp \
    investigations/taylor_uncertainty.h \
    investigations/twoColorPyrometery.h \
    math/algorithms/combinations.hpp \
    math/algorithms/complex.h \
    math/algorithms/spline-quantity.h \
    math/algorithms/spline.h \
    math/algorithms/spline_cplx.h \
    math/construct/periodic_time_distribution.h \
    math/construct/range.h \
    math/curveFit/cosine.h \
    math/differential/waveEquation/analytical.h \
    math/estimation/constrained.hpp \
    math/estimation/cosfit.hpp \
    math/estimation/lmdiff.hpp \
    math/estimation/parameterestimation.hpp \
    math/estimation/settings.h \
    math/estimation/utils.hpp \
    math/functions/cosine.h \
    math/functions/periodic.h \
    math/functions/periodicData.h \
    math/functions/PeriodicProperties.h \
    math/functions/sine.h \
    math/functions/wrap2pi.h \
    math/geometry/interval.h \
    math/matrixAnalysis/valid.h \
    math/numericalAnalysis/differentiation/firstDerivative/central_difference.h \
    math/numericalAnalysis/differentiation/firstDerivative/forward_difference.h \
    math/numericalAnalysis/matrixs/inversion.h \
    math/numericalAnalysis/ublas/apply_to_all.h \
    math/numIntegration/gslfunc.hpp \
    math/numIntegration/simpsons_3_8.hpp \
    math/random/random.h \
    math/solvers/sor.h \
    math/solvers/tma.h \
    math/utilities/equalto.h \
    math/bisection.hpp \
    math/utility.hpp \
    physics/classical_mechanics/kinematics.h \
    sensible/layer.h \
    sensible/property.h \
    sensible/radiativeSysProp.h \
    sensible/TBCsystem.h \
    sensible/temperature_scale.h \
    statistics/sum.h \
    thermal/analysis/bulkSpeciman/temperature/conductivity_from_phases.h \
    thermal/analysis/cmplx_combination/cmplx_combination.h \
    thermal/analysis/sweep/temp_cmplx.h \
    thermal/analysis/sweep/temp_ss.h \
    thermal/analysis/basedata.hpp \
    thermal/analysis/gum_uncertainty.h \
    thermal/analysis/kernal.hpp \
    thermal/analysis/lmdiff_poptea.hpp \
    thermal/analysis/lmdiff_poptea_help.hpp \
    thermal/analysis/methods.hpp \
    thermal/analysis/pie.hpp \
    thermal/analysis/poptea.hpp \
    thermal/analysis/poptea_initialize.h \
    thermal/analysis/thermalData.hpp \
    thermal/analysis/thermalsweepoptimizer.hpp \
    thermal/define/conductivity.h \
    thermal/define/construct.hpp \
    thermal/define/diffusivity.h \
    thermal/define/effusivity.hpp \
    thermal/define/lthermal.h \
    thermal/define/model.hpp \
    thermal/define/model_type.h \
    thermal/define/omega.h \
    thermal/define/temperature.h \
    thermal/define/volumetricHeatCapacity.h \
    thermal/emission/blackBody/constants.h \
    thermal/emission/blackBody/planckWienApprox.h \
    thermal/emission/blackBody/signal.h \
    thermal/emission/emission.hpp \
    thermal/emission/noise.hpp \
    thermal/emission/phase99.hpp \
    thermal/emission/signal.h \
    thermal/emission/signalRatio.h \
    thermal/emission/spectrum.h \
    thermal/equipment/detector/detector.h \
    thermal/equipment/detector/measurement.h \
    thermal/equipment/detector/measurements.h \
    thermal/equipment/laser.h \
    thermal/equipment/setup.h \
    thermal/model/one_dim/analytical_2005/analytical_2005.h \
    thermal/model/one_dim/numerical_2011/mesh.hpp \
    thermal/model/one_dim/numerical_2011/numerical_2011.h \
    thermal/model/one_dim/numerical_2011/Numerical_Setup.h \
    thermal/model/one_dim/numerical_2011/Numerical_Temperature.h \
    thermal/model/one_dim/one_dim.h \
    thermal/model/one_dim/Tss_ana.h \
    thermal/model/slab/slab.h \
    thermal/model/two_dim/analytical_2009/heat2DAna.hpp \
    thermal/model/utilities/heat_generation/Iheat.h \
    thermal/model/utilities/nondimensional/tau_0.h \
    thermal/model/labels.h \
    thermal/pyrometry/twoColor/calibratedSignalRatio.h \
    thermal/pyrometry/twoColor/calibrationCoefficient.h \
    thermal/pyrometry/twoColor/calibrationGenerator.h \
    thermal/pyrometry/twoColor/normalizedDetectorMeasurements.h \
    thermal/pyrometry/twoColor/normalizedSignalRatio.h \
    thermal/pyrometry/twoColor/normalizedSignalRatio_from_measurement.h \
    thermal/pyrometry/twoColor/pyrometery_settings_file.h \
    thermal/pyrometry/twoColor/signalRatio.h \
    thermal/pyrometry/twoColor/temperatureSteady.h \
    thermal/pyrometry/twoColor/transient_analysis.h \
    thermal/simulations/Numerical_PhaseOfEmission.h \
    thermalfluids/dimensionless/prandtl_number.h \
    tools/bimap/bimap.h \
    tools/interface/import/columnData.h \
    tools/interface/exportfile.hpp \
    tools/interface/filesystem.hpp \
    tools/interface/xml.h \
    tools/programoptions/programoptions.hpp \
    tools/timing.h \
    tools/tools.hpp \
    units/si/constants/codata.h \
    units/si/constants/thermal.h \
    units/si/extension.h \
    units/si/predefined.h \
    units/si/prefixes.h \
    units/si/si.h \
    units/systems/si/base.h \
    units/cmath.h \
    units/operators.h \
    units/physical_dimensions.h \
    units/quantity.h \
    units/scale.h \
    units.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

QMAKE_CXXFLAGS += -isystem /usr/local/include


unix|win32: LIBS += -lboost_program_options
unix|win32: LIBS += -lboost_filesystem
unix|win32: LIBS += -lboost_system