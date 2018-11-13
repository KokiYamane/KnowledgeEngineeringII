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
    sprintf(writefilename, "averagedata/mean%02d.txt", i+1);

    // 出力ファイル読み込み
    FILE *wfp;
    wfp = fopen(writefilename, "w");
    if(wfp == NULL) {
      printf("can't open tha write file.\n");
      exit(1);
    }

    // 平均特徴量
    int add[DATASIZE] = {0};

    // 入力データ読み込み
    for(int j = 0; j < DATANUM; j++) {
      for(int k = 0; k < DATASIZE; k++) {
        int tmp;
        fscanf(rfp, "%d", &tmp);
        add[k] += tmp; 
      }
    }

    //出力
    for(int k = 0; k < DATASIZE; k++) {
      fprintf(wfp, "%d\n", add[k] / DATANUM);
    }

    fclose(rfp);
    fclose(wfp);
  }
}
