//
//  Root.h
//  2048程序
//
//  Created by 李居彬 on 15/6/16.
//  Copyright (c) 2015年 ljb. All rights reserved.
//

#ifndef ___048____Root__
#define ___048____Root__
#define X 4
#define Y 4

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int randNum(int *p,int index);
int changeXY(int (*p)[Y],char gest[],int *max,int *hisScore);
int isEnd(int (*p)[Y]);
void show(int *p);
int selMax(int *p,int *max);
void showMain(int (*numbers)[],int *p,int *maxNum,int *score,int *hisScore);
void write_file(int *max,int *hisScore);
void read_file(int *max,int *hisScore);

#endif /* defined(___048____Root__) */
