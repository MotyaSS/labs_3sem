#include <stdio.h>
#include "l4_5.h"
#include <string.h>
#include <stdlib.h>


int main(int argc, char** argv) {
    char* end;
    long long a = strtoll("-", &end, 10);
    
    execute(argc, argv);
}
