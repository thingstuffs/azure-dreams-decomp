#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800A9E70_arg0.h"





extern s32 func_80047784();
extern s32 func_800A2B5C();
extern s32 func_800A4ACC();
extern s32 func_800C7930();
extern s16 D_80083228;
extern u16 D_80083462;
extern s32 D_80174E3C;

/* Clear the actor flag and apply an effect and animation change when allowed. */
void func_80174928(void *action_state, s32 effect_arg, void *anim_state, void *actor) {
    ((Rec_D_800E3D7C *)actor)->unk_71.as_u8 = ((Rec_D_800E3D7C *)actor)->unk_71.as_u8 & 0x7F;
    if (!(D_80083462 & 0x2000) && ((func_800A2B5C(actor) << 0x10) == 0)) {
        func_800C7930((u8 *)actor - 0x20, effect_arg, 8, 0x300);
        if ((func_800A2B5C(actor) << 0x10) == 0) {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_s8 = 0x17;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_8C = 0;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_s8 = 0;
            (*(s32 * *)((u8 *)anim_state + 0x2C)) = &D_80174E3C;
            func_80047784(anim_state,
                         *((((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7)
                           + (u8 *)&D_80174E3C),
                         0);
            func_800A4ACC(actor);
            ((Rec_D_800E3D7C *)actor)->unk_6D.as_u8 = ((Rec_D_800E3D7C *)actor)->unk_6D.as_u8 - 1;
        }
    }
}
