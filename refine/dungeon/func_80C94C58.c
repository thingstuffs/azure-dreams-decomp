#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80172458_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    s32 unk_A0;
    s16 unk_A4;
    s16 unk_A6;
    u16 unk_A8;
} S_80172458_0;   /* arg0 in func_80172458 */





M2C_UNK func_800419EC();            /* extern */
M2C_UNK func_80047784();         /* extern */
s32 func_800644B8();                             /* extern */
s16 func_800A0818();       /* extern */
M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800A4ACC();                      /* extern */
M2C_UNK func_800A9A04();                      /* extern */
M2C_UNK func_800AD594();             /* extern */
s32 func_800AD9B4();                  /* extern */
M2C_UNK func_800B66C8();                      /* extern */
s16 func_800BCB04();                   /* extern */
extern M2C_UNK D_80082E80;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern u8 D_8017102C[];
extern u8 D_801752CC[];
extern u8 D_801752D4[];

/* Updates tile movement and height interpolation, then finalizes the action when its timer expires. */
void func_80172458(void *action, void *motion, void *map_entry, void *actor) {
    M2C_UNK facing_output;
    s32 move_frames;
    s16 next_move_frame;
    s16 height_frame;
    s32 actor_flags;
    s32 scaled_height_delta;
    s16 *global_state;
    u8 *reference_map_entry;
    register s32 move_value ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 flags_mask;
    register s32 move_operand ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    u16 timer_or_flags;
    s32 phase;

    phase = ((S_80172458_0 *)action)->unk_9B;
    if (phase == 1) {
        goto update_movement;
    }
    if (phase >= 2) {
        goto check_settling;
    }
    if (phase == 0) {
        goto start_movement;
    }
    goto update_timer;
check_settling:
    if (phase == 2) {
        goto finish_movement;
    }
    goto update_timer;
start_movement:
    if (((Rec_D_80082E80 *)map_entry)->unk_14.at00_u16.v & 0x6000) {
        (*(u8 **)((u8 *)map_entry + 0x2C)) = D_801752CC;
        func_80047784(map_entry, D_801752CC[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
        ((S_80172458_0 *)action)->unk_98 = (u16) (((S_80172458_0 *)action)->unk_98 | 8);
        ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 & 0xF7FFFFFF);
        ((S_80172458_0 *)action)->unk_9E = 5;
        ((S_80172458_0 *)action)->unk_A0 = 0;
        ((S_80172458_0 *)action)->unk_9B = (u8) (((S_80172458_0 *)action)->unk_9B + 1);
        ((S_80172458_0 *)action)->unk_A6 = func_800BCB04((((Rec_D_80082E80 *)map_entry)->unk_24 << 6) | 0x20, (((Rec_D_80082E80 *)map_entry)->unk_25 << 6) | 0x20, (s16) (((Rec_D_800E3D7C *)actor)->unk_88.as_u16 - 0x20));
        ((S_80172458_0 *)action)->unk_A8 = (u16) ((Rec_D_800E3D7C *)motion)->unk_08.at02_u16.v;
        goto update_movement;
    }
    goto update_timer;
update_movement:
    move_frames = ((S_80172458_0 *)action)->unk_9E;
    ((S_80172458_0 *)action)->unk_90 = (s32) (((S_80172458_0 *)action)->unk_90 - ((S_80172458_0 *)action)->unk_A0);
    if (move_frames != 0) {
        move_value = ((Rec_D_80082E80 *)map_entry)->unk_24;
        move_operand = ((Rec_D_800E3D7C *)motion)->unk_00.at02_s16.v;
        move_value <<= 6;
        move_operand -= 0x20;
        move_value = ((move_value - move_operand) << 0x10) / move_frames;
        move_operand = ((Rec_D_800E3D7C *)motion)->unk_04.at02_s16.v;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = move_value;
        move_value = ((Rec_D_80082E80 *)map_entry)->unk_25;
        move_operand -= 0x20;
        move_value <<= 6;
        move_value -= move_operand;
        move_operand = ((S_80172458_0 *)action)->unk_9E;
        move_value = (move_value << 0x10) / move_operand;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = move_value;
        if (((S_80172458_0 *)action)->unk_A4 == 3) {
            ((S_80172458_0 *)action)->unk_A0 = (s32) ((0 - func_800644B8(((S_80172458_0 *)action)->unk_9E * 0x155)) << 9);
            ((S_80172458_0 *)action)->unk_90 += ((S_80172458_0 *)action)->unk_A0;
            goto advance_movement;
        }
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        height_frame = ((S_80172458_0 *)action)->unk_9E;
        if (height_frame == 4) {
            goto height_frame_4;
        }
        if (height_frame >= 5) {
            goto height_frame_ge5;
        }
        if (height_frame == 3) {
            goto height_frame_3;
        }
        ((S_80172458_0 *)action)->unk_90 = 0;
        goto advance_movement;
height_frame_ge5:
        if (height_frame == 5) {
            goto height_frame_5;
        }
        flags_mask = 0xF7FF0000;
        if (height_frame != 6) {
            goto clear_height;
        }
        move_operand = (((S_80172458_0 *)action)->unk_A6 - (s16) ((S_80172458_0 *)action)->unk_A8) << 0x10;
        move_value = (s32) (0xFFFE0000 - move_operand);
        goto mask_flags;
height_frame_5:
        move_value = (s32) (0 - ((((S_80172458_0 *)action)->unk_A6 - (s16) ((S_80172458_0 *)action)->unk_A8) << 0x10));
        flags_mask = 0xF7FF0000;
mask_flags:
        ((S_80172458_0 *)action)->unk_90 = move_value;
        flags_mask |= 0xFFFF;
        ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 & flags_mask);
        goto advance_movement;
height_frame_4:
        scaled_height_delta = (((S_80172458_0 *)action)->unk_A6 - (s16) ((S_80172458_0 *)action)->unk_A8) * 3;
        if (scaled_height_delta < 0) {
            scaled_height_delta += 3;
        }
        ((S_80172458_0 *)action)->unk_90 = (s32) (0 - ((scaled_height_delta >> 2) << 0x10));
        ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 & 0xF7FFFFFF);
        goto advance_movement;
height_frame_3:
        ((S_80172458_0 *)action)->unk_90 = (s32) (0 - ((((((S_80172458_0 *)action)->unk_A6 - (s16) ((S_80172458_0 *)action)->unk_A8) * 2) / 5) << 0x10));
        goto advance_movement;
clear_height:
        ((S_80172458_0 *)action)->unk_90 = 0;
    }
