#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172288_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    s16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
} S_80172288_0;   /* arg0 in func_80172288 */


typedef struct {
    u16 x;
    u16 y;
} PathPoint;

typedef struct {
    PathPoint point[8];
} PathTable;

extern void func_80047784(void *, u8, s32);
extern s16 func_800A0818(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80170838[16];
extern s32 D_80170E84;
extern u8 D_80174820[];

/* Updates an actor's jump motion, landing animation, and completion state. */
void func_80172288(u8 *motion, EntityRec *position, u8 *sprite, EntityRec *actor)
{
    PathTable frame_path;
    s32 facing_result;
    s32 frames_left;
    s32 current_y;
    s16 timer;
    s32 actor_flags;
    s32 phase;
    u8 phase_value;
    DungeonGlobalStatus *global_counter;

    frame_path = *(PathTable *)D_80170838;
    phase = ((S_80172288_0 *)motion)->unk_9B;

    switch (phase) {
    case 0:
        if (((S_80172288_0 *)motion)->unk_96 < 8) {
            ((S_80172288_0 *)motion)->unk_98 |= 8;
            position->flags14 = 0xFFEE0000;
            actor->flags1C &= 0xF7FFFFFF;
            phase_value = ((S_80172288_0 *)motion)->unk_9B;
            ((S_80172288_0 *)motion)->unk_A0 = 0;
            ((S_80172288_0 *)motion)->unk_9B = phase_value + 1;
        }
        break;
    case 1:
        frames_left = ((S_80172288_0 *)motion)->unk_96;
        ((S_80172288_0 *)motion)->unk_90 -= ((S_80172288_0 *)motion)->unk_A0;
        if (frames_left != 0) {
            {
                s32 target_x;
                s32 current_x;

                target_x = sprite[0x24];
                current_x = position->x.w.i;
                target_x <<= 6;
                current_x -= 0x20;
                position->unk_0C =
                    ((target_x - current_x) << 16) / frames_left;
            }
            current_y = position->y.w.i - 0x20;
            position->unk_10 =
                (((sprite[0x25] << 6) - current_y) << 16) /
                ((S_80172288_0 *)motion)->unk_96;
            ((S_80172288_0 *)motion)->unk_A0 += position->flags14;
            position->flags14 += 0x40000;
        }
        ((S_80172288_0 *)motion)->unk_90 += ((S_80172288_0 *)motion)->unk_A0;
        if (((S_80172288_0 *)motion)->unk_96 < 3) {
            ((S_80172288_0 *)motion)->unk_90 = 0;
            ((S_80172288_0 *)motion)->unk_98 &= 0xFFF7;
            actor->flags1C |= 0x08000000;
            ((S_80172288_0 *)motion)->unk_9B++;
        }
                        /* fall through */
    case 2:
        if (actor->flags1C & 0x08000000) {
            ((S_80172288_0 *)motion)->unk_98 &= 0xFFF7;
            position->flags14 = 0;
            position->unk_10 = 0;
            position->unk_0C = 0;
            func_800A2B04(position, sprite[0x24], sprite[0x25]);
            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80174820;
            func_80047784(
                sprite,
                D_80174820[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            phase_value = ((S_80172288_0 *)motion)->unk_9B;
            ((S_80172288_0 *)motion)->unk_9B = phase_value + 1;
        }
        break;
    }

    timer = ((S_80172288_0 *)motion)->unk_96 - 1;
    ((S_80172288_0 *)motion)->unk_96 = timer;
    if ((timer << 16) <= 0) {
        position->flags14 = 0;
        position->unk_10 = 0;
        position->unk_0C = 0;
        func_800A2B04(position, sprite[0x24], sprite[0x25]);
        func_800AD594(actor, 4);
        func_800A4ACC(actor);


        global_counter = &dungeonStatus;
        if (global_counter->unk_08 != 0) {
            (*(u16 *)&global_counter->unk_08)--;
        }

        actor_flags = actor->flags1C;
        if (actor_flags & 0x2000) {
            if (actor->unk_46 & 0x8000) {
                actor->unk_46 &= 0x7FFF;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {
                actor->facing = func_800A0818(
                    sprite[0x24], sprite[0x25], D_80082E80.tileX, D_80082E80.tileY,
                    &facing_result);
            }
        }

        if ((func_800AD9B4(sprite, actor) << 16) <= 0) {
            return;
        }
        ((S_80172288_0 *)motion)->unk_8C = &D_80170E84;
        func_800A9A04(actor);
    }
    ((Rec_D_80082E80 *)sprite)->unk_1C.at00_u16.v = frame_path.point[((S_80172288_0 *)motion)->unk_96].x;
    ((Rec_D_80082E80 *)sprite)->unk_1C.at02_u16.v = frame_path.point[((S_80172288_0 *)motion)->unk_96].y;
}
