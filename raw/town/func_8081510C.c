#include "common.h"

extern s32 D_80084D5C;

void func_8081510C(void *arg0) {
    void *temp_s1;

    temp_s1 = *(void **)((u8 *)arg0 + 0xC);
    if (*(s16 *)arg0 == 0) {
        if (*(u16 *)((u8 *)temp_s1 + 0x1A) & 8) {
            *(u16 *)((u8 *)arg0 - 2) =
                (u16)(*(u16 *)((u8 *)arg0 - 2) | 0x8000);
            D_80084D5C |= 0x8000;
        }
    }
}
