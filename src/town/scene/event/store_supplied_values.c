#include "script_symbols.h"
#include "town/scene/entry_requests.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene/event.h"

extern void func_8001611C(s32 value_18e44, s32 value_18e48); /* placed copy of set_global_entry_pair */
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
    func_8001611C(value, data);
    func_80017EB0(value, data);
}
