//
//  main.c
//  HaarWaveletTransform
//
//  Created by leo on 16-6-22.
//  Copyright (c) 2016年 leo. All rights reserved.
//
#include "stdafx.h"
#include "wavelet.h"

Wavelet::Wavelet()
{
	;
}

void Wavelet::Haar_transformation(unsigned char m_t[8][8]){
    double A[8][8];     //类型转换 char-> double
    double L[8][8] = {0.0};//临时变量
    double S[8][8] = {0.0};//临时变量
    double L2[4][4] = {0.0};
    double S2[4][4] = {0.0};
    double L3[2][2] = {0.0};
    double S3[2][2] = {0.0};
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++){
            A[i][j] = (double) m_t[i][j];
        }
    }
    //1级哈尔小波变换S = H * A * H_t
    for (int i = 0; i < 8; i++) {//L = H * A
        for (int j = 0; j < 8; j++){
            for (int k = 0; k < 8; k++) {
                L[i][j] += H[i][k] * A[k][j];
            }
        }
    }
    for (int i = 0; i < 8; i++) {//S = L * H_t
        for (int j = 0; j < 8; j++){
            for (int k = 0; k < 8; k++) {
                S[i][j] += L[i][k] * H_t[k][j];
            }
        }
    }
    //2级哈尔小波变换
    for (int i = 0; i < 4; i++) {//L = H * A
        for (int j = 0; j < 4; j++){
            for (int k = 0; k < 4; k++) {
                L2[i][j] += (H2[i][k] * S[k][j]);
            }
        }
    }
    for (int i = 0; i < 4; i++) {//S = L * H_t
        for (int j = 0; j < 4; j++){
            for (int k = 0; k < 4; k++) {
                S2[i][j] += L2[i][k] * H_t2[k][j];
            }
        }
    }
    for (int i = 0; i < 4; i++) {//写回S
        for (int j = 0; j < 4; j++){
            S[i][j] = S2[i][j];
        }
    }
    //3级哈尔小波变换
    for (int i = 0; i < 2; i++) {//L = H * A
        for (int j = 0; j < 2; j++){
            for (int k = 0; k < 2; k++) {
                L3[i][j] += H3[i][k] * S[k][j];
            }
        }
    }
    for (int i = 0; i < 2; i++) {//S = L * H_t
        for (int j = 0; j < 2; j++){
            for (int k = 0; k < 2; k++) {
                S3[i][j] += L3[i][k] * H_t3[k][j];
            }
        }
    }
    for (int i = 0; i < 2; i++) {//写回S
        for (int j = 0; j < 2; j++){
            S[i][j] = S3[i][j];
        }
    }
    
    for (int i = 0; i < 8; i++) {//类型转换 double -> int
        for (int j = 0; j < 8; j++){
            R[i][j] = (int)S[i][j];
        }
    }
}

void Wavelet::inverse_Harr_transformation(int r[8][8]){
    double B[8][8] = {0.0};
    double N[8][8] = {0.0};//临时变量
    double P[8][8] = {0.0};//临时变量
    double N2[4][4] = {0.0};//临时变量
    double P2[4][4] = {0.0};
    double N3[2][2] = {0.0};//临时变量
    double P3[2][2] = {0.0};
    
    for (int i = 0; i < 8; i++) {//类型转换 int -> double
        for (int j = 0; j < 8; j++){
            B[i][j] = (double)r[i][j];
        }
    }
    //逆3级哈尔小波变换
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++){
            for (int k = 0; k < 2; k++) {
                N3[i][j] += H_t3[i][k] * B[k][j];
            }
        }
    }
    //P = N * H
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++){
            for (int k = 0; k < 2; k++) {
                P3[i][j] += N3[i][k] * H3[k][j];
            }
        }
    }
    for (int i = 0; i < 2; i++) {//写回S
        for (int j = 0; j < 2; j++){
            B[i][j] = P3[i][j];
        }
    }
    //逆2级哈尔小波变换
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++){
            for (int k = 0; k < 4; k++) {
                N2[i][j] += H_t2[i][k] * B[k][j];
            }
        }
    }
    //P = N * H
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++){
            for (int k = 0; k < 4; k++) {
                P2[i][j] += N2[i][k] * H2[k][j];
            }
        }
    }
    for (int i = 0; i < 4; i++) {//写回S
        for (int j = 0; j < 4; j++){
            B[i][j] = P2[i][j];
        }
    }
    
    //逆1级哈尔小波变换 P = H_t * B * H
    //N = H_t * B
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++){
            for (int k = 0; k < 8; k++) {
                N[i][j] += H_t[i][k] * B[k][j];
            }
        }
    }
    //P = N * H
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++){
            for (int k = 0; k < 8; k++) {
                P[i][j] += N[i][k] * H[k][j];
            }
        }
    }
    
    
    for (int i = 0; i < 8; i++) {//类型转换 double -> unsigned char
        for (int j = 0; j < 8; j++){
            I[i][j] = (unsigned char) P[i][j];
        }
    }
}

/*

int main(int argc, const char * argv[]) {
    unsigned char t[8][8] = {0};
    
    for (int i = 0; i < 8; i++) {//随意地赋值
        for (int j = 0; j < 8; j++){
            t[i][j] = i*20;
        }
    }
    Haar_transformation(t);
    inverse_Harr_transformation(R);
    //printf("%c",I[0][0]);
    
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++){
            printf("%d ",R[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++){
            printf("%d ",(int)I[i][j]);
        }
        printf("\n");
    }
    //printf("Hello, World!\n");
    return 0;
}
*/