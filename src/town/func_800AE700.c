#include "common.h"

typedef struct {
    u8 a;
    u8 b;
    u8 pad2;
    u8 pad3;
} S_80081508;

extern s32 has_runtime_key_pair(s32, s32);
extern s16 D_80080B04[5];
extern S_80081508 *D_80081508[3];

/* Appends an accepted byte pair to the first list and marks its end. */
void append_valid_key_pair(s32 first_value, s32 second_value) {
    S_80081508 *entry;

    if (D_80080B04[0] < 64) {
        if ((s16)has_runtime_key_pair((u16)first_value, (u16)second_value) == 0) {
            entry = &D_80081508[0][D_80080B04[0]];
            entry->a = (u8)first_value;
            entry->b = (u8)second_value;
            D_80080B04[0]++;
            entry[1].a = 0;
        }
    }
}
