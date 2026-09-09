#include "common.h"

void func_800B3DC4(void *arg0) {
    void **p;
    void **q;
    u8 *s1;
    u8 *s2;
    if (*((s32 *)(*(void ***)arg0) + 3) == 0) {
        void *dead0;
        void *dead1;

        p = *(void ***)((u8 *)arg0 + 0x5C);
        dead0 = *(void **)p;
        dead1 = *((void **)p + 1);
        q = dead0;
        p = dead1;
    } else {

        p = *(void ***)((u8 *)arg0 + 0x5C);
        q = *((void **)p + 1);
        p = *(void **)p;
    }
    {
        s1 = *((void **)q + 1);
        s2 = *((void **)p + 1);
        s1[0] = 0x80;
        s1[1] = 0x80;
        s1[2] = 0x80;
        s2[0] = 0x40;
        s2[1] = 0x40;
        s2[2] = 0x40;
    }
}
