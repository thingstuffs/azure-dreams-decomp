#include "common.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_800E3D7C.h"


extern s32 func_8009C93C();
extern s32 func_800A2B5C();
extern void func_800C7930();
extern void func_80175F44();
extern u16 D_80083462;


/* Start the actor action and reset its state when ready, or dispatch the alternate action. */
void func_80172D88(Rec_func_800A9E70_arg0 *state, s32 world_pos, s32 tile_pos, void *actor)
{
    if (state->unk_B5 == 0) {
        ((Rec_D_800E3D7C *)actor)->unk_71.as_u8 &= 0x7F;
        if (!(D_80083462 & 0x2000) && ((func_800A2B5C(actor) << 16) == 0)) {
            func_800C7930(actor - 0x20, world_pos, 8, 0x300);
            if ((func_800A2B5C(actor) << 16) == 0) {
                state->unk_8C = 0;
                state->unk_9A.as_s8 = 0x11;
                state->unk_9B.as_s8 = 0;
                state->unk_96.as_s16 = 0;
                ((Rec_D_800E3D7C *)actor)->unk_6D.as_u8--;
                state->unk_98 |= 8;
                func_8009C93C(actor, tile_pos, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1, 0);
                ((Rec_D_800E3D7C *)actor)->unk_84.as_s8 = 0x7C;
                ((Rec_D_800E3D7C *)actor)->unk_85.as_s8 = 0;
                return;
            }
        }
    } else {
        func_80175F44(state, world_pos, tile_pos, 1, 1);
    }
}
