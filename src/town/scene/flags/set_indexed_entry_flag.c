#include "common.h"
#include "m2c_compat.h"
#include "town/player.h"
#include "town/player/script_flags.h"
#include "town/scene/record_actions.h"


typedef struct S_80019958_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_80019958_1;

/* Set the indexed entry flag using its identifier and entry pointer. */
void set_indexed_entry_flag(Rec_func_800165F4_arg0 *record, s32 entry_index) {
    set_script_flag_bit(((S_80019958_1 *)(record->unk_10 + entry_index * 0x10))->unk_0C);
}
