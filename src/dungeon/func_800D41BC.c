#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_800D991C_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    s16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s32 unk_A4;
} S_800D991C_0;   /* arg0 in func_800D991C */





M2C_UNK func_8003DB94();        /* extern */
s16 func_800A0818();       /* extern */
M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800A4ACC();                      /* extern */
M2C_UNK func_800A9A04();                      /* extern */
M2C_UNK func_800AD594();             /* extern */
s32 func_800AD9B4();                  /* extern */
extern M2C_UNK D_800D8C64;
extern void *D_800E262C[];

/* Update airborne movement toward a map tile and finish the landing transition. */
void func_800D991C(void *motion_state, void *transform, void *map_entity, void *actor) {
    M2C_UNK direction_aux;
    void **animation_table;
    s32 frames_left;
    s16 next_timer;
    s32 target_x;
    s32 velocity_x;
    s32 target_y;
    s32 actor_flags;
    s32 current_x;
    s32 current_y;
    s32 phase;

    phase = ((S_800D991C_0 *)motion_state)->unk_9B;
    switch (phase) {
        case 0:
            ((S_800D991C_0 *)motion_state)->unk_98 = (u16) (((S_800D991C_0 *)motion_state)->unk_98 | 8);
            ((EntityRec *)transform)->flags14 = 0xFFF00000;
            ((EntityRec *)actor)->flags1C = (s32) (((EntityRec *)actor)->flags1C & 0xF7FFFFFF);
            ((S_800D991C_0 *)motion_state)->unk_A4 = 0;
            ((S_800D991C_0 *)motion_state)->unk_9B = (u8) (((S_800D991C_0 *)motion_state)->unk_9B + 1);
            break;
        case 1:
            break;
        case 2:
            goto check_landing;
        default:
            goto tick_timer;
    }
update_motion:
    frames_left = ((S_800D991C_0 *)motion_state)->unk_96;
    ((S_800D991C_0 *)motion_state)->unk_90 = (s32) (((S_800D991C_0 *)motion_state)->unk_90 - ((S_800D991C_0 *)motion_state)->unk_A4);
    if (frames_left != 0) {
        target_x = ((Rec_D_80082E80 *)map_entity)->unk_24 << 6;
        current_x = ((EntityRec *)transform)->x.w.i - 0x20;
        velocity_x = (s32) ((target_x - current_x) << 0x10) / frames_left;
        current_y = ((EntityRec *)transform)->y.w.i - 0x20;
        ((EntityRec *)transform)->unk_0C = velocity_x;
        target_y = ((Rec_D_80082E80 *)map_entity)->unk_25 << 6;
        ((EntityRec *)transform)->unk_10 = (s32) ((s32) ((target_y - current_y) << 0x10) / (s16) ((S_800D991C_0 *)motion_state)->unk_96);
        ((S_800D991C_0 *)motion_state)->unk_A4 = (s32) (((S_800D991C_0 *)motion_state)->unk_A4 + ((EntityRec *)transform)->flags14);
        ((EntityRec *)transform)->flags14 = (s32) (((EntityRec *)transform)->flags14 + 0x48000);
    }
    ((S_800D991C_0 *)motion_state)->unk_90 = (s32) (((S_800D991C_0 *)motion_state)->unk_90 + ((S_800D991C_0 *)motion_state)->unk_A4);
    if (((S_800D991C_0 *)motion_state)->unk_96 < 2) {
        ((S_800D991C_0 *)motion_state)->unk_90 = 0;
        ((S_800D991C_0 *)motion_state)->unk_98 = (u16) (((S_800D991C_0 *)motion_state)->unk_98 & 0xFFF7);
        ((EntityRec *)actor)->flags1C = (s32) (((EntityRec *)actor)->flags1C | 0x08000000);
        ((S_800D991C_0 *)motion_state)->unk_9B = (u8) (((S_800D991C_0 *)motion_state)->unk_9B + 1);
    }
check_landing:
    if (((EntityRec *)actor)->flags1C & 0x08000000) {
        ((S_800D991C_0 *)motion_state)->unk_98 = (u16) (((S_800D991C_0 *)motion_state)->unk_98 & 0xFFF7);
        ((EntityRec *)transform)->flags14 = 0;
        ((EntityRec *)transform)->unk_10 = 0;
        ((EntityRec *)transform)->unk_0C = 0;
        func_800A2B04(transform, ((Rec_D_80082E80 *)map_entity)->unk_24, ((Rec_D_80082E80 *)map_entity)->unk_25);
        animation_table = D_800E262C;
        (*(void **)((u8 *)map_entity + 0x2C)) = animation_table;
        func_8003DB94(map_entity, *(void **)((u8 *)animation_table + (((s32) (gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 7) & 0x1C)), 0);
        ((S_800D991C_0 *)motion_state)->unk_9B = (u8) (((S_800D991C_0 *)motion_state)->unk_9B + 1);
    }
tick_timer:
    next_timer = (u16) ((S_800D991C_0 *)motion_state)->unk_96 - 1;
    ((S_800D991C_0 *)motion_state)->unk_96 = next_timer;
    if ((next_timer << 0x10) <= 0) {
        ((EntityRec *)transform)->flags14 = 0;
        ((EntityRec *)transform)->unk_10 = 0;
        ((EntityRec *)transform)->unk_0C = 0;
        func_800A2B04(transform, ((Rec_D_80082E80 *)map_entity)->unk_24, ((Rec_D_80082E80 *)map_entity)->unk_25);
        func_800AD594(actor, 4);
        func_800A4ACC(actor);
        if (dungeonStatus.unk_08 != 0) {
            dungeonStatus.unk_08 = (s16) ((u16) dungeonStatus.unk_08 - 1);
        }
        actor_flags = ((EntityRec *)actor)->flags1C;
        if (actor_flags & 0x2000) {
            goto finish_motion;
        }
        if (actor_flags & 0x410) {
            goto finish_motion;
        }
        if (!(actor_flags & 0x20000)) {
            goto finish_motion;
        }
        ((EntityRec *)actor)->facing = func_800A0818(((Rec_D_80082E80 *)map_entity)->unk_24, ((Rec_D_80082E80 *)map_entity)->unk_25, D_80082E80.tileX, D_80082E80.tileY, &direction_aux);
finish_motion:
        if ((func_800AD9B4(map_entity, actor) << 0x10) > 0) {
            ((S_800D991C_0 *)motion_state)->unk_8C = &D_800D8C64;
            func_800A9A04(actor);
        }
    }
}
