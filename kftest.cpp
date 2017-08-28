
/*
 * FileName : test_kalman_filter.c
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : 2014/9/25 8:34:29
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#include <stdio.h>

#include "Matrix.h"
//#include "kf.h"
#include "free_test07.h"


int main(void)    
{
	int i = 0,data_len;
    float *datax = NULL;
	float *datay = NULL;
	float *datavx = NULL;
	float *datavy = NULL;
    /* For 2 Dimension */
    float init_x[4];
    float init_p[4][4] = {
				{ 0, 0, 0, 0}, 
				{ 0, 0, 0, 0},
				{ 0, 0, 0, 0}, 
				{ 0, 0, 0, 0}
				};
	float init_a[4][4] = {
				{ 1, 0, 1, 0}, 
				{ 0, 1, 0, 1},
				{ 0, 0, 1, 0}, 
				{ 0, 0, 0, 1}
				};
	float init_q[4][4] = {
				{ 0.001, 0, 0, 0}, 
				{ 0, 0.001, 0, 0},
				{ 0, 0, 0.001, 0}, 
				{ 0, 0, 0, 0.001}
				};
    float out1 = 0;
	float out2 = 0;
    float out3 = 0;
	float out4 = 0;

    datax = x1;
	datay = x2;
	datavx =x3;
	datavy =x4;
    data_len = sizeof(x1)/sizeof(float);

    // 2 dimension
    init_x[0] = datax[0];
    init_x[1] = datay[0];
	init_x[2] = datavx[0];
	init_x[3] = datavy[0];
    Matrix A(4,4),P(4,4),Q(4,4),H(2,4),R(2,2),K(4,2),X(4,1),X_old(4,1),P_old(4,4);
    for(size_t i=0; i<X.rows(); i++)
	{
		X[i][0]= init_x[i];
	}
	
    for(size_t i=0; i<P.rows(); i++)
	{
		for(size_t j=0; j<P.cols();j++)
		{
			P[i][j]= init_p[i][j];
		}
	}
    //state->A       = {{1, 0.1}, {0, 1}};
	 for(size_t i=0; i<P.rows(); i++)
	{
		for(size_t j=0; j<P.cols();j++)
		{
			A[i][j]= init_a[i][j];
		}
	}
    //state->H       = {1,0};
    H[0][0]  = 1;
    H[0][1]  = 0;
	H[0][2]  = 0;
	H[0][3]  = 0;
	H[1][0]  = 0;
    H[1][1]  = 1;
	H[1][2]  = 0;
	H[1][3]  = 0;

    //state->q       = {{10e-6,0}, {0,10e-6}};  /* measure noise convariance */
	 for(size_t i=0; i<P.rows(); i++)
	{
		for(size_t j=0; j<P.cols();j++)
		{
			Q[i][j]= init_q[i][j];
		}
	}

    R[0][0]   = 2;  /* estimated error convariance */
    R[0][1]   = 0;
	R[1][0]   = 0;
	R[1][1]   = 2;
    //printf("%d %d %d\n", data, data_len-2, data_len-2);
	
    for (i=2; i<data_len; i++) {
		
  // Filter start from 2
        printf("%.2f", datax[i]);      // Original data
        /* 2 dimension */
        /*out2 = kalman2_filter(init_x, init_p, data[i]);*/
		Matrix Z(2,1);
		Z[0][0] = datax[i];
		Z[1][0] = datay[i];

		X_old=operator*(A,X);
		Matrix A_trans(4,4),H_trans(4,2);
		A_trans=trans(A);
		H_trans=trans(H);
		P_old=operator+(operator*(operator*(A,P),A_trans),Q);
		K=operator*(operator*(P_old,H_trans),inverse(operator+(operator*(operator*(H,P_old),H_trans),R)));
		X=operator+(X_old,operator*(K,operator-(Z,operator*(H,X_old))));
		P=operator-(P_old,operator*(operator*(K,H),P_old));
		X_old = X;
		P_old = P;
		out1 = X[0][0];
        printf(" %.2f  ", out1);  // Filter result
		out2 = X[1][0];
		printf(" %.2f   ", out2);  // Filter result
		out3 = X[2][0];
		printf(" %.2f   ", out3);  // Filter result
		out4 = X[3][0];
		printf(" %.2f\n", out4);  // Filter result
	}
	system ("PAUSE");
    return 0;


}

