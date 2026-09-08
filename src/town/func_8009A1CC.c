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

typedef struct S_8009792C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_8009792C_0;   /* temp_v0 in func_8009792C */

typedef struct S_8009792C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8009792C_1;   /* temp_s2 in func_8009792C */

typedef struct S_8009792C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
} S_8009792C_2;   /* arg0 in func_8009792C */

typedef struct S_8009792C_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8009792C_3;   /* temp_s0 in func_8009792C */

void *func_8009792C(S_8009792C_2 *arg0, u32 arg1) {
    s16 *temp_a0_2;
    s16 *temp_s4;
    s16 *table_x;
    s32 temp_a0;
    s32 temp_s0_2;
    s32 var_v0;
    s32 var_v0_2;
    u32 temp_s4_idx;
    u8 *temp_page;
    register void *temp_call ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    void *temp_a1;
    S_8009792C_3 *temp_s0;
    S_8009792C_1 *temp_s2;
    void *temp_v0;

    arg1 >>= 9;
    temp_s4_idx = arg1 & 7;
    temp_v0 = func_8003FC64(0x212, arg1);
    if (temp_v0 != NULL) {
        temp_call = temp_v0;
        temp_a1 = &D_80045340;
        ASM_KEEP_NV(temp_a1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
        temp_page = (u8 *)&D_800ABB20 + 0x44E0;
#else
        temp_page = (u8 *)0x800B0000;
#endif
        ASM_KEEP_NV(temp_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        temp_s2 = ((S_8009792C_0 *)temp_v0)->unk_08;
        temp_s0 = ((S_8009792C_0 *)temp_v0)->unk_0C;
        ((S_8009792C_0 *)temp_v0)->unk_10 =
            (M2C_UNK *)(temp_page - 0x44E0);
        func_8004491C(temp_call, temp_a1);
        temp_a0 = temp_s4_idx * 2;
        table_x = (s16 *)&D_8006CCD8;
        ASM_KEEP(table_x);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        temp_a0_2 = (s16 *)((u8 *)&D_8006CCE8 + temp_a0);
        temp_s2->unk_02 =
            (s16)(arg0->unk_02 -
                  (table_x[temp_s4_idx] * 0x10));
        temp_s2->unk_06 =
            (s16)(arg0->unk_06 - (*temp_a0_2 * 0x10));
        temp_s2->unk_0A =
            (u16)arg0->unk_0A;
        var_v0 = 0 -
                 (arg0->unk_0C *
                  ((rand(temp_a0_2) & 1) + 2));
        if (var_v0 < 0) {
            var_v0 += 0xF;
        }
        temp_s4 = (s16 *)((s8 *)temp_v0 + 0x20);
        ASM_KEEP(temp_s4);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        temp_s2->unk_0C = (s32)(var_v0 >> 4);
        var_v0_2 = 0 -
                   (arg0->unk_10 *
                    ((rand() & 1) + 2));
        if (var_v0_2 < 0) {
            var_v0_2 += 0xF;
        }
        temp_s2->unk_10 = (s32)(var_v0_2 >> 4);
        temp_s2->unk_14 =
            (s32)((~rand() & 1) << 0xF);
        func_8003DB94(temp_s0, &D_800D1464, 0);
        temp_s0->unk_0E = 0xFF;
        temp_s0->unk_0D = 0xFF;
        temp_s0->unk_0C = 0xFF;
        temp_s0->unk_1E = 0x1000;
        temp_s0->unk_1C = 0x1000;
        temp_s0->unk_10 = 0x60;
        temp_s0->unk_14 =
            (u16)(temp_s0->unk_14 | 0xC);
        temp_s0_2 = func_800374F4(7);
        temp_s4[1] = (s16)(temp_s0_2 + func_800374F4(7));
    }
    return temp_v0;
}

/* MECHANISM: Hold the zero-low-half 0x800B page across the two object loads,
   then apply -0x44E0 at the store to split D_800ABB20's lui/addiu as retail.
   Nonvolatile a1 liveness plus the guarded a0 ABI pin fixes the ready-list order. */
