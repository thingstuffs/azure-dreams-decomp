#include "common.h"

typedef struct {
    u8 a;
    u8 b;
    u8 pad2;
    u8 pad3;
} S_80081508;

extern S_80081508 *D_80081508;

/* Returns whether the terminated record array contains both input values truncated to 16 bits. */
s32 func_800448BC(s32 first_value, s32 second_value) {
    u16 first_key = (u16)first_value;
    u16 second_key = (u16)second_value;
    S_80081508 *record = D_80081508;

    if (record->a != 0) {
        do {
            if (record->a == first_key && record->b == second_key) {
                return 1;
            }
            record += 1;
        } while (record->a != 0);
    }
    return 0;
}
