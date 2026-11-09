#include "script_symbols.h"
#include "common.h"
#include "town/scene/entry_requests.h"
#include "town/player/script_flags.h"
#include "town/scene.h"

typedef struct SceneActionEntry {
    u8 pad_00[0x18];
    s16 unk_18;
} SceneActionEntry;

extern s16 D_80018CFA[5];

/* Update the object and select the action for 0x5BC from the combined status checks. */
s32 update_scene_and_select_action(SceneActionEntry *object, s32 value) {
    s32 status;

    store_scene_value_pair(object, value);
    if (get_script_flag_mask(object->unk_18) != 0) {
        status = get_script_flag_mask(D_80018CFA[0]);
    } else {
        status = 0;
    }

    if (status != 0) {
        clear_script_flag_bit(F_sbs11_pad25);
    } else {
        set_script_flag_bit(F_sbs11_pad25);
    }
    return status;
}
