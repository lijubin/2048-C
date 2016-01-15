//
//  main.c
//  2048程序
//
//  Created by 李居彬 on 15/6/15.
//  Copyright (c) 2015年 ljb. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "Root.h"

int maxNum = 0;//最大值
int score = 0;//当前得分
int hisScore = 0;//历史最高分

int main(int argc, const char * argv[]) {
    int numbers[X][Y]={0};
    int * p = *numbers;
    randNum(p,1);//首次登陆显示两个随机数
    randNum(p,1);
    show(p);
    maxNum = selMax(p,&maxNum);
    read_file(&maxNum, &hisScore);
    showMain(numbers,p,&maxNum,&score,&hisScore);
    printf("max = %d\n",maxNum);
    
    return 0;
}

