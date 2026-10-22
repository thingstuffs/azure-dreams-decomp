#include "slus/owned_800448BC.h"

#include "slus/owned_800448BC.h"
#include "engine/effect.h"

/* Searches a zero-terminated list for the two arguments truncated to 16-bit keys; returns 1 on a match. */
s32 has_runtime_key_pair(s32 first_value, s32 second_value) {
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
S_80081508 * D_80081508 = 0;
