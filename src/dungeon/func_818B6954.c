#include "common.h"

#ifndef NULL
#define NULL 0
#endif


typedef long long s64_local;

typedef struct S_818B6954_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_818B6954_0;   /* temp_v0 in func_818B6954 */

typedef struct S_818B6954_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
} S_818B6954_1;   /* temp_v0_2 in func_818B6954 */

typedef struct S_818B6954_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_818B6954_2;   /* temp_s0_2 in func_818B6954 */


extern s32 func_800242DC() __attribute__((noreturn));
extern s32 func_8003DB94();
extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 func_800644B8();
extern s32 func_80064584();
extern s32 rand();

extern u8 D_800240B8[];
extern u8 D_80045340[];
extern u8 D_800DEC70[];

s32 func_818B6954(s32 arg0, void *arg1, s32 arg2) {
    s16 temp_s0;
    register s32 temp_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 temp_a1;
    s64_local temp_copy01;
    s32 temp_copy4;
    s32 temp_copy5;
    register s32 ret ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 scale ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 temp_v0_3;
    s32 temp_v1;
    s32 var_s0;
    s32 var_v0;
    S_818B6954_2 *temp_s0_2;
    void *temp_s2;
    register void *temp_v0 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    S_818B6954_1 *temp_v0_2;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        ((S_818B6954_0 *)temp_v0)->unk_10 = D_800240B8;
        temp_v0_2 = (u8 *)temp_v0 + 0x20;
        ((S_818B6954_0 *)temp_v0)->unk_20 = arg0;
        temp_v0_2->unk_04 = 0;
        temp_v0_2->unk_06 = 0;
        temp_s0_2 = ((S_818B6954_0 *)temp_v0)->unk_0C;
        temp_s0_2->unk_0C = arg2;
        temp_s0_2->unk_12 = 0x7DCF;
        temp_s0_2->unk_14 |= 0xC;
        temp_s0_2->unk_10 |= 0x20;
        temp_s0_2->unk_14 |= 0x100;
        func_8003DB94(temp_s0_2, D_800DEC70, 0);
        var_v0 = rand();
        temp_v1 = var_v0;
        if (temp_v1 < 0) {
            var_v0 = temp_v1 + 0xFFF;
        }
        ASM_KEEP(temp_v1);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        temp_s0_2->unk_1A = temp_v1 - ((var_v0 >> 0xC) << 0xC);
        temp_s0_2->unk_1E = 0xC00;
        temp_s0_2->unk_1C = 0xC00;
        func_8004491C(temp_v0, D_80045340);
        temp_s2 = ((S_818B6954_0 *)temp_v0)->unk_08;
        temp_copy01 = (*(s64_local *)((u8 *)arg1 + 0));
        temp_a0 = (*(s32 *)((u8 *)arg1 + 8));
        temp_a1 = (*(s32 *)((u8 *)arg1 + 0xC));
        (*(s64_local *)((u8 *)temp_s2 + 0)) = temp_copy01;
        (*(s32 *)((u8 *)temp_s2 + 8)) = temp_a0;
        (*(s32 *)((u8 *)temp_s2 + 0xC)) = temp_a1;
        temp_copy4 = (*(s32 *)((u8 *)arg1 + 0x10));
        temp_copy5 = (*(s32 *)((u8 *)arg1 + 0x14));
        (*(s32 *)((u8 *)temp_s2 + 0x10)) = temp_copy4;
        (*(s32 *)((u8 *)temp_s2 + 0x14)) = temp_copy5;
        temp_v0_3 = rand(temp_a0, temp_a1);
        var_s0 = temp_v0_3;
        if (temp_v0_3 < 0) {
            var_s0 = temp_v0_3 + 0xFFF;
        }
        temp_s0 = temp_v0_3 - ((var_s0 >> 0xC) << 0xC);
        (*(s32 *)((u8 *)temp_s2 + 0)) += (func_80064584(temp_s0) >> 4) * 0x1200;
        temp_a0 = func_800644B8(temp_s0) >> 4;
        ret = (s32)temp_v0;
        ASM_KEEP(ret);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        scale = temp_a0 * 0x1200;
        temp_a0 = (*(s32 *)((u8 *)temp_s2 + 4)) + scale;
        (*(s32 *)((u8 *)temp_s2 + 4)) = temp_a0;
        func_800242DC(temp_a0);
    }
    return 0;
}
