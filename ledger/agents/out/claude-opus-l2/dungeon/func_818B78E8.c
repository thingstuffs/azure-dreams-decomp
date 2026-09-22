#include "common.h"
#include "m2c_compat.h"

extern s32 D_800814A0[3];
extern void func_800478B8(void *);
M2C_UNK func_80024FD4();

typedef struct {
    u8 pad[0x14];
    u16 field14;
} S818B78E8_Child;

typedef struct {
    S818B78E8_Child *child;
    u8 pad04[0xA];
    s16 state;
    s16 field10;
    u16 field12;
    s16 field14;
} S818B78E8_Obj;

typedef struct {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10;
    s32 x14;
} S818B78E8_Vec;

typedef struct {
    u8 pad[0xC];
    s8 fieldC;
    s8 fieldD;
    s8 fieldE;
    u8 pad0F[3];
    s16 field12;
    u16 flags;
    u8 pad16[4];
    u16 field1A;
    s16 field1C;
    s16 field1E;
} S818B78E8_State;

/* Per-frame update for the four-phase spark effect: drift, tint ramp, hold, then mark the owner finished. */
void func_800250E8(S818B78E8_Obj *obj, S818B78E8_Vec *motion, S818B78E8_State *gfx) {
    s32 variant_index;
    s16 fade;
    s16 next_tick;
    s16 phase;
    s16 elapsed;
    s16 limit;
    s32 red_state2;
    s32 red;
    s32 fade_offset;
    s32 elapsed_now;
    s32 variant_s16;
    s32 half_variant_b;
    s32 blue_component;
    s32 half_variant;
    s32 shifted;
    s32 vec_x10;
    s32 vec_x14;
    s32 variant;
    s32 tick;
    u16 phase_value;
    S818B78E8_Child *child;

    child = obj->child;
    child->field14 = (u16) (child->field14 + 1);
    tick = obj->field12;
    next_tick = tick + 1;
    obj->field10 = (u16) (obj->field10 + 1);
    obj->field12 = (u16) next_tick;
    shifted = next_tick << 0x10;
    variant = shifted >> 0x10;
    variant %= 7;
    variant_index = variant + 1;
    func_800478B8(gfx);
    gfx->field1A = (u16) (gfx->field1A + 0x300);
    phase = obj->state;
    if (phase == 1) {
        goto state1;
    }
    if (phase < 2) {
        if (phase == 0) {
            goto state0;
        }
        goto done;
    }
    if (phase == 2) {
        goto state2;
    }
    if (phase != 3) {
        goto done;
    }
    goto state3;

state0:
    vec_x10 = motion->x10;
    vec_x14 = motion->x14;
    motion->x0 = (s32) (motion->x0 + motion->xC);
    motion->x4 = (s32) (motion->x4 + vec_x10);
    motion->x8 = (s32) (motion->x8 + vec_x14);
    elapsed = (s16) obj->field10;
    limit = obj->field14;
    if (elapsed >= limit) {
        phase_value = (u16) obj->state;
        obj->field10 = 0U;
        obj->state = (s16) (phase_value + 1);
    }
    goto done;

state1:
    variant_s16 = (s16) variant_index;
    red = variant_s16;
    gfx->field12 = 0;
    gfx->flags = (u16) (gfx->flags & 0xFEFF);
    if (variant_s16 < 0) {
        red = variant_s16 + 3;
    }
    half_variant = variant_s16 / 2;
    red >>= 2;
    red <<= 7;
    fade_offset = ((s16) obj->field10 * 8) - 0x80;

    red -= fade_offset;
    gfx->fieldC = (s8) red;
    gfx->fieldD = (s8) (((s32) (((s16) half_variant - (((s32) ((s16) half_variant + ((u32) (half_variant << 0x10) >> 0x1F)) >> 1) * 2)) << 0x10) >> 9) - (s16) (((s16) obj->field10 * 8) - 0x80));
    gfx->fieldE = (s8) (((s32) ((variant_s16 - (half_variant * 2)) << 0x10) >> 9) - (s16) (((s16) obj->field10 * 8) - 0x80));
    elapsed_now = obj->field10;

    fade = (0x19 - elapsed_now) << 8;
    gfx->field1E = fade;
    gfx->field1C = fade;
    if ((s16) obj->field10 >= 0x10) {
        func_80024FD4((void *)obj, (void *)motion);
        phase_value = (u16) obj->state;
        obj->field10 = 0U;
        obj->state = (s16) (phase_value + 1);
    }
    goto done;

state2:
    variant_s16 = (s16) variant_index;
    red_state2 = variant_s16;
    if (variant_s16 < 0) {
        red_state2 = variant_s16 + 3;
    }
    half_variant_b = variant_s16 / 2;
    gfx->fieldC = (s8) ((red_state2 >> 2) << 7);
    blue_component = (s32) ((variant_s16 - (half_variant_b * 2)) << 0x10) >> 9;
    gfx->fieldD = (s8) ((s32) (((s16) half_variant_b - (((s32) ((s16) half_variant_b + ((u32) (half_variant_b << 0x10) >> 0x1F)) >> 1) * 2)) << 0x10) >> 9);
    gfx->fieldE = (s8) blue_component;
    if ((s16) obj->field10 >= 0x20) {
        phase_value = (u16) obj->state;
        obj->field10 = 0U;
        obj->state = (s16) (phase_value + 1);
    }
    goto done;

state3:
    if (gfx->flags & 0x6000) {
        *((u16 *)obj - 1) = (u16) (*((u16 *)obj - 1) | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }

done:
    ;
}
