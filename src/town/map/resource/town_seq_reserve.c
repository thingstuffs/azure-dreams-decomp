#include "common.h"
#include "m2c_compat.h"

extern u8 town_pending_sound[];

typedef struct S_800C17A0_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
} S_800C17A0_0;   /* base in town_seq_reserve */

/* town_seq_reserve: reserve the town sequence pair. */
void town_seq_reserve(s16 sequence_effect, s16 sequence_id) {
    S_800C17A0_0 *reserved_sound;

    reserved_sound = (S_800C17A0_0 *)town_pending_sound;
    reserved_sound->unk_04 = sequence_effect;
    reserved_sound->unk_06 = sequence_id;
}
