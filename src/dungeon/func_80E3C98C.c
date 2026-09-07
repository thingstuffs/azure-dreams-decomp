#include "common.h"
#include "records/Rec_D_80082E80.h"

#ifndef NULL
#define NULL 0
#endif


typedef struct S_80E3C98C_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80E3C98C_1;   /* arg2 in func_80E3C98C */

typedef struct S_80E3C98C_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80E3C98C_2_pre;   /* the 0x14 bytes before var_s0 in func_80E3C98C, addressed as var_s0[-1] */

typedef struct S_80E3C98C_2 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x8];
    u8 unk_28;
} S_80E3C98C_2;   /* var_s0 in func_80E3C98C */

typedef struct S_80E3C98C_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80E3C98C_3_pre;   /* the 0x14 bytes before var_s1 in func_80E3C98C, addressed as var_s1[-1] */

typedef struct S_80E3C98C_3 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_80E3C98C_3;   /* var_s1 in func_80E3C98C */

typedef struct S_80E3C98C_4 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_80E3C98C_4;   /* var_s0_2 in func_80E3C98C */

typedef struct S_80E3C98C_5 {
    u8 pad_00[0xAC];
    void * unk_AC;
    u8 pad_B0[0x34];
    void * unk_E4;
} S_80E3C98C_5;   /* temp_v0 in func_80E3C98C */

typedef struct S_80E3C98C_6 {
    u8 pad_00[0x12];
    s16 unk_12;
} S_80E3C98C_6;   /* ((S_80E3C98C_2_pre *)var_s0)[-1].unk_00 in func_80E3C98C */

typedef struct S_80E3C98C_7 {
    u8 pad_00[0x12];
    u16 unk_12;
} S_80E3C98C_7;   /* ((S_80E3C98C_3_pre *)var_s1)[-1].unk_00 in func_80E3C98C */



extern s32 func_8003F320();
extern s32 func_80042640();
extern s32 func_80042710();
extern s32 func_8004397C();
extern void *(*func_800A0B94())(s32, u8, u8, s16);
extern void *func_800A1618();
extern s32 func_800A1BD0();
extern s32 func_800A7A38();
extern void *func_800B23F8();
extern void func_80176368(void) __attribute__((noreturn));
extern s8 D_800E2968;
extern u8 D_800E3548[];
extern u8 *D_800E3D7C;

void *func_80E3C98C(void *unused0, void *unused1, S_80E3C98C_1 *arg2, Rec_D_80082E80 *arg3) {
    s32 var_a0;
    s32 temp_a0;
    u8 *table_base;
    void *(*temp_s0)(s32, u8, u8, s16);
    s32 table_offset;
    S_80E3C98C_5 *temp_v0;
    void *temp_v1;
    void *var_s1;
    void *var_s0;
    S_80E3C98C_4 *var_s0_2;
    void *var_v0;

    temp_a0 = arg3->unk_60.as_s32;
    if (temp_a0 > 0) {
        var_s0 = func_800B23F8(((u32)arg3->unk_1C.at00_u32.v >> 0xD) & 1,
                               arg2->unk_24, arg2->unk_25,
                               arg3->unk_88.as_s16,
                               func_800A7A38(((s32)(((u16)arg3->unk_60.as_s32 - 1) << 0x10) >> 0xE) + D_800E3548));
        if (var_s0 != NULL) {
            ((S_80E3C98C_2 *)var_s0)->unk_14 = 0;
            ((S_80E3C98C_2 *)var_s0)->unk_1C = 0;
            func_80042710(var_s0, arg3);
            ((S_80E3C98C_2 *)var_s0)->unk_14 |= 0x20000000;
            ((S_80E3C98C_2 *)var_s0)->unk_1C =
                (((S_80E3C98C_2 *)var_s0)->unk_1C | 0x02000200) & 0xFFFEFFFF;
            func_80176368();
        }
        goto block_11;
    }
    D_800E2968 = 1;
    var_s1 = (void *)temp_a0;
    
    var_s0_2 = func_800A1618(((S_80E3C98C_3 *)var_s1)->unk_13, 1);
    if (((var_s0_2 != NULL) && (var_s0_2->unk_01 != 0)) ||
        (var_s0_2 = func_800A1618(((S_80E3C98C_3 *)var_s1)->unk_13, 3),
         var_v0 = NULL, var_s0_2 != NULL)) {
        func_8004397C(var_s1);
        temp_s0 = func_800A0B94(((S_80E3C98C_3 *)var_s1)->unk_13, var_s0_2, 1);
        func_8003F320();
        var_a0 = 4;
        if (arg3->unk_1C.at00_u32.v & 0x2000) {
            var_a0 = 7;
        }
        var_s0 = temp_s0(var_a0, arg2->unk_24, arg2->unk_25, arg3->unk_88.as_s16);
        if (var_s0 != NULL) {
            func_80042640(var_s0, ((S_80E3C98C_2 *)var_s0)->unk_13);
            ((S_80E3C98C_2 *)var_s0)->unk_14 = 0;
            ((S_80E3C98C_2 *)var_s0)->unk_1C = 0;
            func_80042710(var_s0, arg3);
            ((S_80E3C98C_2 *)var_s0)->unk_28++;
            ((S_80E3C98C_2 *)var_s0)->unk_13 = ((S_80E3C98C_3 *)var_s1)->unk_13;
            ((S_80E3C98C_6 *)(((S_80E3C98C_2_pre *)var_s0)[-1].unk_00))->unk_12 =
                ((S_80E3C98C_7 *)(((S_80E3C98C_3_pre *)var_s1)[-1].unk_00))->unk_12 & 3;
            ((S_80E3C98C_2 *)var_s0)->unk_14 |= 0x20000000;
            ((S_80E3C98C_2 *)var_s0)->unk_1C = (((S_80E3C98C_2 *)var_s0)->unk_1C | 0x02000000) & 0xFFFEFFFF;
        }
block_11:
        if (arg3->unk_14.at00_s32.v & 0x4000) {
            table_offset = func_800A1BD0(arg3);
            table_base = D_800E3D7C;
            temp_v0 = (void *)(((s32)(table_offset << 0x10) >> 0xE) +
                               (s32)table_base);
            
            temp_v1 = temp_v0->unk_AC;
            temp_v0->unk_AC = var_s0;
            temp_v0->unk_E4 = temp_v1;
        }
        var_v0 = NULL;
        if (var_s0 != NULL) {
            var_v0 = (u8 *)var_s0 - 0x20;
        }
    }
    return var_v0;
}
