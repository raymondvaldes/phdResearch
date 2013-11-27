#ifndef NUMERICAL_SETUP_H_INCLUDED
#define NUMERICAL_SETUP_H_INCLUDED

double x_ini10(const int x_ref);

void fdjac2(void (*fcn)(int, int, double *, double *, int *,
                        const struct parameter_constraints*,
                        class thermalAnalysisMethod::PopTea poptea),
            int m, int n, double x[], double fvec[], double fjac[], int,
            int *iflag, double epsfcn, double wa[],
            const struct parameter_constraints*st_ptr,
            class thermalAnalysisMethod::PopTea poptea);

double gspatial(double eta, double opt, double lambda, double R1,
                double Iplus0, double Iplus1);


void cosfcn(int P, int , double *x, double *fvec, int *, double **variables);

double simpson_3_8(const double *Y, const double *X, const size_t A,
                   const size_t B);
double simpson_3_8(const std::vector<double>& Y, const double *X,
                   const size_t A,const size_t B);
double simpson_3_8(const std::vector<double>& Y, const std::vector<double>&X,
                   const size_t A,const size_t B);
double simpson_3_8(const double* Y, const std::vector<double>& X,
                   const size_t A, const size_t B);

std::complex<double> simpson_3_8Complex(const double* YReal,
                                        const double* YCPLX,
                                        const std::vector<double>& X,
                                        const size_t A,const size_t B);
std::complex<double> simpson_3_8Complex(const std::vector<double>& YReal,
                                        const std::vector<double>& YCPLX,
                                        const std::vector<double>& X,
                                        const size_t A,const size_t B);
std::complex<double> simpson_3_8Complex(const double* YReal,
                                        const double* YCPLX,
                                        const double* X,
                                        const size_t A,const size_t B);

double x_limiter1(const double xi);
double x_limiter2(const double xi,const double x_min, const double x_max);
double kx_limiter1(const double ki);
double kx_limiter2(const double ki,const double k_min,const double k_max);
double x_ini10(const double x_ref);

double x_ini(double x_min, double x_max);

void solveMatrix(const int64_t n, const std::vector<double>& b,
                 const std::vector<double>& d, const std::vector<double>& a,
                 const std::vector<double>& C, std::vector<double>& u);

double SOR(double**A, double*b, const size_t M2, double*phi, double omega,
           double error);

void minimizer( double (*to_minimize)(double*,double*), double *variable,
               double *constants, double temp_variable_min,
               double temp_variable_max, double min_goal,const size_t max_iterations);

double average(const double a, const double b);

double gs_int(const double eta, const double opt, const double lambda, const double R1, const double Iplus0,
              const double Iplus1);
double psi(const double eta, const double psi_layer1, const double psi_layer2);
double psi(const std::vector<std::vector<double>>& T, const double eta,
           const size_t j, const size_t n, const double psi_c,
           const double psi_ref);

double k(const std::vector<std::vector<double>>& T, const double zpos,
         const double k_c, const double k_ref);

double kthermal(const double eta, const double k_layer1, const double k_layer2);

double Kappa(const std::vector<std::vector<double>>& T, const double eta,
             const double eta_j, const size_t j, const size_t n,
             const double k_ref, const int prop_linearity, const double k_c);
void scaleDiag(const int mode, const size_t N, double * diag,
               const class thermalAnalysisMethod::PopTea poptea );

double x_normal(const double Xmean, const double Xstddev);

double x_normal(const double Xmean, const double Xstddev, const double seed1);

double Psi_non(const std::vector<std::vector<double>>& T, const double eta,
               const double eta_j, const size_t j, const size_t n,
               const double psi_ref, const int prop_linearity,
               const double psi_c);

void cosfit(double **dependent, const double *independent, double *x, int j,
            double omega1, int Nend);

void cosfit(double *dependent,const std::vector<double> &independentVec,
            double *x, int Nend);

void cosfcn1(int P, int, double *x, double *fvec, int *, double **variables);

double Iheat(double Isteady, double Itransient, double omega, double t) ;//verified

size_t sumVector(const size_t *const vector1,const size_t sizeV);

double Iheat_int(const double Isteady,const double Itransient,
                        const double omega, const double t); //verified

double tau_0(const double omega);
double x_bias(const double Xmean, const double Xstddev);

size_t discretizeSpace(const int nodes,const double beta1,const double beta2,
                       const double split, double *z_norm, double *z_real,
                       const double L_coat,const double L_substrate, double*eta,
                       double* zNorm2);

double omega(const double L_coat, const double l_thermal, const double k_c,
             const double psi_c);

double lthermal(const double L_coat, const double k_c, const double psi_c,
                const double omega);

double x_ini(const double x_min, const double x_max, const size_t position,
             const size_t gN);
void mainMemoryAllocate(class thermalAnalysisMethod::PopTea poptea);

size_t xINTrandom(const size_t xmin, const size_t xmax);
void range1og10(const double l_min, const double l_max, const size_t L_end,
             double* l_thermal);
void range1og10(const double l_min, const double l_max, const size_t L_end,
                std::vector<double> &l_thermal);

void range(double* l_thermal, const double l_min, const double l_max,
           const size_t L_end);
void range(std::vector<double>& l_thermal, const double l_min,
           const double l_max, const size_t L_end);

double percentile(const double xmin, const double xmax, const double x);
double percentilelog10(const double xmin, const double xmax, const double x);

class perturbStruct
{
  public:
    size_t pNum;

    size_t xnumber;  //keep this odd
    double spread;
    double lmin1;

    double lmax2;
    double PtolBand;
    const double lminRef = 0.2;
    const double lmaxRef = 0.8;
    const double lmin2 = .6;
    const double lmax1 = lmin1;

    size_t iterates;
    double* xArea;
    double* lmin;
    double* lmax;
    double* temp;
    double* bands;

    perturbStruct(const size_t a, const size_t b, const double c );
    perturbStruct(const size_t a, const size_t b, const double c,
                  const double e, const double h, const size_t i);
    void lThermalMC();
    void lthermalDeterministic();
    void lthermalBands(const double PtolBand1);
    void cleanup();
    void cleanup2();
};

class parameterStr
{
public:
  class thermalAnalysisMethod::PopTea *poptea;
};


#endif // NUMERICAL_SETUP_H_INCLUDED