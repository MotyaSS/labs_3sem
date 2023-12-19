#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdarg.h>
#include "my_flag_lib.h"


bool if_flag(const char arg[]) {
    if (arg == NULL) {
        return false;
    }
    if (arg[0] != '-' && arg[0] != '/') {
        return false;
    }
    return true;
}

bool if_l(const char arg[]) {
    if (arg == NULL) {
        return false;
    }
    char temp1[80];
    if (strlen(arg) >= 80) {
        return false;
    }
    
    char* temp2 = NULL;
    strcpy(temp1, arg);
    temp2 = temp1;
    size_t len = strlen(arg);
    if (arg[0] == '-') {
        temp2 = temp1 + 1;
        len--;
    }
    
    long long number = 0;
    for (int i = 0; i < len; i++) {
        if (!isdigit(temp2[i])) {
            return false;
        }
        if (number > LONG_MAX / 10) {
            return false;
        }
        if (number == (LONG_MAX / 10) && (temp2[i] - '0') > (LONG_MAX % 10)) {
            return false;
        }
        number *= 10;
        number += temp2[i] - '0';
    }
    return true;
}

bool if_i(const char arg[]) {
    if (arg == NULL) {
        return false;
    }
    char temp1[80];
    if (strlen(arg) >= 80) {
        return false;
    }
    
    char* temp2;
    strcpy(temp1, arg);
    temp2 = temp1;
    size_t len = strlen(arg);
    if (arg[0] == '-') {
        temp2 = temp1 + 1;
        len--;
    }
    
    int number = 0;
    for (int i = 0; i < len; i++) {
        if (temp2[i] < '0' || temp2[i] > '9') {
            return false;
        }
        if (number > INT_MAX / 10) {
            return false;
        }
        if (number == (INT_MAX / 10) && (temp2[i] - '0') > (INT_MAX % 10)) {
            return false;
        }
        number *= 10;
        number += temp2[i] - '0';
    }
    return true;
}

bool if_u(const char arg[]) {
    if (arg == NULL) {
        return false;
    }
    char temp1[80];
    
    char* temp2;
    strcpy(temp1, arg);
    temp2 = temp1;
    
    int number = 0;
    for (int i = 0; arg[i] != 0; i++) {
        if (temp2[i] < '0' || temp2[i] > '9') {
            return false;
        }
        if (number > UINT_MAX / 10) {
            return false;
        }
        if (number == (UINT_MAX / 10) && (temp2[i] - '0') > (UINT_MAX % 10)) {
            return false;
        }
        number *= 10;
        number += temp2[i] - '0';
    }
    return true;
}

bool if_ll(const char arg[]) {
    if (arg == NULL || *arg == 0) {
        return false;
    }
    char temp1[80];
    if (strlen(arg) >= 80) {
        return false;
    }
    
    char* temp2;
    strcpy(temp1, arg);
    temp2 = temp1;
    size_t len = strlen(arg);
    if (arg[0] == '-') {
        if (arg[1] == 0) {
            return false;
        }
        temp2 = temp1 + 1;
        len--;
    }
    
    long long number = 0;
    for (int i = 0; i < len; i++) {
        if (temp2[i] < '0' || temp2[i] > '9') {
            return false;
        }
        if (number > LLONG_MAX / 10) {
            return false;
        }
        if (number == (LLONG_MAX / 10) && (temp2[i] - '0') > (LLONG_MAX % 10)) {
            return false;
        }
        number *= 10;
        number += temp2[i] - '0';
    }
    return true;
}

bool if_lf(const char arg[]) {
    if (arg == NULL) {
        return false;
    }
    char* endptr = NULL;
    strtod(arg, &endptr);
    if (endptr == arg + strlen(arg)) {
        return true;
    }
    return false;
}

void strcpy_without_first(const char cpy[], char var[]) {
    if (cpy == NULL) {
        return;
    }
    strcpy(var, (cpy + 1));
}

#include "stdio.h"


int close_files(int count, ...) {
    if (count <= 0) {
        return -1;
    }
    va_list ap;
    va_start(ap, count);
    for (int i = 0; i < count; i++) {
        FILE* file = va_arg(ap, FILE *);
        if (file) {
            fclose(file);
        }
    }
    va_end(ap);
    return 0;
}


int my_fgets(FILE* stream, char* buff, unsigned int cap) {
    
    if (stream == NULL) {
        return -1;
    }
    if (buff == NULL) {
        return -2;
    }
    
    int ch;
    while (isspace(ch = fgetc(stream)));
    
    if (feof(stream)) {
        return 1;
    }
    
    int cnt = 0;
    buff[cnt++] = ch;
    while ((ch = fgetc(stream)) != EOF && !isspace(ch) && cnt < cap - 1) {
        buff[cnt++] = ch;
    }
    buff[cnt] = '\0';
    if (cnt == cap - 1) {
        //skip rest letters of current lexema
        while ((ch = fgetc(stream)) != EOF && !isspace(ch));
        if (ch != EOF) {
            fseek(stream, -1, SEEK_CUR);
        }
    }
    return 0;
}