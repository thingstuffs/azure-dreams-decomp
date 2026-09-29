#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_80082E80.h"



typedef struct S_8016AFC4_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_8016AFC4_3;   /* entry in func_8016AFC4 */

typedef struct S_8016AFC4_4 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_8016AFC4_4;   /* (u8 *)arg3 + ((S_8016AFC4_0 *)arg3)->unk_8A.s in func_8016AFC4 */



extern s32 func_80047784();
extern s32 func_8009A21C();
extern s32 func_8009A3D0();
extern s32 func_8009A66C();
extern s16 func_800A0818();

extern u8 D_801739C0[8];
extern u8 D_801739C8[8];
extern u8 D_801739D0[8];
extern u8 D_801739D8[8];

/* Advance the actor along its path and update its animation, facing, and movement timing. */
void func_8016AFC4(void *actor, s32 unused, void *sprite, EntityRec *movement)
{
    s32 move_mode;
    s32 behavior;
    s32 step_count;
    s32 old_x;
    s32 old_y;
    s16 direction;
    u8 *path_step;

    if (((s8)movement->unk_71) <= 0) {
        return;
    }
    {
        s32 path_count = movement->unk_71;
        if (movement->unk_8A >= path_count) {
            return;
        }
    }

    behavior = ((Rec_func_800A9E70_arg0 *)actor)->unk_AC;
    switch (behavior) {
    case 0:
        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != D_801739C0) {
            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801739C0;
            func_80047784(sprite,
                D_801739C0[((gameWork.view.viewAngle + movement->facing + 0x100) >> 9) & 7],
                0);
        }
        break;
    case 1:
        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != D_801739C8) {
            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801739C8;
            func_80047784(sprite,
                D_801739C8[((gameWork.view.viewAngle + movement->facing + 0x100) >> 9) & 7],
                0);
        }
        break;
    case 2:
        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != D_801739D0) {
            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801739D0;
            func_80047784(sprite,
                D_801739D0[((gameWork.view.viewAngle + movement->facing + 0x100) >> 9) & 7],
                0);
        }
        break;
    case 3:
        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != D_801739D8) {
            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801739D8;
            func_80047784(sprite,
                D_801739D8[((gameWork.view.viewAngle + movement->facing + 0x100) >> 9) & 7],
                0);
        }
        break;
    }

    move_mode = 0x3000;
    old_x = ((Rec_D_80082E80 *)sprite)->unk_24;
    old_y = ((Rec_D_80082E80 *)sprite)->unk_25;
    if (movement->flags1C & 0x2000) {
        move_mode = 0x300;
    }
    func_8009A3D0(old_x, old_y, move_mode);

    path_step = (u8 *)movement + movement->unk_8A;
    direction = func_800A0818(old_x, old_y, ((S_8016AFC4_3 *)path_step)->unk_74,
                              ((S_8016AFC4_3 *)path_step)->unk_7C, (u8 *)actor + 0x98);
    func_8009A66C(direction, sprite, movement, 0x20);

    ((Rec_D_80082E80 *)sprite)->unk_24 =
        ((S_8016AFC4_4 *)((u8 *)movement + movement->unk_8A))->unk_74;
    ((Rec_D_80082E80 *)sprite)->unk_25 =
        ((S_8016AFC4_4 *)((u8 *)movement + movement->unk_8A))->unk_7C;
    (*(u16 *)&movement->unk_8A)++;

    func_8009A21C(((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
                  (movement->flags1C & 0x2000) ? 0x300 : 0x3000);

    movement->facing = direction;
    ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_s8 = 0xF;
    ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
    (movement->flags1C) |= 0x40000000;

    if (dungeonStatus.flags & 0x80) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_96.as_s16 = 0;
        return;
    }

    if (((Rec_func_800A9E70_arg0 *)actor)->unk_B0 != 0) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_96.as_s16 = 0x10;
    } else {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_96.as_s16 = 8;
    }
    step_count = movement->unk_71;
    if (step_count > 0) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_96.as_s16 = ((Rec_func_800A9E70_arg0 *)actor)->unk_96.as_s16 / step_count;
    }
}
