#include "common.h"

typedef struct {
    s32 value[5];
} TownFiveWords;

typedef struct {
    s32 value[4];
} TownFourWords;

extern TownFiveWords D_800894D0;
extern TownFourWords D_800895F0;
extern u8 D_800133A6;
extern u8 D_800133A7;
extern u8 D_800133BA;
extern u8 D_800133BB;
extern u8 D_800133C8;
extern u8 D_800133C9;
extern u8 D_800133E6;
extern s8 D_800133E7[9];

/* Checks fixed value pairs and requires all four table values among five indexed pairs. */
s32 func_800B8C90(void)
{
    TownFiveWords pair_indices = D_800894D0;
    TownFourWords required_values = D_800895F0;
    s32 *required_cursor;
    s32 *pair_index;
    u8 *data_base;
    u8 *pair_base;
    s32 required_value;
    s32 pair_count;
    s32 required_num;
    s32 pair_num;
    s32 expected_value;

    expected_value = 3;
    if (D_800133BA != expected_value) {
        u8 *data_base = (u8 *)0x80010000;

        if (data_base[0x33BB] != expected_value) {
            return 0;
        }
        ASM_KEEP(data_base);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    }
    expected_value = 0x29;
    if (D_800133E6 != expected_value) {
        u8 *data_base = (u8 *)0x80010000;

        if (data_base[0x33E7] != expected_value) {
            return 0;
        }
        ASM_KEEP(data_base);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    }
    expected_value = 7;
    if (D_800133C8 != expected_value) {
        u8 *data_base = (u8 *)0x80010000;

        if (data_base[0x33C9] != expected_value) {
            return 0;
        }
        ASM_KEEP(data_base);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    }
    expected_value = 10;
    if (D_800133A6 != expected_value) {
        register u8 *data_base ASM_REG("$3") = (u8 *)0x80010000;   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

        ASM_KEEP(data_base);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        required_num = 0;
        if (data_base[0x33A7] != expected_value) {
return_zero:
            return 0;
        }
        goto loop_preheader;
    }
    required_num = 0;
loop_preheader:

    data_base = (u8 *)0x80010000;
    pair_count = 5;
    required_cursor = pair_indices.value;
    do {
        pair_num = 0;
        required_value = required_cursor[6];
        pair_index = pair_indices.value;
        do {
            pair_base = (u8 *)((u32)(*pair_index * 2) + (u32)data_base);
            if ((pair_base[0x33A4] == required_value) || (pair_base[0x33A5] == required_value)) {
                break;
            }
            pair_num++;
            pair_index++;
        } while (pair_num < 5);
        if (pair_num == pair_count) {
            goto return_zero;
        }
        required_num++;
        required_cursor++;
    } while (required_num < 4);
    ASM_KEEP(required_cursor);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    return 1;
}

/* MECHANISM: sibling five-word/four-word aggregates create the frameless 0x28 copy layout.
   A shared early zero-return label restores the backward failure edge and removes tail drift.
   Scoped data_base pins plus t0/a3/t1/t2 role pins reproduce the retail loop live ranges.
   Integer-domain index+data_base addition preserves the final addu operand order. */
