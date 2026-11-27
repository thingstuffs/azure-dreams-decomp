#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene.h"
#include "town/scene/flags.h"

extern u8 library_first_entry_response[16];
extern u8 D_8001ADE7[16];
extern u8 D_8001AE39[16];

/* Checks prerequisites, conditionally performs an action, and returns its response. */
void *select_entry_response_and_set_flag(TownObjectSet *object, s32 action_arg) {
    void *response;

    if (get_script_flag_mask(object->entry_flag) == 0) {
        set_script_flag_bit(object->entry_flag);
        return library_first_entry_response;
    }
    if (check_callback_record_bytes(13, 5) == 0) {
        response = D_8001ADE7;
    } else {
        set_indexed_entry_flag(object, action_arg);
        response = D_8001AE39;
    }
    return response;
}
