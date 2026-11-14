#include "modules/town_map_props.h"
#include "common.h"
#include "shared/sprite_source.h"
#include "town/map/state.h"
#include "engine/script.h"

typedef struct S_800BDFA0_0 {
    u8 pad_00[0x68];
    u16 unk_68;
    u8 pad_6A[0x36];
    SpriteSourceEntry *unk_A0;
    SpriteSourceEntry *unk_A4;
} S_800BDFA0_0;   /* record in cycle_prop_animation */



/* Advances sprite animation and cycles two animation entries as the script and object checks change. */
void cycle_prop_animation(S_800BDFA0_0 *record, s32 unused, SpriteFrameState *value) {
    s16 state;

    advance_sprite_animation_and_textures(value);
    state = (s16)record->unk_68;
    switch (state) {
    case 0:
        if ((service_script_controller() != 0) && (check_town_target_and_callback(record) != 0)) {
            select_record_entry_and_value(value, record->unk_A4, 0);
            record->unk_68++;
        }
        break;
    case 1:
        if ((service_script_controller() == 0) || (check_town_target_and_callback(record) == 0)) {
            record->unk_68++;
        }
        break;
    case 2:
        if ((service_script_controller() != 0) && (check_town_target_and_callback(record) != 0)) {
            select_record_entry_and_value(value, record->unk_A0, 0);
            record->unk_68++;
        }
        break;
    case 3:
        if ((service_script_controller() == 0) || (check_town_target_and_callback(record) == 0)) {
            record->unk_68 = 0;
        }
        break;
    }
}
