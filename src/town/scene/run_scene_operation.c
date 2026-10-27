#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"

typedef struct S_80017308_1 {
    u8 pad_00[0x2];
    s8 unk_02;
} S_80017308_1;   /* ((D_80016000->unk_08.at00_s32.v * 8) + D_80016000->unk_40.as_s32) in run_scene_operation_514 */


extern void func_80018854(s32); /* placed copy of set_script_flag_bit */

/* Invoke operation 0x514 and set the current entry counter to two. */
void run_scene_operation_514(void) {
    func_80018854(F_sbs07_pad29);
    ((S_80017308_1 *)(((town_scene_root->entry_index * 8) + ((u8 *)town_scene_root->event_data))))->unk_02 = 2;
}
