#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENUM   46    // ファイルの個数
#define DATASIZE 196    // 一文字の特徴データを構成する数値の個数
#define DATANUM  180    // 使用する文字特徴データの個数

void main(int argc, char *argv[])
{
  for(int i = 0; i < FILENUM; i++) {

    // ファイル名読み込み
    char readfilename[50];
    sprintf(readfilename, "sampledata/c%02d.txt", i+1);

    // 入力ファイル読み込み
    FILE *rfp;
    rfp = fopen(readfilename, "r");
    if(rfp==NULL) {
      printf("can't open tha read file.\n");
      exit(1);
    }

    // 出力ファイル名設定
    char writefilename[50] = "";
    sprintf(writefilename, "covariancedata/sigma%02d.txt", i+1);

    // 出力ファイル読み込み
    FILE *wfp;
    wfp = fopen(writefilename, "w");
    if(wfp == NULL) {
      printf("can't open tha write file.\n");
      exit(1);
    }

    int data[DATANUM][DATASIZE] = {0};
    int add[DATASIZE] = {0};
    double average[DATASIZE] = {0};
    double covariance[DATASIZE][DATASIZE] = {0};

    // 入力データ読み込み
    for(int j = 0; j < DATANUM; j++) {
      for(int k = 0; k < DATASIZE; k++) {
        fscanf(rfp, "%d", &data[j][k]);
        add[k] += data[j][k];
      }
    }

    // 平均特徴量算出
    for(int j = 0; j < DATASIZE; j++) {
      average[j] = add[j] / DATANUM;
    }

    // 共分散行列算出
    for(int j = 0; j < DATANUM; j++) {
      for(int k = 0; k < DATASIZE; k++) {
        for(int l = 0; l < DATASIZE; l++) {
          covariance[k][l] += data[j][k] * data[j][l];
        }
      }
    }
    for(int k = 0; k < DATASIZE; k++) {
      for(int l = 0; l < DATASIZE; l++) {
        covariance[k][l] /= DATANUM;
        covariance[k][l] -= (average[k] * average[l]);
        fprintf(wfp, "%f\n", covariance[k][l]);
      }
    }

    fclose(rfp);
    fclose(wfp);
  }
}
