#include "common.h"
#include "m2c_compat.h"

typedef struct S_80025C94_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x12];
    s16 unk_2A;
    u8 pad_2C[0x2C];
    void * unk_58;
    M2C_UNK (*unk_5C)(void *, void *, void *, void *);
    u8 pad_60[0xA];
    s16 unk_6A;
    u8 pad_6C[0x6];
    union { s8 s; u8 u; } unk_72;   /* accessed as both */
    union { s8 s; u8 u; } unk_73;   /* accessed as both */
    u8 pad_74[0x14];
    s16 unk_88;
} S_80025C94_0;   /* temp_s0 in func_80025C94 */

typedef struct S_80025C94_1 {
    u8 pad_00[0x92];
    s16 unk_92;
    u8 pad_94[0x2];
    s16 unk_96;
    u8 pad_98[0x5];
    s8 unk_9D;
} S_80025C94_1;   /* temp_a3 in func_80025C94 */

typedef struct S_80025C94_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
} S_80025C94_2;   /* temp_s1 in func_80025C94 */

typedef struct S_80025C94_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0xA];
    s16 unk_16;
} S_80025C94_3;   /* temp_s2 in func_80025C94 */

typedef struct S_80025C94_4 {
    u8 pad_00[0xC8];
    u16 unk_C8;
} S_80025C94_4;   /* temp_s5 in func_80025C94 */

typedef struct S_80025C94_5 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xB];
    u16 unk_1A;
} S_80025C94_5;   /* temp_s3 in func_80025C94 */

typedef struct S_80025C94_6 {
    u8 pad_00[0x2094];
    u16 unk_2094;
} S_80025C94_6;   /* (s8 *)temp_table + (((S_80025C94_0 *)temp_s0)->unk_6A * 2) in func_80025C94 */

typedef struct S_80025C94_7_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80025C94_7_pre;   /* the 0x14 bytes before ((S_80025C94_0 *)temp_s0)->unk_58 in func_80025C94, addressed as ((S_80025C94_0 *)temp_s0)->unk_58[-1] */

typedef struct S_80025C94_7 {
    u8 pad_00[0x26];
    s16 unk_26;
} S_80025C94_7;   /* ((S_80025C94_0 *)temp_s0)->unk_58 in func_80025C94 */


extern s16 D_80027156;
extern s16 D_80027158;
extern s16 D_8002715A;
extern u16 D_8002715C;
extern s8 D_8006CCD8[];
extern s8 D_8006CCE8[];
extern s8 D_80083160[];
extern u16 D_800DCEAC[];
extern u16 D_800DCEBC[];

