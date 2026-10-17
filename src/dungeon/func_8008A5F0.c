#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_8008ACDC_arg0.h"


extern void func_80048A44(void *, s16, s16, s32);
extern void dungeonBeginWakeNearbyMonsters(u8 *state_ptr, s32 value, u8 *target_ptr, u8 *angle_ptr);
extern s32 dungeonCollectGroundItem(void *, void *, void *, void *);
extern void dungeonSetRecordIntegerTileCenter(void *, u8, u8);

extern M2C_UNK D_8008EAC8;
extern u8 D_800DD0E0[];

/* Updates movement toward the destination tile and handles arrival when the timer expires. */
void dungeonAdvanceAlternateTileCenterMotion(void *actor, EntityRec *motion, void *sprite, EntityRec *facing) {
    u16 ticks_left;

    if (dungeonStatus.flags & 0x80) {
        dungeonStatus.unk_04 = 0;
    }
    if (dungeonStatus.unk_04 != 0) {
        motion->unk_0C = (s32) ((s32) ((((((Rec_D_80082E80 *)sprite)->unk_24 << 6) + 0x20) << 0x10)
            - motion->x.v) / dungeonStatus.unk_04);
        motion->unk_10 = (s32) ((s32) ((((((Rec_D_80082E80 *)sprite)->unk_25 << 6) + 0x20) << 0x10)
            - motion->y.v) / dungeonStatus.unk_04);
    }
    if ((((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 & 0x100) && (dungeonStatus.unk_04 == 6)) {
        dungeonBeginWakeNearbyMonsters(actor, motion, sprite, facing);
        return;
    }
    if (!(((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 & 0x10)) {
        u8 *old_anim_table = ((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8;
        u8 *anim_table = D_800DD0E0;
        if (old_anim_table != anim_table) {
            (*(u8 **)((u8 *)sprite + (0x2C))) = anim_table;
            func_80048A44(sprite, anim_table[((s32) (gameWork.view.viewAngle + facing->facing + 0x100) >> 9) & 7], 0,
                1);
        }
    }
    ticks_left = dungeonStatus.unk_04 - 1;
    dungeonStatus.unk_04 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        dungeonStatus.unk_04 = 0U;
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        dungeonSetRecordIntegerTileCenter(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        if ((dungeonCollectGroundItem(actor, motion, sprite, facing) << 0x10) > 0) {
            ((Rec_func_8008ACDC_arg0 *)actor)->unk_8C.as_pm = &D_8008EAC8;
        }
    }
}
