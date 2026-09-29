#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_80172A24_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172A24_0;   /* arg0 in func_80172A24 */

typedef struct S_80172A24_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172A24_2_pre;   /* the 0x14 bytes before obj in func_80172A24, addressed as obj[-1] */

typedef struct S_80172A24_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172A24_3;   /* rec in func_80172A24 */




typedef struct S_80172A24_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172A24_7;   /* block in func_80172A24 */




extern int abs(int);
extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);
extern void func_800DA840(void *, s16);

extern u8 D_80170E54[];
extern u8 D_80173C7C[];

/* Advances an actor's motion action and clears its state when the action finishes. */
void func_80172A24(void *action_state, void *transform, void *sprite, EntityRec *actor)
{
    u16 position[4];
    u8 *motion;
    s16 use_player_target;
    void *target;
    s32 delay;
    u8 *action_status;

    use_player_target = 0;
    switch (((S_80172A24_0 *)action_state)->unk_9B) {
    case 0:
        if (((u32)actor->flags1C) & 0x2000) {
            static void *const dispatch_labels[] = {&&player_motion_3, &&player_motion_2, &&player_motion_1, &&no_motion};
            extern void *const D_80170838[];
            u32 motion_index = (u32)((actor->unk_46 & 0x3FFF) - 1);

            if (motion_index >= 7) {
                goto no_motion;
            }
            (void)dispatch_labels;
            goto *D_80170838[motion_index];
        player_motion_3:
            use_player_target = 1;
            goto motion_3;
        player_motion_2:
            use_player_target = 1;
            goto motion_2;
        player_motion_1:
            use_player_target = 1;
            goto motion_1;
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
            ((S_80172A24_0 *)action_state)->unk_98 &= 0xFF7F;
            {
                s16 player_target = use_player_target;

                if (player_target != 0) {
                    target = D_800814A8;
                    actor->target = target;
                    goto have_target;
                }
            }
            if (D_8006DE24[*motion].kind == 2) {
                target = actor->target;
                if (target == 0) {
                    goto advance_motion;
                }
            have_target:
                action_status = (u8 *)((S_80172A24_2_pre *)target)[-1].unk_00;
                actor->unk_72 = ((S_80172A24_3 *)action_status)->unk_24;
                actor->unk_73 = ((S_80172A24_3 *)action_status)->unk_25;
                goto advance_motion;
            }
            actor->target =
                func_800A05A4(actor, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
                              actor->facing, 0x10);
            actor->unk_72 = abs(actor->unk_72);
            actor->unk_73 = abs(actor->unk_73);
        advance_motion:
            position[0] = ((u16)((EntityRec *)transform)->x.w.i);
            position[1] = ((u16)((EntityRec *)transform)->y.w.i);
            position[2] = ((u16)((EntityRec *)transform)->z.w.i);
            transform = (void *)func_800A94A0(actor, motion, use_player_target, (u8 *)action_state + 0x98);
            if (transform == 0) {
                return;
            }
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
            func_800A56E0(0x703);
            func_800DA840(position, (*motion - 1) % 3);
            ((S_80172A24_0 *)action_state)->unk_9B = ((S_80172A24_0 *)action_state)->unk_9B + 1;
            return;
        }

        ((EntityRec *)transform)->flags14 = 0;
        ((EntityRec *)transform)->unk_10 = 0;
        ((EntityRec *)transform)->unk_0C = 0;
        func_800A2B04(transform, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        dungeonStatus.unk_0C = 0;
        (*(u16 *)((u8 *)&D_800814A8->unk_A4 + 2)) = (*(u16 *)((u8 *)D_800814A8 + 0xA6)) - 1;
        func_800A4ACC(actor);
        actor->unk_6D = ((u8)actor->unk_6D) - 1;
        ((S_80172A24_0 *)action_state)->unk_8C = D_80170E54;
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (func_8003F270() != 0) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            return;
        }
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        ((S_80172A24_0 *)action_state)->unk_9B = ((S_80172A24_0 *)action_state)->unk_9B + 1;
        /* fallthrough */
    case 2:
        if ((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 4 && (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            ((S_80172A24_0 *)action_state)->unk_96 = 0x3;
            ((S_80172A24_0 *)action_state)->unk_98 |= 0x80;
        }
        delay = ((S_80172A24_0 *)action_state)->unk_96 - 1;
        ((S_80172A24_0 *)action_state)->unk_96 = delay;
        if ((s16)delay <= 0) {
            ((S_80172A24_0 *)action_state)->unk_96 = 0;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        }
        if ((((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }
        ((EntityRec *)transform)->flags14 = 0;
        ((EntityRec *)transform)->unk_10 = 0;
        ((EntityRec *)transform)->unk_0C = 0;
        func_800A2B04(transform, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        {
            u8 *direction_table = D_80173C7C;

            if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != direction_table) {
                (*(u8 * *)((u8 *)sprite + 0x2C)) = direction_table;
                func_80047784(sprite,
                    direction_table[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
        }
        action_status = (u8 *)&dungeonStatus.unk_00;
        if (((S_80172A24_7 *)action_status)->unk_0C != 0) {
            return;
        }
        ((S_80172A24_7 *)action_status)->unk_0A = ((S_80172A24_7 *)action_status)->unk_0A - 1;
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        ((S_80172A24_0 *)action_state)->unk_8C = D_80170E54;
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
