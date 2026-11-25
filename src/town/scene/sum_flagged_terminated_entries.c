#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene.h"
#include "shared/town_root.h"

typedef s32 (*Callback)(struct DungeonItemEntry *);


/* Sum callback results for flagged entries in a terminated four-byte entry list. */
s32 sum_flagged_terminated_entries(void *entry, s32 callback_mode) {
    s32 total;
    Callback callback;

    total = 0;
    while (((u8 *)entry)[1] != 0) {
        if (((u8 *)entry)[3] & 0x20) {
            if (callback_mode == 0) {
                callback = town_scene_root->services->get_item_buy_money;
            } else {
                callback = town_scene_root->services->callback_06C;
            }
            total += callback(entry);
        }
        entry += 4;
    }
    return total;
}
