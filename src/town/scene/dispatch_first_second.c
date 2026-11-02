#include "script_symbols.h"
#include "common.h"
#include "town/scene/entry_requests.h"
#include "town/player/script_flags.h"

typedef struct SceneActionEntry {
    u8 pad_00[0x18];
    s16 unk_18;
} UnkStruct;

extern s16 D_80018CFA[5];

/* Processes an entry and applies updates based on its status and the global status. */
s32 dispatch_first(UnkStruct *entry, s32 value) {
    s32 status;

    store_scene_value_pair(entry, value);
    if (get_script_flag_mask(entry->unk_18) != 0) {
        status = get_script_flag_mask(D_80018CFA[0]);
    } else {
        status = 0;
    }

    if (status != 0) {
        clear_script_flag_bit(F_sbs11_pad25);
    } else {
        set_script_flag_bit(F_sbs11_pad25);
    }
    set_script_flag_bit(F_sbs11_pad26);
    return status;
}
