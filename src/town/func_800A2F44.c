#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A06A4_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x14];
    s32 unk_18;
    M2C_UNK * unk_1C;
    u8 pad_20[0x40];
    M2C_UNK * unk_60;
    u8 pad_64[0x14];
    s16 unk_78;
    u8 pad_7A[0x4];
    s16 unk_7E;
    u8 pad_80[0x20];
    s16 unk_A0;
    u8 pad_A2[0x2];
    u8 unk_A4;
} S_800A06A4_0;   /* arg0 in func_800A06A4; pointer addresses record offset 0x10 */


M2C_UNK func_800A06E8();                            /* extern */
M2C_UNK func_800A06EC();                            /* extern */
extern M2C_UNK D_800A0708;
extern M2C_UNK D_800A07A4;
extern M2C_UNK D_800A0AC8;
extern M2C_UNK D_800A0BE4;
extern M2C_UNK D_800D09E0;

void func_800A06A4(void *arg0, s32 arg1) {
    u8 temp_v1;

    temp_v1 = ((S_800A06A4_0 *)((u8 *)arg0 - 0x10))->unk_A4;
    ((S_800A06A4_0 *)((u8 *)arg0 - 0x10))->unk_00 = &D_800A0708;
    if (temp_v1 == 1) {
        register M2C_UNK *next ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

        ((S_800A06A4_0 *)((u8 *)arg0 - 0x10))->unk_A0 = 2;
        next = &D_800A0BE4;
        ASM_TAILSLOT_PIN(next);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_800A06E8();
        return;
    }
    if (temp_v1 == 0) {
        M2C_UNK *next;

        next = &D_800A0AC8;
        ASM_TAILSLOT_PIN(next);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_800A06EC();
        return;
    }
    {
        M2C_UNK *handler;

        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        handler = &D_800A07A4;
        ((S_800A06A4_0 *)((u8 *)arg0 - 0x10))->unk_7E = 0;
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ((S_800A06A4_0 *)((u8 *)arg0 - 0x10))->unk_60 = handler;
    }
    ((S_800A06A4_0 *)((u8 *)arg0 - 0x10))->unk_18 = arg1;
    ((S_800A06A4_0 *)((u8 *)arg0 - 0x10))->unk_1C = &D_800D09E0;
    ((S_800A06A4_0 *)((u8 *)arg0 - 0x10))->unk_78 = 0;
}

/* MECHANISM: Frameless leaf CFG with guarded $v0 continuation-address pins preserves both shared-entry tail jumps.
   A block-entry schedule barrier selects the fall-through lui for the branch slot; a held callback pointer
   plus memory fence fixes the sh-before-sw order. The length-exact lineage is 2.95.2-G0. */
