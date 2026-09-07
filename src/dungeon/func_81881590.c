#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80024D90_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_80024D90_0;   /* temp_v0 in func_80024D90 */

typedef struct S_80024D90_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024D90_1;   /* saved_arg0 in func_80024D90 */

typedef struct S_80024D90_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80024D90_2;   /* temp_s1 in func_80024D90 */

typedef struct S_80024D90_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x6];
    s16 unk_16;
    s16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
    s16 unk_1E;
} S_80024D90_3;   /* component in func_80024D90 */

typedef struct S_80024D90_4 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x8];
    s16 unk_1E;
    u8 pad_20[0x4];
    s16 unk_24;
} S_80024D90_4;   /* temp_a0 in func_80024D90 */



extern s32 func_8003DB94();
extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 func_800644B8();
extern s32 func_80064584();

extern s32 D_80024B98[3];
extern s32 D_80025854[3];
extern s32 D_80045C34[3];

void *func_80024D90(void *arg0, s16 arg1) {
    register void *saved_arg0 = arg0;
    register s16 saved_arg1 = arg1;
    register s32 var_s3 = 0;
    register s32 *callback = D_80024B98;
    register u16 *counter_page = (u16 *)0x80020000;
    register s32 var_s4 = -0x400;
    register void *temp_v0;
    S_80024D90_2 *temp_s1;
    register s32 angle;
    s32 work;
    register void *component;
    register void *temp_a0 ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 const_400;

    do {
        temp_v0 = func_8003FC64(0x202);
        if (temp_v0 != NULL) {
            ((S_80024D90_0 *)temp_v0)->unk_10 = callback;
            func_8004491C(temp_v0, D_80045C34);
            angle = var_s3 << 8;
            temp_s1 = ((S_80024D90_0 *)temp_v0)->unk_08;
            work = ((S_80024D90_1 *)saved_arg0)->unk_02 + (func_80064584(angle) >> 7);
            temp_s1->unk_02 = work;
            work = ((S_80024D90_1 *)saved_arg0)->unk_06 + (func_800644B8(angle) >> 7);
            temp_s1->unk_06 = work;
            temp_s1->unk_0A =
                (s16)(((S_80024D90_1 *)saved_arg0)->unk_0A - 0x100);
            component = ((S_80024D90_0 *)temp_v0)->unk_0C;
            ((S_80024D90_3 *)component)->unk_1C = 0x800;
            ((S_80024D90_3 *)component)->unk_1E = 0x1CCC;
            ((S_80024D90_3 *)component)->unk_0C = 0;
            func_8003DB94(component, D_80025854, 0);
            const_400 = 0x400;
            ASM_KEEP(const_400);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
            work = counter_page[0x57CC / 2];
            temp_a0 = (u8 *)temp_v0 + 0x20;
            ((S_80024D90_3 *)component)->unk_16 = const_400;
            ((S_80024D90_3 *)component)->unk_18 = var_s4;
            ((S_80024D90_4 *)temp_a0)->unk_24 = var_s3;
            ((S_80024D90_4 *)temp_a0)->unk_14 = saved_arg1;
            ((S_80024D90_4 *)temp_a0)->unk_1E = (s16)(var_s3 * 2);
            work += 1;
            counter_page[0x57CC / 2] = work;
        }
        var_s3 += 1;
        var_s4 += 0x100;
    } while (var_s3 < 0x10);
    return temp_v0;
}

/* MECHANISM: The 0x38 frame and ten saved roles come from the natural loop lifetimes.
   A short-lived $v0-held 0x400 local plus ASM_KEEP forces retail's li/lhu/addiu/sh order.
   The $s1/$v1/$a0 pins preserve the child, counter, and subobject-base live ranges. */
