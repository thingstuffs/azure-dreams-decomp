#include "common.h"

extern u8 D_80020084[];
extern s32 D_80027F18[];
extern u8 D_80028570[];
extern s32 D_800287CC[];

extern void strcpy(void *, s32);
extern void strcat(void *, void *);
extern s32 firstfile2(void *, void *);
extern void *nextfile(void *);

s32 func_8002191C(void)
{
    u8 context[32];
    u8 *entry;
    s32 *setting;
    s32 count;

    count = 0;
    entry = D_80028570;
    setting = D_80027F18;
    if (D_800287CC[0] != 0) {
        setting++;
    }

    strcpy(context, *setting);
    strcat(context, D_80020084);

    if (firstfile2(context, D_80028570) != 0) {
        do {
            count++;
            entry += 40;
        } while (nextfile(entry) == entry);
    }

    return count;
}
