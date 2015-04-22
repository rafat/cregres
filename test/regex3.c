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

	N = 20;
	p = 3;
	// This is an example of polynomial regression
	// Brockwell and Davis US populaton example data from 1790-1980
	// p = 3 corresponds to one dependent variable (YY) and two independent variables (***)
	// YY = b0 + b1 * X + b2 * X * X + u
	// where u is residual vector of length N
	// YY, X and X*X are vectors each of length N = 20

	// (***) Even though X1 = X and X2 = X^2 , X1 and X2 are linearly independent

	// IMPORTANT - You may want to transform input data instead of using it as is.
	// For example YY can be scaled down or transformed to a log scale.
	// XX can be transformed to 1,2,3 instead of 1790,1800,1810 etc.
	// This example simply demonstrates the usage of polynomial regression.



	res2 = (double*)malloc(sizeof(double)* N);

	double XX[20] = { 1790, 1800, 1810, 1820, 1830, 1840, 1850, 1860, 1870, 1880,
		1890, 1900, 1910, 1920, 1930, 1940, 1950, 1960, 1970, 1980 };
	double YY[20] = { 3929214, 5308483, 7239881, 9638453, 12860702, 17063353, 23191876, 31443321, 38558371, 50189209, 62979766,
		76212168, 92228496, 106021537, 123202624, 132164569, 151325798, 179323175, 203302031, 226542203 };


	fit = reg_init(N, p);
	regress_poly(fit, XX, YY, res2, varcovar, alpha);// Perform Polynomial Regression
	// res2 - residuals vector. varcovar - variance-covariance matrix
	// alpha - Used to determine (1-alpha) * 100 % confidence interval
	// alpha = 0.05 for 95% confidence interval

	summary(fit); // summary of regression
	anova(fit); // ANOVA Table
	confint(fit); //Confidence Intervals of Regression Parameters
	zerohyp_val(fit, tval3, pval3); // Obtain Zerohypothesis t-test values

	double inpx[2] = { 1990, 1990 * 1990 };// Find population estimate for the year 1990
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
