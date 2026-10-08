#include "common.h"
extern int abs(int);
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_80172834_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172834_0;   /* arg0 in func_8015A834 */

typedef struct S_80172834_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172834_2_pre;   /* the 0x14 bytes before object in func_8015A834, addressed as object[-1] */

typedef struct S_80172834_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172834_3;   /* record in func_8015A834 */


extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, u16 *);
extern void func_800DA840(u16 *, s32);

extern u8 D_80159058[];
extern u8 D_8015C888[];

/* Starts the selected actor action, waits for completion, and resets its state. */
void func_8015A834(void *action_state, EntityRec *motion, void *sprite, EntityRec *actor)
{
    u8 *action_data;
    s32 phase;
    s32 is_special;
    void *target;
    s16 x;
    s32 y;
    u16 position[3];

    phase = ((S_80172834_0 *)action_state)->unk_9B;
    is_special = 0;
    switch (phase) {
    case 0:
        if (((u32)actor->flags1C) & 0x2000) {
            switch (actor->unk_46 & 0x3FFF) {
            case 7:
                is_special = 1;
            case 3:
                action_data = (u8 *)actor + 0xE;
                break;
            case 6:
                is_special = 1;
            case 2:
                action_data = (u8 *)actor + 0xB;
                break;
            case 5:
                is_special = 1;
            case 1:
                action_data = (u8 *)actor + 8;
                break;
            default:
                action_data = 0;
                break;
            }
        } else {
            switch (actor->unk_46 & 0x3FFF) {
            case 3:
                action_data = (u8 *)actor + 0xE;
                break;
            case 2:
                action_data = (u8 *)actor + 0xB;
                break;
            case 1:
                action_data = (u8 *)actor + 8;
                break;
            default:
                action_data = 0;
                break;
            }
        }
        if (*action_data != 0) {
            x = ((S_80172834_0 *)action_state)->unk_98;
            x &= 0xFF7F;
            ((S_80172834_0 *)action_state)->unk_98 = x;
            x = is_special;
            if (x != 0) {
                target = D_800814A8;
                actor->target = target;
                phase = ((S_80172834_2_pre *)target)[-1].unk_00;
                actor->unk_72 = ((S_80172834_3 *)phase)->unk_24;
                actor->unk_73 = ((S_80172834_3 *)phase)->unk_25;
            } else if (D_8006DE24[*action_data].kind == 2) {
                target = actor->target;
                if (target != 0) {
                    phase = ((S_80172834_2_pre *)target)[-1].unk_00;
                    actor->unk_72 = ((S_80172834_3 *)phase)->unk_24;
                    actor->unk_73 = ((S_80172834_3 *)phase)->unk_25;
                }
            } else {
                actor->target =
                    func_800A05A4(actor,
                                  ((Rec_D_80082E80 *)sprite)->unk_24,
                                  ((Rec_D_80082E80 *)sprite)->unk_25,
                                  actor->facing, 0x10);
                {
                    s32 abs_x = abs(actor->unk_72);
                    s32 abs_y = abs(actor->unk_73);
                    actor->unk_72 = abs_x;
                    actor->unk_73 = abs_y;
                }
            }

            position[0] = ((u16)motion->x.w.i);
            position[1] = ((u16)motion->y.w.i);
            position[2] = ((u16)motion->z.w.i);
            if (func_800A94A0(actor, action_data, is_special,
                              (u16 *)((u8 *)action_state + 0x98)) == 0) {
                return;
            }
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
            func_800DA840(position, (s16)(((s32)*action_data - 1) % 3));
            func_800A56E0(0x703);
            ((S_80172834_0 *)action_state)->unk_9B++;
            return;
        }

        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        dungeonStatus.unk_0C = 0;
        (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
        func_800A4ACC(actor);
        (*(u8 *)&actor->unk_6D)--;
        ((S_80172834_0 *)action_state)->unk_8C = D_80159058;
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
        ((S_80172834_0 *)action_state)->unk_9B++;

    case 2:
        if (!((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 3) &&
              (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) &&
            !(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        ((S_80172834_0 *)action_state)->unk_98 |= 0x80;
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != D_8015C888) {
            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_8015C888;
            func_80047784(
                sprite,
                D_8015C888[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
        }
        {

            if (((s32)dungeonStatus.unk_0C) != 0) {
                return;
            }
            dungeonStatus.unk_0A--;
        }
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        ((S_80172834_0 *)action_state)->unk_8C = D_80159058;
        func_800A4ACC(actor);
        if (actor->unk_6D > 0) {
            (*(u8 *)&actor->unk_6D)--;
        }
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        func_800A56E0(0xB4);

        return;
    default:
        return;
    }
}
