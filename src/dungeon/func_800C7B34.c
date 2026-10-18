#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CD294_0 {
    void * unk_00;
    u8 pad_04[0x23];
    u8 unk_27;
    u8 pad_28[0x74];
    s16 unk_9C;
} S_800CD294_0;   /* arg0 in check_trap_record_and_trigger_effects; pointer addresses record offset 0x14 */

typedef struct S_800CD294_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800CD294_1;


/* cfail-repair: tf7-phase1-cache-v3 */

extern s32 D_800DCF14;
extern void adjust_source_value_and_finalize();
extern s32 play_sound_if_enabled();
extern void display_fixed_item_action_message();
extern void * spawn_randomized_particle_burst();
s32 roll_threshold_effect_variant_b();        /* extern */
void wrap_position_and_set_state_value();                         /* extern */
extern M2C_UNK D_800E1C03;

/* Checks the record and triggers the associated visual and sound effects on success. */
s32 check_trap_record_and_trigger_effects(void *record_data) {
        /* Retail forwards the current argument registers into display_fixed_item_action_message
       untouched; this row never writes the fourth argument. */
    M2C_UNK check_mask;
    S_800CD294_1 *entity;

    check_mask = 0x40;
    if (D_800E3D40 != 0) {
        check_mask = 0x400;
    }
    if (roll_threshold_effect_variant_b(record_data, check_mask, 0x10) == 0) {
        if (((S_800CD294_0 *)((u8 *)record_data - 0x14))->unk_27 == 0) {
            display_fixed_item_action_message();
            return 1;
        }
        return 1;
    }
    adjust_source_value_and_finalize(record_data, &D_800E1C03);
    if (((S_800CD294_0 *)((u8 *)record_data - 0x14))->unk_27 == 0) {
        wrap_position_and_set_state_value(D_800DCF14);
    }
    entity = ((S_800CD294_0 *)((u8 *)record_data - 0x14))->unk_00;
    if (!(entity->unk_14 & 0x8000)) {
        spawn_randomized_particle_burst((entity->unk_24 << 6) | 0x20, (entity->unk_25 << 6) | 0x20,
            ((S_800CD294_0 *)((u8 *)record_data - 0x14))->unk_9C, 0xFFFFFF, 0x40, 0);
        play_sound_if_enabled(0x612);
    }
    return 1;
}
