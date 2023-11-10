#include <stdio.h>
#include "l3-10.h"


typedef enum {
  ok,
  argc_invalid,
  bad_alloc,
  input_invalid,
  file_invalid
} st_code;

st_code execute(int argc, char* argv[]) {
  if (argc != 3) {
    return argc_invalid;
  }

  FILE* in = fopen(argv[1], "r");
  if (!in) {
    return file_invalid;
  }
  FILE* out = fopen(argv[2], "w");
  if (!out) {
    fclose(in);
    return file_invalid;
  }
  String str;
  if (string_init(&str, 10) != 0) {
    fclose(in);
    fclose(out);
    return bad_alloc;
  }
  Tree tree;
  while (!feof(in)) {
    int code = getline(&str, in);
    if (code != get_str_ok) {
      fclose(in);
      fclose(out);
      if (code == get_str_bad_alloc) {
        return bad_alloc;
      }
      return input_invalid;
    }
    code = tree_create(&tree, &str);
    if (code != 0) {
      tree_destroy(&tree);
      fclose(in);
      fclose(out);
      if (code > 0) {
        return bad_alloc;
      }
      return input_invalid;
    }
    str_fprint(&str, out);
    fputc('\n', out);
    print_tree(&tree, out);
    tree_destroy(&tree);
  }
  fclose(in);
  fclose(out);
  return ok;
}

int main(int argc, char* argv[]) {
  switch (execute(argc, argv)) {
    case ok:
      printf("All went ok\n");
      break;
    case argc_invalid:
      printf("Argument count invalid\n");
      break;
    case file_invalid:
      printf("File invalid\n");
      break;
    case input_invalid:
      printf("Invalid input detected\n");
      break;
    case bad_alloc:
      printf("Allocation issues\n");
  }
}
