#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_801724B0_arg0.h"


typedef struct S_801724B0_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_801724B0_3;   /* (u8 *)arg3 + ((S_801724B0_0 *)arg3)->unk_8A.s in func_801724B0 */


extern s32 func_80047784();
extern s32 func_8009A21C();
extern s32 func_8009A3D0();
extern s16 func_8009A66C();
extern s16 func_800A0818();
extern s32 func_80172E0C();

extern u8 D_800E2348[8];

/* Advance the actor along its queued path and update movement timing. */
void func_801724B0(void *motion, s32 actor_index, void *actor, EntityRec *move_data) {
    s32 tile_mask;
    s16 heading;
    s32 x;
    s32 y;

    if ((((s8)move_data->unk_71) > 0) &&
        (move_data->unk_71 > move_data->unk_8A)) {
        if (((Rec_D_80082E80 *)actor)->unk_2C.as_pu8 != D_800E2348) {
            (*(u8 * *)((u8 *)actor + 0x2C)) = D_800E2348;
            func_80047784(
                actor,
                D_800E2348[((gameWork.view.viewAngle + move_data->facing + 0x100) >> 9) & 7],
                0);
            ((Rec_func_801724B0_arg0 *)motion)->unk_9E = 0;
        }

        x = ((Rec_D_80082E80 *)actor)->unk_24;
        y = ((Rec_D_80082E80 *)actor)->unk_25;
        tile_mask = (move_data->flags1C & 0x2000) ? 0x300 : 0x3000;
        func_8009A3D0(x, y, tile_mask);

        heading = func_800A0818(
            x,
            y,
            ((S_801724B0_3 *)((u8 *)move_data + move_data->unk_8A))->unk_74,
            ((S_801724B0_3 *)((u8 *)move_data + move_data->unk_8A))->unk_7C,
            (u8 *)motion + 0x98);
        x = (s16)func_8009A66C(heading, actor, move_data, 0x20);

        ((Rec_D_80082E80 *)actor)->unk_24 =
            ((S_801724B0_3 *)((u8 *)move_data + move_data->unk_8A))->unk_74;
        tile_mask = 0x3000;
        ((Rec_D_80082E80 *)actor)->unk_25 =
            ((S_801724B0_3 *)((u8 *)move_data + move_data->unk_8A))->unk_7C;
        (*(u16 *)&move_data->unk_8A)++;

        {
            s32 next_x = ((Rec_D_80082E80 *)actor)->unk_24;
            s32 next_y = ((Rec_D_80082E80 *)actor)->unk_25;

            if (move_data->flags1C & 0x2000) {
                tile_mask = 0x300;
            }
            func_8009A21C(next_x, next_y, tile_mask);
        }

        move_data->facing = heading;
        if (x == 3) {
            if (!(dungeonStatus.flags & 0x80) && !(((Rec_D_80082E80 *)actor)->unk_14.at00_u16.v & 0x8000)) {
                func_80172E0C(motion, actor_index, actor, move_data);
                ((Rec_func_801724B0_arg0 *)motion)->unk_8C = 0;
                goto post_state;
            }
        }

        ((Rec_func_801724B0_arg0 *)motion)->unk_9A = 0xF;
        ((Rec_func_801724B0_arg0 *)motion)->unk_8C = 0;

post_state:
        (move_data->flags1C) |= 0x40000000;
        if (dungeonStatus.flags & 0x80) {
            ((Rec_func_801724B0_arg0 *)motion)->unk_96 = 0;
            return;
        }

        ((Rec_func_801724B0_arg0 *)motion)->unk_96 = 8;
        x = move_data->unk_71;
        if (x > 0) {
            ((Rec_func_801724B0_arg0 *)motion)->unk_96 = 8 / x;
        }
    }

    return;
}

/* MECHANISM: The four live arguments and two call results naturally produce the retail 0x38 frame and saved-register order.
   A guarded s0 pin holds the signed func_8009A66C result; placing ASM_KEEP before the result store lets that sh fill the bne delay slot.
   Explicit mode initialization plus scoped next-coordinate locals reproduce the post
       -call load/store and branch emission order. */
