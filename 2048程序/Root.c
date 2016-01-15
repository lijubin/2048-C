//
//  Root.c
//  2048程序
//
//  Created by 李居彬 on 15/6/16.
//  Copyright (c) 2015年 ljb. All rights reserved.
//

#include "Root.h"

void showMain(int (*numbers)[],int *p,int *maxNum,int *score,int *hisScore)
{
    int cond=0;//循环条件
    int zt = 0;//状态
    char gesture[2];//滑动指令
    do {
        printf("W(上)、S(下)、A(左)、D(右)\n");
        printf("MAX = %d\t当前得分=%d\t历史最高分=%d\n",*maxNum,*score,*hisScore);
        printf("指令:");
        scanf("%s",gesture);
        if (strcmp(gesture, "W") == 0
            || strcmp(gesture, "w") == 0
            || strcmp(gesture, "S") == 0
            || strcmp(gesture, "s") == 0
            || strcmp(gesture, "A") == 0
            || strcmp(gesture, "a") == 0
            || strcmp(gesture, "D") == 0
            || strcmp(gesture, "d") == 0) {
            zt = changeXY(numbers,gesture,score,hisScore);
            if (zt == 1) {
                randNum(p,1);
                show(p);
                
                int cd = selMax(p,maxNum);
                //存储最大值和历史最高分
                if (*score > *hisScore
                    || cd > *maxNum) {
                    *maxNum = cd;
                    write_file(maxNum,score);//保存历史最高分
                }
                
            }else if(zt == -1) {
                if(isEnd(numbers) == 0) {
                    printf("game over!\n");
                    cond = 1;
                }
            }
        }else{
            printf("指令有误!\n");
        }
    } while (cond == 0);
}

/*
 返回值 -1 无可随机位置
 返回值 0 正常
 参数 index = 0 校验是否结束
 参数 index = 1 生成随机数
 */
int randNum(int *p,int index)//index 判断是否生产随机数，
{
    srand((unsigned)time(0));
    int nums[X*Y]={0};
    int z = 0;//可用位置存储
    int z1 = 0;//是否有可用位置
    int baseNum = 0;//基数
    for (int i = 0; i < X*Y; i++) {
        if (*(p+i) == 0) {
            nums[z] = i;
            z++;
            z1 = 1;
        }
    }
    if (z1 == 0) {
        return -1;
    }
    //index = 0 校验是否结束
    //index = 1 生成随机数
    if (index == 1) {
        int location = 0;//位置
        location = rand()%z;
        baseNum = (rand()%2+1)*2;//随机2、4
        *(p+nums[location]) = baseNum;
    }
    return 0;
}

/*
 返回值  isChange  0 1 －1
 -1 无可移动需要判断是否结束
 0 无可移动
 1 移动完成
 */
int changeXY(int (*p)[Y],char gest[],int *score,int *hisScore)
{
    int i = 0;
    int isChange = 0;//是否移动过;
    do{
        if (strcmp(gest, "W") == 0
            || strcmp(gest, "w") == 0) {
            for (int i = 1; i < X; i++) {
                for (int j = 0; j < Y; j++) {
                    if (*(*(p+i)+j) == *(*(p+i-1)+j)
                        && *(*(p+i)+j) != 0) {
                        *(*(p+i-1)+j) = *(*(p+i-1)+j) * 2;
                        *(*(p+i)+j) = 0;
                        isChange = 1;
                        *score += *(*(p+i-1)+j);
                    }else if (*(*(p+i-1)+j) == 0
                              && *(*(p+i)+j) != 0) {
                        *(*(p+i-1)+j) = *(*(p+i)+j);
                        *(*(p+i)+j) = 0;
                        isChange = 1;
                    }
                }
            }
        }else if (strcmp(gest, "A") == 0
                  || strcmp(gest, "a") == 0) {
            for (int j = 1; j < Y; j++) {
                for (int i = 0; i<X; i++) {
                    if (*(*(p+i)+j) == *(*(p+i)+j-1)
                        && *(*(p+i)+j) != 0) {
                        *(*(p+i)+j-1) = *(*(p+i)+j-1) * 2;
                        *(*(p+i)+j) = 0;
                        isChange = 1;
                        *score += *(*(p+i)+j-1);
                    }else if (*(*(p+i)+j-1) == 0
                              && *(*(p+i)+j) != 0) {
                        *(*(p+i)+j-1) = *(*(p+i)+j);
                        *(*(p+i)+j) = 0;
                        isChange = 1;
                    }
                }
            }
        }else if (strcmp(gest, "D") == 0
                  || strcmp(gest, "d") == 0) {
            for (int j = Y-2; j >= 0; j--) {
                for (int i = X-1; i>=0; i--) {
                    if (*(*(p+i)+j) == *(*(p+i)+j+1)
                        && *(*(p+i)+j) != 0) {
                        *(*(p+i)+j+1) = *(*(p+i)+j+1) * 2;
                        *(*(p+i)+j) = 0;
                        isChange = 1;
                        *score += *(*(p+i)+j+1);
                    }else if (*(*(p+i)+j+1) == 0
                              && *(*(p+i)+j) != 0) {
                        *(*(p+i)+j+1) = *(*(p+i)+j);
                        *(*(p+i)+j) = 0;
                        isChange = 1;
                    }
                }
            }
        }else{
            for (int i = X-2; i >= 0; i--) {
                for (int j = Y - 1; j >= 0; j--) {
                    if (*(*(p+i)+j) == *(*(p+i+1)+j)
                        && *(*(p+i)+j) != 0) {
                        *(*(p+i+1)+j) = *(*(p+i+1)+j) * 2;
                        *(*(p+i)+j) = 0;
                        isChange = 1;
                        *score += *(*(p+i+1)+j);
                    }else if (*(*(p+i+1)+j) == 0
                              && *(*(p+i)+j) != 0) {
                        *(*(p+i+1)+j) = *(*(p+i)+j);
                        *(*(p+i)+j) = 0;
                        isChange = 1;
                    }
                }
            }
        }
        i++;
    }while(i < 3);
    if (isChange == 0) {
        isChange = randNum(*p,0);
    }
    
    return isChange;
}

