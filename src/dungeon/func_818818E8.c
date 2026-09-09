#include "common.h"

typedef struct S_800250E8_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800250E8_0;   /* arg1 in func_800250E8 */

typedef struct S_800250E8_1_pre {
    u16 unk_00;
} S_800250E8_1_pre;   /* the 0x2 bytes before arg0 in func_800250E8, addressed as arg0[-1] */

typedef struct S_800250E8_1 {
    u8 pad_00[0x1A];
    s16 unk_1A;
    union { s16 s; u16 u; } unk_1C;   /* accessed as both */
    u8 pad_1E[0x8];
    s16 unk_26;
} S_800250E8_1;   /* arg0 in func_800250E8 */

typedef struct S_800250E8_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800250E8_2;   /* tail_arg in func_800250E8 */



extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_80069EF8(void);
extern s16 func_800BCB04(u16, u16, s16);

extern u16 D_800257CE[5];
extern s32 D_800814A0[3];

__asm__(".set D_800257CE, 0x800257CE");

void func_800250E8(void *arg0, S_800250E8_0 *arg1, void *arg2)
{
    register void *tail_arg ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 temp_v0;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_v0_8;
    register s32 temp_v1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 temp_lo;
    s32 random_value;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 call_arg0;
    s32 call_arg1;
    s16 call_arg2;
    u16 counter;
    u16 *counter_ptr;

    tail_arg = arg2;
    ASM_KEEP_NV(tail_arg);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    counter_ptr = D_800257CE;
    call_arg0 = arg1->unk_00.at02.v;
    counter = counter_ptr[0];
    call_arg2 = arg1->unk_08.at02.v;
    call_arg1 = arg1->unk_04.at02.v;
    counter++;
    call_arg2 -= 2;
    counter_ptr[0] = counter;
    if (arg1->unk_08.at02u.v <
        func_800BCB04(call_arg0, call_arg1, call_arg2)) {
        if (((S_800250E8_1 *)arg0)->unk_26 == 0) {
            temp_s0 = func_80064584(((S_800250E8_1 *)arg0)->unk_1A);
            arg1->unk_00.at00.v = (s32)(arg1->unk_00.at00.v +
                (((s32)(temp_s0 * ((S_800250E8_1 *)arg0)->unk_1C.s) >> 4) +
                 (func_80069EF8() & 0xFFFF)));

            temp_s0_2 = func_800644B8(((S_800250E8_1 *)arg0)->unk_1A);
            temp_a0 = ((temp_s0_2 * ((S_800250E8_1 *)arg0)->unk_1C.s) >> 4) +
                       (func_80069EF8() & 0xFFFF);
            arg1->unk_04.at00.v = (s32)(arg1->unk_04.at00.v + temp_a0);

            random_value = func_80069EF8();
            arg1->unk_08.at00.v = (s32)(arg1->unk_08.at00.v +
                (0xFFFE0000 - (random_value & 0xFFF)));
        } else {
            arg1->unk_00.at00.v = (s32)(arg1->unk_00.at00.v +
                func_80064584(((S_800250E8_1 *)arg0)->unk_1A) *
                ((S_800250E8_1 *)arg0)->unk_1C.s * 8);
            temp_lo = func_800644B8(((S_800250E8_1 *)arg0)->unk_1A) *
                      ((S_800250E8_1 *)arg0)->unk_1C.s;
            temp_a0_2 = arg1->unk_14;
            temp_v1 = temp_a0_2;
            ASM_KEEP_NV(temp_v1);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            temp_v0_8 = arg1->unk_08.at00.v;
            arg1->unk_14 = temp_v1 + 0x6000;
            arg1->unk_08.at00.v = (s32)(temp_v0_8 + temp_a0_2);
            arg1->unk_04.at00.v = (s32)(arg1->unk_04.at00.v + temp_lo * 8);
        }
    }

    temp_v0 = ((S_800250E8_1 *)arg0)->unk_1C.u - 1;
    ((S_800250E8_1 *)arg0)->unk_1C.s = temp_v0;
    if ((temp_v0 << 16) <= 0 ||
        (((S_800250E8_2 *)tail_arg)->unk_14 & 0x8000)) {
        ((S_800250E8_1_pre *)arg0)[-1].unk_00 = (u16)(((S_800250E8_1_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
