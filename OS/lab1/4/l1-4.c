#include <string.h>
#include "l1-4.h"
#include "../../../my_flag_lib.h"

st_code input(int argc, char* argv[]) {
  if (argc < 3) {
    return inv_argc;
  }

  FILE* stream = fopen(argv[1], "rb");

  if (stream == NULL) {
    return unknown_file;
  }

  const char* flag = argv[2] + 1;

  if (strcmp(flag, "xor8") == 0) {
    if (argc != 3) {
      return inv_argc;
    }
    printf("%d", xor8(stream));
  } else if (strcmp(flag, "xor32") == 0) {
    if (argc != 3) {
      return inv_argc;
    }
    printf("%d", xor32(stream));
  } else if (strcmp(flag, "mask") == 0) {
    if (argc != 4 ||) {
      return inv_argc;
    }

  }

  fclose(stream);
  return ok;
}

byte xor8(FILE* stream) {
  if (!stream) {
    return 0;
  }
  byte res = 0;
  int a;
  while ((a = fgetc(stream)) != EOF) {
    res = a ^ res;
  }

  return res;
}

byte4 xor32(FILE* stream) {
  if (!stream) {
    return 0;
  }

  byte4 res = 0;
  byte4 temp;
  while (fread(&temp, sizeof(byte4), 1, stream) == 1) {
    res = res ^ temp;
  }

  temp = 0;
  byte temp1;
  while (fread(&temp1, sizeof(byte), 1, stream) == 1) {
    temp = temp << 8;
    temp = temp | temp1;
  }
  res = res ^ temp;
  return res;
}

#include <stdlib.h>
#include <math.h>

ull search_for_mask(FILE* stream, const char* mask) {

  char* t_ptr = NULL;
  byte4 mask_bin = strtoul(mask, &t_ptr, 16);
  if (t_ptr != mask + strlen(mask)) {
    return -1;
  }

  byte4 cur_mask;
  byte byte_from_file;
  ull count = 0;
  while (fread(&byte_from_file, sizeof(byte), 1, stream) == 1) {
    cur_mask = cur_mask << 8;
    cur_mask = cur_mask | byte_from_file;

    if (cur_mask == mask_bin) {
      count++;
    }
  }
  return count;
}