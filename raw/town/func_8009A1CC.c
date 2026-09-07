#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_800374F4();
extern M2C_UNK func_8003DB94();
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern s32 rand();
extern M2C_UNK D_80045340;
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern M2C_UNK D_800ABB20;
extern M2C_UNK D_800D1464;

void *func_8009792C(void *arg0, u32 arg1) {
    s16 *temp_a0_2;
    s16 *temp_s4;
    s16 *table_x;
    s32 temp_a0;
    s32 temp_s0_2;
    s32 var_v0;
    s32 var_v0_2;
    u32 temp_s4_idx;
    u8 *temp_page;
    register void *temp_call ASM_REG("$4");
    void *temp_a1;
    void *temp_s0;
    void *temp_s2;
    void *temp_v0;

    arg1 >>= 9;
    temp_s4_idx = arg1 & 7;
    temp_v0 = func_8003FC64(0x212, arg1);
    if (temp_v0 != NULL) {
        temp_call = temp_v0;
        ASM_KEEP_NV(temp_call);
        temp_a1 = &D_80045340;
        ASM_KEEP_NV(temp_a1);
#ifdef NON_MATCHING
        temp_page = (u8 *)&D_800ABB20 + 0x44E0;
#else
        temp_page = (u8 *)0x800B0000;
#endif
        ASM_KEEP_NV(temp_page);
        temp_s2 = M2C_FIELD(temp_v0, void **, 8);
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) =
            (M2C_UNK *)(temp_page - 0x44E0);
        func_8004491C(temp_call, temp_a1);
        temp_a0 = temp_s4_idx * 2;
        table_x = (s16 *)&D_8006CCD8;
        ASM_KEEP(table_x);
        temp_a0_2 = (s16 *)((u8 *)&D_8006CCE8 + temp_a0);
        M2C_FIELD(temp_s2, s16 *, 2) =
            (s16)(M2C_FIELD(arg0, u16 *, 2) -
                  (table_x[temp_s4_idx] * 0x10));
        M2C_FIELD(temp_s2, s16 *, 6) =
            (s16)(M2C_FIELD(arg0, u16 *, 6) - (*temp_a0_2 * 0x10));
        M2C_FIELD(temp_s2, u16 *, 0xA) =
            (u16)M2C_FIELD(arg0, u16 *, 0xA);
        var_v0 = 0 -
                 (M2C_FIELD(arg0, s32 *, 0xC) *
                  ((rand(temp_a0_2) & 1) + 2));
        if (var_v0 < 0) {
            var_v0 += 0xF;
        }
        temp_s4 = (s16 *)((s8 *)temp_v0 + 0x20);
        ASM_KEEP(temp_s4);
        M2C_FIELD(temp_s2, s32 *, 0xC) = (s32)(var_v0 >> 4);
        var_v0_2 = 0 -
                   (M2C_FIELD(arg0, s32 *, 0x10) *
                    ((rand() & 1) + 2));
        if (var_v0_2 < 0) {
            var_v0_2 += 0xF;
        }
        M2C_FIELD(temp_s2, s32 *, 0x10) = (s32)(var_v0_2 >> 4);
        M2C_FIELD(temp_s2, s32 *, 0x14) =
            (s32)((~rand() & 1) << 0xF);
        func_8003DB94(temp_s0, &D_800D1464, 0);
        M2C_FIELD(temp_s0, u8 *, 0xE) = 0xFF;
        M2C_FIELD(temp_s0, u8 *, 0xD) = 0xFF;
        M2C_FIELD(temp_s0, u8 *, 0xC) = 0xFF;
        M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_s0, s16 *, 0x10) = 0x60;
        M2C_FIELD(temp_s0, u16 *, 0x14) =
            (u16)(M2C_FIELD(temp_s0, u16 *, 0x14) | 0xC);
        temp_s0_2 = func_800374F4(7);
        temp_s4[1] = (s16)(temp_s0_2 + func_800374F4(7));
    }
    return temp_v0;
}

/* MECHANISM: Hold the zero-low-half 0x800B page across the two object loads,
   then apply -0x44E0 at the store to split D_800ABB20's lui/addiu as retail.
   Nonvolatile a1 liveness plus the guarded a0 ABI pin fixes the ready-list order. */
