#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

void listFiles(const char *path) {
    struct dirent *entry;
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        char fullpath[1024];
        struct stat fileStat;
        sprintf(fullpath, "%s/%s", path, entry->d_name);
        if (stat(fullpath, &fileStat) < 0) {
            perror("Error stat");
            closedir(dir);
            exit(EXIT_FAILURE);
        }
        printf("%-32s ", fullpath);
        if (S_ISREG(fileStat.st_mode)) {
            printf("Regular file\n");
        } else if (S_ISDIR(fileStat.st_mode)) {
            printf("Directory\n");
        } else if (S_ISLNK(fileStat.st_mode)) {
            printf("Symbolic link\n");
        } else if (S_ISFIFO(fileStat.st_mode)) {
            printf("FIFO/pipe\n");
        } else if (S_ISSOCK(fileStat.st_mode)) {
            printf("Socket\n");
        } else if (S_ISCHR(fileStat.st_mode)) {
            printf("Character device\n");
        } else if (S_ISBLK(fileStat.st_mode)) {
            printf("Block device\n");
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <directory1> <directory2> ... <directoryN>\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        printf("\t\t\tContents of \"%s\":\n", argv[i]);
        listFiles(argv[i]);
    }

    return 0;
}