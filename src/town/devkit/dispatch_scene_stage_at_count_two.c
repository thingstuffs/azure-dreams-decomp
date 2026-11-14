#include "common.h"
#include "town/devkit.h"
#include "town/scene/hooks.h"

typedef struct S_808B2FE4_0 {
    u8 pad_00[0x8];
    s32 * unk_08;
} S_808B2FE4_0;   /* *(void **)0xA0700F5C in dispatch_scene_stage_at_count_two */

typedef struct S_808B2FE4_1 {
    u8 pad_00[0xE];
    u8 unk_0E;
} S_808B2FE4_1;   /* status in dispatch_scene_stage_at_count_two */
extern void func_807002D4(s32 index);
extern s32 dispatch_first_failed_entry(void);

/* When the gate and the counter both pass, refresh the status byte and return the stage handler's result. */
s32 dispatch_scene_stage_at_count_two(s32 entry)
{
    S_808B2FE4_1 *status;

    if ((check_devkit_secondary_condition_8070021c(1) != 0) &&
        (*((S_808B2FE4_0 *)(*(void **)0xA0700F5C))->unk_08 >= 2)) {
        forward_indexed_table_value(1);
        status = *(void **)0xA0700F40;
        status->unk_0E = status->unk_0E;
        return dispatch_first_failed_entry();
    }
    func_807002D4(1);
    return entry;
}
