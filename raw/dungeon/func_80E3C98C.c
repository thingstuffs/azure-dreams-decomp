#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

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

void *func_80E3C98C(void *unused0, void *unused1, void *arg2, void *arg3) {
    s32 var_a0;
    s32 temp_a0;
    u8 *table_base;
    void *(*temp_s0)(s32, u8, u8, s16);
    s32 table_offset;
    void *temp_v0;
    void *temp_v1;
    void *var_s1;
    void *var_s0;
    void *var_s0_2;
    void *var_v0;

    temp_a0 = FIELD(arg3, s32, 0x60);
    if (temp_a0 > 0) {
        var_s0 = func_800B23F8(((u32)FIELD(arg3, u32, 0x1C) >> 0xD) & 1,
                               FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                               FIELD(arg3, s16, 0x88),
                               func_800A7A38(((s32)(((u16)FIELD(arg3, s32, 0x60) - 1) << 0x10) >> 0xE) + D_800E3548));
        if (var_s0 != NULL) {
            FIELD(var_s0, s32, 0x14) = 0;
            FIELD(var_s0, s32, 0x1C) = 0;
            func_80042710(var_s0, arg3);
            FIELD(var_s0, s32, 0x14) |= 0x20000000;
            FIELD(var_s0, s32, 0x1C) =
                (FIELD(var_s0, s32, 0x1C) | 0x02000200) & 0xFFFEFFFF;
            func_80176368();
        }
        goto block_11;
    }
    D_800E2968 = 1;
    var_s1 = (void *)temp_a0;
    
    var_s0_2 = func_800A1618(FIELD(var_s1, u8, 0x13), 1);
    if (((var_s0_2 != NULL) && (FIELD(var_s0_2, u8, 1) != 0)) ||
        (var_s0_2 = func_800A1618(FIELD(var_s1, u8, 0x13), 3),
         var_v0 = NULL, var_s0_2 != NULL)) {
        func_8004397C(var_s1);
        temp_s0 = func_800A0B94(FIELD(var_s1, u8, 0x13), var_s0_2, 1);
        func_8003F320();
        var_a0 = 4;
        if (FIELD(arg3, u32, 0x1C) & 0x2000) {
            var_a0 = 7;
        }
        var_s0 = temp_s0(var_a0, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25), FIELD(arg3, s16, 0x88));
        if (var_s0 != NULL) {
            func_80042640(var_s0, FIELD(var_s0, u8, 0x13));
            FIELD(var_s0, s32, 0x14) = 0;
            FIELD(var_s0, s32, 0x1C) = 0;
            func_80042710(var_s0, arg3);
            FIELD(var_s0, u8, 0x28)++;
            FIELD(var_s0, u8, 0x13) = FIELD(var_s1, u8, 0x13);
            FIELD(FIELD(var_s0, void *, -0x14), s16, 0x12) =
                FIELD(FIELD(var_s1, void *, -0x14), u16, 0x12) & 3;
            FIELD(var_s0, s32, 0x14) |= 0x20000000;
            FIELD(var_s0, s32, 0x1C) = (FIELD(var_s0, s32, 0x1C) | 0x02000000) & 0xFFFEFFFF;
        }
block_11:
        if (FIELD(arg3, s32, 0x14) & 0x4000) {
            table_offset = func_800A1BD0(arg3);
            table_base = D_800E3D7C;
            temp_v0 = (void *)(((s32)(table_offset << 0x10) >> 0xE) +
                               (s32)table_base);
            
            temp_v1 = FIELD(temp_v0, void *, 0xAC);
            FIELD(temp_v0, void *, 0xAC) = var_s0;
            FIELD(temp_v0, void *, 0xE4) = temp_v1;
        }
        var_v0 = NULL;
        if (var_s0 != NULL) {
            var_v0 = (u8 *)var_s0 - 0x20;
        }
    }
    return var_v0;
}
