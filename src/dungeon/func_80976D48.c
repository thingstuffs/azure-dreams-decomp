#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800A9E70_arg0.h"

M2C_UNK func_8009C93C(); /* extern */
s32 func_800A2B5C();                          /* extern */
M2C_UNK func_800C7930(); /* extern */
extern u16 D_80083462;



/* Clear the entity flag and advance its action state when the checks pass. */
void func_80172548(Rec_func_800A9E70_arg0 *action_state, M2C_UNK effect_context, M2C_UNK update_context, void *entity) {
    ((Rec_D_800E3D7C *)entity)->unk_71.as_u8 = (u8) (((Rec_D_800E3D7C *)entity)->unk_71.as_u8 & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2B5C(entity) << 0x10) == 0)) {
        func_800C7930(entity - 0x20, effect_context, 8, 0x300);
        if ((func_800A2B5C(entity) << 0x10) == 0) {
            action_state->unk_8C = 0;
            action_state->unk_9A.as_s8 = 0x11;
            action_state->unk_9B.as_s8 = 0;
            action_state->unk_96.as_s16 = 0;
            ((Rec_D_800E3D7C *)entity)->unk_6D.as_u8 = (u8) (((Rec_D_800E3D7C *)entity)->unk_6D.as_u8 - 1);
            func_8009C93C(entity, update_context, ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16, 1, 0);
            ((Rec_D_800E3D7C *)entity)->unk_84.as_s8 = 0x7C;
            ((Rec_D_800E3D7C *)entity)->unk_85.as_s8 = 0;
        }
    }
}
