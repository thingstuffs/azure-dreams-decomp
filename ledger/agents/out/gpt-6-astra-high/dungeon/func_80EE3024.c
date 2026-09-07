#include "common.h"
#include "m2c_compat.h"

s32 func_800A2B5C();                          /* extern */
M2C_UNK func_800A4ACC();                      /* extern */
M2C_UNK func_800C7930(); /* extern */
extern u16 D_80083462;

typedef struct S_80174824_0 {
    u8 pad_00[0x6D];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_80174824_0;   /* arg3 in func_80174824 */

typedef struct S_80174824_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
} S_80174824_1;   /* arg0 in func_80174824 */

/* Clears an entity flag and resets its action state after processing completes. */
void func_80174824(S_80174824_1 *action_state, M2C_UNK context, M2C_UNK unused, void *entity) {
    ((S_80174824_0 *)entity)->unk_71 = (u8) (((S_80174824_0 *)entity)->unk_71 & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2B5C(entity) << 0x10) == 0)) {
        func_800C7930(entity - 0x20, context, 8, 0x300);
        if ((func_800A2B5C(entity) << 0x10) == 0) {
            action_state->unk_8C = 0;
            action_state->unk_9A = 0x17;
            action_state->unk_9B = 0;
            func_800A4ACC(entity);
            ((S_80174824_0 *)entity)->unk_6D = (u8) (((S_80174824_0 *)entity)->unk_6D - 1);
            action_state->unk_96 = 0;
        }
    }
}
