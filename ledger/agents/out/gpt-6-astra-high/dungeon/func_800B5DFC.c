#include "common.h"
#include "m2c_compat.h"

extern s32 D_80083460[3];
extern s32 D_800814A0[3];
s32 func_800644B8();
s32 func_80064584();
s16 func_800A07D0();
M2C_UNK func_800A56E0();
M2C_UNK func_800BB2E4();
M2C_UNK func_800BC0A8();

typedef struct DungeonWork {
    u8 pad_00[0x30];
    s16 field_30[5];
    u8 pad_3A[2];
    s16 field_3C[5];
} DungeonWork;


typedef struct S_800BB55C_0_pre {
    s32 unk_00;
    u8 pad_04[0xE];
    u16 unk_12;
} S_800BB55C_0_pre;   /* the 0x14 bytes before arg0 in func_800BB55C, addressed as arg0[-1] */

typedef struct S_800BB55C_0 {
    u8 pad_00[0x4A];
    union { s16 s; u16 u; } unk_4A;   /* accessed as both */
    s16 unk_4C;
    u16 unk_4E;
    s16 unk_50;
    u8 pad_52[0x6];
    s16 unk_58;
    u8 pad_5A[0x2];
    s32 unk_5C;
    s32 (*unk_60)();
    u16 unk_64;
} S_800BB55C_0;   /* arg0 in func_800BB55C */

typedef struct S_800BB55C_1 {
    u8 pad_00[0x30];
    s16 unk_30;
    u8 pad_32[0xA];
    s16 unk_3C;
} S_800BB55C_1;   /* var_s2_angle in func_800BB55C */

typedef struct S_800BB55C_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800BB55C_2;   /* arg1 in func_800BB55C */

typedef struct S_800BB55C_3 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_800BB55C_3;   /* temp_a0 in func_800BB55C */

typedef struct S_800BB55C_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800BB55C_4;   /* global_ptr in func_800BB55C */

