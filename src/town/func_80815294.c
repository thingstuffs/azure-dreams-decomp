#include "common.h"

#ifndef NULL
#define NULL 0
#endif

extern void *func_800373DC();
extern u8 D_8052FEDC[];

void func_80815294(s16 arg0) {
    void *temp_v0;

    temp_v0 = func_800373DC(2);
    if (temp_v0 != NULL) {
        *(s32 *)((s8 *)temp_v0 + 0x10) = (s32)D_8052FEDC;
        *(s16 *)((s8 *)temp_v0 + 0x72) = arg0;
    }
}
