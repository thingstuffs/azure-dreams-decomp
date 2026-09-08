#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

typedef struct S_800C382C_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
} S_800C382C_0;   /* arg1 in func_800C382C */




extern s32 func_800374F4(s32 arg0);
extern void func_800C2E84(void *arg0, void *arg1, void *arg2);
extern void func_800C3920(void) __attribute__((noreturn));
extern s32 D_800C355C;

void func_800C382C(Rec_func_80094268_arg0 *arg0, S_800C382C_0 *arg1, void *arg2) {
    s32 i;
    s32 direction;
    void *next;

    arg1->unk_0C = 0;
    arg1->unk_10 = 0;

    for (i = 0; i < 16; i++) {
        direction = func_800374F4(4) & 0xFFFF;

        if (direction == 0) {
            if (arg1->unk_02 <
                arg0->unk_84.as_s16 + arg0->unk_8C) {
                arg0->unk_72.as_s16 = 0x400;
                func_800C3920();
            }
        } else if (direction == 1) {
            if (arg1->unk_06 <
                arg0->unk_86.as_s16 + arg0->unk_8E) {
                arg0->unk_72.as_s16 = 0;
                func_800C3920();
            }
        } else if (direction == 2) {
            if (arg0->unk_84.as_s16 - arg0->unk_8C <
                arg1->unk_02) {
                arg0->unk_72.as_s16 = 0xC00;
                func_800C3920();
            }
        } else {
            if (arg0->unk_86.as_s16 - arg0->unk_8E <
                arg1->unk_06) {
                arg0->unk_72.as_s16 = 0x800;
                func_800C3920();
            }
        }
    }

    ASM_KEEP(arg0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    next = *(volatile void **)((u8 *)arg0->unk_7C.as_pv + 4);
    do {
        func_800C2E84(arg0, arg2, next);
    } while (0);
    arg0->unk_50.as_pv = &D_800C355C;
}
