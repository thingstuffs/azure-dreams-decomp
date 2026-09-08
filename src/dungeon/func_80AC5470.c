#include "common.h"
#include "m2c_compat.h"

typedef struct S_80AC5470_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    s32 unk_04;
    s32 unk_08;
} S_80AC5470_0;   /* arg1 in func_80AC5470 */

typedef struct S_80AC5470_1_pre {
    u16 unk_00;
} S_80AC5470_1_pre;   /* the 0x2 bytes before arg0 in func_80AC5470, addressed as arg0[-1] */

typedef struct S_80AC5470_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x1];
    union { struct { s8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; s8 v; } at01; struct { u8 pad[0x2]; s8 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
    u8 pad_34[0x2];
    s16 unk_36;
    u8 pad_38[0x8];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
} S_80AC5470_1;   /* arg0 in func_80AC5470 */


extern M2C_UNK D_800814A0;

void func_80AC5470(void *arg0, void *arg1) {
    s16 temp_v0;
    s32 reg_v0;
    s32 reg_v1;
    register s32 reg_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 reg_a1;
    register s32 reg_a2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 var_a0;
    s32 var_a1;
    s32 var_v0;
    s32 var_v1;

    ((S_80AC5470_0 *)arg1)->unk_00.at00.v = (s32) (((S_80AC5470_0 *)arg1)->unk_00.at00.v + ((S_80AC5470_1 *)arg0)->unk_40);
    ((S_80AC5470_0 *)arg1)->unk_04 = (s32) (((S_80AC5470_0 *)arg1)->unk_04 + ((S_80AC5470_1 *)arg0)->unk_44);
    ((S_80AC5470_0 *)arg1)->unk_08 = (s32) (((S_80AC5470_0 *)arg1)->unk_08 + ((S_80AC5470_1 *)arg0)->unk_48);
    reg_v0 = ((S_80AC5470_1 *)arg0)->unk_40;
    reg_v1 = ((S_80AC5470_1 *)arg0)->unk_4C;
    reg_a0 = ((S_80AC5470_1 *)arg0)->unk_50;
    reg_a2 = ((S_80AC5470_1 *)arg0)->unk_54;
    reg_v0 += reg_v1;
    ((S_80AC5470_1 *)arg0)->unk_40 = reg_v0;
    reg_v0 = ((S_80AC5470_1 *)arg0)->unk_44;
    reg_v1 = ((S_80AC5470_1 *)arg0)->unk_48;
    reg_v0 += reg_a0;
    ((S_80AC5470_1 *)arg0)->unk_44 = reg_v0;
    reg_v0 = ((S_80AC5470_1 *)arg0)->unk_36;
    reg_v1 += reg_a2;
    ((S_80AC5470_1 *)arg0)->unk_48 = reg_v1;
    reg_v1 = ((S_80AC5470_0 *)arg1)->unk_00.at02.v;
    var_v0 = reg_v0 - reg_v1;
    if (var_v0 < 0) {
        var_v0 = 0 - var_v0;
    }
    if (var_v0 < 0x10) {
        (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_80AC5470_1_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }
    reg_v1 = ((S_80AC5470_1 *)arg0)->unk_00;
    reg_v0 = ((S_80AC5470_1 *)arg0)->unk_32;
    reg_a0 = reg_v1 * reg_v0;
    if (reg_a0 < 0) {
        reg_a0 += 0xFF;
    }
    reg_v1 = ((S_80AC5470_1 *)arg0)->unk_01;
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    reg_v0 = ((S_80AC5470_1 *)arg0)->unk_32;
    reg_a1 = reg_v1 * reg_v0;
    reg_v0 = reg_a0 >> 8;
    ((S_80AC5470_1 *)arg0)->unk_04.at00.v = (s8) reg_v0;
    if (reg_a1 < 0) {
        reg_a1 += 0xFF;
    }
    reg_v1 = ((S_80AC5470_1 *)arg0)->unk_02;
    reg_v0 = ((S_80AC5470_1 *)arg0)->unk_32;
    reg_v1 *= reg_v0;
    reg_v0 = reg_a1 >> 8;
    ((S_80AC5470_1 *)arg0)->unk_04.at01.v = (s8) reg_v0;
    if (reg_v1 < 0) {
        reg_v1 += 0xFF;
    }
    reg_v0 = reg_v1 >> 8;
    ((S_80AC5470_1 *)arg0)->unk_04.at02.v = (s8) reg_v0;
    temp_v0 = (u16) ((S_80AC5470_1 *)arg0)->unk_32 - 8;
    ((S_80AC5470_1 *)arg0)->unk_32 = temp_v0;
    ((S_80AC5470_1 *)arg0)->unk_08 = ((S_80AC5470_1 *)arg0)->unk_04.at00u.v;
    if ((temp_v0 << 0x10) <= 0) {
        (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_80AC5470_1_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
/* MECHANISM: Frameless leaf holds arg0 in $a3; guarded short-lived $v0/$v1/$a0/$a1/$a2
   roles reproduce the interleaved accumulator and multiply schedules. Direct scalar
   global RMW removes the +1 cascade; memory barriers force signed-scale reloads, and
   $v0 shift temporaries plus the full-word +4 to +8 copy close the tail. */
