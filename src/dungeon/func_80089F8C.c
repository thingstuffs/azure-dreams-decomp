#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_8008ACDC_arg0.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80048A44();
M2C_UNK func_8009A66C();
M2C_UNK func_8009F644();
s32 func_800A44E0();
s32 func_800A7234();
extern u8 D_80081485;
extern u8 D_800DD0D0[];

/* Updates actor state and animation when the position checks succeed. */
void func_8008F6EC(void *state, EntityRec *target, void *sprite, u32 actor_or_can) {
    EntityRec *actor = (void *)actor_or_can;
    s16 probe_a;
    s16 probe_b;
    s16 probe_c;
    s32 direction_offset;

    actor_or_can = 0;
    if (D_80081485 == 0x13) {
        s32 animate_result = func_8009A66C(actor->facing, sprite, actor, 0x20);
        animate_result <<= 0x10;
        actor_or_can = animate_result > 0;
    } else if ((func_800A44E0(((u16)target->x.w.i), ((u16)target->y.w.i), actor->unk_88, actor->facing) << 0x10) == 0) {
        direction_offset = ((u16) actor->facing >> 8) & 0xE;
        if ((func_800A7234((s16) (((Rec_D_80082E80 *)sprite)->unk_24 + *(u16 *)(((u8 *)dirStepX) + direction_offset)), (s16) (((Rec_D_80082E80 *)sprite)->unk_25 + *(u16 *)(((u8 *)dirStepY) + direction_offset)), actor->unk_88, &probe_a, &probe_b, &probe_c) << 0x10) != 0) {
            actor_or_can = 1;
        }
    }
    if (actor_or_can != 0) {
        ((Rec_func_8008ACDC_arg0 *)state)->unk_9A.as_s8 = 0x1F;
        ((Rec_func_8008ACDC_arg0 *)state)->unk_9B.as_s8 = 0;
        ((Rec_func_8008ACDC_arg0 *)state)->unk_8C.as_s32 = 0;
        (*(u8 **)((u8 *)sprite + 0x2C)) = D_800DD0D0;
        func_80048A44(sprite, D_800DD0D0[(((s32) (gameWork.view.viewAngle + actor->facing + 0x100)) >> 9) & 7], 0, 1);
        dungeonStatus.unk_0A = ((u16)dungeonStatus.unk_0A) + 1;
        func_8009F644(actor, 0x28, 0, 0);
    }
}
