#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct S_80172810_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172810_0;   /* arg0 in func_80172810 */

typedef struct S_80172810_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172810_2_pre;   /* the 0x14 bytes before obj in func_80172810, addressed as obj[-1] */

typedef struct S_80172810_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172810_3;   /* rec in func_80172810 */

typedef struct S_80172810_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80172810_4;   /* arg2 in func_80172810 */


typedef struct S_80172810_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172810_7;   /* block in func_80172810 */


extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);
extern void func_800DA840(void *, s16);

extern int abs(int);
extern u8 D_80170E54[];
extern u8 D_801739C0[];

/* Advances an actor motion through selection, playback, and completion cleanup. */
void func_80172810(void *action_state, void *position, void *sprite, EntityRec *actor)
{
    u16 saved_position[4];
    u8 *motion;
    s16 use_player;
    void *target;
    s32 offset_x;
    s32 offset_y;
    s32 wait_ticks;
    u8 *action_globals;

    use_player = 0;
    switch (((S_80172810_0 *)action_state)->unk_9B) {
    case 0:
        if (((u32)actor->flags1C) & 0x2000) {
            switch ((actor->unk_46 & 0x3FFF) - 1) {
            case 0:
                use_player = 1;
                goto motion_3;
            case 1:
                use_player = 1;
                goto motion_2;
            case 2:
                use_player = 1;
                goto motion_1;
            case 3:
            case 4:
            case 5:
            case 6:
            default:
                goto no_motion;
            }
        }

        switch (actor->unk_46 & 0x3FFF) {
        case 3:
motion_3:
            motion = (u8 *)actor + 0xE;
            break;
        case 2:
motion_2:
            motion = (u8 *)actor + 0xB;
            break;
        case 1:
motion_1:
            motion = (u8 *)actor + 8;
            break;
        default:
no_motion:
            motion = (u8 *)0;
            break;
        }

        if (*motion != 0) {
            ((S_80172810_0 *)action_state)->unk_98 &= 0xFF7F;
            {
                s16 player_target = use_player;

                if (player_target != 0) {
                    target = D_800814A8;
                    actor->target = target;
                    goto have_target;
                }
            }
            if (D_8006DE24[*motion].kind == 2) {
                target = actor->target;
                if (target == 0) {
                    goto apply_motion;
                }
have_target:
                action_globals = ((S_80172810_2_pre *)target)[-1].unk_00;
                actor->unk_72 = ((S_80172810_3 *)action_globals)->unk_24;
                actor->unk_73 = ((S_80172810_3 *)action_globals)->unk_25;
                goto apply_motion;
            }
            actor->target =
                func_800A05A4(actor, ((S_80172810_4 *)sprite)->unk_24, ((S_80172810_4 *)sprite)->unk_25,
                              actor->facing, 0x10);
            offset_x = abs(actor->unk_72);
            offset_y = abs(actor->unk_73);
            actor->unk_72 = offset_x;
            actor->unk_73 = offset_y;
apply_motion:
            saved_position[0] = ((u16)((EntityRec *)position)->x.w.i);
            saved_position[1] = ((u16)((EntityRec *)position)->y.w.i);
            saved_position[2] = ((u16)((EntityRec *)position)->z.w.i);
            position = (void *)func_800A94A0(actor, motion, use_player, (u8 *)action_state + 0x98);
            if (position == 0) {
                return;
            }
            ((S_80172810_4 *)sprite)->unk_14 &= 0xF7FF;
            func_800A56E0(0x703);
            func_800DA840(saved_position, (*motion - 1) % 3);
            ((S_80172810_0 *)action_state)->unk_9B = ((S_80172810_0 *)action_state)->unk_9B + 1;
            return;
        }

        ((EntityRec *)position)->flags14 = 0;
        ((EntityRec *)position)->unk_10 = 0;
        ((EntityRec *)position)->unk_0C = 0;
        func_800A2B04(position, ((S_80172810_4 *)sprite)->unk_24, ((S_80172810_4 *)sprite)->unk_25);
        dungeonStatus.unk_0C = 0;
        (*(u16 *)((u8 *)&D_800814A8->unk_A4 + 2)) = (*(u16 *)((u8 *)D_800814A8 + 0xA6)) - 1;
        func_800A4ACC(actor);
        actor->unk_6D = ((u8)actor->unk_6D) - 1;
        ((S_80172810_0 *)action_state)->unk_8C = D_80170E54;
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (func_8003F270() != 0) {
            ((S_80172810_4 *)sprite)->unk_14 |= 0x800;
            return;
        }
        ((S_80172810_4 *)sprite)->unk_14 &= 0xF7FF;
        ((S_80172810_0 *)action_state)->unk_9B = ((S_80172810_0 *)action_state)->unk_9B + 1;
                        /* fallthrough */
    case 2:
        if ((((S_80172810_4 *)sprite)->unk_04 == 14 && (((S_80172810_4 *)sprite)->unk_14 & 0x1000)) ||
            (((S_80172810_4 *)sprite)->unk_14 & 0xE000)) {
            ((S_80172810_4 *)sprite)->unk_14 |= 0x800;
            ((S_80172810_0 *)action_state)->unk_96 = 0x3;
            ((S_80172810_0 *)action_state)->unk_98 |= 0x80;
        }
        wait_ticks = ((S_80172810_0 *)action_state)->unk_96 - 1;
        ((S_80172810_0 *)action_state)->unk_96 = wait_ticks;
        if ((s16)wait_ticks <= 0) {
            ((S_80172810_0 *)action_state)->unk_96 = 0;
            ((S_80172810_4 *)sprite)->unk_14 &= 0xF7FF;
        }
        if ((((S_80172810_4 *)sprite)->unk_14 & 0xE000) == 0) {
            return;
        }
        ((EntityRec *)position)->flags14 = 0;
        ((EntityRec *)position)->unk_10 = 0;
        ((EntityRec *)position)->unk_0C = 0;
        func_800A2B04(position, ((S_80172810_4 *)sprite)->unk_24, ((S_80172810_4 *)sprite)->unk_25);
        {
            u8 *direction_frames = D_801739C0;

            if (((S_80172810_4 *)sprite)->unk_2C != direction_frames) {
                (*(u8 * *)((u8 *)sprite + 0x2C)) = direction_frames;
                func_80047784(sprite,
                    direction_frames[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
        }
        action_globals = (u8 *)&dungeonStatus.unk_00;
        if (((S_80172810_7 *)action_globals)->unk_0C != 0) {
            return;
        }
        ((S_80172810_7 *)action_globals)->unk_0A = ((S_80172810_7 *)action_globals)->unk_0A - 1;
        ((S_80172810_4 *)sprite)->unk_14 &= 0xF7FF;
        ((S_80172810_0 *)action_state)->unk_8C = D_80170E54;
        func_800A4ACC(actor);
        if (actor->unk_6D > 0) {
            actor->unk_6D = ((u8)actor->unk_6D) - 1;
        }
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        func_800A56E0(0xB4);
        break;
    }
}
