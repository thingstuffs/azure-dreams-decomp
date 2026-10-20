#include "common.h"

/* S_80086C00: 12-byte-stride sound-driver "sequence slot" table (8 entries),
 * indexed by the slot index arg0. Canonical layout established by sibling
 * functions (w_8005AE08.c, w_8005AE90.c, w_8005B27C.c, w_8005C5D0.c). */
typedef struct S_80086C00 {
    s16 field_0;   /* 0x0: -1 == free slot */
    s16 field_2;   /* 0x2: type/status */
    s32 field_4;   /* 0x4: data pointer / word value */
    u16 field_8;   /* 0x8 */
    u16 field_A;   /* 0xA */
} S_80086C00;

extern S_80086C00 audio_sequence_slots[8];
extern s32 audio_update_guard[4]; /* forced hi/lo access via size > 8 */

extern void activate_entries_and_clear_state(void);
extern void audio_reset_sequence_tracks_and_channels(void);

/* Resets a sound sequence slot to its free/default state. */
void sound_free_sequence_slot(s32 slot_id)
{
    s16 slot_index;

    audio_update_guard[0] = 1;
    activate_entries_and_clear_state();
    audio_reset_sequence_tracks_and_channels();
    slot_index = (s16)slot_id;

    audio_sequence_slots[slot_index].field_0 = -1;
    audio_sequence_slots[slot_index].field_2 = 0;
    audio_sequence_slots[slot_index].field_A = 0x7F;
    audio_sequence_slots[slot_index].field_8 = 0x7F;

    audio_update_guard[0] = 0;
}
