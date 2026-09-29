#include "common.h"
#include "shared/sys_flags.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_8008C13C_2 {
    u8 pad_00[0x8C];
    union { s32 s; void * u; } unk_8C;   /* accessed as both */
    u8 pad_90[0x8];
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
} S_8008C13C_2;   /* arg0 in func_8008C13C */


extern u8 D_8008EAC8[];
extern u8 D_800DCFD8[8];
extern u8 D_800DD0B8[8];

extern void func_80048A44(void *, s32, s32, s32);
extern void func_80094ED4(void *, s32, void *, void *);
extern void func_80099F04(s32);
extern void func_80099F70(s32);
extern void func_8009A21C(s32, s32, s32);
extern void func_8009A3D0(s32, s32, s32);
extern s16 func_8009ABA0(s16, s32, void *, s16, s32);
extern void func_8009F644(void *, s32, s32, s32);
extern s32 func_800A5C70(void);
extern void func_800A67F4(void);


/* Synthetic batch key: func_800869DC; true rowbase link symbol: func_8008C13C. */
/* Attempts a move and updates the actor position, animation, and movement state. */
void func_8008C13C(void *controller, s32 actor_id, void *actor, EntityRec *actor_data) {
    GameWork *dungeon_state;
    s16 move_result;
    u8 direction_index;
    u8 tile_x;
    u8 *x_offsets;

    dungeon_state = &gameWork;
    move_result = func_8009ABA0(actor_data->facing, actor_id, actor,
                           actor_data->unk_88, 0x20);

    if (move_result > 0) {
        func_8009A3D0(((Rec_D_80082E80 *)actor)->unk_24, ((Rec_D_80082E80 *)actor)->unk_25, 0x300);

        direction_index = ((u16)actor_data->facing >> 8) & 0xE;
        x_offsets = ((u8 *)dirStepX);
        tile_x = ((Rec_D_80082E80 *)actor)->unk_24;
        tile_x += x_offsets[direction_index];
        ((Rec_D_80082E80 *)actor)->unk_24 = tile_x;
        ((Rec_D_80082E80 *)actor)->unk_25 += ((u8 *)dirStepY)[direction_index];

        func_8009A21C(((Rec_D_80082E80 *)actor)->unk_24, ((Rec_D_80082E80 *)actor)->unk_25, 0x300);

        dungeonStatus.flags |= 8;
        ((S_8008C13C_2 *)controller)->unk_8C.s = 0;

        if (move_result != 4) {
            if (D_80013714 & 2) {
                dungeonStatus.flags |= 0x80;
            } else if ((dungeon_state->buttons & 0x20) && func_800A5C70()) {
                dungeonStatus.flags |= 0x80;
            }
        }

        if ((dungeonStatus.flags & 0x80) || (move_result == 1)) {
            if (((Rec_D_80082E80 *)actor)->unk_2C.as_pv != D_800DCFD8) {
                (*(void * *)((u8 *)actor + 0x2C)) = D_800DCFD8;
                direction_index = ((gameWork.view.viewAngle + actor_data->facing + 0x100) >> 9) & 7;
                func_80048A44(actor, D_800DCFD8[direction_index], 0, 1);
            }
            func_80099F70(actor_data->unk_5C);
            func_80099F04(actor_data->unk_5C);
            dungeonStatus.unk_04 = 8;
            ((S_8008C13C_2 *)controller)->unk_9A = 0x1D;
        } else {
            ((S_8008C13C_2 *)controller)->unk_98 |= 0xC;
            ((Rec_D_80082E80 *)actor)->unk_14.at00_u16.v |= 0x4000;
            func_80094ED4(controller, actor_id, actor, actor_data);
            if (move_result == 2) {
                ((S_8008C13C_2 *)controller)->unk_9B = 8;
            }
            dungeonStatus.unk_04 = 8;
            ((S_8008C13C_2 *)controller)->unk_9A = 0x1E;
            actor_data->flags1C |= 0x40000000;
            func_8009F644(actor_data, 8, 0, 0);
            return;
        }

        func_8009F644(actor_data, 8, 0, 0);
    } else {
        ((Rec_D_80082E80 *)actor)->unk_2C.as_pv = D_800DD0B8;
        direction_index = ((dungeon_state->view.viewAngle + actor_data->facing + 0x100) >> 9) & 7;
        func_80048A44(actor, D_800DD0B8[direction_index], 0, 1);
        ((S_8008C13C_2 *)controller)->unk_8C.u = D_8008EAC8;
        return;
    }

    func_800A67F4();
    func_80094ED4(controller, actor_id, actor, actor_data);
    actor_data->flags1C |= 0x40000000;
    dungeonStatus.flags |= 0x812;
}