int selMax(int *p,int *max)
{
    for (int i = 0; i < X*Y; i++) {
        *max = *(p+i) > *max ?*(p+i):*max;
    }
    return *max;
}

//返回值 0 结束，1，正常
int isEnd(int (*p)[Y])
{
//    int i = 0;
    int isEnd = 0;//是否结束
//    do{
        //W
        for (int i = 1; i < X; i++) {
            for (int j = 0; j < Y; j++) {
                if (*(*(p+i)+j) == *(*(p+i-1)+j)
                    && *(*(p+i)+j) != 0) {
                    isEnd = 1;
                }else if (*(*(p+i-1)+j) == 0
                          && *(*(p+i)+j) != 0) {
                    isEnd = 1;
                }
            }
        }
        //A
        for (int j = 1; j < Y; j++) {
            for (int i = 0; i<X; i++) {
                if (*(*(p+i)+j) == *(*(p+i)+j-1)
                    && *(*(p+i)+j) != 0) {
                    isEnd = 1;
                }else if (*(*(p+i)+j-1) == 0
                          && *(*(p+i)+j) != 0) {
                    isEnd = 1;
                }
            }
        }
        //D
        for (int j = Y-2; j >= 0; j--) {
            for (int i = X-1; i>=0; i--) {
                if (*(*(p+i)+j) == *(*(p+i)+j+1)
                    && *(*(p+i)+j) != 0) {
                    isEnd = 1;
                }else if (*(*(p+i)+j+1) == 0
                          && *(*(p+i)+j) != 0) {
                    isEnd = 1;
                }
            }
        }
        //S
        for (int i = X-2; i >= 0; i--) {
            for (int j = Y - 1; j >= 0; j--) {
                if (*(*(p+i)+j) == *(*(p+i+1)+j)
                    && *(*(p+i)+j) != 0) {
                    isEnd = 1;
                }else if (*(*(p+i+1)+j) == 0
                          && *(*(p+i)+j) != 0) {
                    isEnd = 1;
                }
            }
        }
//        i++;
//    }while(i < 3);
    
    return isEnd;
}

void show(int *p)
{
    for (int i = 0; i < X*Y; i++) {
        if(i % 4 == 0) printf("\n");
        if (*(p+i) > 0) {
            printf("%d\t",*(p+i));
        }else{
            printf(".\t");
        }
    }
    printf("\n");
}

void write_file(int *max,int *hisScore)
{
    FILE * fp = NULL;
    fp = fopen("2048Root.dat", "w");
    if(!fp) {
        return;
    }
    fwrite(max, sizeof(int), 1, fp);
    fwrite(hisScore, sizeof(int), 1, fp);

    fclose(fp);
}

void read_file(int *max,int *hisScore)
{
    FILE * fp = NULL;
    fp = fopen("2048Root.dat", "r");
    if(!fp) {
        return;
    }
    fread(max, sizeof(int), 1, fp);
    fread(hisScore, sizeof(int), 1, fp);
    
    fclose(fp);
}