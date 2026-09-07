#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 index;
} Struct8001B74C_arg0;

extern u8 D_80408ADD[][4];
extern s32 D_80408B2C[][4];

extern void func_80402508(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3, s32 *arg4);
extern void func_80402670(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_8001B74C(Struct8001B74C_arg0 *arg0) {
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 idx = arg0->index;
    s32 count = D_80408ADD[idx][0] - 1;

    if (D_80408ADD[idx][1] != 0) {
        func_80402508(D_80408B2C[idx][count], arg0->unk0, &sp18, &sp1C, &sp20);
        func_80402670(arg0, sp18, sp1C, count, sp20);
    }
}
