#include "common.h"

extern void func_800C2E84(void *arg0, void *arg1, void *arg2);
extern void func_800C4174(void *arg0, s32 arg1, void *arg2);

extern u8 D_80082660[];
extern u8 D_800D6CA8[];

typedef struct {
    u8 pad0[0xC];
    u8 unkC;
    u8 unkD;
    u8 unkE;
} Func800CEC24Arg2;

void func_800CC384(void *arg0, s32 arg1, Func800CEC24Arg2 *arg2) {
    register u32 value ASM_REG("$3");

    func_800C2E84(arg0, arg2, D_800D6CA8);
    D_80082660[*(s32 *)((u8 *)arg0 + 0x60) * 8] = 0;

    value = arg2->unkC + 0x20;
    ASM_KEEP(value);
    if (value >= 0x100) {
        value = 0xFF;
    }

    arg2->unkE = value;
    arg2->unkD = value;
    arg2->unkC = value;
    func_800C4174(arg0, arg1, arg2);
}
