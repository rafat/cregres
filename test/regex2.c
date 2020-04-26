#include <stdio.h>
#include <stdlib.h>
#include "../header/cregres.h"

int main(void) {
	int N, p;
	double alpha;
	double *res2;
	reg_object fit;

	double varcovar[9] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
	alpha = 0.05;

	double tval3[3] = { 0.0, 0.0, 0.0 };
	double pval3[3] = { 0.0, 0.0, 0.0 };
	/*
	TABLE C.4 PER CAPITA PERSONAL CONSUMPTION EXPENDITURE (PPCE) AND PER CAPITA
	PERSONAL DISPOSABLE INCOME (PPDI) IN THE UNITED STATES, 1956�1970,
	IN 1958 DOLLARS, Gujarati D, Basic Econometrics, 4th Ed. McGraw-Hill
	*/

	N = 15;
	p = 3;
	// p = 3 corresponds to number of coefficients (including the intercept) - b0, b1 , b2
	// YY = b0 + b1 * X1 + b2 * X2 + u
	// where u is residual vector of length N
	// contained in XX vector. where XX = [X1,X2] .
	// YY, X1 and X2 are each of length N = 15
	// X1 = [1839,1844,1831,1881,1883,1910,1969,2016,2126,2239,2336,2404,
	//	2487,2535,2595]
	// X2 =[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]



	res2 = (double*)malloc(sizeof(double)* N);

	double XX[30] = { 1839, 1844, 1831, 1881, 1883, 1910, 1969, 2016, 2126, 2239, 2336, 2404,
		2487, 2535, 2595, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	double YY[15] = { 1673, 1688, 1666, 1735, 1749, 1756, 1815, 1867, 1948, 2048, 2128, 2165,
		2257, 2316, 2324 };


	fit = reg_init(N, p);
	setIntercept(fit,1);// Optional as default value for intercept is 1
	setLLSMethod(fit,"svd");
	regress(fit, XX, YY, res2, varcovar, alpha);// Perform Regression
	// res2 - residuals vector. varcovar - variance-covariance matrix
	// alpha - Used to determine (1-alpha) * 100 % confidence interval
	// alpha = 0.05 for 95% confidence interval

	summary(fit); // summary of regression
	anova(fit); // ANOVA Table
	confint(fit); //Confidence Intervals of Regression Parameters
	zerohyp_val(fit, tval3, pval3); // Obtain Zerohypothesis t-test values

	double inpx[2] = { 2610, 16 };
	double varx[2] = { 0.0, 0.0 };
	double oupx;

	oupx = pointpredict(fit, inpx, varcovar, varx); // Fit Values. Returns output
	// for a given (p-1) input vector.
	// varx[0] - Variance of Mean Prediction
	// varx[1] - Variance Of Individual Prediction

	printf("Output %lf , Variance(Mean Pred) %lf , Variance(Indiv. Pred) %lf \n", oupx, varx[0], varx[1]);

	free_reg(fit);
	free(res2);

	return 0;

}
