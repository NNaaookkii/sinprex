#include <stdio.h>
#define I 4
#define J 6
/*
シンプレックス表(例)
f:目的関数の最適値, a:係数, b:定数項, x:変数, λ:スラック変数
     |  x1  x2  λ1  λ2  λ3   b
---------------------------------
     | a00 a01 a02 a03 a04  -f
   λ1| a10 a11 a12 a13 a14  b1 
   λ2| a20 a21 a22 a23 a24  b2
   λ3| a30 a31 a32 a33 a34  b3
*/
void output(double l[I][J]){
    for(int i=0;i<I;i++){
        for(int j=0;j<J;j++){
            printf("%.1lf  ",l[i][j]);
        }
        printf("\n");
    }
    
}

int row_index(double l[I][J]){  //行の最小値の列を出力する関数
    int min_index=0;
    double min = l[0][0];
    for(int j=1;j<J;j++){
        if (min > l[0][j]){
            min = l[0][j];
            printf("%.1lf \n",min);
            min_index = j;
            printf("%d\n",j);///////////////////ここから
        }

    }
    return min_index;
}
int line_min (double l[I][J]){  //行の最小値を出力する関数
    double m = l[0][0];
    for(int j=1;j<J;j++){
        if (m > l[0][j]){
            m = l[0][j];
            
        }

    }
    return m;
}

int line_index(double list[I][J], int L){
    int K=1;
    double x, c = 0, C = 0;
    double count_a = 10000;
    for(int i=1;i<I;i++){
        if (list[i][L] == 0){
            continue;
        }
        else if(list[i][L] < 0){
            x = -list[i][L];
        }
        else{
            x = list[i][L];
        }
        // printf("%.1lf ",x);
        c = list[i][J-1];
        C = c / x;
        printf("%.1lf ", C);
        if (count_a > C){
            count_a = C;
            // printf("%.1lf ", count_a);
            K = i;
            // printf("%d ", K);
        }

    }
    printf("\n%d\n",K);
    return K;
}



int main(void){
    int min_max = 1; //最小化問題なら0, 最大化問題なら1
    double x1 =0.0, x2=0.0;
    double l[I][J] = {{-30, -20, 0, 0, 0, 0},  //最大化問題の場合は最小化問題に変換して入力
                      {2, 0, 1, 0, 0, 4},
                      {2, 1, 0, 1, 0, 8},
                      {0, 1, 0, 0, 1, 6}};
    output(l);
    while(1){
        int L = row_index(l);
        int K = line_index(l, L);

        double P = l[K][L];
        if (l[K][L] != 0){
            for(int a=0;a<J;a++){
                l[K][a] /= P;
                // printf("%.1lf ", l[K][a]);
            }
        }
        
        /*掃き出しを行う*/
        for(int i=0;i<I;i++){
            if (K == i){
                continue;
            }
            double xx = l[K][L]*(-l[i][L]);
            for(int j=0;j<J;j++){
                l[i][j] += l[K][j]*xx; 
            }
        
        }
        
        output(l);
        printf("\n");

        if (line_min(l) >= 0.0){
            break;
        }
        

        
    }
    for(int i=0;i<I;i++){
        if (l[i][0] == 1){
             x1 = l[i][J-1];
        }
        if(l[i][1] == 1){
             x2 = l[i][J-1];
        }
    }
    if(min_max == 0){
        printf("最適解はx1=%.1lf, x2=%.1lf, f=%.1lf", x1, x2, -l[0][J-1]);
    }
    else{
        printf("最適解はx1=%.1lf, x2=%.1lf, f=%.1lf", x1, x2, l[0][J-1]);

    }

}