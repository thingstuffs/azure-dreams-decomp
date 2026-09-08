#include "common.h"
#include "m2c_compat.h"

typedef struct S_800D50FC_0 {
    u16 unk_00;
    u8 pad_02[0xC];
    u8 unk_0E;
    u8 unk_0F;
    u8 unk_10;
    u8 pad_11[0xF];
    u16 unk_20;
    s16 unk_22;
} S_800D50FC_0;   /* arg0 in func_800D50FC; pointer addresses record offset 0x2 */

typedef struct S_800D50FC_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800D50FC_1;   /* arg1 in func_800D50FC */

typedef struct S_800D50FC_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_800D50FC_2;   /* arg2 in func_800D50FC */

typedef struct S_800D50FC_3 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_800D50FC_3;   /* page in func_800D50FC */


s32 rand();                                /* extern */
void func_800D5188(void) __attribute__((noreturn)); /* extern */
extern M2C_UNK D_800814A0;

void func_800D50FC(void *arg0, S_800D50FC_1 *arg1, S_800D50FC_2 *arg2) {
    s32 temp_s0;
    u16 temp_v0;
    u32 temp_v1;

    temp_v1 = ((S_800D50FC_0 *)((u8 *)arg0 - 0x2))->unk_20 & 7;
    switch (temp_v1) {
    case 1:
    case 2:
    case 5:
    case 6:
        break;
    case 0:
    case 4:
        arg1->unk_0C = (s32) (((rand() & 0x3FFF) - 0x2000) << 5);
        temp_s0 = (s32) (((rand() & 0x3FFF) - 0x2000) << 5);
        ASM_KEEP(arg0);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(arg2);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        arg1->unk_10 = temp_s0;
        func_800D5188();
    case 3:
    case 7:
        arg1->unk_10 = 0;
        arg1->unk_0C = 0;
        break;
    }
    arg1->unk_00 = (s32) (arg1->unk_00 + arg1->unk_0C);
    arg1->unk_04 = (s32) (arg1->unk_04 + arg1->unk_10);
    arg1->unk_08 = (s32) (arg1->unk_08 + arg1->unk_14);
    arg2->unk_0C = (s8) ((s32) (((S_800D50FC_0 *)((u8 *)arg0 - 0x2))->unk_0E * (s16) ((S_800D50FC_0 *)((u8 *)arg0 - 0x2))->unk_20) / (s16) ((S_800D50FC_0 *)((u8 *)arg0 - 0x2))->unk_22);
    arg2->unk_0D = (s8) ((s32) (((S_800D50FC_0 *)((u8 *)arg0 - 0x2))->unk_0F * (s16) ((S_800D50FC_0 *)((u8 *)arg0 - 0x2))->unk_20) / (s16) ((S_800D50FC_0 *)((u8 *)arg0 - 0x2))->unk_22);
    arg2->unk_0E = (s8) ((s32) (((S_800D50FC_0 *)((u8 *)arg0 - 0x2))->unk_10 * (s16) ((S_800D50FC_0 *)((u8 *)arg0 - 0x2))->unk_20) / (s16) ((S_800D50FC_0 *)((u8 *)arg0 - 0x2))->unk_22);
    temp_v0 = ((S_800D50FC_0 *)((u8 *)arg0 - 0x2))->unk_20 - 1;
    ((S_800D50FC_0 *)((u8 *)arg0 - 0x2))->unk_20 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        register u32 page ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        page = 0x80080000;
        ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        ((S_800D50FC_0 *)((u8 *)arg0 - 0x2))->unk_00 = (u16) (((S_800D50FC_0 *)((u8 *)arg0 - 0x2))->unk_00 | 0x8000);
        ((S_800D50FC_3 *)page)->unk_14A0 = ((S_800D50FC_3 *)page)->unk_14A0 | 0x8000;
    }
}

/* MECHANISM: Split the second RNG result, then keep all three arguments live across both calls
   to preserve the 0x20 frame and s1/s0/ra/s2 save order while LEAD 18 forms the continuation j.
   A guarded $v1 page base emits the branch-slot lui and both 0x14A0($v1) accesses exactly. */
