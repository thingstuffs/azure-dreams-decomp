#include "common.h"
#include "engine/audio/spu.h"
#include "slus.h"
#include "slus/data.h"

/* D_80073828: short flag array (established in code.c: index 0 set by func_8005ACD0). */

/* D_80073734: s32 count array (established elsewhere; index 0 = active-entry count). */
extern s32 audio_voice_count[4];

/* D_80073740: s32 flag-value array, one entry per D_80085458 slot. */
extern s32 audio_voice_masks[];

/* S_8005ACDC_85458: D_80085458 element, stride 0x78; only field f1a (u16, offset
 * 0x1A) is touched by this function. */
typedef struct S_8005ACDC_85458 {
    /* 0x00 */ u8 pad00[0x1A];
    /* 0x1A */ u16 f1a;
    /* 0x1C */ u8 pad1c[0x78 - 0x1C];
} S_8005ACDC_85458;

extern S_8005ACDC_85458 audio_voice_records[64];

/* Advance active entry counters, drain ready flags, and apply the combined flags unless suppressed. */
void drain_ready_sound_voice_flags(void)
{
    s32 entry_index;
    s32 flags;

    flags = 0;
    if (audio_voice_drain_suppressed[0] == 0) {
        for (entry_index = 0; entry_index < audio_voice_count[0]; entry_index++) {
            if (audio_voice_records[entry_index].f1a != 0) {
                if (read_selected_voice_key_state(audio_voice_masks[entry_index]) == 3) {
                    s32 dispatch_state;
                    u32 counter;

                    counter = audio_voice_records[entry_index].f1a;
                    if (counter >= 2) {
                        flags |= audio_voice_masks[entry_index];
                        do {
                            set_spu_voice_keys(0, audio_voice_masks[entry_index]);
                            dispatch_state = read_selected_voice_key_state(audio_voice_masks[entry_index]);
                        } while (dispatch_state != 2 && dispatch_state != 0);
                        audio_voice_records[entry_index].f1a = 0;
                    } else {
                        audio_voice_records[entry_index].f1a = counter + 1;
                    }
                }
            }
        }
    }

    if (flags != 0) {
        set_spu_voice_keys(0, flags);
    }
}
