#ifndef CREGRES_H_
#define CREGRES_H_


#ifdef __cplusplus
extern "C" {
#endif

typedef struct bparam_t {
	double value;
	double lower;
	double upper;
	double stdErr;
} bparam;

typedef struct reg_set* reg_object;

reg_object reg_init(int N, int p);

struct reg_set{
	int N;
	int p;
	double alpha;
	double sigma;
	double sigma_lower;
	double sigma_upper;
	double r2;
	double r2adj;
	double R2[2];
	int df;
	int intercept;
	double TSS;
	double ESS;
	double RSS;
	int df_ESS;
	int df_RSS;
	double FStat;
	double PVal;
	bparam beta[1];
};
// Stats

double mean(double* vec, int N);

double var(double* vec, int N);

// N length of the time series
// M Length of the covariance/correlation vector. The maximum lag is M-1 or N-1 , whichever is smaller.

void autocovar(double* vec, int N, double* acov, int M);

void autocorr(double* vec, int N, double* acorr, int M);

// Probability Distributions (pdf,cdf and inverse cdf)

// 1. Normal Distribution

double normalpdf(double x, double mu, double sigma);

double normalcdf(double x, double mu, double sigma);

double normalinv(double p, double mu, double sigma);

// 2. Student's T Distribution

double tpdf(double t, int df);

double tcdf(double t, int df);

double tinv_appx(double p, int df);

double tinv(double p, int df);

// 3. F Distribution

double fpdf(double x, int k1, int k2);

double fcdf(double x, int k1, int k2);

double finv(double p, int k1, int k2);

// 4. Gamma Distribution

double gammapdf(double x, double k, double th);

double gammacdf(double x, double k, double th);

double gammainv(double p, double k, double th);

// 5. Chi-squared Distribution

double chipdf(double x, int df);

double chicdf(double x, int df);

double chiinv(double p, int df);

void linreg_clrm(double *x,double *y, int N, double* b,
	double *var,double *res,double alpha,double *anv,
	double* ci_lower, double* ci_upper);

void zerohyp_clrm(int N, double *b, double *val, double *tval, double *pval);

//void linreg_multi2(int p, double *x,double *y, int N, double* b); // p number of variables.
// p = 2 for one dependent variable	and one independent variable
// p = 3 for one dependent variable	and two independent variables etc.

void linreg_multi(int p, double *xi,double *y, int N, double* b,double *sigma2,
			double *xxti,double *R2,double *res,double alpha,double *anv,
			double* ci_lower, double* ci_upper, int intercept);

void zerohyp_multi(int N, double *b, int p, double *varcovar, double *tval, double *pval);

void regress(reg_object obj, double *x, double *y, double *res, double *varcovar, double alpha);

void regress_poly(reg_object obj, double *x, double *y, double *res, double *varcovar, double alpha);

void setIntercept(reg_object obj,int intercept);

void summary(reg_object obj);

void anova(reg_object obj);

void confint(reg_object obj);

void zerohyp_val(reg_object obj, double *tval, double *pval);

double pointpredict(reg_object obj, double *inp, double *varcovar, double *var);

void free_reg(reg_object object);

#ifdef __cplusplus
}
#endif


#endif /* CREGRES_H_ */
