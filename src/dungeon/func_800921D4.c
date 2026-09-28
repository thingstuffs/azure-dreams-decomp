#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

extern void func_8003DB94(void *arg0, void *arg1, s32 arg2);
extern void func_80042B68(void *arg0, s32 arg1);
extern void func_8008CBD4(void *arg0, void *arg1, void *arg2, void *arg3);
extern void func_80096384(void);
extern void func_800AD4D0(void *arg0);

extern void *D_800DD274[8];

/* Refresh the directional sprite and advance the actor state when sprite flags are set. */
void func_80097934(Rec_func_8008ACDC_arg0 *state, EntityRec *motion, Rec_D_80082E80 *sprite, void *actor)
{
    s32 tracked_addr;

    if (state->unk_9B.as_u8 == 0) {
        func_800AD4D0(actor);
        state->unk_9B.as_u8++;
    }

    if (sprite->unk_14.at00_u16.v & 0xE000) {
        sprite->unk_2C.as_pv = D_800DD274;
        func_8003DB94(
            sprite,
            D_800DD274[
                ((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
            0);

        tracked_addr = ((s32)dungeonStatus.unk_10);
        if (tracked_addr == (u32)((u8 *)actor - 0x20)) {
            dungeonStatus.unk_10 = tracked_addr & 0x7FFFFFFF;
        }

        if (((EntityRec *)actor)->unk_28 == 0) {
            ((EntityRec *)actor)->unk_28 = 0;
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_80042B68(actor, 10);
            func_8008CBD4(state, motion, sprite, actor);
            return;
        }

        state->unk_96.as_s16 = 8;
        state->unk_8C.as_pv = func_80096384;
    }
}
