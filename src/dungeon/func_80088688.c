#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

M2C_UNK func_80048A44(void *, u8, s32, s32); /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
M2C_UNK func_8008CAA0(); /* extern */
M2C_UNK func_8008CBD4(); /* extern */
M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800AD4D0();                      /* extern */
extern M2C_UNK D_8008ACDC;
extern u8 D_800DCFB0[8];
extern u8 D_800DCFE0[8];


typedef struct S_8008DDE8_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8008DDE8_4;   /* temp_global in func_8008DDE8 */

/* Update death movement and animation, then select the next death state. */
void func_8008DDE8(void *state, void *motion, void *sprite, void *actor) {
    s16 frames_left;
    s32 pos_y;
    s32 pos_x;
    u16 anim_frames;
    u16 move_frames;
    u16 next_timer;
    u32 velocity_x;
    u8 *anim_table;

    if (((Rec_func_8008ACDC_arg0 *)state)->unk_9B.as_u8 == 0) {
        func_800AD4D0(actor);
        ((Rec_func_8008ACDC_arg0 *)state)->unk_9B.as_u8 = (u8) (((Rec_func_8008ACDC_arg0 *)state)->unk_9B.as_u8 + 1);
        ((EntityRec *)motion)->unk_0C = (u32) (func_80064584(((s16)((EntityRec *)actor)->unk_6A)) << 9);
        ((EntityRec *)motion)->unk_10 = (s32) (func_800644B8(((s16)((EntityRec *)actor)->unk_6A)) << 9);
        ((Rec_func_8008ACDC_arg0 *)state)->unk_96.as_u16 = 0xCU;
    }
    if (((Rec_func_8008ACDC_arg0 *)state)->unk_10C & 1) {
        func_8008CAA0(state, motion, sprite, actor);
        return;
    }
    if ((((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 == D_800DCFE0) && (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000)) {
        anim_frames = ((Rec_func_8008ACDC_arg0 *)state)->unk_96.as_u16 - 1;
        ((Rec_func_8008ACDC_arg0 *)state)->unk_96.as_u16 = anim_frames;
        if ((anim_frames << 0x10) > 0) {
            func_80048A44(sprite, ((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8[((s32) (gameWork.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7], 0, 1);
        }
    }
    frames_left = (s16) ((Rec_func_8008ACDC_arg0 *)state)->unk_96.as_u16;
    if (frames_left > 0) {
        pos_x = ((EntityRec *)motion)->x.v;
        pos_y = ((EntityRec *)motion)->y.v;
        ((EntityRec *)motion)->x.v = (s32) (pos_x + ((s32) ((((((Rec_D_80082E80 *)sprite)->unk_24 << 6) + 0x20) << 0x10) - pos_x) / frames_left));
        ((EntityRec *)motion)->y.v = (s32) (pos_y + ((s32) ((((((Rec_D_80082E80 *)sprite)->unk_25 << 6) + 0x20) << 0x10) - pos_y) / (s16) ((Rec_func_8008ACDC_arg0 *)state)->unk_96.as_u16));
        velocity_x = ((u32)((EntityRec *)motion)->unk_0C);
        ((EntityRec *)motion)->unk_0C = (u32) ((s32) (velocity_x + (velocity_x >> 0x1F)) >> 1);
        ((EntityRec *)motion)->unk_10 = (s32) ((s32) ((EntityRec *)motion)->unk_10 / 2);
        move_frames = ((Rec_func_8008ACDC_arg0 *)state)->unk_96.as_u16 - 1;
        ((Rec_func_8008ACDC_arg0 *)state)->unk_96.as_u16 = move_frames;
        if ((move_frames << 0x10) == 0) {
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0U;
            func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        }
    }
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
        anim_table = D_800DCFB0;
        (*(u8 **)((u8 *)sprite + (0x2C))) = anim_table;
        func_80048A44(sprite, anim_table[((s32) (gameWork.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7], 0, 1);
        if (((s32)dungeonStatus.unk_10) == (actor - 0x20)) {
            dungeonStatus.unk_10 = (s32) (((s32)dungeonStatus.unk_10) & 0x7FFFFFFF);
        }
        if (((EntityRec *)actor)->unk_28 == 0) {
            if (D_800E296C & 0x08000000) {
                ((EntityRec *)actor)->unk_28 = 1U;
                goto assign_timer;
            }
            ((EntityRec *)actor)->unk_28 = 0U;
            func_8008CBD4(state, motion, sprite, actor);
            return;
        }
        next_timer = 8U;
        goto store_timer;
assign_timer:
        next_timer = 8U;
store_timer:
        ((Rec_func_8008ACDC_arg0 *)state)->unk_96.as_u16 = next_timer;
        ((Rec_func_8008ACDC_arg0 *)state)->unk_8C.as_pm = &D_8008ACDC;
    }
}

