#include "common.h"
extern int abs(int);

typedef struct Motion {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} Motion;

typedef struct Position16 {
    u16 pad0;
    s16 x;
    u16 pad4;
    s16 y;
    u16 pad8;
    s16 z;
} Position16;

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
extern void *D_80024008[];
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
extern void func_800240CC(void *, void *, s16);
extern void func_8002441C(void *, void *);
extern void func_800245CC(void *, void *);
extern void *func_800D24A8(u8, s16, s16, s16);
extern void func_80042640(void *, s32);
extern s32 func_800A6D30(void);

extern void func_80024888(void) __attribute__((noreturn));
extern void func_80024980(void) __attribute__((noreturn));
extern void func_80024AE4(void) __attribute__((noreturn));
extern void func_80024D54(void) __attribute__((noreturn));
extern void func_80024DE0(void) __attribute__((noreturn));

/* Update the effect's launch, movement, impact, and cleanup phases. */
void func_81898EBC(EffectState *effect_state, Motion *effect_motion, ColorPart *color_part)
{
    EffectState *state = effect_state;
    Motion *motion = effect_motion;
    ColorPart *part;
    register void *owner ASM_REG("$17");
    void *owner_data;
    void *owner_node;
    void *source_pos;
    register u8 *origin;
    Scratch scratch;
    u8 *global_page;
    s32 state_id;
    s32 source_z;
    s32 adjusted_z;
    s32 axis;
    u8 *delta_ptr;

    state->timer++;
    state_id = state->state;
    owner = state->owner;

    part = color_part;
    switch (state_id) {
    case 0:

        origin = D_80082E80_early;
        ASM_SCHED_BARRIER();

        {
            register u32 lookup_addr ASM_REG("$2") =
                (u32)PTR_AT((u8 *)owner - 0x20, 0xC);
            register s32 start_x ASM_REG("$4") = U8_AT(lookup_addr, 0x24);
            register s32 start_y ASM_REG("$5") = U8_AT(lookup_addr, 0x25);
            u32 origin_x;
            register u32 x_table ASM_REG("$7");
            u32 x_offset;
            u32 y_offset;

            x_table = (u32)D_8006CCD8_early;
            lookup_addr = (u32)D_800814A8_early[0];
            y_offset = U16_AT(lookup_addr, 0x2A);
            origin_x = origin[0x24];
            y_offset = (y_offset >> 8) & 0xE;
            x_offset = y_offset + x_table;
            lookup_addr = (u32)D_8006CCE8_early;
            y_offset += lookup_addr;
            x_offset = U16_AT(x_offset, 0);
            y_offset = U16_AT(y_offset, 0);

            U16_AT(owner, 0x2A) = func_800A0818(
                start_x, start_y, origin_x + x_offset, origin[0x25] + y_offset, &result);
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

        source_pos = PTR_AT(owner_data, 8);
        U16_AT(motion, 2) = U16_AT(source_pos, 2);
        U16_AT(motion, 6) = U16_AT(source_pos, 6);
        source_z = U16_AT(source_pos, 0xA);
        U16_AT(motion, 0xA) = source_z;
        if (!(U16_AT(PTR_AT(owner_data, 0xC), 0x14) & 0x8000)) {
            U16_AT(motion, 2) += probe[0];
            U16_AT(motion, 6) += probe[1];
            ASM_MEM_BARRIER();
            adjusted_z = U16_AT(motion, 0xA);
            source_z = U16_AT(probe, 4);
            adjusted_z += source_z;
            ASM_TAILSLOT_PIN(adjusted_z);
            func_80024888();
        }

        ASM_KEEP(source_z);
        adjusted_z = source_z - 0x40;
        U16_AT(motion, 0xA) = adjusted_z;
        if (!(U16_AT(state->image, 0) & 0x80)) {
            goto done;
        }

        if ((U16_AT(owner_data, 0x1E) | 0x2000) != 0) {
            u8 *position_base = D_80082E80;
            void *direction_node = D_800814A8[0];
            register u32 direction_x ASM_REG("$2");
            register u32 direction_y ASM_REG("$2");

            direction_x = U16_AT(direction_node, 0x2A);
            state->x = position_base[0x24] +
                ((s16 *)((u8 *)D_8006CCD8 +
                ((direction_x >> 8) & 0xE)))[0];
            direction_y = U16_AT(direction_node, 0x2A);
            state->y = position_base[0x25] +
                ((s16 *)((u8 *)D_8006CCE8 +
                ((direction_y >> 8) & 0xE)))[0];
            func_80024980();
        }

        {
            s16 *target_pos = scratch.work;

            ASM_SCHED_BARRIER();
            state->x = D_80082E80[0x24] + D_8006CCD8[state->direction];
            state->y = D_80082E80[0x25] + D_8006CCE8[state->direction];
            ASM_SCHED_BARRIER();
            {
                void *height_node;
                s32 tile_coord;

                tile_coord = state->x;
                global_page = (u8 *)0x80080000;
                S16_AT(target_pos, 2) = tile_coord * 64 + 0x20;
                tile_coord = state->y;
                height_node = PTR_AT(global_page, 0x14A8);
                S16_AT(target_pos, 6) = tile_coord * 64 + 0x20;
                S16_AT(target_pos, 0xA) = ((s16 *)height_node)[0x44] - 0x20;
            }
            S16_AT(target_pos, 0xA) = func_800BCAD0(target_pos);
            state->z = S16_AT(target_pos, 0xA);
            func_8009A350(state->x - 1, state->y, 0, &map_flags);
            if (map_flags & 0x3300) {
                s32 fallback_value;

                fallback_value =
                    ((s16 *)PTR_AT(global_page, 0x14A8))[0x44] << 16;
                S32_AT((u8 *)target_pos, 8) = fallback_value;
                fallback_value = 6;
                ASM_TAILSLOT_PIN(fallback_value);
                func_80024AE4();
            }
            {
                register s32 target_z ASM_REG("$6") = S16_AT(target_pos, 0xA);
                register s32 in_range ASM_REG("$2");

                in_range = target_z < 0x201;
                if (!in_range) {
                    s32 fallback_value;

                    fallback_value =
                        ((s16 *)PTR_AT(global_page, 0x14A8))[0x44] << 16;
                    S32_AT((u8 *)target_pos, 8) = fallback_value;
                    fallback_value = 6;
                    ASM_TAILSLOT_PIN(fallback_value);
                    func_80024AE4();
                }
            }
            if ((func_800A45D8(U16_AT(target_pos, 2), U16_AT(target_pos, 6)) << 16) != 0) {
                s32 fallback_value;

                fallback_value =
                    ((s16 *)PTR_AT(global_page, 0x14A8))[0x44] << 16;
                S32_AT((u8 *)target_pos, 8) = fallback_value;
                fallback_value = 6;
                ASM_TAILSLOT_PIN(fallback_value);
                func_80024AE4();
            }
            if ((func_800A5690() << 16) == 0) {
                s32 fallback_value;

                fallback_value =
                    ((s16 *)PTR_AT(global_page, 0x14A8))[0x44] << 16;
                S32_AT((u8 *)target_pos, 8) = fallback_value;
                fallback_value = 6;
                ASM_TAILSLOT_PIN(fallback_value);
                func_80024AE4();
            }
            if ((U16_AT(owner_data, 0x1E) | 0x2000) != 0) {
                state->status = 1;
            } else {
                state->status = 2;
            }
            state->state++;
            ASM_SCHED_BARRIER();

            {
                s32 delta_x;
                s32 raised_z;
                s32 delta_y;
                s32 delta_z;

                axis = 1;
                delta_ptr = (u8 *)&scratch + 2;
                delta_x = S16_AT(target_pos, 2) - S16_AT(motion, 2);
                delta_x = abs(delta_x);
                probe[0] = delta_x;
                delta_y = S16_AT(target_pos, 6) - S16_AT(motion, 6);
                delta_y = abs(delta_y);
                probe[1] = delta_y;
                raised_z = S16_AT(motion, 0xA) + 160;
                delta_z = S16_AT(target_pos, 0xA) - raised_z;
                delta_z = abs(delta_z);
                probe[2] = delta_z;
                state->duration = delta_x;
            }
            do {
                s32 axis_delta;

                axis_delta = S16_AT(delta_ptr, 24);
                if (state->duration < axis_delta) {
                    state->duration = U16_AT(delta_ptr, 24);
                }
                axis++;
                delta_ptr += 2;
            } while (axis < 3);
            state->duration =
                (state->duration >> 4) + (state->duration >> 5);
            if (state->duration == 0) {
                state->duration = 1;
            }
            S32_AT(motion, 0xC) =
                (S32_AT(target_pos, 0) - S32_AT(motion, 0)) / state->duration;
            {
                s32 current_y;
                s32 y_step;
                s32 move_frames;

                current_y = S32_AT(motion, 4);
                y_step = S32_AT(target_pos, 4) - current_y;
                move_frames = state->duration;
                y_step /= move_frames;
                S32_AT(motion, 0x10) = y_step;
            }
            {
                s32 raised_z;
                s32 z_offset;

                z_offset = 0x00A00000;
                raised_z = S32_AT(motion, 8) + z_offset;
                S32_AT(motion, 0x14) =
                    (S32_AT(target_pos, 8) - raised_z) / state->duration;
            }
            func_800240CC(state, motion, state->duration);
            func_800240CC(state, motion, state->duration);
            func_800240CC(state, motion, state->duration);
            state->timer = 0;
            func_80024DE0();
        }

    case 2:
        S32_AT(motion, 0) += S32_AT(motion, 0xC);
        S32_AT(motion, 4) += S32_AT(motion, 0x10);
        S32_AT(motion, 8) += S32_AT(motion, 0x14);
        if (state->timer < state->duration) {
            goto done;
        }
        func_8002441C(state, motion);
        func_800A56E0(0x300);
        func_80024D54();

    case 3:
        if (state->timer < 0x10) {
            goto done;
        }
        func_800245CC(state, motion);
        func_80024D54();

    case 4:
        if (state->timer < 0x11) {
            goto done;
        }
        if (state->status != 0) {
            void *effect = func_800D24A8(state->status, state->x, state->y,
                                        state->z);
            register s32 intensity ASM_REG("$4");
            s32 clamped_intensity;
            s32 effect_id;
            s32 random_bits;

            func_80042640(effect, 52);
            random_bits = func_800A6D30();
            effect_id = U8_AT(state, 9);
            intensity = effect_id >> 1;
            intensity += effect_id << 1;
            intensity += random_bits & 3;
            intensity += 16;
            clamped_intensity = intensity;
            ASM_KEEP(intensity);
            if (intensity >= 256) {
                clamped_intensity = 255;
            }
            U8_AT(effect, 0x28) = clamped_intensity;
            U8_AT(effect, 0x29) = clamped_intensity;
        }
        state->timer = 0;
        state->state++;
        func_80024DE0();

    case 5:
        if (state->field_14 != 0) {
            goto done;
        }
        D_8008346C = 0;
        U16_AT(state, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        func_80024DE0();

    case 6:
        S32_AT(motion, 0) += S32_AT(motion, 0xC);
        S32_AT(motion, 4) += S32_AT(motion, 0x10);
        if (state->timer >= state->duration) {
            state->state = 5;
            state->timer = 0;
        }

    }

done:
    state->field_14 = 0;
}
