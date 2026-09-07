#include "common.h"

#ifndef NULL
#define NULL 0
#endif

extern void func_800A9358(s32 arg2);
extern s32 func_800A953C(s32 arg0, s32 arg1);

typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    s32 unk0C;
} Struct800ABDC8;

s32 func_800A9528(void *arg0, s32 arg1, s32 arg2) {
    register Struct800ABDC8 *v0 ASM_REG("$4");
    register Struct800ABDC8 *v1 ASM_REG("$16");
    s32 x;
    s32 y;

    v0 = (Struct800ABDC8 *)arg2;
    ASM_KEEP(v0);
    func_800A9358((s32)v0);
    v0 = *(Struct800ABDC8 **)((u8 *)arg0 - 8);
    v1 = (Struct800ABDC8 *)((u8 *)v0 + 0x20);
    if (v0 == NULL) {
        ASM_CLOBBER("$4");
        return 0;
    }
    ASM_KEEP(v1);
    x = v0->unk08;
    y = v0->unk0C;
    return func_800A953C(y, x);
}
