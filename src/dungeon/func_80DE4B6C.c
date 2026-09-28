#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"


typedef struct S_8017236C_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_8017236C_1;   /* arg0 in func_8017236C */



extern s32 func_80047784();
extern s32 func_800A2B5C();
extern s32 func_800A4ACC();
extern s32 func_800C7930();
extern s32 D_80174558;

/* Updates actor flags and starts a directional animation when the actor is ready. */
void func_8017236C(void *actor_state, s32 action_param, void *sprite, void *actor) {
    ((EntityRec *)actor)->unk_71 = ((EntityRec *)actor)->unk_71 & 0x7F;
    if (!(dungeonStatus.flags & 0x2000) && ((func_800A2B5C(actor) << 0x10) == 0)) {
        func_800C7930((u8 *)actor - 0x20, action_param, 8, 0x300);
        if ((func_800A2B5C(actor) << 0x10) == 0) {
            ((S_8017236C_1 *)actor_state)->unk_9A = 0x18;
            ((S_8017236C_1 *)actor_state)->unk_8C = 0;
            ((S_8017236C_1 *)actor_state)->unk_9B = 0;
            (*(s32 * *)((u8 *)sprite + 0x2C)) = &D_80174558;
            func_80047784(sprite,
                         *((((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7)
                           + (u8 *)&D_80174558),
                         0);
            func_800A4ACC(actor);
            ((EntityRec *)actor)->unk_6D = ((u8)((EntityRec *)actor)->unk_6D) - 1;
        }
    }
}
