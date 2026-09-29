#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"


extern void func_8001ACA0(s16 *result);
extern u8 D_8001F244[];
extern u8 D_8001F288[];

typedef s32 (*TownCallback)(s32, u8, s32, s32);


/* Invokes the town callback for an enabled entry using its mode and adjusted position. */
void func_803334D4(s32 slot_id)
{
    s16 position[2];
    u8 entry_index;
    u8 *entry;
    u8 mode;
    s32 x;
    s32 y;

    0 >> 0;
    entry_index = D_8001F244[slot_id];
    if (entry_index != 0x1C) {
        u8 *entries = D_8001F288;
        entry = &entries[entry_index * 3];
        if (entry[2] != 0) {
            func_8001ACA0(position);
            mode = entry[1];
            x = (entry[0] << 6) + position[0] + 0x20;
            y = position[1] - 0x40;
            (*(TownCallback *)((u8 *)(D_80016000->unk_20) + 0x264))(
                0xF,
                mode,
                x,
                y);
        }
    }
}
