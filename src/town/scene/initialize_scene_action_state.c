#include "script_symbols.h"
#include "common.h"
#include "town/scene/entry_requests.h"
#include "town/player/script_flags.h"
#include "town/scene.h"
#include "town/scene/event.h"

typedef struct SceneActionEntry {
    u8 pad_00[0x18];
    s16 unk_18;
} SceneActionEntry;

extern s16 D_80018CFA[5];

/* Initializes the object and selects follow-up actions from status checks. */
s32 initialize_scene_action_state(SceneActionEntry *object, s32 value) {
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
        if (get_script_flag_mask(Frg_vivian_fine) != 0) {
            forward_stored_pair();
            return 1;
        }
        set_script_flag_bit(F_sbs11_pad25);
        set_script_flag_bit(F_sbs11_pad27);
        set_script_flag_bit(F_sbs11_pad34);
    }
    return status;
}
