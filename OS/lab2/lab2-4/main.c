#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef unsigned long long ull;

typedef enum {
    OK,
    INV_INPUT,
    INV_FILE,
    BAD_ALLOC,
    PROC_ERR
} st_code;

void print_error(st_code code) {
    switch (code) {
        case OK:
            return;
        case INV_INPUT:
            printf("Invalid input\n");
            return;
        case INV_FILE:
            printf("File cannot be opened\n");
            return;
        case BAD_ALLOC:
            printf("Memory lack error occurred\n");
            return;
        case PROC_ERR:
            printf("An error occurred while creating a process\n");
            return;
        default:
            printf("Unexpected error occurred\n");
            return;
    }
}

st_code handle_file(char* path, char* pattern, int* has_occ) {
    FILE* input = fopen(path, "r");
    if (input == NULL) {
        return INV_FILE;
    }

    ull buf_size = strlen(pattern);
    if (buf_size == 0) {
        return INV_INPUT;
    }

    char* buf = (char*) malloc(sizeof(char) * (buf_size + 1));
    if (buf == NULL) {
        fclose(input);
        return BAD_ALLOC;
    }

    int ch = ' ';
    buf[buf_size] = '\0';
    for (int i = 0; i < buf_size; ++i) {
        ch = getc(input);
        if (ch != EOF) {
            buf[i] = ch;
        } else {
            fclose(input);
            free(buf);
            *has_occ = 0;
            return OK;
        }
    }

    while (ch != EOF) {
        if (!(strcmp(buf, pattern))) {
            *has_occ = 1;
            return OK;
        }

        ch = getc(input);
        for (int i = 1; i < buf_size; ++i) {
            buf[i - 1] = buf[i];
        }
        buf[buf_size - 1] = ch;
    }

    fclose(input);
    free(buf);
    *has_occ = 0;
    return OK;
}

st_code get_paths(char* main_path, ull* path_cnt, char*** paths) {
    FILE* main_file = fopen(main_path, "r");
    if (main_file == NULL) {
        return INV_FILE;
    }

    ull size = 2;
    ull all_cnt = 0;
    char** all_paths = (char**) malloc(sizeof(char*) * size);
    if (all_paths == NULL) {
        fclose(main_file);
        return BAD_ALLOC;
    }

    st_code error_flag = OK;
    int ch = ' ';
    while (ch != EOF && error_flag == OK) {
        ull path_size = 2;
        ull path_len = 0;
        char* path = (char*) malloc(sizeof(char) * path_size);
        if (path == NULL) {
            error_flag = BAD_ALLOC;
        }

        ch = fgetc(main_file);
        while ((ch != '\n' && ch != EOF) && error_flag == OK) {
            if (path_len + 1 == path_size) {
                path_size *= 2;
                char* tmp = (char*) realloc(path, sizeof(char) * path_size);
                if (tmp == NULL) {
                    error_flag = BAD_ALLOC;
                } else {
                    path = tmp;
                }
            }
            if (error_flag == OK) {
                path[path_len++] = ch;
            }
            ch = fgetc(main_file);
        }

        if (error_flag == OK) {
            path[path_len] = '\0';

            if (all_cnt == size) {
                size *= 2;
                char** tmp = (char**) realloc(all_paths, sizeof(char*) * size);
                if (tmp == NULL) {
                    error_flag = BAD_ALLOC;
                } else {
                    all_paths = tmp;
                }
            }
            if (error_flag == OK) {
                all_paths[all_cnt++] = path;
            }
        }
    }

    if (error_flag != OK) {
        for (int i = 0; i < all_cnt; ++i) {
            if (all_paths[i] != NULL) {
                free(all_paths[i]);
            }
        }
        free(all_paths);
        fclose(main_file);
        return error_flag;
    }

    *path_cnt = all_cnt;
    *paths = all_paths;
    return OK;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        print_error(INV_INPUT);
        return INV_INPUT;
    }

    ull path_cnt;
    char** paths;
    st_code paths_code = get_paths(argv[1], &path_cnt, &paths);
    if (paths_code != OK) {
        print_error(paths_code);
        return paths_code;
    }

    pid_t pid = 1;
    for (ull i = 0; i < path_cnt && pid != 0; ++i) {
        pid = fork();
        if (pid == -1) {
            print_error(PROC_ERR);
            return PROC_ERR;
        } else if (pid == 0) {
            int has_occ = 0;
            st_code code;
            if ((code = handle_file(paths[i], argv[2], &has_occ)) != OK) {
                printf("While processing the file %llu occurred an error:\n", i + 1);
                print_error(code);
            } else if (has_occ) {
                printf("File %llu contains the pattern\n", i + 1);
            } else {
                printf("File %llu does not contain the pattern\n", i + 1);
            }
        }
    }
}