#include "common.h"
#include "engine/audio/sequence.h"

/* S_80086C00: 12-byte-stride entry table (8 entries), indexed by the "slot
 * index" arg0. field_0/field_2 are s16, field_4 is a s32 buffer/base
 * pointer value, field_8/field_A are u16 (not accessed here). */
typedef struct {
    /* 0x00 */ s16 field_0;
    /* 0x02 */ s16 field_2;
    /* 0x04 */ s32 field_4;
    /* 0x08 */ u16 field_8;
    /* 0x0A */ u16 field_A;
} S_80086C00; /* size 0xC (12) */

extern S_80086C00 audio_sequence_slots[8];
extern s16 audio_current_bank_slot[8];  /* forced hi/lo access via size > 8 */
extern s16 audio_active_sequence_sub_id[8];  /* forced hi/lo access via size > 8 */
extern s32 audio_sequence_stream_limit[4];  /* forced hi/lo access via size > 8 */
extern s32 audio_sequence_data_base[4];  /* forced hi/lo access via size > 8 */
extern s32 audio_sequence_active[4];  /* forced hi/lo access via size > 8 */
extern s32 audio_update_guard[4];  /* forced hi/lo access via size > 8 */

/* Activates an occupied slot with the requested sub-id and mode. */
void sound_activate_loaded_sequence_slot(s16 slot_index, u8 mode, s16 sub_id)
{
    if (slot_index != -1) {
        audio_reset_sequence_tracks_and_channels();
        if (audio_sequence_slots[slot_index].field_0 != -1) {
            audio_current_bank_slot[0] = audio_sequence_slots[slot_index].field_0;
            audio_active_sequence_sub_id[0] = sub_id;
            audio_sequence_stream_limit[0] = 0x10000;
            audio_sequence_data_base[0] = audio_sequence_slots[slot_index].field_4;
            func_800599B0();
            if (!(mode & 0xFF)) {
                audio_sequence_active[0] = 0;
                audio_update_guard[0] = 1;
                audio_sequence_slots[slot_index].field_2 = 4;
            } else {
                audio_sequence_active[0] = 1;
                audio_update_guard[0] = 0;
                audio_sequence_slots[slot_index].field_2 = 1;
            }
        }
    }
}
