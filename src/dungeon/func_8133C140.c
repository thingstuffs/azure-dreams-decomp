#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80173140_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80173140_0;   /* temp_v0 in func_80173140 */

typedef struct S_80173140_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0x72];
    s16 unk_92;
    u8 pad_94[0xC];
    s32 unk_A0;
} S_80173140_1;   /* temp_s1 in func_80173140 */

typedef struct S_80173140_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173140_2;   /* temp_a1 in func_80173140 */


typedef struct S_80173140_4 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    union { M2C_UNK * s; void * u; } unk_2C;   /* accessed as both */
} S_80173140_4;   /* temp_s0 in func_80173140 */

typedef struct S_80173140_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173140_5;   /* ((Rec_D_800E3D7C *)(&D_80083498))->unk_08.at00_pv.v in func_80173140 */


void *func_8003FD64();            /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_80047784();         /* extern */
M2C_UNK func_8009A028();                      /* extern */
M2C_UNK func_8009A3D0();             /* extern */
void func_800A9C18(void *, void *, void *, s32); /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80082E80;
extern s16 D_80083228;
extern M2C_UNK D_80083498;
extern M2C_UNK D_80171D74;
extern M2C_UNK D_80173DA4;
extern void *D_80175D54;

void func_80173140(void) {
    s32 temp_v1;
    s32 flag_mask;
    s32 temp_v0_2;
    s16 temp_neg;
    s32 call2_a0;
    s32 call2_a1;
    register void *temp_v0 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    M2C_UNK var_a2;
    s32 env_first;
    s32 env_second;
    void *temp_a1;
    void *temp_s0;
    void *temp_s1;
    u8 *temp_v1_global;

    temp_v0 = func_8003FD64(0x112, &D_80083498);
    if (temp_v0 != NULL) {
        temp_s1 = temp_v0 + 0x20;
        ((S_80173140_0 *)temp_v0)->unk_10 = &D_80171D74;
        ((S_80173140_1 *)temp_s1)->unk_13 = 2;
        func_8004491C(temp_v0, &D_80045340);
        temp_v1_global = (u8 *)&D_80082E80;
        temp_a1 = ((S_80173140_0 *)temp_v0)->unk_08;
        ((S_80173140_2 *)temp_a1)->unk_0A = (u16) ((S_80173140_5 *)(((Rec_D_800E3D7C *)(&D_80083498))->unk_08.at00_pv.v))->unk_0A;
        temp_s0 = ((S_80173140_0 *)temp_v0)->unk_0C;
        env_first = temp_v1_global[0x24];
        ((S_80173140_4 *)temp_s0)->unk_24 = (u8) (env_first - 1);
        env_second = temp_v1_global[0x25];
        ((S_80173140_4 *)temp_s0)->unk_2C.s = &D_80173DA4;
        ((S_80173140_4 *)temp_s0)->unk_25 = (u8) (env_second + 7);
        func_800A9C18(temp_v0, temp_a1, temp_s0, 0);
        (*(s16 *)((u8 *)temp_s1 + 0x2A)) = 0xC00;
        func_80047784(temp_s0, ((u8 *) ((S_80173140_4 *)temp_s0)->unk_2C.u)[((s32) (D_80083228 + 0xD00) >> 9) & 7], 0);
        ((S_80173140_4 *)temp_s0)->unk_1E = 0x1000;
        ((S_80173140_4 *)temp_s0)->unk_1C = 0x1000;
        temp_v0_2 = ((S_80173140_1 *)temp_s1)->unk_1C;
        flag_mask = 0x40000;
        ((S_80173140_1 *)temp_s1)->unk_A0 = 0;
        temp_v0_2 |= flag_mask;
        ((S_80173140_1 *)temp_s1)->unk_1C = temp_v0_2;
        ASM_KEEP(temp_v0_2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        temp_v1 = temp_v0_2;
        ASM_KEEP(temp_v1);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        temp_neg = -0x20;
        ASM_KEEP(temp_neg);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        temp_v1 &= 0x2000;
        ((S_80173140_1 *)temp_s1)->unk_92 = temp_neg;
        call2_a0 = ((S_80173140_4 *)temp_s0)->unk_24;
        call2_a1 = ((S_80173140_4 *)temp_s0)->unk_25;
        var_a2 = 0x3000;
        if (temp_v1) {
            var_a2 = 0x300;
        }
        func_8009A3D0(call2_a0, call2_a1, var_a2);
        func_8009A028(temp_s1);
        D_80175D54 = temp_v0;
        ((S_80173140_0 *)temp_v0)->unk_10 = (M2C_UNK *) ((s32) ((S_80173140_0 *)temp_v0)->unk_10 | 0x80000000);
    }
}

/* MECHANISM: The 0x20 frame holds s2=obj, s1=obj+0x20, and s0 as the reused global/object base.
   A held D_80082E80 byte base plus split env_first/env_second live ranges fixes the call schedule.
   Byte indexing, split v0/v1 flag RMW roles, and a store/OR memory seam close the final rotation. */
