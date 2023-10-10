#include <stdio.h>
#include <stdlib.h>
typedef enum {
  ok,
  inv_argc,
  cant_open_file
} st_code;

int print_all_file(FILE* stream) {
  printf("Empty:  _ptr: %p, _base: %p, _bufsiz: %d, _charbuf: %d, _cnt: %d, _file: %d, _flag: %d\n", stream->_ptr,
         stream->_base,
         stream->_bufsiz, stream->_charbuf,
         stream->_cnt, stream->_file, stream->_flag);
  char buff[1];
  do {
    fread(buff, sizeof(char), 1, stream);
    printf("%c: _ptr: %p, _base: %p, _bufsiz: %d, _charbuf: %d, _cnt: %d, _file: %d, _flag: %d\n", buff[0],
           stream->_ptr,
           stream->_base,
           stream->_bufsiz, stream->_charbuf,
           stream->_cnt, stream->_file, stream->_flag);
  } while (!feof(stream));
  return 0;
}

int print_n_bytes_from_file(FILE* stream, int n) {
  char* buff = (char*)malloc(sizeof(char) * (n + 1));
  if(buff == NULL) {
    return -1;
  }
  fread(buff, sizeof(char), n, stream);
  buff[n] = 0;
  printf("Buff after shifting for %d bytes: %s\n", n,buff);
  return 0;
}

int fill_file(FILE* stream) {
  char buff[11] = "3141592653";
  fwrite(buff, sizeof(char), 10, stream);
  return 0;
}

st_code execute(char* filename) {

  FILE* stream = fopen(filename, "w");
  if (stream == NULL) {
    return cant_open_file;
  }
  fill_file(stream);
  fclose(stream);

  stream = fopen(filename, "r");
  if (stream == NULL) {
    return cant_open_file;
  }
  print_all_file(stream);
  fclose(stream);
  stream = fopen(filename, "r");
  fclose(stream);
  stream = fopen(filename, "r");
  if (stream == NULL) {
    return cant_open_file;
  }
  fseek(stream, 3, SEEK_SET);
  print_n_bytes_from_file(stream, 4);
  fclose(stream);
  return ok;
}

st_code input(int argc, char* argv[]) {
  if (argc != 2) {
    return inv_argc;
  }
  return execute(argv[1]);
}

int main(int argc, char* argv[]) {
  input(argc, argv);
}
