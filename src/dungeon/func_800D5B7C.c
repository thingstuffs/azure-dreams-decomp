#include "common.h"



typedef s32 M2C_UNK;

typedef struct S_800DB2DC_6 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800DB2DC_6;   /* var_a2 in func_800DB2DC */

typedef struct S_800DB2DC_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800DB2DC_7;   /* ((S_800DB2DC_6 *)var_a2)->unk_08 in func_800DB2DC */


#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *func_8003FD64();
extern M2C_UNK D_80083498;
extern M2C_UNK D_800DB420;

typedef struct S_800DB2DC_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
    u8 pad_24[0x26];
    u16 unk_4A;
} S_800DB2DC_0;   /* var_a2 in func_800DB2DC */

typedef struct S_800DB2DC_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_800DB2DC_1;   /* held_arg2 in func_800DB2DC */

typedef struct S_800DB2DC_2 {
    u8 pad_00[0x12];
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x12];
    s32 unk_28;
    s32 unk_2C;
} S_800DB2DC_2;   /* held_arg1 in func_800DB2DC */

typedef struct S_800DB2DC_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x2];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
    s32 unk_2C;
} S_800DB2DC_3;   /* temp_a0 in func_800DB2DC */

typedef struct S_800DB2DC_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800DB2DC_4;   /* held_arg0 in func_800DB2DC */

typedef struct S_800DB2DC_5 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
} S_800DB2DC_5;   /* temp_v1 in func_800DB2DC */

void func_800DB2DC(void *arg0, void *arg1, void *arg2, s16 arg3) {
    register M2C_UNK *held_callback;
    s32 held_scale;
    S_800DB2DC_4 *held_arg0;
    S_800DB2DC_2 *held_arg1;
    register S_800DB2DC_1 *held_arg2 ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s16 held_arg3;
    s32 var_s0;
    register s32 var_s1 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u16 temp_v0;
    u16 temp_u16;
    s32 temp_s32;
    S_800DB2DC_3 *temp_a0;
    S_800DB2DC_5 *temp_v1;
    void *var_a2;

    var_a2 = arg2;
    held_arg0 = arg0;
    held_arg1 = arg1;
    held_arg2 = arg2;
    held_arg3 = arg3;
    var_s1 = 3;
    held_callback = &D_800DB420;
    held_scale = 0x1000;
    do {
        var_s0 = 3;
        do {
        var_a2 = func_8003FD64(0x312, &D_80083498, var_a2);
        if (var_a2 != 0) {
            ((S_800DB2DC_0 *)var_a2)->unk_10 = held_callback;
            temp_a0 = ((S_800DB2DC_0 *)var_a2)->unk_0C;
            ((S_800DB2DC_0 *)var_a2)->unk_4A =
                (u16)held_arg2->unk_2A;
            temp_s32 = held_arg1->unk_28;
            temp_a0->unk_1E = held_scale;
            temp_a0->unk_1C = held_scale;
            temp_a0->unk_28 = temp_s32;
            temp_v0 = held_arg1->unk_14;
            temp_a0->unk_14 = temp_v0;
            temp_u16 = held_arg1->unk_12;
            temp_a0->unk_0C = 0x808080;
            temp_a0->unk_14 = (u16)(temp_v0 | 0xC);
            temp_a0->unk_12 =
                (s16)(temp_u16 - 0x80);
            ((S_800DB2DC_0 *)var_a2)->unk_20 = held_arg0;
            ((S_800DB2DC_7 *)(((S_800DB2DC_6 *)var_a2)->unk_08))->unk_02 =
                (u16)held_arg0->unk_02;
            ((S_800DB2DC_7 *)(((S_800DB2DC_6 *)var_a2)->unk_08))->unk_06 =
                (u16)held_arg0->unk_06;
            ((S_800DB2DC_7 *)(((S_800DB2DC_6 *)var_a2)->unk_08))->unk_0A =
                (u16)held_arg0->unk_0A;
            temp_v1 = var_a2 + 0x20;
            temp_v1->unk_06 = held_arg3;
            temp_v1->unk_04 = (s16)(var_s1 != 0);
            temp_a0->unk_2C =
                (s32)held_arg1->unk_2C;
        }
        ASM_KEEP(var_s0);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        } while (--var_s0 >= 0);
        var_s1 -= 3;
    } while (var_s1 >= 0);
    ASM_KEEP(held_arg0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
}

/* MECHANISM: A 0x38 frame follows from pinned long-lived args/bases and two nested loop counters.
   Nested do loops independently initialize s1/s0, fixing the ra/s0 save order and loop delay slots.
   Split +0x28 word and +0x12 halfword live ranges preserve retail scheduling without extra nops. */