advance_movement:
    next_move_frame = (u16) ((S_80172458_0 *)action)->unk_9E - 1;
    ((S_80172458_0 *)action)->unk_9E = next_move_frame;
    if (next_move_frame < 0) {
        ((S_80172458_0 *)action)->unk_90 = 0;
        ((S_80172458_0 *)action)->unk_98 = (u16) (((S_80172458_0 *)action)->unk_98 & 0xFFF7);
        ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 | 0x08000000);
        ((S_80172458_0 *)action)->unk_9B = (u8) (((S_80172458_0 *)action)->unk_9B + 1);
    }
finish_movement:
    if (((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 & 0x08000000) {
        ((S_80172458_0 *)action)->unk_98 = (u16) (((S_80172458_0 *)action)->unk_98 & 0xFFF7);
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)map_entry)->unk_24, ((Rec_D_80082E80 *)map_entry)->unk_25);
        (*(u8 **)((u8 *)map_entry + 0x2C)) = D_801752D4;
        func_80047784(map_entry, D_801752D4[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
        func_800419EC(4, 8);
        func_800B66C8(motion);
        ((S_80172458_0 *)action)->unk_9B = 3U;
    }
update_timer:
    timer_or_flags = ((S_80172458_0 *)action)->unk_96 - 1;
    ((S_80172458_0 *)action)->unk_96 = timer_or_flags;
    if ((timer_or_flags << 0x10) <= 0) {
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)map_entry)->unk_24, ((Rec_D_80082E80 *)map_entry)->unk_25);
        func_800AD594(actor, 4);
        func_800A4ACC(actor);
        global_state = (s16 *)&D_80083460;
        if (global_state[4] != 0) {
            global_state[4] = (s16) ((u16) global_state[4] - 1);
        }
        actor_flags = ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32;
        if (actor_flags & 0x2000) {
            timer_or_flags = ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v;
            if (timer_or_flags & 0x8000) {
                ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v = timer_or_flags & 0x7FFF;
            }
            goto check_next_action;
        }
        if (actor_flags & 0x410) {
            goto check_next_action;
        }
        if (!(actor_flags & 0x20000)) {
            goto check_next_action;
        }
        reference_map_entry = (u8 *)&D_80082E80;
        ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 = func_800A0818(((Rec_D_80082E80 *)map_entry)->unk_24, ((Rec_D_80082E80 *)map_entry)->unk_25, reference_map_entry[0x24], reference_map_entry[0x25], &facing_output);
check_next_action:
        if ((func_800AD9B4(map_entry, actor) << 0x10) > 0) {
            ((S_80172458_0 *)action)->unk_8C = D_8017102C;
            func_800A9A04(actor);
        }
    }
}
