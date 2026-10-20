#include "common.h"

typedef struct {
    u8 pad_00[0x2C];
    s32 field_2C;
    u8 pad_30[0x50 - 0x30];
} Slot;

extern s32 audio_sequence_track_count[3];
extern Slot audio_sequence_tracks[];

/* Return 1 if any slot is active, or 3 if all slots are finished. */
s32 get_sequence_play_state(void) {
    u32 i;
    for (i = 0; i < audio_sequence_track_count[0]; i++) {
        if (audio_sequence_tracks[i].field_2C == 0) {
            return 1;
        }
    }
    return 3;
}
