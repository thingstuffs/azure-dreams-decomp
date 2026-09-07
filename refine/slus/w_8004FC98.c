#include "common.h"

#include "common.h"

extern s32 func_80018174(s32, s32, s32, s32, s32);
extern void func_8004F884(void *);
extern u8 D_80071784[];

/* Initializes items using the selected table row, then activates and updates the state. */
s32 func_8004FC98(void *state) {
    s32 item_result;
    s32 item_index;
    u8 position;
    u8 *slot;
    u8 *table;
    u8 *row;

    item_index = 0;
    if (*(s32 *)((u8 *)state + 0x24) > 0) {
        table = D_80071784;
        slot = state;
loop:
#ifdef NON_MATCHING
        row = table + *(s32 *)((u8 *)state + 0x30) * 3;
#else
        row = (u8 *)((u32)(*(s32 *)((u8 *)state + 0x30) * 3) + (u32)table);
#endif
        position = row[item_index];
        item_result = func_80018174(*(s32 *)(slot + 0x10), item_index, 0x18,
                               position * 0xC - 0x40,
                               position * 0x1E + 0x200);
        *(s32 *)(slot + 4) = item_result;
        if (item_result == 0) {
            return 0;
        }
        item_result = *(s32 *)((u8 *)state + 0x24);
        item_index++;
        slot += 4;
        if (item_index < item_result) {
            goto loop;
        }
    }

    *(s32 *)((u8 *)state + 0x2C) = 1;
    *(s32 *)((u8 *)state + 0x28) = 1;
    func_8004F884(state);
    return 1;
}
