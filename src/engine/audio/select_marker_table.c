#include "common.h"
#include "engine/audio.h"
#include "slus/data.h"

/* D_800847F0: only a single s16 field is ever touched here (sh of 0/1), but
 * the target addresses it via lui/%lo rather than gp-relative, so it must be
 * declared >8 bytes to force %hi/%lo addressing. */
typedef struct S_800847F0 {
    /* 0x0 */ s16 field0;
    /* 0x2 */ u8 pad2[10];
} S_800847F0;

extern S_800847F0 sound_stream_marker_index;

/*
 * Fires event 0x71 and selects the marker table and flag for types 0x21 and 0x22.
 *
 * Marker-table arrays: only their addresses are taken here (matching the sibling usage in
 * src/w_8004437C.c), never dereferenced.
 */
void select_marker_table(s32 marker_code) {
    u8 marker_type = marker_code & 0xFF;

    handle_audio_status_code(0x71);

    switch (marker_type) {
    case 0x21:
        sound_stream_marker_index.field0 = 0;
        build_record_pointer_table(sound_stream_primary_marker_address, 0);
        break;
    case 0x22:
        sound_stream_marker_index.field0 = 1;
        build_record_pointer_table(sound_stream_secondary_marker_address, 1);
        break;
    }
}
