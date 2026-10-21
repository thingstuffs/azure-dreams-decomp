#include "common.h"
#include "engine/util.h"

/* see src/code2.c sibling audio_set_all_track_tempo_steps: same D_80085FA8 array-of-structs / D_800869B4 count idiom */

extern int audio_sequence_track_count[3];

typedef struct {
    int field_00;
    char pad_04[0x2C - 0x04];
    int field_2C;
    char pad_30[0x50 - 0x30];
} Struct_80059D1C_80085FA8;

extern Struct_80059D1C_80085FA8 audio_sequence_tracks[];

/* Sets field_2C to 1 and clears field_00 for each active entry. */
void activate_entries_and_clear_state(void) {
    int one;
    unsigned int entry_index = 0;
    unsigned int entry_count;

    if (audio_sequence_track_count[0] != 0) {
        one = 1;
        entry_count = audio_sequence_track_count[0];
        do {
            audio_sequence_tracks[entry_index].field_2C = one;
            audio_sequence_tracks[entry_index].field_00 = 0;
            entry_index++;
        } while (entry_index < entry_count);
    }
}
