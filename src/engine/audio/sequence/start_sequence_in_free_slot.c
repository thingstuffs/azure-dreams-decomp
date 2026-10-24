#include "common.h"
#include "engine/audio/sequence.h"
#include "engine/audio/spu.h"

/* D_80073734: s32 count array (established elsewhere; index 0 = active-entry count). */
extern s32 audio_voice_count[4];

/* D_80073740: s32 flag-value array, one entry per D_80085458 slot. */
extern s32 audio_voice_masks[24];

/* S_80085458: D_80085458 element, stride 0x78 (120) bytes; only field f1a
 * (u16, offset 0x1A) is touched by this function. */
typedef struct S_80085458 {
    /* 0x00 */ u8 pad00[0x1A];
    /* 0x1A */ u16 f1a;
    /* 0x1C */ u8 pad1c[0x78 - 0x1C];
} S_80085458;

extern S_80085458 audio_voice_records[24];

/* D_80085F98: mode/busy flag, set while this function runs. */
extern s32 audio_update_guard[4];

#include "engine/audio/channel_voice.h"

/* Dispatches to the first done or empty slot and returns the result, or -1 if none is available. */
s16 start_sequence_in_free_slot(s16 bank, s16 program, s16 tone, s16 note, s16 fine_note,
    s16 left_gain, s16 right_gain)
{
    s32 slot;

    audio_update_guard[0] = 1;

    slot = 0;
    while (SpuGetKeyStatus(audio_voice_masks[slot]) != 0) {
        slot++;
        if (slot > audio_voice_count[0] - 1) {
            slot = -1;
            break;
        }
    }

    if (slot == -1) {
        slot = 0;
        while (1) {
            if (audio_voice_records[slot].f1a == 0) {
                break;
            }
            slot++;
            if (slot > audio_voice_count[0] - 1) {
                slot = -1;
                break;
            }
        }
    }

    if (slot != -1) {
        slot = (s16) start_voice_on_channel((s16) slot, bank, program, tone, note, fine_note,
            left_gain, right_gain);
    }

    audio_update_guard[0] = 0;
    return slot;
}
