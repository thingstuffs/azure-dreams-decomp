#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/record_actions.h"


typedef struct S_80016844_2 {
    u8 pad_00[0x4];
    s8 unk_04;
} S_80016844_2;   /* ((((S_80016844_1 *)(D_80016000[0]))->unk_08 * 8) +
                   ((S_80016844_1 *)(D_80016000[0]))->unk_40) in run_object_handler_and_clear_entry */

typedef struct S_80016844_3 {
    u8 pad_00[0x4];
    s8 unk_04;
} S_80016844_3;   /* ((((S_80016844_1 *)(D_80016000[0]))->unk_08 * 8) +
                       ((S_80016844_1 *)(D_80016000[0]))->unk_40) in run_object_handler_and_clear_entry */


extern s32 func_800177CC(void *object, s32 entryIndex);
extern void initialize_state_two_entries_pointer(s32 bit_index);
extern s32 func_8001868C(s32 flagIndex);

/* Runs the selected object handler and clears the current entry status. */
s32 run_object_handler_and_clear_entry(Rec_func_800165F4_arg0 *object, s32 context) {
    s32 result;

    result = 0;
    if (func_8001868C(F_s34_sero_quickstart) != 0) {
        initialize_state_two_entries_pointer(object->unk_18);
        ((S_80016844_2 *)(((town_scene_root->entry_index * 8) +
                   ((s32)town_scene_root->event_data))))->unk_04 = 0;
        return func_800177CC(object, context);
    }
    if (func_8001868C(F_s34_sero_start) != 0) {
        initialize_state_two_entries_pointer(object->unk_18);
        result = func_800176B8(object, context);
        if (result != 0) {
            ((S_80016844_3 *)(((town_scene_root->entry_index * 8) +
                       ((s32)town_scene_root->event_data))))->unk_04 = 0;
        }
    }
    return result;
}
