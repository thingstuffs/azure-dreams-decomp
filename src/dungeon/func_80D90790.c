#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800A9E70_arg0.h"

extern s32 func_800A2B5C();
extern void func_800C7930();
extern void func_80047784();
extern void func_8009C93C();

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_8017386C[];

/* Update actor action state and select its directional animation. */
void func_80171F90(void *action_state, s32 update_arg, void *sprite, void *actor)
{
    ((Rec_D_800E3D7C *)actor)->unk_71.as_u8 &= 0x7F;

    if (!(D_80083462 & 0x2000) &&
        ((func_800A2B5C(actor) << 0x10) == 0) &&
        (func_800C7930((u8 *)actor - 0x20, update_arg, 8, 0x300),
         ((func_800A2B5C(actor) << 0x10) == 0))) {
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_8C = 0;
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_s8 = 0;

        if (((Rec_func_800A9E70_arg0 *)action_state)->unk_98 & 0x8000) {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_u8 = 0x17;
            ((Rec_D_800E3D7C *)actor)->unk_84.as_s8 = 0x10;
            ((Rec_D_800E3D7C *)actor)->unk_85.as_s8 = 0x10;
        } else {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_u8 = 0x11;
            ((Rec_D_800E3D7C *)actor)->unk_84.as_s8 = 0x7C;
            ((Rec_D_800E3D7C *)actor)->unk_85.as_s8 = 0;
        }
        (*(u8 **)((u8 *)sprite + 0x2C)) = D_8017386C;
        func_80047784(sprite,
                      D_8017386C[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                      0);
        ((Rec_D_800E3D7C *)actor)->unk_6D.as_u8--;

        if (((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_u8 == 0x11) {
            func_8009C93C(actor, sprite, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1, 0);
        }
    }
}
