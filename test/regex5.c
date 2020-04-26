#include <stdio.h>
#include <stdlib.h>
#include "../header/cregres.h"

int main(void) {
	int N, p, intercept;
	double alpha;
	double *res2;
	char *llsmethod = "qr";

	N = 15;
	p = 3;
	intercept = 1;

	// p = 3 corresponds to one dependent variable (YY) and two independent variables
	// YY = b0 + b1 * X1 + b2 * X2 + u
	// where u is residual vector of length N
	// contained in XX vector. where XX = [X1,X2] .
	// YY, X1 and X2 are each of length N = 15
	// X1 = [1839,1844,1831,1881,1883,1910,1969,2016,2126,2239,2336,2404,
	//	2487,2535,2595]
	// X2 =[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]

	res2 = (double*)malloc(sizeof(double)* N);

	/*
	TABLE C.4 PER CAPITA PERSONAL CONSUMPTION EXPENDITURE (PPCE) AND PER CAPITA
	PERSONAL DISPOSABLE INCOME (PPDI) IN THE UNITED STATES, 1956�1970,
	IN 1958 DOLLARS, Gujarati D, Basic Econometrics, 4th Ed. McGraw-Hill
	*/


	double b2[3] = { 0.0, 0.0, 0.0 };// p = 3 Parameters
	double anv2[7] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };// Anova
	double low[4] = { 0.0, 0.0, 0.0,0.0 };// Lower limit for 3 parameters and Variance
	double up[4] = { 0.0, 0.0, 0.0,0.0 };// Upper limit for 3 parameters and Variance
	double tval2[3] = { 0.0, 0.0, 0.0 };// t values corresponding to the three parameters
	double pval2[3] = { 0.0, 0.0, 0.0 };// Probablities Associated with t values
	double sig2[1] = { 0.0 };
	double R2[2] = { 0.0, 0.0 };// R2 values R2[0] = R2. R2[1] = R2 adjusted
	double varcovar[9] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };// p * p Variance-Covariance Matrix
	alpha = 0.05;


	double XX[30] = { 1839, 1844, 1831, 1881, 1883, 1910, 1969, 2016, 2126, 2239, 2336, 2404,
		2487, 2535, 2595, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	double YY[15] = { 1673, 1688, 1666, 1735, 1749, 1756, 1815, 1867, 1948, 2048, 2128, 2165,
		2257, 2316, 2324 };

	linreg_multi(p, XX, YY, N, b2, sig2, varcovar, R2, res2, alpha, anv2, low, up,llsmethod,intercept);
	printf("Estimates Regression Parameters : Beta1 = %lf ,Beta 2 = %lf ,Beta 3 = %lf \n", b2[0], b2[1], b2[2]);
	printf("sigma2 = %lf , R^2 = %lf R^2 (Adj.) = %lf \n", sig2[0], R2[0], R2[1]);

	printf("Confidence Interval %lf \n", (1. - alpha) * 100.);
	printf("Beta1 : Lower Limit = %lf ,Upper Limit = %lf \n", low[0], up[0]);
	printf("Beta2 : Lower Limit = %lf ,Upper Limit = %lf \n", low[1], up[1]);
	printf("Beta3 : Lower Limit = %lf ,Upper Limit = %lf \n", low[2], up[2]);
	printf("Variance : Lower Limit = %lf ,Upper Limit = %lf \n", low[3], up[3]);

	zerohyp_multi(N, b2, p, varcovar, tval2, pval2);

	printf("Beta1 : T Value = %g ,P Value = %g \n", tval2[0], pval2[0]);
	printf("Beta2 : T Value = %g ,P Value = %g \n", tval2[1], pval2[1]);
	printf("Beta3 : T Value = %g ,P Value = %g \n", tval2[2], pval2[2]);

	printf("\n ANOVA : \n");
	printf("Regression :  df = %lf ,SS = %lf ,MSS = %lf ,F Stat = %lf \n", anv2[3], anv2[1], anv2[1] / anv2[3], anv2[5]);
	printf("Residual :  df = %lf ,SS = %lf ,MSS = %lf \n", anv2[4], anv2[2], anv2[2] / anv2[4]);
	printf("Total :  df = %lf ,SS = %lf  \n", anv2[3] + anv2[4], anv2[0]);
	printf("F pvalue = %g \n", anv2[6]);


	free(res2);

	return 0;

}

