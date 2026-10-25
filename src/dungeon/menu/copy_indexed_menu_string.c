#include "dungeon/menu/entries.h"
extern char *strcpy(char *destination, const char *source);

char *copy_indexed_menu_string(char *resource, s32 index, s32 unused_data, s32 unused_size) {
    strcpy(resource, D_8002946C[index]);
    return resource;
}
