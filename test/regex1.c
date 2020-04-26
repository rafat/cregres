#include <stdio.h>
#include <stdlib.h>
#include "../header/cregres.h"

int main(void) {
	int N, i, p;
	double alpha;
	double *X,*Y,*res2;

	reg_object fit;

	p = 2;// Total Number of variables. Simple Model -> Y = b0 + b1 * X + u with p = 2 ( two variables).

	double varcovar[4] = { 0.0, 0.0, 0.0, 0.0}; // Size p * p Variance Covariance Matrix
	alpha = 0.05;

	double tval3[2] = { 0.0, 0.0};// t values . Size p
	double pval3[2] = { 0.0, 0.0 };//p values . Size p. (Probabilities associated with each t value)

	FILE *ifp;
	double temp[10000];


	ifp = fopen("../data/Galton.txt","r");// Galton Child/Parent height dataset. Column 1 - Height of Child. Corresponding Column 2 - Height of Parent
	i = 0;
	if (!ifp) {
	printf("Cannot Open File");
	}
	while(!feof(ifp)) {
	fscanf(ifp,"%lf %lf \n",&temp[i],&temp[i+1]);
	i = i + 2;;
	}
	N = i/2;
	fclose(ifp);

	X = (double*)malloc(sizeof(double)* N);// Independent Variable. Size N
	Y = (double*)malloc(sizeof(double)* N);// Dependent Variable. Size N
	res2 = (double*)malloc(sizeof(double)* N);// residuals . Size N

	for (i = 0; i < N; ++i) {
		Y[i] = temp[2*i];// Height Of Child
		X[i] = temp[2*i + 1];// height of Parent
	}

	fit = reg_init(N, p);
	regress(fit, X, Y, res2, varcovar, alpha);// Perform Regression
	// res2 - residuals vector. varcovar - variance-covariance matrix
	// alpha - Used to determine (1-alpha) * 100 % confidence interval
	// alpha = 0.05 for 95% confidence interval

	/*
	Following functions are used to print various values and tables.
	Please don't use these functions in any industrial codes as printing to
	terminal incurs considerable cost. All of these values are available to
	you already after you run regression functions. See classes and functions
	*/
	summary(fit); // summary of regression
	anova(fit); // ANOVA Table
	confint(fit); //Confidence Intervals of Regression Parameters
	zerohyp_val(fit, tval3, pval3); // Print Zerohypothesis t-test values

	double inpx[1] = { 68.4 };
	double varx[2] = { 0.0, 0.0 };
	double oupx;

	oupx = pointpredict(fit, inpx, varcovar, varx); // Fit Values. Returns output
	// for a given (p-1) input vector.
	// varx[0] - Variance of Mean Prediction
	// varx[1] - Variance Of Individual Prediction

	printf("\nOutput %lf , Variance(Mean Pred) %lf , Variance(Indiv. Pred) %lf \n\n", oupx, varx[0], varx[1]);

	free_reg(fit);


	free(res2);
	free(X);
	free(Y);
	return 0;

}
