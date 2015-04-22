#include <stdio.h>
#include <stdlib.h>
#include "../header/cregres.h"

int main(void) {
	int N;
	double alpha;
	double *res;
	double *b;

	N = 10;

	res = (double*)malloc(sizeof(double)* N);
	b = (double*)malloc(sizeof(double)* 2);

	//  Simple Model -> Y = b0 + b1 * X + u

	double X[10] = { 80, 100, 120, 140, 160, 180, 200, 220, 240, 260 };
	double Y[10] = { 70, 65, 90, 95, 110, 115, 120, 140, 155, 150 };
	double var[5] = { 0.0, 0.0, 0.0, 0.0, 0.0 };
	double anv[7] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
	double lower[3] = { 0.0, 0.0, 0.0 };
	double upper[3] = { 0.0, 0.0, 0.0 };
	double tval[2] = { 0.0, 0.0 };
	double pval[2] = { 0.0, 0.0 };
	alpha = 0.05;


	linreg_clrm(X, Y, N, b, var, res, alpha, anv, lower, upper);
	printf("Estimates Regression Parameters : Beta1 = %lf ,Beta 2 = %lf \n", b[0], b[1]);
	printf("Confidence Interval %lf \n", (1. - alpha) * 100.);
	printf("Beta1 : Lower Limit = %lf ,Upper Limit = %lf \n", lower[0], upper[0]);
	printf("Beta2 : Lower Limit = %lf ,Upper Limit = %lf \n", lower[1], upper[1]);
	printf("Variance : Lower Limit = %lf ,Upper Limit = %lf \n", lower[2], upper[2]);
	printf("%lf ,%lf %lf %lf %lf \n", var[0], var[1], var[2], var[3], var[4]);

	zerohyp_clrm(N, b, var, tval, pval);

	printf("Beta1 : T Value = %g ,P Value = %g \n", tval[0], pval[0]);
	printf("Beta2 : T Value = %g ,P Value = %g \n", tval[1], pval[1]);

	printf("\n ANOVA : \n");
	printf("Regression :  df = %lf ,SS = %lf ,MSS = %lf ,F Stat = %lf \n", anv[3], anv[1], anv[1] / anv[3], anv[5]);
	printf("Residual :  df = %lf ,SS = %lf ,MSS = %lf \n", anv[4], anv[2], anv[2] / anv[4]);
	printf("Total :  df = %lf ,SS = %lf  \n", anv[3] + anv[4], anv[0]);
	printf("F pvalue = %g \n", anv[6]);


	free(res);
	free(b);

	return 0;

}
