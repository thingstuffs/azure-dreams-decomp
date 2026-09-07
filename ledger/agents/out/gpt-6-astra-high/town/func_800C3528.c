#include "common.h"

extern s16 D_800D253C[66];
extern s16 D_800D25C0[66];

void func_80033AA8(s16 value);
void func_80033AE8(s16 value);

/* Dispatch paired table values according to each entry's kind and record flag. */
void func_800C0C88(void)
{
    s32 first_value;
    s32 entry_index;

    first_value = D_800D253C[0];
    entry_index = 0;
    do { entry_index = 0; } while (0);
    if (first_value != 0) {
        s16 *primary_value;
        s16 *secondary_value;
        u8 *table_base;
        u8 *record_base;
        u8 entry_kind;

        table_base = (u8 *)0x80010000U;
        primary_value = &D_800D253C[entry_index];
        secondary_value = D_800D25C0;
        record_base = table_base;

loop:
        entry_kind = table_base[entry_index * 4 + 0x981];
        if (entry_kind == 0) goto zero_kind;
        if (entry_kind != 0x13) goto ordinary;
        if (record_base[0xAC4] == 0) goto ordinary;

        func_80033AE8(*primary_value);
        primary_value++;
        func_80033AA8(*secondary_value);
        secondary_value++;
        record_base += 0x54;
        goto check;

ordinary:
        func_80033AA8(*primary_value);
        goto common;

zero_kind:
        func_80033AE8(*primary_value);

common:
        func_80033AE8(*secondary_value);
        primary_value++;
        secondary_value++;
        record_base += 0x54;

check:
        entry_index++;
        if (*primary_value != 0) goto loop;
    }
}
