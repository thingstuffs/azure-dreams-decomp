#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_800C4174(void *arg0, void *arg1, s32 arg2);
extern void func_800C51CC(void);


typedef struct S_800C5100_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
    s32 unk_14;
} S_800C5100_0;   /* arg1 in func_800C5100 */

void func_800C5100(void *arg0, S_800C5100_0 *arg1, s32 arg2) {
    if (arg1->unk_08 == -0x08000000) {
        func_800C4174(arg0, arg1, arg2);
        func_800C51CC();
        return;
    }

    arg1->unk_10 += 0xFFFE0000;
    arg1->unk_14 -= 0x8000;
    arg1->unk_04 += arg1->unk_10;
    arg1->unk_08 += arg1->unk_14;

    if (arg1->unk_10 <= (s32)0xFF000000) {
        arg1->unk_10 = -0x01000000;
    }
    if (arg1->unk_14 <= (s32)0xFF000000) {
        arg1->unk_14 = -0x01000000;
    }
    if (arg1->unk_04 <= (s32)0xF8000000) {
        arg1->unk_04 = -0x08000000;
    }
    if (arg1->unk_08 <= (s32)0xF8000000) {
        arg1->unk_08 = -0x08000000;
    }
}
