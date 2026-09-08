#include "common.h"

typedef struct Motion {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} Motion;

typedef struct EffectState {
    void *owner;
    void *image;
    u8 unk8;
    u8 id;
    s16 state;
    s16 unkC;
    s16 direction;
    s16 timer;
    s16 duration;
    s16 field_14;
    s16 x;
    s16 y;
    s16 z;
    u8 status;
    u8 pad1D[0x7B];
} EffectState;

typedef struct ColorPart {
    u8 pad[0xC];
    u32 color;
} ColorPart;

typedef struct Scratch {
    s16 work[8];
    u8 gap[8];
    s16 probe[3];
    u8 result_gap[2];
    s16 result;
    u16 map_flags;
} Scratch;

#define U8_AT(p, n) (*(u8 *)((u8 *)(p) + (n)))
#define S8_AT(p, n) (*(s8 *)((u8 *)(p) + (n)))
#define U16_AT(p, n) (*(u16 *)((u8 *)(p) + (n)))
#define S16_AT(p, n) (*(s16 *)((u8 *)(p) + (n)))
#define S32_AT(p, n) (*(s32 *)((u8 *)(p) + (n)))
#define PTR_AT(p, n) (*(void **)((u8 *)(p) + (n)))
#define probe scratch.probe
#define result scratch.result
#define map_flags scratch.map_flags

extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern void *D_800814A8[4];
extern u32 D_800814A0[4];
extern s32 D_8008346C;
extern u8 D_80082E80[];
extern s16 D_8006CCD8_early[] __asm__("D_8006CCD8");
extern s16 D_8006CCE8_early[] __asm__("D_8006CCE8");
extern void *D_800814A8_early[4] __asm__("D_800814A8");
extern u8 D_80082E80_early[] __asm__("D_80082E80");

extern s16 func_800A0818(u8, u8, s16, s16, s16 *);
extern s32 func_8003DE58(void *, void *, void *, s32);
extern s16 func_800BCAD0(void *);
extern s32 func_8009A350(s16, s16, s32, u16 *);
extern s32 func_800A45D8(u16, u16);
extern s32 func_800A5690(void);
extern void func_800A56E0(s32);
extern void func_800240F8(void *, void *, s16);
extern void func_800242F0(void *, void *, s32);
extern void func_80024A44(void *, void *, s32);
extern void func_800419EC(s32, s32);
extern void *func_800D1C70(u8, s16, s16, s16);
extern void func_80042640(void *, s32);
extern s32 func_800A6D30(void);

