#include "common.h"

typedef struct S_800D6804_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800D6804_0;   /* state in func_800D6804 */

typedef struct S_800D6804_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x1];
    union { struct { u8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
    u8 pad_0C[0x26];
    union { s16 s; u16 u; } unk_32;   /* accessed as both */
    s16 unk_34;
} S_800D6804_1;   /* arg0 in func_800D6804 */



extern s32 D_800814A0;

void func_800D6804(void *arg0, void *arg1)
{
    s16 timer;

    {
        register void *state ASM_REG("$7");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        register s32 amount ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
        s32 scaled;
        register s32 addend ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
        s32 current;
        s32 quarter;

        state = arg1;
        amount = ((S_800D6804_0 *)state)->unk_14;
        current = ((S_800D6804_0 *)state)->unk_08;
        scaled = amount << 1;
        addend = amount;
        ASM_KEEP(addend);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        scaled += amount;
        current += addend;
        ((S_800D6804_0 *)state)->unk_08 = current;
        if (scaled < 0) {
            scaled += 3;
        }
        quarter = scaled >> 2;
        ((S_800D6804_0 *)state)->unk_14 = quarter;
    }

    ((S_800D6804_1 *)arg0)->unk_04.at00.v =
        (((S_800D6804_1 *)arg0)->unk_00 * ((S_800D6804_1 *)arg0)->unk_32.s) /
        ((S_800D6804_1 *)arg0)->unk_34;
    ((S_800D6804_1 *)arg0)->unk_04.at01.v =
        (((S_800D6804_1 *)arg0)->unk_01 * ((S_800D6804_1 *)arg0)->unk_32.s) /
        ((S_800D6804_1 *)arg0)->unk_34;
    ((S_800D6804_1 *)arg0)->unk_04.at02.v =
        (((S_800D6804_1 *)arg0)->unk_02 * ((S_800D6804_1 *)arg0)->unk_32.s) /
        ((S_800D6804_1 *)arg0)->unk_34;

    timer = ((S_800D6804_1 *)arg0)->unk_32.u - 1;
    ((S_800D6804_1 *)arg0)->unk_32.s = timer;
    ((S_800D6804_1 *)arg0)->unk_08 = ((S_800D6804_1 *)arg0)->unk_04.at00u.v;
    if ((timer << 16) <= 0) {
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: The true-space function is a frameless leaf; state stays in a3 while arg0 stays in a2.
   A split shift/copy/add fixes the opening live ranges, and the tail copies the full word at +4.
   Direct scalar RMW plus moved-source orientation at 2.7.2-cdk-G0 closes the final coloring. */
