#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
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

extern void *D_800814A8_early[4] __asm__("D_800814A8");
extern u8 D_80082E80_early[] __asm__("D_80082E80");

extern s16 func_800A0818(u8, u8, s16, s16, s16 *);
extern s32 func_8003DE58(void *, void *, void *, s32);
extern s16 func_800BCAD0(void *);
extern s32 func_8009A350(s16 x, s16 y, s16 offset_index, u16 *flags);
extern s32 func_800A45D8(s32, s32, s32);
extern s32 func_800A5690(void);
extern void func_800A56E0(s32);
extern void func_800240CC(void *, void *, s16);
extern void func_8002441C(void *, void *);
extern void func_800245CC(void *, void *);
extern void *func_800D24A8(u8, s16, s16, s16);
extern void func_80042640(void *, s32);
extern s32 func_800A6D30(void);

/* Update the effect's launch, movement, impact, and cleanup phases. */
void func_800246BC(EffectState *state, Motion *motion, ColorPart *part)
{
    void *owner;
    void *owner_data;
    void *owner_node;
    void *source_pos;
    register u8 *origin;
    Scratch scratch;
    u8 *global_page;
    s32 state_id;
    u32 source_z;
    s32 axis;
    u8 *delta_ptr;
    s16 *target_pos;
    s32 target_z;

    state->timer++;
    state_id = state->state;
    owner = state->owner;

    switch (state_id) {
    case 0:

        origin = D_80082E80_early;
        {
            void *node = PTR_AT((u8 *)owner - 0x20, 0xC);
            s32 dir = (U16_AT(D_800814A8_early[0], 0x2A) >> 9) & 7;
            U16_AT(owner, 0x2A) = func_800A0818(U8_AT(node, 0x24), U8_AT(node, 0x25),
                origin[0x24] + dirStepX[dir], origin[0x25] + dirStepY[dir], &result);
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
                break;
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
            U16_AT(motion, 0xA) += probe[2];
        } else {
            U16_AT(motion, 0xA) = source_z - 0x40;
        }
        if (!(U16_AT(state->image, 0) & 0x80)) {
            break;
        }

        target_pos = scratch.work;
        if ((U16_AT(owner_data, 0x1E) | 0x2000) != 0) {
            void *direction_node = D_800814A8;

            state->x = D_80082E80.tileX + dirStepX[(U16_AT(direction_node, 0x2A) >> 9) & 7];
            state->y = D_80082E80.tileY + dirStepY[(U16_AT(direction_node, 0x2A) >> 9) & 7];
        } else {
            state->x = D_80082E80.tileX + dirStepX[state->direction];
            state->y = D_80082E80.tileY + dirStepY[state->direction];
        }

        {
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
                state->state = 6;
            } else {
                target_z = S16_AT(target_pos, 0xA);

                if (target_z >= 0x201) {
                    s32 fallback_value;

                    fallback_value =
                        ((s16 *)PTR_AT(global_page, 0x14A8))[0x44] << 16;
                    S32_AT((u8 *)target_pos, 8) = fallback_value;
                    state->state = 6;
                } else if ((func_800A45D8(U16_AT(target_pos, 2), U16_AT(target_pos, 6), target_z) << 16) != 0) {
                    s32 fallback_value;

                    fallback_value =
                        ((s16 *)PTR_AT(global_page, 0x14A8))[0x44] << 16;
                    S32_AT((u8 *)target_pos, 8) = fallback_value;
                    state->state = 6;
                } else if ((func_800A5690() << 16) == 0) {
                    s32 fallback_value;

                    fallback_value =
                        ((s16 *)PTR_AT(global_page, 0x14A8))[0x44] << 16;
                    S32_AT((u8 *)target_pos, 8) = fallback_value;
                    state->state = 6;
                } else {
                    if ((U16_AT(owner_data, 0x1E) | 0x2000) != 0) {
                        state->status = 1;
                    } else {
                        state->status = 2;
                    }
                    state->state++;
                }
            }

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
            break;
        }

    case 2:
        S32_AT(motion, 0) += S32_AT(motion, 0xC);
        S32_AT(motion, 4) += S32_AT(motion, 0x10);
        S32_AT(motion, 8) += S32_AT(motion, 0x14);
        if (state->timer < state->duration) {
            break;
        }
        func_8002441C(state, motion);
        func_800A56E0(0x300);
        state->timer = 0;
        state->state++;
        break;

    case 3:
        if (state->timer < 0x10) {
            break;
        }
        func_800245CC(state, motion);
        state->timer = 0;
        state->state++;
        break;

    case 4:
        if (state->timer < 0x11) {
            break;
        }
        if (state->status != 0) {
            void *effect = func_800D24A8(state->status, state->x, state->y,
                                         state->z);
            s32 intensity;
            s16 clamped_intensity;
            u32 effect_id;
            s32 random_bits;

            func_80042640(effect, 52);
            random_bits = func_800A6D30();
            effect_id = U8_AT(state, 9);
            intensity = effect_id >> 1;
            intensity += effect_id << 1;
            intensity += random_bits & 3;
            intensity += 16;
            clamped_intensity = intensity;
            if (intensity >= 256) {
                clamped_intensity = 255;
            }
            U8_AT(effect, 0x28) = clamped_intensity;
            U8_AT(effect, 0x29) = clamped_intensity;
        }
        state->timer = 0;
        state->state++;
        break;

    case 5:
        if (state->field_14 != 0) {
            break;
        }
        dungeonStatus.unk_0C = 0;
        U16_AT(state, -2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
        break;

    case 6:
        S32_AT(motion, 0) += S32_AT(motion, 0xC);
        S32_AT(motion, 4) += S32_AT(motion, 0x10);
        if (state->timer >= state->duration) {
            state->state = 5;
            state->timer = 0;
        }

    }

    state->field_14 = 0;
}