/* Updates an object's fade and position, draws it, and restores its color. */
void func_80025C94(void *object_arg, void *position_arg, void *sprite_arg) {
    s16 move_ticks;
    s32 start_y;
    s32 move_ticks_left;
    s32 draw_scale;
    s32 direction;
    s8 fade_out_ticks;
    s8 fade_out_left;
    s8 state;
    u16 saved_render_value;
    u16 update_count;
    u8 fade_in_left;
    u8 fade_out_level;
    u8 next_fade_out;
    u8 fade_in_level;
    u8 next_fade_in;
    s32 red;
    s32 green;
    s32 blue;
    u16 *direction_table;
    register S_80025C94_1 *motion ASM_REG("$7");   /* MATCH pin: retail register colouring depends on it */
    S_80025C94_0 *object;
    S_80025C94_2 *sprite;
    S_80025C94_3 *position;
    S_80025C94_5 *appearance;
    S_80025C94_4 *render_context;
    void *object_ptr;
    void *fade_in_ticks;

    update_count = D_8002715C;
    object_ptr = object_arg;
    motion = object_ptr;
    position = position_arg;
    sprite = sprite_arg;
    object = motion;
    D_8002715C = update_count + 1;
    render_context = D_80083160;
    state = object->unk_72.s;
    if (state == 1) {
        goto fade_in;
    }
    if (state < 2) {
        if (state == 0) {
            goto initialize;
        }
        motion->unk_96 = 0;
        goto done;
    }
    if (state == 2) {
        goto check_fade_out;
    }
    if (state == 3) {
        goto fade_out;
    }
    motion->unk_96 = 0;
    goto done;
initialize:
    sprite->unk_1E = 0x1000;
    sprite->unk_1C = 0x1000;
    sprite->unk_0E = 0U;
    sprite->unk_0D = 0U;
    sprite->unk_0C = 0U;
    object->unk_73.s = 8;
    object->unk_2A = 0x400;
    direction_table = (u16 *)0x80010000;
    direction = (((S_80025C94_6 *)((s8 *)direction_table + (object->unk_6A * 2)))->unk_2094 + 2) & 7;
    position->unk_00.at02.v = D_800DCEAC[direction];
    start_y = D_800DCEBC[direction];
    position->unk_0A = 0;
    position->unk_04.at02.v = start_y;
    sprite->unk_24 = (u8) (D_8006CCD8[direction * 2] + 1);
    sprite->unk_25 = (u8) (D_8006CCE8[direction * 2] + 1);
    object->unk_72.s = (s8) ((u8) object->unk_72.s + 1);
fade_in:
    fade_in_ticks = (void *) object->unk_73.s;
    if (fade_in_ticks != NULL) {
        fade_in_level = sprite->unk_0E;
        next_fade_in = fade_in_level + ((s32) (0x80 - fade_in_level) / (s32) fade_in_ticks);
        sprite->unk_0E = next_fade_in;
        sprite->unk_0D = next_fade_in;
        sprite->unk_0C = next_fade_in;
    }
    fade_in_left = object->unk_73.u - 1;
    object->unk_73.u = fade_in_left;
    if ((fade_in_left << 0x18) > 0) {
        goto check_fade_out;
    }
    sprite->unk_0E = 0x80U;
    sprite->unk_0D = 0x80U;
    sprite->unk_0C = 0x80U;
    object->unk_73.u = 0U;
    object->unk_72.u = (u8) (object->unk_72.u + 1);
check_fade_out:
    if (D_8002715A == 0) {
        goto update_position;
    }
    object->unk_73.u = 8U;
    position->unk_16 = 8;
    goto advance_state;
fade_out:
    fade_out_ticks = object->unk_73.s;
    if (fade_out_ticks != 0) {
        fade_out_level = sprite->unk_0E;
        next_fade_out = fade_out_level + ((s32) (0 - fade_out_level) / fade_out_ticks);
        sprite->unk_0E = next_fade_out;
        sprite->unk_0D = next_fade_out;
        sprite->unk_0C = next_fade_out;
    }
    fade_out_left = (u8) object->unk_73.s - 1;
    object->unk_73.s = fade_out_left;
    if ((fade_out_left << 0x18) > 0) {
        goto update_position;
    }
advance_state:
    object->unk_72.u = (u8) (object->unk_72.u + 1);
update_position:
    move_ticks = motion->unk_96;
    if (move_ticks != 0) {
        position->unk_00.at00.v = (s32) (position->unk_00.at00.v + ((s32) ((((sprite->unk_24 - 1) << 6) - (s16) position->unk_00.at02.v) << 0x10) / move_ticks));
        position->unk_04.at00.v = (s32) (position->unk_04.at00.v + ((s32) ((((sprite->unk_25 - 1) << 6) - (s16) position->unk_04.at02.v) << 0x10) / (s16) motion->unk_96));
        move_ticks_left = (u16) motion->unk_96 - 1;
        motion->unk_96 = move_ticks_left;
        if ((move_ticks_left << 0x10) <= 0) {
            motion->unk_96 = 0;
        }
    }
    if (object->unk_14 & 0x40000) {
        motion->unk_92 = -0x20;
        goto prepare_draw;
    }
    motion->unk_92 = 0;
prepare_draw:
    motion->unk_9D = 0;
    appearance = ((S_80025C94_7_pre *)(object->unk_58))[-1].unk_00;
    saved_render_value = render_context->unk_C8;
    render_context->unk_C8 = (u16) appearance->unk_1A;
    sprite->unk_14 = (u16) (sprite->unk_14 & 0xFFBF);
    position->unk_00.at02.v = (u16) (position->unk_00.at02.v + 0x100);
    position->unk_04.at02.v = (u16) (position->unk_04.at02.v + 0x100);
    if (D_80027158 == object->unk_6A) {
        draw_scale = (D_80027156 << 9) + 0x400;
        goto store_draw_scale;
    }
    draw_scale = 0x400;
store_draw_scale:
    object->unk_2A = draw_scale;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    object->unk_5C(motion, position, sprite, motion);
    position->unk_00.at02.v = (u16) (position->unk_00.at02.v - 0x100);
    position->unk_04.at02.v = (u16) (position->unk_04.at02.v - 0x100);
    render_context->unk_C8 = saved_render_value;
    object->unk_88 = 0;
    red = appearance->unk_0C;
    if (object->unk_6A != ((S_80025C94_7 *)(object->unk_58))->unk_26) {
        red = red >> 1;
    }
    sprite->unk_0C = red;
    green = appearance->unk_0D;
    if (object->unk_6A != ((S_80025C94_7 *)(object->unk_58))->unk_26) {
        green = green >> 1;
    }
    sprite->unk_0D = green;
    blue = appearance->unk_0E;
    if (object->unk_6A != ((S_80025C94_7 *)(object->unk_58))->unk_26) {
        blue = blue >> 1;
    }
    sprite->unk_0E = blue;
    goto done;
done:
    return;
}
