#include "common.h"

#include "common.h"

typedef struct S_80056558_85458 {
    /* 0x00 */ u8 pad00[0x10];
    /* 0x10 */ u16 f10;
    /* 0x12 */ u16 f12;
    /* 0x14 */ u8 pad14[0x44];
    /* 0x58 */ s32 f58;
    /* 0x5C */ u8 pad5c[0x10];
    /* 0x6C */ s16 f6c;
    /* 0x6E */ u8 pad6e[0x0A];
} S_80056558_85458;

extern s32 D_80073734[4];
extern S_80056558_85458 D_80085458[64];

extern s32 func_800563B0();

void func_80056558(void) {
    s32 i;
    S_80056558_85458 *p;
    s32 temp;
    s32 check;

    for (i = 0; i < D_80073734[0]; i++) {
        p = &D_80085458[i];
        check = p->f6c;
        __asm__ volatile("" : : "r"(check));
        temp = p->f58;
        if (check != temp) {
            func_800563B0(i, p->f10 + temp, p->f12 + temp);
        }
    }
}
