#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_8004A24C_0 {
    u16 unk_00;
    u8 pad_02[0x6];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
} S_8004A24C_0;   /* arg0 in func_8004A24C */


M2C_UNK func_80049F68();                            /* extern */
M2C_UNK func_8004A030();       /* extern */
s32 func_8004A0C0();                         /* extern */
s32 func_8004A10C();                             /* extern */
M2C_UNK func_8004A170();       /* extern */
s32 func_8004DC14();                /* extern */

/* Initializes resource state, resolves its size, and sets its position. */
void func_8004A24C(S_8004A24C_0 *state, M2C_UNK config_id, M2C_UNK resource_id, s16 x, s32 y, s32 size) {
    s32 resource_handle;
    u16 resolved_size;
    s32 requested_size;

    func_80049F68(state);
    state->unk_1C = func_8004A0C0(config_id);
    resource_handle = func_8004DC14(resource_id, 1);
    requested_size = size;
    resolved_size = requested_size;
    state->unk_18 = resource_handle;
    requested_size = (s16)requested_size;
    if (requested_size == -1) {
        resolved_size = func_8004A10C(resource_handle) + 0x20;
    }
    func_8004A170(state, state->unk_08, resolved_size & 0xFFFF, state->unk_00 & 1);
    state->unk_14 = (s32) state->unk_08;
    func_8004A030(state, x, (s16) y, (s16) resolved_size);
}
