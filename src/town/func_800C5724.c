#include "common.h"

extern void func_800C2CB0(void *arg0, void *arg1, s32 arg2, s32 arg3);
extern s32 func_800C2E1C(s16 arg0, s16 arg1, s32 *arg2);

typedef struct {
    /* 0x64 */ char pad0[0x64];
    /* 0x64 */ s16 unk64;
    /* 0x66 */ char pad1[0x0C];
    /* 0x72 */ s16 unk72;
    /* 0x74 */ char pad2[0x02];
    /* 0x78 */ s32 *unk78;
} Struct800C5724;

void func_800C2E84(Struct800C5724 *arg0, s8 *arg1, s32 *arg2) {
    s32 *var_a2;
    s16 var_v1;

    var_a2 = arg2;
    arg0->unk78 = var_a2;
    var_v1 = 0;
    if (*var_a2 != 0) {
        do {
            var_a2 += 1;
            var_v1++;
        } while (*var_a2 != 0);
    }
    arg0->unk64 = var_v1;
    func_800C2CB0(arg0, arg1, arg0->unk78[func_800C2E1C(arg0->unk72, var_v1, var_a2)], 0);
    arg1[5] = 0;
}
