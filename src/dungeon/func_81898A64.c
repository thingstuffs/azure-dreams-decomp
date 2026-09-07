#include "common.h"



#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void *func_80024350() __attribute__((noreturn));
M2C_UNK func_8003DB94();
void *func_8003FC64();
M2C_UNK func_8004491C();
extern M2C_UNK D_800241D8;
extern M2C_UNK D_80024EF4;
extern M2C_UNK D_80045340;

typedef struct S_80024264_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
    s16 unk_24;
} S_80024264_0;   /* temp_v0 in func_80024264 */

typedef struct S_80024264_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xB];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80024264_1;   /* temp_s0 in func_80024264 */

typedef struct S_80024264_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80024264_2;   /* temp_a0 in func_80024264 */

typedef struct S_80024264_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80024264_3;   /* arg1 in func_80024264 */

void *func_80024264(s32 arg0, S_80024264_3 *arg1)
{
    S_80024264_2 *temp_a0;
    S_80024264_1 *temp_s0;
    S_80024264_0 *temp_v0;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 == NULL) {
        register void *dispatch_result ASM_REG("$2") = NULL;   /* MATCH pin: retail delay-slot contents depend on it */

        ASM_TAILSLOT_PIN(dispatch_result);   /* MATCH pin: retail delay-slot contents depend on it */
        func_80024350();
    }
    temp_v0->unk_10 = &D_800241D8;
    temp_s0 = temp_v0->unk_0C;
    temp_v0->unk_20 = arg0;
    temp_v0->unk_24 = 0;
    temp_s0->unk_0E = 0x80;
    temp_s0->unk_0D = 0x80;
    temp_s0->unk_0C = 0x80;
    func_8003DB94(temp_s0, &D_80024EF4, 0);
    temp_s0->unk_1C = 0x2000;
    temp_s0->unk_1E = 0x1000;
    temp_s0->unk_1A = 0xC00;
    func_8004491C(temp_v0, &D_80045340);
    temp_a0 = temp_v0->unk_08;
    temp_a0->unk_00 = arg1->unk_00;
    temp_a0->unk_04 = arg1->unk_04;
    temp_a0->unk_08 = arg1->unk_08 + 0x500000;
    temp_a0->unk_0C = arg1->unk_0C;
    temp_a0->unk_10 = arg1->unk_10;
    temp_a0->unk_14 = arg1->unk_14;
    return temp_v0;
}

/* MECHANISM: The aligned-2 seed already had the exact 0x28 frame, saved-register roles, and CFG.
   Unsigned byte fields materialize retail's +0x80; a guarded $v0 null carrier plus
   ASM_TAILSLOT_PIN sinks move v0,zero into the LEAD-18 noreturn-j delay slot. */
