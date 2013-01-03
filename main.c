// clang main.c xsha1.c -o xsha1test && ./xsha1test

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "xsha1.h"

int main(int argc, char** argv) {
  const char *testValue = "1234567890";
  uint32_t outbuff[5];
  xsha1_calcHashBuf(testValue, strlen(testValue), (uint32_t *)outbuff);
  printf("xsha1(\"%s\") == %08x%08x%08x%08x%08x\n", testValue, outbuff[0], outbuff[1], outbuff[2], outbuff[3], outbuff[4]);
  printf("xsha1(\"%s\") == 99f0fab8b5b4523e0d58e5efe126fa5f12633b4b\n", testValue);
  return 1;
}
