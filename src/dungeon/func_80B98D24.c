#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void func_80047784();
M2C_UNK func_8009C12C();
M2C_UNK func_800A2B04();
M2C_UNK func_800A4ACC();
M2C_UNK func_800A56E0();
M2C_UNK func_800AD594();
extern M2C_UNK D_80170E9C;
extern u8 D_80174F30;
extern u8 D_80174F38;
extern u8 D_80174F40;


typedef struct S_80172524_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    union { u8 n; u8 v; } unk_9B;   /* accessed as both */
} S_80172524_0;   /* arg0 in func_80172524 */

/* Advance the action phases, updating movement and directional animation. */
void func_80172524(void *action, EntityRec *motion, void *sprite, void *actor) {
    u16 move_ticks;
    u16 settle_ticks;
    u8 phase;

    phase = ((S_80172524_0 *)action)->unk_9B.n;
    switch (phase) {
    case 0:
        ((S_80172524_0 *)action)->unk_98 = (u16) (((S_80172524_0 *)action)->unk_98 | 8);
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((S_80172524_0 *)action)->unk_9B.n = 5U;
            ((S_80172524_0 *)action)->unk_96.u = 0U;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v
                | 0x6000);
            func_8009C12C(actor, sprite, ((EntityRec *)actor)->facing, 1);
            return;
        }
        motion->unk_0C = (s32) (*(s16 *)(((u8 *)dirStepX) + (((u16) ((EntityRec *)actor)->facing >> 8) & 0xE)) << 0x14);
        motion->unk_10 = (s32) (*(s16 *)(((u8 *)dirStepY) + (((u16) ((EntityRec *)actor)->facing >> 8) & 0xE)) << 0x14);
        goto advance_phase;
    case 1:
        motion->unk_0C = (s32) ((s32) motion->unk_0C >> 1);
        motion->unk_10 = (s32) ((s32) motion->unk_10 >> 1);
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        (*(M2C_UNK **)((u8 *)sprite + (0x2C))) = (M2C_UNK *)&D_80174F30;
        func_80047784(sprite, *(u8 *)((((s32) (gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100)
            >> 9) & 7) + (u32)&D_80174F30), 0);
        goto advance_phase;
    case 2:
        motion->unk_0C = (s32) ((s32) motion->unk_0C >> 1);
        motion->unk_10 = (s32) ((s32) motion->unk_10 >> 1);
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        func_800A56E0(0x808);
        (*(M2C_UNK **)((u8 *)sprite + (0x2C))) = (M2C_UNK *)&D_80174F38;
        func_80047784(sprite, *(u8 *)((((s32) (gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100)
            >> 9) & 7) + (u32)&D_80174F38), 0);
        goto advance_phase;
    case 3:
        if (((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 2) {
            if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000) {
                func_8009C12C(actor, sprite, ((EntityRec *)actor)->facing, 1);
                {
                    u16 move_duration = 6;
                    ((S_80172524_0 *)action)->unk_96.u = move_duration;
                }
                ((S_80172524_0 *)action)->unk_9B.n += 1;
                return;
            }
        }
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        (*(M2C_UNK **)((u8 *)sprite + (0x2C))) = &D_80174F40;
        func_80047784(sprite, *((((s32) (gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7)
            + &D_80174F40), 0);
        func_8009C12C(actor, sprite, ((EntityRec *)actor)->facing, 1);
        ((S_80172524_0 *)action)->unk_9B.n = 5U;
        ((S_80172524_0 *)action)->unk_96.u = 0;
        return;
    case 4:
        move_ticks = ((S_80172524_0 *)action)->unk_96.u - 1;
        ((S_80172524_0 *)action)->unk_96.u = move_ticks;
        if ((s16) move_ticks > 0) {
            {
                s32 target_coord = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
                s32 current_coord = motion->x.w.i - 0x20;
                motion->unk_0C = ((target_coord - current_coord) << 0x10) / (s16) move_ticks;
            }
            {
                s32 target_coord = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
                s32 current_coord = motion->y.w.i - 0x20;
                motion->unk_10 = ((target_coord - current_coord) << 0x10) / ((S_80172524_0 *)action)->unk_96.s;
            }
        } else {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
        }
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        (*(M2C_UNK **)((u8 *)sprite + (0x2C))) = (M2C_UNK *)&D_80174F40;
        func_80047784(sprite, *(u8 *)((((s32) (gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100)
            >> 9) & 7) + (u32)&D_80174F40), 0);
advance_phase:
        ((S_80172524_0 *)action)->unk_9B.n += 1;
        return;
    case 5:
        settle_ticks = ((S_80172524_0 *)action)->unk_96.u - 1;
        ((S_80172524_0 *)action)->unk_96.u = settle_ticks;
        if ((s16) settle_ticks > 0) {
            {
                s32 target_coord = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
                s32 current_coord = motion->x.w.i - 0x20;
                motion->unk_0C = ((target_coord - current_coord) << 0x10) / (s16) settle_ticks;
            }
            {
                s32 target_coord = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
                s32 current_coord = motion->y.w.i - 0x20;
                motion->unk_10 = ((target_coord - current_coord) << 0x10) / ((S_80172524_0 *)action)->unk_96.s;
            }
        } else {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
        }
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        ((S_80172524_0 *)action)->unk_98 = (u16) (((S_80172524_0 *)action)->unk_98 & 0xFFF7);
        func_800AD594(actor, 0x100);
        ((S_80172524_0 *)action)->unk_8C = &D_80170E9C;
        dungeonStatus.unk_0C = 0;
        ((EntityRec *)actor)->unk_46 = (u16) ((*(u16 *)((u8 *)actor + (0x46))) & 0x7FFF);
        func_800A4ACC(actor);
        return;
    default:
        return;
    }
}
