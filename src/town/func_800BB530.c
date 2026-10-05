#include "common.h"
extern u8 D_80010000[];

typedef struct {
    s32 value[5];
} TownFiveWords;

typedef struct {
    s32 value[4];
} TownFourWords;

extern TownFiveWords D_800894D0;
extern TownFourWords D_800895F0;
extern u8 D_800133A6;
extern u8 D_800133BA;
extern u8 D_800133C8;
extern u8 D_800133E6;

/* Checks fixed value pairs and requires all four table values among five indexed pairs. */
s32 func_800B8C90(void)
{
    TownFiveWords pair_indices = D_800894D0;
    TownFourWords required_values = D_800895F0;
    u8 *pair_base;
    s32 required_value;
    s32 required_num;
    s32 pair_num;
    u8 *data_base;
    s32 pair_count;
    s32 expected_value;

    expected_value = 3;
    if (D_800133BA != expected_value) {
        pair_base = D_80010000;
        if (pair_base[0x33BB] != expected_value) {
            return 0;
        }
    }
    expected_value = 0x29;
    if (D_800133E6 != expected_value) {
        pair_base = D_80010000;
        if (pair_base[0x33E7] != expected_value) {
            goto return_zero;
        }
    }
    expected_value = 7;
    if (D_800133C8 != expected_value) {
        pair_base = D_80010000;
        if (pair_base[0x33C9] != expected_value) {
            goto return_zero;
        }
    }
    expected_value = 10;
    if (D_800133A6 != expected_value) {
        pair_base = D_80010000;
        if (pair_base[0x33A7] != expected_value) {
return_zero:
            return 0;
        }
    }
    required_num = 0;
    data_base = (u8 *)0x80010000;
    pair_count = 5;
    do {
        pair_num = 0;
        required_value = required_values.value[required_num];
        do {
            pair_base = (u8 *)((u32)(pair_indices.value[pair_num] * 2) + (u32)data_base);
            if ((pair_base[0x33A4] == required_value) || (pair_base[0x33A5] == required_value)) {
                break;
            }
            pair_num++;
        } while (pair_num < 5);
        if (pair_num == pair_count) {
            goto return_zero;
        }
        required_num++;
    } while (required_num < 4);
    return 1;
}
