#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define __USE_MISC
#include <sys/stat.h>
#include <dirent.h>

#define ARRAY_LEN(arr) (sizeof((arr)) / sizeof(*(arr)))

#define COLOR_RED           "\33[31m"
#define COLOR_BLUE          "\33[34m"
#define COLOR_PURPLE        "\33[35m"
#define COLOR_GRAY          "\33[90m"
#define COLOR_CYAN          "\33[36m"
#define COLOR_YELLOW        "\33[33m"
#define COLOR_WHITE         "\33[97m"
#define COLOR_GREEN         "\33[32m"
#define COLOR_BLUE_HIGH     "\33[94m"
#define COLOR_YELLOW_HIGH   "\33[93m"
#define COLOR_PURPLE_HIGH   "\33[95m"
#define COLOR_BOLD          "\33[1m"
#define COLOR_UNDERLINE     "\33[4m"
#define COLOR_ITALIC        "\33[3m"
#define COLOR_STRIKETHROUGH "\33[9m"
#define COLOR_END           "\33[0m"


static void print_filename(const char *filename, unsigned char type) {

    const char *color = NULL;
    switch (type) {
        case DT_DIR:
            color = COLOR_BLUE;
            break;
        default:
            color = COLOR_GREEN;
            break;
    }

    printf("%s%s%s%s\n", COLOR_BOLD, color, filename, COLOR_END);

}


static void traverse_dirs(const char *dirname, int depth) {
    DIR *dir = opendir(dirname);
    assert(dir != NULL);

    struct dirent *entry = NULL;
    while ((entry = readdir(dir)) != NULL) {
        const char *name = entry->d_name;

        if (strcmp(name, ".") && strcmp(name, "..")) {

            for (int _=0; _ < depth; ++_)
                printf("│   ");

            long pos = telldir(dir);
            bool is_last = readdir(dir) == NULL;
            rewinddir(dir);
            seekdir(dir, pos);

            if (is_last)
                printf("└── ");
            else
                printf("├── ");

            unsigned char type = entry->d_type;
            print_filename(name, type);

            if (entry->d_type == DT_DIR) {
                char namebuf[BUFSIZ] = { 0 };
                snprintf(namebuf, ARRAY_LEN(namebuf) - 1, "%s/%s", dirname, name);
                traverse_dirs(namebuf, depth+1);
            }
        }
    }

    closedir(dir);
}


int main(void) {

    const char *dir = ".";
    printf("%s%s%s%s\n", COLOR_BOLD, COLOR_BLUE, dir, COLOR_END);
    traverse_dirs(dir, 0);

    return 0;
}
