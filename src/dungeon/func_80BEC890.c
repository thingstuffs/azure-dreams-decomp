#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_80082E80.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u16 D_80083462[5];
extern u8 D_8017423C[];
extern s16 D_80083228[5];
M2C_UNK func_8009C93C(); /* extern */
s16 func_800A2B5C();                          /* extern */
s32 func_800C7930(); /* extern */




/* Start the actor action and animation when input and actor checks allow it. */
void func_80172090(Rec_func_800A9E70_arg0 *action_state, M2C_UNK context, Rec_D_80082E80 *animation, void *actor) {
    ((Rec_D_800E3D7C *)actor)->unk_71.as_u8 = (u8) (((Rec_D_800E3D7C *)actor)->unk_71.as_u8 & 0x7F);
    if (!(*D_80083462 & 0x2000) && ((func_800A2B5C(actor) << 0x10) == 0)) {
        func_800C7930(actor - 0x20, context, 8, 0x300);
        if ((func_800A2B5C(actor) << 0x10) == 0) {
            action_state->unk_9A.as_s8 = 0x11;
            action_state->unk_8C = 0;
            action_state->unk_9B.as_s8 = 0;
            animation->unk_2C.as_pu8 = D_8017423C;
            func_80047784(animation, D_8017423C[((s32) (*D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
            ((Rec_D_800E3D7C *)actor)->unk_6D.as_u8 = (u8) (((Rec_D_800E3D7C *)actor)->unk_6D.as_u8 - 1);
            action_state->unk_98 = (u16) (action_state->unk_98 | 8);
            func_8009C93C(actor, animation, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1, 0);
            ((Rec_D_800E3D7C *)actor)->unk_84.as_s8 = 0x7C;
            ((Rec_D_800E3D7C *)actor)->unk_85.as_s8 = 0;
        }
    }
}