/* Draws a growing five-point pattern and updates its rotating fade-out effect. */
void func_800BB55C(void *effect, S_800BB55C_2 *position, s32 restore_link) {
    s32 draw_params[2];
    s16 start_xy[2];
    s16 end_xy[2];
    s16 end_y;
    s16 line_angle;
    s16 arc_length;
    register s32 slot_or_angle ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 base_angle;
    s32 radius_decay;
    register s32 packet_or_angle ASM_REG("$16");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 saved_link;
    s32 segment_index;
    s32 point_index;
    u16 rotation;
    u16 phase_ticks;
    u16 next_phase;
    register u16 fade_ticks ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    u8 red;
    u8 green;
    u8 blue;
    u8 *effect_globals;
    S_800BB55C_3 *color;
    register DungeonWork *arc_or_count ASM_REG("$19");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    DungeonWork *arc_state;

    draw_params[0] = 0x01000340;
    draw_params[1] = 0x460044;
    packet_or_angle = effect + 0xC;
    func_800478B8(packet_or_angle);
    saved_link = restore_link;
    ((S_800BB55C_0_pre *)effect)[-1].unk_00 = packet_or_angle;
    func_800BB2E4(NULL, NULL, draw_params, 0, effect);
    base_angle = -0x400;
    point_index = 0;
    slot_or_angle = (s32) effect;
    do {
        packet_or_angle = (s16)base_angle;
        start_xy[0] = (func_80064584(packet_or_angle) >> 7) + 0x362;
        start_xy[1] = (func_800644B8(packet_or_angle) >> 7) + 0x122;
        packet_or_angle += 0x999;
        end_xy[0] = (func_80064584(packet_or_angle) >> 7) + 0x362;
        end_y = (func_800644B8(packet_or_angle) >> 7) + 0x122;
        end_xy[1] = end_y;
        line_angle = func_800A07D0(start_xy[0], start_xy[1], end_xy[0], end_y);
        end_xy[0] = (u16) start_xy[0] + ((s32) (func_80064584(line_angle) * ((S_800BB55C_1 *)slot_or_angle)->unk_30) >> 0xB);
        end_xy[1] = (u16) start_xy[1] + ((s32) (func_800644B8(line_angle) * ((S_800BB55C_1 *)slot_or_angle)->unk_30) >> 0xB);
        ((S_800BB55C_1 *)slot_or_angle)->unk_3C = base_angle;
        base_angle += 0x999;
        func_800BB2E4(start_xy, end_xy, draw_params, 0, NULL);
        point_index += 1;
        slot_or_angle += 2;
    } while (point_index < 5);
    base_angle = -0x400;
    ASM_KEEP_NV(base_angle);   /* MATCH pin: load-bearing for the whole function shape */
    ASM_KEEP_NV(effect);   /* MATCH pin: keeps a constant in a register as retail does */
    arc_or_count = effect;
    packet_or_angle = base_angle << 0x10;
    do {
        packet_or_angle >>= 0x10;
        start_xy[0] = (func_80064584((s16) packet_or_angle) >> 7) + 0x362;
        start_xy[1] = (func_800644B8((s16) packet_or_angle) >> 7) + 0x122;
        slot_or_angle = base_angle;
        segment_index = 0;
        if (arc_or_count->field_30[0] > 0) {
            arc_state = arc_or_count;
            packet_or_angle = slot_or_angle + 0x19;
            do {
                slot_or_angle = packet_or_angle;
                ASM_KEEP_NV(packet_or_angle);   /* MATCH pin: retail register colouring depends on it */
                end_xy[0] = (func_80064584((s16)packet_or_angle) >> 7) + 0x362;
                end_xy[1] = (func_800644B8((s16)packet_or_angle) >> 7) + 0x122;
                func_800BB2E4(start_xy, end_xy, draw_params, 0, NULL);
                start_xy[0] = (u16) end_xy[0];
                start_xy[1] = (u16) end_xy[1];
                packet_or_angle = slot_or_angle + 0x19;
            } while (++segment_index < arc_state->field_30[0]);
        }
        arc_length = (u16) arc_or_count->field_30[0] + 1;
        arc_or_count->field_30[0] = arc_length;
        base_angle += 0x333;
        if (arc_length >= 0x1F) {
            arc_or_count->field_30[0] = 0x1F;
            if (((S_800BB55C_0 *)effect)->unk_4A.s == 0) {
                if (((S_800BB55C_0 *)effect)->unk_60() != 0) {
                    ((S_800BB55C_0 *)effect)->unk_50 = 0x120;
                    ((S_800BB55C_0 *)effect)->unk_4A.s = (s16) ((u16) ((S_800BB55C_0 *)effect)->unk_4A.s + 1);
                    func_800A56E0(0x603);
                }
            }
            ((S_800BB55C_0 *)effect)->unk_4C = 0x20;
        }
        arc_or_count = (DungeonWork *)((u8 *)arc_or_count + 2);
        packet_or_angle = base_angle << 0x10;
    } while ((s32) arc_or_count < (s32) (effect + 0xA));
    func_800BB2E4(NULL, NULL, draw_params, 1, NULL);
    ((S_800BB55C_0_pre *)effect)[-1].unk_00 = saved_link;
    if (((S_800BB55C_0 *)effect)->unk_4A.s != 0) {
        ((S_800BB55C_0 *)effect)->unk_4E = (u16) (((S_800BB55C_0 *)effect)->unk_4E + 0x100);
        arc_or_count = (DungeonWork *) 0;
        do {
            arc_or_count = (DungeonWork *)((s32) arc_or_count + 1);
            rotation = ((S_800BB55C_0 *)effect)->unk_4E + 0x400;
            ((S_800BB55C_0 *)effect)->unk_4E = rotation;
            func_800BC0A8(position->unk_02, position->unk_06, position->unk_0A, (s16) rotation, (s32) ((S_800BB55C_0 *)effect)->unk_50, (s32) ((S_800BB55C_0 *)effect)->unk_58, ((S_800BB55C_0 *)effect)->unk_5C, 6);
        } while ((s32) arc_or_count < 4);
        if (((S_800BB55C_0 *)effect)->unk_58 < 0x20) {
            ((S_800BB55C_0 *)effect)->unk_58 = (s16) ((u16) ((S_800BB55C_0 *)effect)->unk_58 + 1);
        }
        if (((S_800BB55C_0 *)effect)->unk_4A.s == 1) {
            phase_ticks = ((S_800BB55C_0 *)effect)->unk_64 + 1;
            ((S_800BB55C_0 *)effect)->unk_64 = phase_ticks;
            if ((s16) phase_ticks >= 0x21) {
                next_phase = ((S_800BB55C_0 *)effect)->unk_4A.u + 1;
                ((S_800BB55C_0 *)effect)->unk_64 = 0x10U;
                ((S_800BB55C_0 *)effect)->unk_4A.u = next_phase;
                return;
            }
        } else {
            red = (u8) ((S_800BB55C_0 *)effect)->unk_5C;
            color = effect + 0x5C;
            color->unk_00 = (u8) (red - ((s32) red / (s16) ((S_800BB55C_0 *)effect)->unk_64));
            green = color->unk_01;
            color->unk_01 = (u8) (green - ((s32) green / (s16) ((S_800BB55C_0 *)effect)->unk_64));
            blue = color->unk_02;
            color->unk_02 = (u8) (blue - ((s32) blue / (s16) ((S_800BB55C_0 *)effect)->unk_64));
            radius_decay = (s16) ((S_800BB55C_0 *)effect)->unk_50 / (s16) ((S_800BB55C_0 *)effect)->unk_64;
            fade_ticks = ((S_800BB55C_0 *)effect)->unk_64 - 1;
            ((S_800BB55C_0 *)effect)->unk_64 = fade_ticks;
            ((S_800BB55C_0 *)effect)->unk_50 = (s16) ((u16) ((S_800BB55C_0 *)effect)->unk_50 - radius_decay);
            if ((fade_ticks << 0x10) <= 0) {
                effect_globals = (u8 *)D_80083460;
                ((S_800BB55C_4 *)effect_globals)->unk_0A = (u16) (((S_800BB55C_4 *)effect_globals)->unk_0A - 1);
                ((S_800BB55C_0_pre *)effect)[-1].unk_12 = (u16) (((S_800BB55C_0_pre *)effect)[-1].unk_12 | 0x8000);
                D_800814A0[0] = D_800814A0[0] | 0x8000;
            }
        }
    }
}
