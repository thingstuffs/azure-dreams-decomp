#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"

extern s16 scene_request_flag_id;
extern s32 D_80018B00;
extern s32 D_80019A30;
extern s32 D_80019ACC;

extern void apply_entry_keyed_values(void *, void *, s32);
extern s32 resolve_entry_flag(void *entry_table, void *context, s32 entry_key); /* placed copy of resolve_entry_flag */

/* Prepare request state and select a result buffer based on status checks. */
void *prepare_scene_request_state(void *request_id, s32 unused, s32 request_value)
{
    void *request_state = &D_80018B00;

    apply_entry_keyed_values(request_state, request_id, request_value);
    if (((get_script_flag_mask(scene_request_flag_id) == 0) &&
         (resolve_entry_flag(request_state, request_id, request_value) == 0)) ||
        (get_script_flag_mask(F_sbs07_pad21) == 0)) {
        set_script_flag_bit(F_sbs07_pad21);
        return &D_80019ACC;
    }
    return &D_80019A30;
}
