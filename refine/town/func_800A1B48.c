#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009F2A8_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8009F2A8_0;   /* arg2 in func_8009F2A8 */

typedef struct S_8009F2A8_1 {
    u8 pad_00[0x6C];
    s16 unk_6C;
    u8 pad_6E[0x32];
    s32 unk_A0;
} S_8009F2A8_1;   /* arg0 in func_8009F2A8 */


M2C_UNK func_80053DA8();                     /* extern */
s32 func_800644B8();                             /* extern */
M2C_UNK func_8009F4C0(); /* extern */
M2C_UNK func_800A3248();                      /* extern */
M2C_UNK func_800A33E8();                      /* extern */
extern s32 D_800834B8;
extern M2C_UNK D_800935BC;
extern s32 D_800CFCC4;

/* Update the target offset, advance the phase, and handle the active event. */
void func_8009F2A8(void *state, s32 event_id, void *target, M2C_UNK context) {
    s32 active_event;

    ((S_8009F2A8_0 *)target)->unk_08 = (s32) (((S_8009F2A8_1 *)state)->unk_A0 + (func_800644B8(((S_8009F2A8_1 *)state)->unk_6C) << 7));
    (*(s16 *)((u8 *)state + 0x6C)) = (s16) ((u16) ((S_8009F2A8_1 *)state)->unk_6C + 0x40);
    active_event = D_800CFCC4;
    if ((active_event == event_id) && (D_800834B8 == &D_800935BC)) {
        func_800A33E8(target);
        func_800A3248(target);
        func_80053DA8(0x513);
        func_8009F4C0(state, active_event, target, context);
    }
}
