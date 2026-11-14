#include "common.h"
#include "town/scene/flags.h"
#include "town/scene.h"



typedef struct S_800166B0_1 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_800166B0_1;   /* ((attach_scene_event_data_and_run_callback(arg0, arg2) * 8) + arg0) in query_entry_flag_by_key */

typedef struct S_800166B0_2 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_800166B0_2;   /* ((((S_800166B0_1 *)(((attach_scene_event_data_and_run_callback(arg0, arg2) * 8) + arg0)))->unk_02 * 4) + arg1->unk_14) in query_entry_flag_by_key */

s32 select_data_array_based_flag(s32 flagIndex);

typedef struct S_800166B0_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800166B0_0;   /* arg1 in query_entry_flag_by_key */

/* Look up an entry and query its associated flag. */
void query_entry_flag_by_key(s32 entries, S_800166B0_0 *context, s32 entry_key) {
    select_data_array_based_flag(((S_800166B0_2 *)(((((S_800166B0_1 *)(((find_entry_index_or_assert(entries, entry_key) * 8)
        + entries)))->unk_02 * 4) + context->unk_14)))->unk_02);
}
