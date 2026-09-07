#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef void (*Callback)(void);

extern void *func_800373DC(s32);
extern void func_8003BC18(void *, void *);
extern s32 func_80071494(void);
extern void func_8028E170(void);
extern void func_8052FC8C(void);
extern u8 D_8003C558[];

void func_80814F08(void *arg0) {
    void *temp_s0;
    void *temp_s2;
    void *temp_v0;

    temp_v0 = func_800373DC(0x136);
    if (temp_v0 != 0) {
        FIELD(temp_v0, Callback, 0x10) = func_8052FC8C;
        func_8003BC18(temp_v0, D_8003C558);
        temp_s2 = FIELD(temp_v0, void *, 8);
        temp_s0 = FIELD(temp_v0, void *, 0xC);
        FIELD(temp_s2, s16, 2) =
            (FIELD(arg0, u16, 2) + (func_80071494() % 40)) - 0x14;
        FIELD(temp_s2, s16, 6) =
            (FIELD(arg0, u16, 6) + (func_80071494() % 40)) - 0x14;
        FIELD(temp_s2, s16, 0xA) =
            (FIELD(arg0, u16, 0xA) + (func_80071494() % 40)) - 0x14;
        FIELD(temp_s2, s32, 0xC) = FIELD(arg0, s32, 0xC);
        FIELD(temp_s2, s32, 0x14) =
            ((func_80071494() & 0x1FF) - 0x100) * 0x400;
        FIELD(temp_v0, s16, 0x2E) = 3;
        FIELD(temp_s0, s16, 0x1E) = 0x1000;
        FIELD(temp_s0, s16, 0x1C) = 0x1000;
        FIELD(temp_s0, Callback, 8) = func_8028E170;
        FIELD(temp_s0, s8, 4) = 0;
        FIELD(temp_s0, s8, 5) = 0;
        FIELD(temp_s0, s32, 0xC) = 0x808080;
        FIELD(temp_s0, u16, 0x14) |= 0xC;
    }
}
