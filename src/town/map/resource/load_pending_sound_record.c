#include "common.h"

typedef struct {
    u8 pad[0x18];
    s16 field18;
    s16 field1A;
} GlobalState;

extern GlobalState D_8006ADBC;
extern s16 D_800D4258[];
extern s16 D_800D4260[];

extern void audio_load_sound_effect_bank(s32 record_id);
extern void load_sound_set(s32 state_index);
extern void SD_Call(s32 flags);
extern void drain_audio_commands_and_service_channels(void);
extern u16 *build_four_value_entry_result(s16 unused, s16 index);

/* Loads a four-value record and applies the pending override to its first value. */
void load_pending_sound_record(void) {
    u16 *record_values;
    u16 *current_values;

    SD_Call(0x72);
    drain_audio_commands_and_service_channels();
    SD_Call(0x74);
    drain_audio_commands_and_service_channels();
    audio_load_sound_effect_bank(2);
    load_sound_set(0);

    record_values = build_four_value_entry_result(D_8006ADBC.field18, D_8006ADBC.field1A);
    D_800D4260[0] = record_values[0];
    current_values = D_800D4260;
    current_values[1] = record_values[1];
    current_values[2] = record_values[2];
    current_values[3] = record_values[3];

    if (D_800D4258[0] == -5) {
        D_800D4258[0] = -1;
        D_800D4260[0] = -1;
    }
    if (D_800D4258[0] != -1) {
        D_800D4260[0] = D_800D4258[0];
    }
    if ((s16) D_800D4260[0] != -1) {
        audio_load_sound_effect_bank((s16) D_800D4260[0]);
    }
}
