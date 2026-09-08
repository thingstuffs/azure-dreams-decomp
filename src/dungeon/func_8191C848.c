#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_8191C848_0_pre {
    u16 unk_00;
} S_8191C848_0_pre;   /* the 0x2 bytes before arg0 in func_8191C848, addressed as arg0[-1] */

typedef struct S_8191C848_0 {
    void * unk_00;
    u8 pad_04[0x4];
    s16 unk_08;
    s16 unk_0A;
} S_8191C848_0;   /* arg0 in func_8191C848 */

typedef struct S_8191C848_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8191C848_1;   /* temp_v1 in func_8191C848 */


typedef struct S_8191C848_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8191C848_3;   /* arg1 in func_8191C848 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_800814A0[3];
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */

/* Advance the motion counter, update status flags, and move the position. */
void func_8191C848(void *motion, S_8191C848_3 *position, Rec_D_80082E80 *status) {
    s32 y_step_scaled;
    S_8191C848_1 *counter_state;
    counter_state = ((S_8191C848_0 *)motion)->unk_00;
    counter_state->unk_14 = (u16) (counter_state->unk_14 + 1);
    func_800478B8(status);
    if (status->unk_14.at00_u16.v & 0x6000) {
        ((S_8191C848_0_pre *)motion)[-1].unk_00 = (u16) (((S_8191C848_0_pre *)motion)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
    position->unk_02 = (u16) (position->unk_02 + ((s32) ((func_800644B8(((S_8191C848_0 *)motion)->unk_08) >> 4) * ((S_8191C848_0 *)motion)->unk_0A) >> 8));
    y_step_scaled = (func_80064584(((S_8191C848_0 *)motion)->unk_08) >> 4) * ((S_8191C848_0 *)motion)->unk_0A;
    position->unk_0A = (u16) (position->unk_0A - 4);
    position->unk_06 = (u16) (position->unk_06 + (y_step_scaled >> 8));
}
