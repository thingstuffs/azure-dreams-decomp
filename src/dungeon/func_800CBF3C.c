#include "common.h"

typedef struct {
    u8 x;
    u8 y;
    s16 value;
} Record;

extern s16 D_80080B04[5];
extern Record *D_80081508[3];

extern s32 func_800448BC(s32 x, s32 y);

/* Appends a coordinate record with a value or sentinel if capacity and the position check allow. */
void func_800D169C(s32 x, s32 y, s32 value, s32 store_value)
{
    s32 has_room;
    s16 record_x;
    s16 record_y;
    Record *record;
    volatile u16 *counter_page;

    has_room = D_80080B04[0] < 64;
    record_x = x;
    record_y = y;
    if (has_room) {
        if ((s16)func_800448BC((u16)record_x, (u16)record_y) == 0) {
            record = &D_80081508[0][D_80080B04[0]];
            record->x = record_x;
            record->y = record_y;
            if ((s16)store_value != 0) {
                record->value = value;
            } else {
                record->value = (s16)0x8000;
            }
            counter_page = (volatile u16 *)0x80080000;
            counter_page[0x582]++;
            record[1].x = 0;
        }
    }
}

