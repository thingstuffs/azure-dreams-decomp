#include "common.h"

extern u8 D_80020084[];
extern s32 D_80027F18[];
extern u8 D_80028570[];
extern s32 D_800287CC[];

extern void strcpy(void *, s32);
extern void strcat(void *, void *);
extern s32 firstfile2(void *, void *);
extern void *nextfile(void *);

/* Collect directory entries matching the selected search path and return their count. */
s32 func_8002191C(void)
{
    u8 search_path[32];
    u8 *dir_entry;
    s32 *path_ptr;
    s32 file_count;

    file_count = 0;
    dir_entry = D_80028570;
    path_ptr = D_80027F18;
    if (D_800287CC[0] != 0) {
        path_ptr++;
    }

    strcpy(search_path, *path_ptr);
    strcat(search_path, D_80020084);

    if (firstfile2(search_path, D_80028570) != 0) {
        do {
            file_count++;
            dir_entry += 40;
        } while (nextfile(dir_entry) == dir_entry);
    }

    return file_count;
}
