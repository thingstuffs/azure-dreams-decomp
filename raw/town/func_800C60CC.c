#include "common.h"

#define FIELD(base, type, off) (*(type *)((u8 *)(base) + (off)))

extern s32 func_800374F4(s32 arg0);
extern void func_800C2E84(void *arg0, void *arg1, void *arg2);
extern void func_800C3920(void) __attribute__((noreturn));
extern s32 D_800C355C;

void func_800C382C(void *arg0, void *arg1, void *arg2) {
    s32 i;
    s32 direction;
    void *next;

    FIELD(arg1, s32, 0xC) = 0;
    FIELD(arg1, s32, 0x10) = 0;

    for (i = 0; i < 16; i++) {
        direction = func_800374F4(4) & 0xFFFF;

        if (direction == 0) {
            if (FIELD(arg1, s16, 2) <
                FIELD(arg0, s16, 0x84) + FIELD(arg0, s16, 0x8C)) {
                FIELD(arg0, s16, 0x72) = 0x400;
                func_800C3920();
            }
        } else if (direction == 1) {
            if (FIELD(arg1, s16, 6) <
                FIELD(arg0, s16, 0x86) + FIELD(arg0, s16, 0x8E)) {
                FIELD(arg0, s16, 0x72) = 0;
                func_800C3920();
            }
        } else if (direction == 2) {
            if (FIELD(arg0, s16, 0x84) - FIELD(arg0, s16, 0x8C) <
                FIELD(arg1, s16, 2)) {
                FIELD(arg0, s16, 0x72) = 0xC00;
                func_800C3920();
            }
        } else {
            if (FIELD(arg0, s16, 0x86) - FIELD(arg0, s16, 0x8E) <
                FIELD(arg1, s16, 6)) {
                FIELD(arg0, s16, 0x72) = 0x800;
                func_800C3920();
            }
        }
    }

    ASM_KEEP(arg0);
    next = *(volatile void **)((u8 *)FIELD(arg0, void *, 0x7C) + 4);
    do {
        func_800C2E84(arg0, arg2, next);
    } while (0);
    FIELD(arg0, void *, 0x50) = &D_800C355C;
}
