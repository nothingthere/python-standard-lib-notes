/*
  Gestalt匹配算法C实现
  Author: Claudio <3261958605@qq.com>
  Created: 2017-04-26 20:10:12
  Commentary:
  参考自：http://collaboration.cmc.ec.gc.ca/science/rpn/biblio/ddj/Website/articles/DDJ/1988/8807/8807c/8807c.htm
  以及：https://github.com/wernsey/miscsrc/blob/master/simil.c
*/
#include <ctype.h>
#include <stdio.h>
/* #include <stdlib.h> */
#include <string.h>

int simil(const char *str1, int len1, const char *str2, int len2);

int main(void) {
  char str1[80];
  char str2[80];
  int len1, len2;
  int matches = 0;

  printf("此程序展示Ratcliff/Obershelp模式匹配算法\n");
  printf("输入两个字符串，用空格分割\n");
  printf("显示两个字符串相似度\n");
  printf("输入'END'和'END'退出\n\n");
  do {
    printf("输入两个字符串，用空格隔开： ");
    scanf("%s %s", str1, str2);
    /* ucase(str1); */
    /* ucase(str2); */
    len1 = strlen(str1);
    len2 = strlen(str2);
    matches = simil(str1, len1, str2, len2);
    printf("相同字符数：%d\n", matches);
    printf("%s 和 %s 的相似度为： %d 。\n\n", str1, str2,
           (int)((matches * 200) / (len1 + len2)));
  } while (strcmp(str1, "END"));
}

int simil(const char *str1, int len1, const char *str2, int len2) {
  int max_matches = 0;       /* 当前匹配字符个数 */
  int left_max_matches = 0;  /* 左边匹配字符个数 */
  int right_max_matches = 0; /* 右边匹配字符个数 */
  int progress;              /* 内层循环中相同的字符数 */
  int i1, i2;                /* 字符串str1的内外层索引 */
  int j1, j2;                /* 字符串str2的内外层索引 */
  int k1, k2;                /* 如果有匹配时，匹配起始位置索引。用来进行左树和右树匹配 */
  k1 = k2 = 0;

  if (len1 <= 0 || len2 <= 0) {
    return 0;
  }

  for (i1 = 0; i1 < len1 - max_matches; i1++)
    for (i2 = 0; i2 < len2 - max_matches; i2++) {
      if (toupper(str1[i1]) == toupper(str2[i2])) {
        for (j1 = i1 + 1, j2 = i2 + 1;
             j1 < len1 && j2 < len2 && toupper(str1[j1]) == toupper(str2[j2]);
             j1++, j2++)
          ;
        progress = j1 - i1;
        /* printf("process: %d\n", progress); */
        /* printf("max_matches=%d\n", max_matches); */
        if (progress > 0 && progress > max_matches) {
          /* 更新最长匹配 */
          max_matches = progress;
          /* 获取最长匹配开始位置的索引 */
          k1 = i1;
          k2 = i2;
        }
      }
    }

  /* 完全没匹配 */
  if (max_matches == 0) {
    return 0;
  }

  /* 左树 */
  /* if (k1 > 0 && k2 > 0) { */
  /* printf("\n左树 k1=%d k2=%d\n", k1, k2); */
  left_max_matches = simil(str1, k1, str2, k2);
  /* printf("左树结果： %d\n\n", left_max_matches); */
  /* } */

  /* 右树 */

  str1 = str1 + k1 + max_matches;
  str2 = str2 + k2 + max_matches;
  len1 = len1 - k1 - max_matches;
  len2 = len2 - k2 - max_matches;

  /* printf("\n右树：str1=%s str2=%s len1=%d len2=%d\n", str1, str2, len1,
   * len2); */
  right_max_matches = simil(str1, len1, str2, len2);

  /* printf("右树结果：%d\n\n", right_max_matches); */

  /* printf("max_matches：%d\tleft_maxmatches: %d\tright_max_matches: %d\n", */
  /*        max_matches, left_max_matches, right_max_matches); */

  return max_matches + left_max_matches + right_max_matches;
}
