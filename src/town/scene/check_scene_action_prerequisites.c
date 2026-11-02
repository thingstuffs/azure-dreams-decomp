#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene.h"
#include "town/scene/flags.h"

extern u8 D_8001AADC[16];
extern u8 D_8001ADE7[16];
extern u8 D_8001AE39[16];

/* Checks prerequisites, conditionally performs an action, and returns its response. */
void *check_scene_action_prerequisites(void *object, s32 action_arg) {
    void *response;

    if (get_script_flag_mask(*(s16 *)((u8 *)object + 0x18)) == 0) {
        set_script_flag_bit(*(s16 *)((u8 *)object + 0x18));
        return D_8001AADC;
    }
    if (check_callback_record_bytes(13, 5) == 0) {
        response = D_8001ADE7;
    } else {
        set_indexed_entry_flag(object, action_arg);
        response = D_8001AE39;
    }
    return response;
}