/* Updates the effect's launch, travel, impact, and cleanup states. */
void func_80024C74(EffectState *effect_state, Motion *effect_motion, ColorPart *color_part)
{
    EffectState *state;
    Motion *motion;
    ColorPart *part;
    void *owner;
    void *owner_data;
    void *owner_node;
    void *owner_motion;
    Scratch scratch;
    register u8 *origin;
    register s32 target_z ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 height_valid ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 state_id;
    s32 source_z;
    s32 adjusted_z;
    s16 *target_pos;
    void *spawned_effect;

    state = effect_state;
    motion = effect_motion;
    state->timer++;
    state_id = state->state;
    owner = state->owner;
    part = color_part;
    switch (state_id) {
    case 0:
        origin = D_80082E80_early;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail immediate-load split depends on it */
        {
            register u32 lookup_addr ASM_REG("$2") =
                (u32)PTR_AT((u8 *)owner - 0x20, 0xC);
            register s32 start_x ASM_REG("$4") = U8_AT(lookup_addr, 0x24);   /* MATCH pin: keeps a constant in a register as retail does */
            register s32 start_y ASM_REG("$5") = U8_AT(lookup_addr, 0x25);   /* MATCH pin: keeps a constant in a register as retail does */
            u32 origin_x;
            register u32 x_offsets ASM_REG("$7");   /* MATCH pin: keeps a constant in a register as retail does */
            u32 step_x;
            u32 step_y;

            x_offsets = (u32)D_8006CCD8_early;
            lookup_addr = (u32)D_800814A8_early[0];
            step_y = U16_AT(lookup_addr, 0x2A);
            origin_x = origin[0x24];
            step_y = (step_y >> 8) & 0xE;
            step_x = step_y + x_offsets;
            lookup_addr = (u32)D_8006CCE8_early;
            step_y += lookup_addr;
            step_x = U16_AT(step_x, 0);
            step_y = U16_AT(step_y, 0);

            U16_AT(owner, 0x2A) = func_800A0818(
                start_x, start_y, origin_x + step_x,
                origin[0x25] + step_y, &result);
        }
        state->timer = 0;
        state->state++;
        state->direction = (U16_AT(owner, 0x2A) >> 9) & 7;
        state->status = 0;
        part->color = 0x00808080;

    case 1:
        owner_data = (u8 *)owner - 0x20;
        owner_node = PTR_AT(owner_data, 0xC);
        if (func_8003DE58(PTR_AT(owner_node, 8), owner_node, probe, 0) == 0) {
            if (!(U16_AT(PTR_AT(owner_data, 0xC), 0x14) & 0x8000)) {
                goto done;
            }
        }
        owner_motion = PTR_AT(owner_data, 8);
        U16_AT(motion, 2) = U16_AT(owner_motion, 2);
        U16_AT(motion, 6) = U16_AT(owner_motion, 6);
        source_z = U16_AT(owner_motion, 0xA);
        U16_AT(motion, 0xA) = source_z;
        if (!(U16_AT(PTR_AT(owner_data, 0xC), 0x14) & 0x8000)) {
            U16_AT(motion, 2) += probe[0];
            U16_AT(motion, 6) += probe[1];
            ASM_MEM_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
            adjusted_z = U16_AT(motion, 0xA);
            source_z = U16_AT(probe, 4);
            adjusted_z += source_z;
        } else {
            adjusted_z = source_z - 0x40;
        }
        U16_AT(motion, 0xA) = adjusted_z;
        if (!(U16_AT(state->image, 0) & 0x80)) {
            goto done;
        }
        target_pos = scratch.work;
        /* This expression is intentionally kept in its retail form. */
        if ((U16_AT(owner_data, 0x1E) | 0x2000) != 0) {
            u8 *position_base = D_80082E80;
            void *direction_node = D_800814A8[0];
            register u32 direction_x ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
            register u32 direction_y ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

            direction_x = U16_AT(direction_node, 0x2A);
            state->x = position_base[0x24] +
                ((s16 *)((u8 *)D_8006CCD8 + ((direction_x >> 8) & 0xE)))[0];
            direction_y = U16_AT(direction_node, 0x2A);
            state->y = position_base[0x25] +
                ((s16 *)((u8 *)D_8006CCE8 + ((direction_y >> 8) & 0xE)))[0];
        } else {
            state->x = D_80082E80[0x24] + D_8006CCD8[state->direction];
            state->y = D_80082E80[0x25] + D_8006CCE8[state->direction];
        }
        {
            void *height_node;
            s32 tile_coord;

            tile_coord = state->x;
            S16_AT(target_pos, 2) = tile_coord * 64 + 0x20;
            tile_coord = state->y;
            height_node = D_800814A8[0];
            S16_AT(target_pos, 6) = tile_coord * 64 + 0x20;
            S16_AT(target_pos, 0xA) = ((s16 *)height_node)[0x44] - 0x20;
        }
        S16_AT(target_pos, 0xA) = func_800BCAD0(target_pos);
        state->z = S16_AT(target_pos, 0xA);
        func_8009A350(state->x - 1, state->y, 0, &map_flags);
        if ((map_flags & 0x3300) != 0 ||
            (target_z = S16_AT(target_pos, 0xA), height_valid = target_z < 0x201, !height_valid) ||
            (func_800A45D8(U16_AT(target_pos, 2), U16_AT(target_pos, 6)) << 16) != 0 ||
            (func_800A5690() << 16) == 0) {
            state->state = 7;
        } else {
            if ((U16_AT(owner_data, 0x1E) | 0x2000) == 0) {
                state->status = 2;
            } else {
                state->status = 1;
            }
            state->state++;
        }
        {
            s32 delta_x;
            s32 delta_y;
            s32 delta_z;

            delta_x = S16_AT(target_pos, 2) - S16_AT(motion, 2);
            if (delta_x < 0) {
                delta_x = -delta_x;
            }
            probe[0] = delta_x;
            delta_y = S16_AT(target_pos, 6) - S16_AT(motion, 6);
            if (delta_y < 0) {
                delta_y = -delta_y;
            }
            probe[1] = delta_y;
            {
                register s32 motion_z ASM_REG("$3");   /* MATCH pin: retail delay-slot fill depends on it */

                delta_z = S16_AT(target_pos, 0xA);
                motion_z = S16_AT(motion, 0xA);
                delta_z -= motion_z;
            }
            if (delta_z < 0) {
                delta_z = -delta_z;
            }
            probe[2] = delta_z;
        }
        state->duration = 12;
        S32_AT(motion, 0xC) = (S32_AT(target_pos, 0) - S32_AT(motion, 0)) / state->duration;
        S32_AT(motion, 0x10) = (S32_AT(target_pos, 4) - S32_AT(motion, 4)) / state->duration;
        S32_AT(motion, 0x14) = (S32_AT(target_pos, 8) - S32_AT(motion, 8)) / state->duration;
        func_800240F8(state, motion, state->duration);
        func_800240F8(state, motion, state->duration);
        func_800240F8(state, motion, state->duration);
        state->timer = 0;
        goto done;

    case 2:
        S32_AT(motion, 0) += S32_AT(motion, 0xC);
        S32_AT(motion, 4) += S32_AT(motion, 0x10);
        S32_AT(motion, 8) += S32_AT(motion, 0x14);
        if (state->timer < state->duration) {
            goto done;
        }
        func_800242F0(state, motion, 12);
        goto advance;

    case 3:
        if (state->timer < 8) {
            goto done;
        }
        func_800A56E0(0x300);
        goto advance;

    case 4:
        if (state->timer < 5) {
            goto done;
        }
        func_80024A44(state, motion, 16);
        func_800419EC(8, 36);
        goto advance;

    case 5:
        if (state->timer < 0x11) {
            goto done;
        }
        if (state->status != 0) {
            s32 strength;
            register s32 clamped_strength ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
            u32 effect_id;
            s32 variation;

            spawned_effect = func_800D1C70(state->status, state->x, state->y, state->z);
            func_80042640(spawned_effect, 51);
            variation = func_800A6D30();
            effect_id = U8_AT(state, 9);
            strength = effect_id >> 1;
            strength += effect_id << 1;
            strength += variation & 3;
            strength += 16;
            clamped_strength = strength;
            ASM_KEEP(strength);   /* MATCH pin: load-bearing for the whole function shape */
            if (strength >= 256) {
                clamped_strength = 255;
            }
            U8_AT(spawned_effect, 0x28) = clamped_strength;
            U8_AT(spawned_effect, 0x29) = clamped_strength;
        }
    advance:
        state->timer = 0;
        state->state++;
        goto done;

    case 6:
        if (state->field_14 != 0) {
            goto done;
        }
        D_8008346C = 0;
        U16_AT(state, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        goto done;

    case 7:
        S32_AT(motion, 0) += S32_AT(motion, 0xC);
        S32_AT(motion, 4) += S32_AT(motion, 0x10);
        if (state->timer >= state->duration) {
            state->state = 6;
            state->timer = 0;
        }
    }

done:
    state->field_14 = 0;
}
