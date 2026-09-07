#include "common.h"

typedef struct {
    u8 a;
    u8 b;
    u8 pad2;
    u8 pad3;
} S_80081508;

extern s32 func_800448BC(s32, s32);
extern s16 D_80080B04[5];
extern S_80081508 *D_80081508[3];

void func_800ABE60(s32 a0, s32 a1) {
    S_80081508 *p;

    if (D_80080B04[0] < 64) {
        if ((s16)func_800448BC((u16)a0, (u16)a1) == 0) {
            p = &D_80081508[0][D_80080B04[0]];
            p->a = (u8)a0;
            p->b = (u8)a1;
            D_80080B04[0]++;
            p[1].a = 0;
        }
    }
}
