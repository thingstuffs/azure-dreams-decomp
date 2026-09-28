#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"





typedef struct S_8008E264_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_8008E264_4;   /* state_base0 in func_8008E264 */

typedef struct S_8008E264_5 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_8008E264_5;   /* state_base1 in func_8008E264 */


M2C_UNK func_80048A44(); /* extern */
s32 func_80094F74();  /* extern */
M2C_UNK func_80099F04();                         /* extern */
M2C_UNK func_80099F70();                         /* extern */
M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern void *D_80088810[];
extern M2C_UNK D_8008ACDC;
extern u8 D_800DD040[];
extern u8 D_800DD058[];

/* Updates movement toward a target tile and advances the actor's animation state. */
void func_8008E264(void *actor, void *motion, void *sprite, void *model) {
    static void *const state_labels[13] = {
        &&start_move, &&update_move, &&done, &&done,
        &&done, &&done, &&done, &&done,
        &&start_move, &&update_move, &&start_move, &&update_move, &&wait_animation
    };
    s16 ticks_left;
    s32 coord_or_ticks;
    s32 motion_value;
    u32 state_index;
    u8 state;
    s32 launch_state;

    state = ((Rec_func_8008ACDC_arg0 *)actor)->unk_9B.as_u8;
    state_index = state;
    if (state_index >= 13) {
        goto done;
    }
    (void)state_labels;
    goto *D_80088810[state_index];
start_move:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
            launch_state = ((Rec_func_8008ACDC_arg0 *)actor)->unk_9B.as_u8;
            if (launch_state != 0) {
                goto check_launch_state;
            }
            ((EntityRec *)motion)->flags14 = 0xFFF00000;
            goto launch_ready;
check_launch_state:
            motion_value = 8;
            if (launch_state != motion_value) {
                motion_value = 0xFFEC0000;
                goto apply_launch;
            }
            motion_value = 0xFFF80000;
apply_launch:
            ((EntityRec *)motion)->flags14 = motion_value;
launch_ready:
            func_80099F70(((EntityRec *)model)->unk_5C);
            func_80099F04(((EntityRec *)model)->unk_5C);
            dungeonStatus.flags = (u16) (dungeonStatus.flags | 0x812);
            ((Rec_func_8008ACDC_arg0 *)actor)->unk_98 = (u16) (((Rec_func_8008ACDC_arg0 *)actor)->unk_98 & 0xFFF3);
            (*(u8 **)((u8 *)sprite + 0x2C)) = D_800DD040;
            func_80048A44(sprite, D_800DD040[((s32) (gameWork.viewAngle + ((EntityRec *)model)->facing + 0x100) >> 9) & 7], 0, 1);
            ((Rec_func_8008ACDC_arg0 *)actor)->unk_9B.as_u8 = (u8) (((Rec_func_8008ACDC_arg0 *)actor)->unk_9B.as_u8 + 1);
            func_800A56E0(0x50A);
            return;
        }
done:
        return;
update_move:
        if (dungeonStatus.unk_04 != 0) {
            motion_value = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
            coord_or_ticks = ((EntityRec *)motion)->x.w.i;
            coord_or_ticks -= 0x20;
            motion_value = (motion_value - coord_or_ticks) << 0x10;
            ((EntityRec *)motion)->unk_0C = motion_value / dungeonStatus.unk_04;
            coord_or_ticks = ((EntityRec *)motion)->y.w.i;
            motion_value = ((Rec_D_80082E80 *)sprite)->unk_25;
            coord_or_ticks -= 0x20;
            motion_value <<= 6;
            motion_value -= coord_or_ticks;
            coord_or_ticks = dungeonStatus.unk_04;
            motion_value <<= 0x10;
            ((EntityRec *)motion)->unk_10 = motion_value / coord_or_ticks;
        }
        ticks_left = (u16) dungeonStatus.unk_04 - 1;
        dungeonStatus.unk_04 = ticks_left;
        if ((ticks_left << 0x10) <= 0) {
            dungeonStatus.unk_04 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
            if ((u8) ((Rec_func_8008ACDC_arg0 *)actor)->unk_9B.as_u8 >= 0xAU) {
                (*(u8 **)((u8 *)sprite + 0x2C)) = D_800DD058;
                func_80048A44(sprite, D_800DD058[((s32) (gameWork.viewAngle + ((EntityRec *)model)->facing + 0x100) >> 9) & 7], 0, 1);
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_9B.as_u8 = (u8) (((Rec_func_8008ACDC_arg0 *)actor)->unk_9B.as_u8 + 1);
                dungeonStatus.unk_04 = 1;
                return;
            }
            goto finish_move;
        }
        return;
wait_animation:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
            dungeonStatus.unk_04 = 0;
            goto finish_move;
        }
        return;
finish_move:
        if ((func_80094F74(actor, motion, sprite, model) << 0x10) > 0) {
            ((Rec_func_8008ACDC_arg0 *)actor)->unk_8C.as_pm = &D_8008ACDC;
        }
}
