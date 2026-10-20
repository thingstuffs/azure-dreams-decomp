#include "engine/scene/cd_cohort_types.h"

/* Two adjacent scalar globals (loaded/stored individually via $gp) that are
 * also treated as one small struct when their combined address is taken. */

/* >8B neighbour spanning 0x800814AC..0x800814B7 (established in w_8003D5A4.c),
 * used to synthesize the hi/lo address-of D_800814B0 (offset 4 into it) per
 * the dual-access-global split-declaration technique. */
extern u8 runtime_saved_state_byte_04_alias[12];

typedef struct {
    s32 f0;
    s32 f4;
} S_8003F2A4_pair;

/* Copy a type 6 ring-head entry's pair to globals and repoint it there, or clear the entry's type. */
void update_cd_queue_head_entry(SlusCdQueueEntry *entry) {
    if (entry->unk00 != 6 ||
        entry != &cd_command_records[cd_command_read_index]) {
        entry->unk00 = 0;
        return;
    }
    cd_queue_buffered_argument_word_0 = ((S_8003F2A4_pair *)(*(u32 *)((u8 *)entry + 4)))->f0;
    cd_queue_buffered_argument_word_1 = ((S_8003F2A4_pair *)(*(u32 *)((u8 *)entry + 4)))->f4;
    (*(u32 *)((u8 *)entry + 4)) = (u32)&runtime_saved_state_byte_04_alias[4];
}
