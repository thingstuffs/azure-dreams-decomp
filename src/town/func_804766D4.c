#include "common.h"

typedef struct {
    s32 unk0;
    s16 value;
    u8 pad[6];
} Entry;

extern s32 func_800198D0(u32);
extern u8 *D_80019BBC[];
extern Entry D_80016470[];
extern u8 D_80016520[];

/* Selects and returns the next eligible entry in the wrapping order list. */
s32 func_800176D4(void)
{
    s32 start_index;
    s32 order_index;
    Entry *entries;
    u8 *order;
    u8 *order_cursor;

    start_index = D_80019BBC[0][4];
    order_index = start_index + 1;
    if (order_index != start_index) {
        entries = D_80016470;
        order = D_80016520;
        order_cursor = &order[order_index];
        do {
            if (*order_cursor == 0) {
                order_cursor = order;
                order_index = 0;
            }
            if (func_800198D0(entries[*order_cursor].value) != 0) {
                break;
            }
            order_index++;
            order_cursor++;
        } while (order_index != start_index);
    }
    D_80019BBC[0][4] = order_index;
    return D_80016520[order_index];
}
