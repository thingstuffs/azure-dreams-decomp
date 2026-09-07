#include "common.h"
#include "m2c_compat.h"

typedef struct S_8008E264_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_8008E264_0;   /* arg0 in func_8008E264 */

typedef struct S_8008E264_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_8008E264_1;   /* arg2 in func_8008E264 */

typedef struct S_8008E264_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8008E264_2;   /* arg1 in func_8008E264 */

typedef struct S_8008E264_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x30];
    s32 unk_5C;
} S_8008E264_3;   /* arg3 in func_8008E264 */

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
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern s16 D_80083464;
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
    u8 *move_flags;
    u8 *move_timer;
    u8 state;
    s32 launch_state;

    state = ((S_8008E264_0 *)actor)->unk_9B;
    state_index = state;
    if (state_index >= 13) {
        goto done;
    }
    (void)state_labels;
    goto *D_80088810[state_index];
start_move:
        if (((S_8008E264_1 *)sprite)->unk_14 & 0x6000) {
            launch_state = ((S_8008E264_0 *)actor)->unk_9B;
            if (launch_state != 0) {
                goto check_launch_state;
            }
            ASM_KEEP(launch_state);   /* MATCH pin: retail branch polarity depends on it */
            motion_value = 0xFFF00000;
            goto apply_launch;
check_launch_state:
            motion_value = 8;
            if (launch_state != motion_value) {
                motion_value = 0xFFEC0000;
                goto apply_launch;
            }
            motion_value = 0xFFF80000;
apply_launch:
            ((S_8008E264_2 *)motion)->unk_14 = motion_value;
            func_80099F70(((S_8008E264_3 *)model)->unk_5C);
            func_80099F04(((S_8008E264_3 *)model)->unk_5C);
            move_flags = (u8 *)&D_80083460;
            ((S_8008E264_4 *)move_flags)->unk_02 = (u16) (((S_8008E264_4 *)move_flags)->unk_02 | 0x812);
            ((S_8008E264_0 *)actor)->unk_98 = (u16) (((S_8008E264_0 *)actor)->unk_98 & 0xFFF3);
            (*(u8 **)((u8 *)sprite + 0x2C)) = D_800DD040;
            func_80048A44(sprite, D_800DD040[((s32) (D_80083228 + ((S_8008E264_3 *)model)->unk_2A + 0x100) >> 9) & 7], 0, 1);
            ((S_8008E264_0 *)actor)->unk_9B = (u8) (((S_8008E264_0 *)actor)->unk_9B + 1);
            func_800A56E0(0x50A);
            return;
        }
done:
        return;
update_move:
        move_timer = (u8 *)&D_80083460;
        if (((S_8008E264_5 *)move_timer)->unk_04 != 0) {
            motion_value = ((S_8008E264_1 *)sprite)->unk_24 << 6;
            coord_or_ticks = ((S_8008E264_2 *)motion)->unk_02;
            coord_or_ticks -= 0x20;
            motion_value = (motion_value - coord_or_ticks) << 0x10;
            ((S_8008E264_2 *)motion)->unk_0C = motion_value / ((S_8008E264_5 *)move_timer)->unk_04;
            coord_or_ticks = ((S_8008E264_2 *)motion)->unk_06;
            motion_value = ((S_8008E264_1 *)sprite)->unk_25;
            coord_or_ticks -= 0x20;
            motion_value <<= 6;
            motion_value -= coord_or_ticks;
            coord_or_ticks = ((S_8008E264_5 *)move_timer)->unk_04;
            motion_value <<= 0x10;
            ((S_8008E264_2 *)motion)->unk_10 = motion_value / coord_or_ticks;
        }
        ticks_left = (u16) ((S_8008E264_5 *)move_timer)->unk_04 - 1;
        ((S_8008E264_5 *)move_timer)->unk_04 = ticks_left;
        if ((ticks_left << 0x10) <= 0) {
            ((S_8008E264_5 *)move_timer)->unk_04 = 0;
            ((S_8008E264_2 *)motion)->unk_10 = 0;
            ((S_8008E264_2 *)motion)->unk_0C = 0;
            func_800A2B04(motion, ((S_8008E264_1 *)sprite)->unk_24, ((S_8008E264_1 *)sprite)->unk_25);
            if ((u8) ((S_8008E264_0 *)actor)->unk_9B >= 0xAU) {
                (*(u8 **)((u8 *)sprite + 0x2C)) = D_800DD058;
                func_80048A44(sprite, D_800DD058[((s32) (D_80083228 + ((S_8008E264_3 *)model)->unk_2A + 0x100) >> 9) & 7], 0, 1);
                ((S_8008E264_0 *)actor)->unk_9B = (u8) (((S_8008E264_0 *)actor)->unk_9B + 1);
                ((S_8008E264_5 *)move_timer)->unk_04 = 1;
                return;
            }
            goto finish_move;
        }
        return;
wait_animation:
        if (((S_8008E264_1 *)sprite)->unk_14 & 0x6000) {
            D_80083464 = 0;
            goto finish_move;
        }
        return;
finish_move:
        if ((func_80094F74(actor, motion, sprite, model) << 0x10) > 0) {
            ((S_8008E264_0 *)actor)->unk_8C = &D_8008ACDC;
        }
}
