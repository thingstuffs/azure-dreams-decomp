#include "common.h"

typedef struct S_func_80D1170C_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[1];
    union {
        s32 unk_04;
        struct {
            s8 unk_04;
            s8 unk_05;
            s8 unk_06;
            u8 pad_07[1];
        } bytes;
    } unk_04;
    s32 unk_08;
    u8 pad_0C[0x26];
    union {
        s16 unk_32;
        u16 unk_32_u;
    } unk_32;
    s16 unk_34;
    u8 pad_36[0xA];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    u8 pad_4C[8];
    s32 unk_54;
} S_func_80D1170C_1;

typedef struct S_func_80D1170C_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_func_80D1170C_2;

typedef struct S_func_80D1170C_3 {
    u16 unk_00;
} S_func_80D1170C_3;

extern s32 D_800814A0;

/* Move and fade the effect, apply vertical acceleration, and flag it when its lifetime ends. */
void func_80170F0C(S_func_80D1170C_1 *effect, S_func_80D1170C_2 *position)
{
    s16 life_left;
    s32 red;
    s32 green;
    s32 blue;
    s32 color_product;
    s32 *flag_page;

    position->unk_00 += effect->unk_40;
    position->unk_04 += effect->unk_44;
    position->unk_08 += effect->unk_48;

    color_product = effect->unk_00 * effect->unk_32.unk_32;
    red = color_product / effect->unk_34;
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    color_product = effect->unk_01 * effect->unk_32.unk_32;
    green = color_product / effect->unk_34;
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    color_product = effect->unk_02 * effect->unk_32.unk_32;
    blue = color_product / effect->unk_34;

    effect->unk_48 += effect->unk_54;
    life_left = effect->unk_32.unk_32_u;
    life_left -= 1;
    effect->unk_32.unk_32_u = life_left;
    effect->unk_04.bytes.unk_04 = red;
    effect->unk_04.bytes.unk_05 = green;
    effect->unk_04.bytes.unk_06 = blue;
    effect->unk_08 = effect->unk_04.unk_04;

    if ((life_left << 16) <= 0) {
        ((S_func_80D1170C_3 *)((u8 *)effect - 2))->unk_00 |= 0x8000;
        flag_page = (s32 *)0x80080000;
        flag_page[0x14A0 / sizeof(s32)] =
            flag_page[0x14A0 / sizeof(s32)] | 0x8000;
    }
}

/* MECHANISM: Frameless leaf; a separate color_product temp keeps mflo in v0 while
   quotient lifetimes color a2/a1/a0, with memory barriers forcing each lh reload.
   Split u16 decrement selects addiu; kept 0x80080000 flag_page emits lone lui + 0x14a0. */
