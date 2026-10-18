#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"

typedef struct S_80017308_1 {
    u8 pad_00[0x2];
    s8 unk_02;
} S_80017308_1;   /* ((D_80016000->unk_08.at00_s32.v * 8) + D_80016000->unk_40.as_s32) in run_scene_operation_514 */


extern s32 call_helper_with_fixed_id_0x118a();

/* Invoke operation 0x514 and set the current entry counter to two. */
void run_scene_operation_514(void) {
    call_helper_with_fixed_id_0x118a(0x514);
    ((S_80017308_1 *)(((D_80016000->unk_08 * 8) + ((s32)D_80016000->unk_40))))->unk_02 = 2;
}
