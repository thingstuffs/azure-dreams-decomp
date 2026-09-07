#include "common.h"

extern s16 D_800D253C[66];
extern s16 D_800D25C0[66];

void func_80033AA8(s16 value);
void func_80033AE8(s16 value);

void func_800C0C88(void)
{
    s32 first;
    s32 index;

    first = D_800D253C[0];
    index = 0;
    do { index = 0; } while (0);
    if (first != 0) {
        s16 *left;
        s16 *right;
        u8 *table;
        u8 *record;
        u8 kind;

        table = (u8 *)0x80010000U;
        left = &D_800D253C[index];
        right = D_800D25C0;
        record = table;

loop:
        kind = table[index * 4 + 0x981];
        if (kind == 0) goto zero_kind;
        if (kind != 0x13) goto ordinary;
        if (record[0xAC4] == 0) goto ordinary;

        func_80033AE8(*left);
        left++;
        func_80033AA8(*right);
        right++;
        record += 0x54;
        goto check;

ordinary:
        func_80033AA8(*left);
        goto common;

zero_kind:
        func_80033AE8(*left);

common:
        func_80033AE8(*right);
        left++;
        right++;
        record += 0x54;

check:
        index++;
        if (*left != 0) goto loop;
    }
}
