#include "script_symbols.h"
#include "town/scene/entry_requests.h"
#include "common.h"
#include "town/player/script_flags.h"

void store_supplied_values(s32 value_18e44, s32 value_18e48);                /* extern */
void func_80017EB0(s32, s32);                /* extern */
void func_800188CC(s32);                     /* extern */
extern s16 scene_request_flag_id;

/* Conditionally processes 0x50C, then forwards the inputs to both shared routines. */
void store_scene_values_after_flag_check(s32 value, s32 data) {
    if (func_8001894C(F_sbs07_pad21) != 0) {
        if (func_8001894C(scene_request_flag_id) == 0) {
            func_800188CC(F_sbs07_pad21);
        }
    }
    store_supplied_values(value, data);
    func_80017EB0(value, data);
}
