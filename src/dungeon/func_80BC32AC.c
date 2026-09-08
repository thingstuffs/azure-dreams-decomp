#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_8009C93C(); /* extern */
s32 func_800A2B5C();                          /* extern */
M2C_UNK func_800C7930(); /* extern */
extern u16 D_80083462;


typedef struct S_80172AAC_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_80172AAC_1;   /* arg0 in func_80172AAC */

/* Clears an actor flag, applies a conditional effect, and updates its action state. */
void func_80172AAC(S_80172AAC_1 *action_state, M2C_UNK effect_context, M2C_UNK action_context, void *actor) {
    ((Rec_D_800E3D7C *)actor)->unk_71.as_u8 = (u8) (((Rec_D_800E3D7C *)actor)->unk_71.as_u8 & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2B5C(actor) << 0x10) == 0)) {
        func_800C7930(actor - 0x20, effect_context, 8, 0x300);
        if ((func_800A2B5C(actor) << 0x10) == 0) {
            action_state->unk_8C = 0;
            action_state->unk_9A = 0x11;
            action_state->unk_9B = 0;
            ((Rec_D_800E3D7C *)actor)->unk_6D.as_u8 = (u8) (((Rec_D_800E3D7C *)actor)->unk_6D.as_u8 - 1);
            func_8009C93C(actor, action_context, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1, 0);
            ((Rec_D_800E3D7C *)actor)->unk_84.as_s8 = 0x7C;
            ((Rec_D_800E3D7C *)actor)->unk_85.as_s8 = 4;
        }
    }
}
