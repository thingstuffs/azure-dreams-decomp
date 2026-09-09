#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800A9E70_arg0.h"

M2C_UNK func_80047784();         /* extern */
M2C_UNK func_8009C93C(); /* extern */
s32 func_800A2B5C();                          /* extern */
M2C_UNK func_800C7930(); /* extern */
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80174038[];

/* Updates the actor's action state and directional animation when it can act. */
void func_8017208C(void *action_state, M2C_UNK context, void *sprite, void *actor) {
    ((Rec_D_800E3D7C *)actor)->unk_71.as_u8 = (u8) (((Rec_D_800E3D7C *)actor)->unk_71.as_u8 & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2B5C(actor) << 0x10) == 0) && (func_800C7930(actor - 0x20, context, 8, 0x300), ((func_800A2B5C(actor) << 0x10) == 0))) {
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_8C = 0;
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_s8 = 0;
        if (((Rec_func_800A9E70_arg0 *)action_state)->unk_98 & 0x8000) {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_s8 = 0x17;
            if (((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 & 0x1000) {
                ((Rec_func_800A9E70_arg0 *)action_state)->unk_98 = (u16) (((Rec_func_800A9E70_arg0 *)action_state)->unk_98 | 0x4000);
            } else {
                ((Rec_func_800A9E70_arg0 *)action_state)->unk_98 = (u16) (((Rec_func_800A9E70_arg0 *)action_state)->unk_98 & 0xBFFF);
            }
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_AC = (u8) ((Rec_D_800E3D7C *)actor)->unk_00.at03_u8.v;
            ((Rec_D_800E3D7C *)actor)->unk_00.at03_u8.v = 0xFFU;
            ((Rec_D_800E3D7C *)actor)->unk_84.as_s8 = 0x7E;
        } else {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_s8 = 0x11;
            ((Rec_D_800E3D7C *)actor)->unk_84.as_s8 = 0x7C;
        }
        do {
            ((Rec_D_800E3D7C *)actor)->unk_85.as_s8 = 8;
        } while (0);
        (*(u8 **)((u8 *)sprite + 0x2C)) = D_80174038;
        func_80047784(sprite, D_80174038[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
        ((Rec_D_800E3D7C *)actor)->unk_6D.as_u8 = (u8) (((Rec_D_800E3D7C *)actor)->unk_6D.as_u8 - 1);
        func_8009C93C(actor, sprite, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1, 0);
        if (!(((Rec_func_800A9E70_arg0 *)action_state)->unk_98 & 0x8000)) {
            ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 & 0xFEFFFFFF);
        }
    }
}

