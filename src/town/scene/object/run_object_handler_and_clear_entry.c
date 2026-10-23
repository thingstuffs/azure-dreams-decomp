#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"


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


extern s32 func_800176B8();
extern s32 func_800177CC();
extern s32 initialize_state_two_entries_pointer();
extern s32 func_8001868C();

typedef struct S_80016844_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_80016844_0;   /* arg0 in run_object_handler_and_clear_entry */

/* Runs the selected object handler and clears the current entry status. */
s32 run_object_handler_and_clear_entry(S_80016844_0 *object, s32 context) {
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
