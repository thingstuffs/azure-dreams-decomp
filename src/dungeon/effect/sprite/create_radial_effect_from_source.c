/* Targeted moving effects, radial color animation, shaded lines, and fragment creation. */
#include "dungeon/effect/sprite/create_radial_effect_from_source.h"
#include "dungeon/effect/sprite/create_radial_effect_from_source.h"
#include "modules/dungeon_native_abi.h"
#include "shared/entity_height_offsets.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
extern int abs(int);

typedef struct S_func_81886800_1 {
    void *unk_00;
    void *unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    union {
        s16 s16;
        u16 u16;
    } unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    union {
        s16 s16;
        u16 u16;
    } unk_10;
    u8 unk_12;
    u8 pad_13[0x1];
    u16 unk_14;
    union {
        s16 s16;
        u16 u16;
    } unk_16;
    union {
        s16 s16;
        u16 u16;
    } unk_18;
    u8 pad_1A[0x2];
    union {
        u32 u32;
        struct {
            u8 pad_1C[0x2];
            union {
                s16 s16;
                struct {
                    union {
                        s8 s8;
                        u8 u8;
                    } unk_1E;
                    union {
                        s8 s8;
                        u8 u8;
                    } unk_1F;
                } parts;
            } unk_1E;
        } parts;
    } unk_1C;
    union {
        s16 s16;
        struct {
            u8 unk_20;
            u8 unk_21;
        } parts;
    } unk_20;
    u8 pad_22[0x6];
    void *unk_28;
    union {
        s32 s32;
        struct {
            u8 pad_2C[0x2];
            union {
                s16 s16;
                u16 u16;
            } unk_2E;
        } parts;
    } unk_2C;
    u8 pad_30[0x28];
    s16 unk_58;
} S_func_81886800_1;

typedef struct S_func_81886800_2 {
    u8 pad_00[0x8];
    void *unk_08;
    void *unk_0C;
} S_func_81886800_2;

typedef struct S_func_81886800_3 {
    u8 pad_00[0x8];
    void *unk_08;
    union {
        u32 u32;
        struct {
            u8 unk_0C;
            u8 unk_0D;
            u8 unk_0E;
        } parts;
    } unk_0C;
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_func_81886800_3;

typedef struct S_func_81886800_4 {
    u16 unk_00;
} S_func_81886800_4;

typedef struct S_func_81886800_5 {
    u16 unk_00;
} S_func_81886800_5;

typedef struct S_func_81886800_6 {
    u16 unk_00;
} S_func_81886800_6;

typedef struct S_func_81886800_7 {
    s32 unk_00;
} S_func_81886800_7;

typedef struct S_func_81886800_8 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x16];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void *unk_60;
    u8 pad_64[0xC];
    union {
        u32 u32;
        struct {
            u8 pad_70[0x2];
            union {
                s8 s8;
                u8 u8;
            } unk_72;
            union {
                s8 s8;
                u8 u8;
            } unk_73;
        } parts;
    } unk_70;
    u8 pad_74[0x14];
    union {
        s16 s16;
        u16 u16;
    } unk_88;
} S_func_81886800_8;

typedef struct S_func_81886800_9 {
    s32 unk_00;
} S_func_81886800_9;

typedef struct S_func_81886800_10 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    union {
        void * ptr;
        struct {
            u8 pad_08[0x2];
            u16 unk_0A;
        } parts;
    } unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_func_81886800_10;

typedef struct S_func_81886800_11 {
    union {
        s32 s32;
        struct {
            u8 pad_00[0x2];
            union {
                s16 s16;
                u16 u16;
            } unk_02;
        } parts;
    } unk_00;
    union {
        s32 s32;
        struct {
            u8 pad_04[0x2];
            union {
                s16 s16;
                u16 u16;
            } unk_06;
        } parts;
    } unk_04;
    union {
        s32 s32;
        struct {
            u8 pad_08[0x2];
            u16 unk_0A;
        } parts;
    } unk_08;
    union {
        s32 s32;
        struct {
            u8 pad_0C[0x2];
            union {
                s16 s16;
                u16 u16;
            } unk_0E;
        } parts;
    } unk_0C;
    union {
        s32 s32;
        struct {
            u8 pad_10[0x2];
            union {
                s16 s16;
                u16 u16;
            } unk_12;
        } parts;
    } unk_10;
} S_func_81886800_11;

typedef struct S_func_81886800_12 {
    u16 unk_00;
} S_func_81886800_12;

typedef struct S_func_81886800_13 {
    void *unk_00;
} S_func_81886800_13;

typedef struct S_func_81886800_14 {
    s16 unk_00;
} S_func_81886800_14;

typedef struct S_func_81886800_15 {
    u16 unk_00;
} S_func_81886800_15;

typedef struct S_func_81886800_16 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_func_81886800_16;

typedef struct S_func_81886800_17 {
    union {
        s16 s16;
        u16 u16;
    } unk_00;
} S_func_81886800_17;

typedef struct S_func_81886800_18 {
    s32 unk_00;
} S_func_81886800_18;

typedef struct S_func_81886800_19 {
    s32 unk_00;
} S_func_81886800_19;


extern void draw_textured_ellipse(void *, void *, s32, s32);
extern s32 get_sprite_attachment_vector(void *, void *, void *, s32);
extern s32 func_800644B8(s32);
extern s32 set_item_w0(s32, s32, s32, s32);
extern s32 check_left_tile_and_center_height(s32, s32, s32);
extern void func_80065F90(s32, s32);
extern void check_the_target_using_scaled_low_byte_conditionally_applies_global_800_e_1_d_01(s32, s32, void *);

extern u8 D_8002632C[];
extern u8 D_80026344[];
extern u8 D_80026878[];

void func_80024064(S_func_81886800_1 *effect, S_func_81886800_11 *motion, S_func_81886800_3 *sprite);

/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol add_flag_adjusted_target_value).  The state table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */
void (*const dungeon_18a6800_entry)(S_func_81886800_1 *, S_func_81886800_11 *, S_func_81886800_3 *) = func_80024064;

/* Initialize and update a moving effect through targeting, collision, and fading states. */
void func_80024064(S_func_81886800_1 *effect, S_func_81886800_11 *motion, S_func_81886800_3 *sprite)
{
    S_func_81886800_8 *owner;
    S_func_81886800_2 *owner_base;
    S_func_81886800_11 *owner_motion;
    S_func_81886800_8 *target_object;
    s32 state;
    u16 owner_flags;
    s16 surface_pos[3];
    s32 texture_rect[2];

    owner = effect->unk_00;
    state = effect->unk_0A.s16;
    owner_base = (S_func_81886800_2 *)((u8 *)owner - 0x20);
    owner_motion = owner_base->unk_08;
    switch (state) {
    case 0:
    texture_rect[0] = 0x01000340;
    texture_rect[1] = 0x00200020;
    draw_textured_ellipse(D_8002632C, texture_rect, 1, 0);

    sprite->unk_0C.u32 = 0x00808080;
    sprite->unk_1E = 0x555;
    sprite->unk_1C = 0x555;
    sprite->unk_08 = D_80026344;
    ((S_func_81886800_4 *)(D_80026324))->unk_00 = 0;
    ((S_func_81886800_5 *)(D_80026328))->unk_00 = 0;
    ((S_func_81886800_6 *)(&D_8002632A))->unk_00 = 0;
    ((S_func_81886800_7 *)(D_80026470))->unk_00 = 0;
    owner_flags = owner->unk_2A;
    ((S_func_81886800_9 *)(D_80026474))->unk_00 = 0;
    effect->unk_16.u16 = (owner_flags >> 9) & 7;
    effect->unk_0A.u16++;

    case 1:
    if (get_sprite_attachment_vector(
            ((S_func_81886800_10 *)(owner_base->unk_0C))->unk_08.ptr,
            owner_base->unk_0C, surface_pos, 0) == 0) {
        if ((((S_func_81886800_10 *)(owner_base->unk_0C))->unk_14 & 0x8000) == 0) {
            break;
        }
    }

    motion->unk_00.parts.unk_02.u16 = owner_motion->unk_00.parts.unk_02.u16;
    motion->unk_04.parts.unk_06.u16 = owner_motion->unk_04.parts.unk_06.u16;
    if (((S_func_81886800_10 *)(owner_base->unk_0C))->unk_14 & 0x8000) {
        motion->unk_08.parts.unk_0A = owner_motion->unk_08.parts.unk_0A - 64;
        effect->unk_2C.parts.unk_2E.u16 = motion->unk_08.parts.unk_0A;
    } else {
        motion->unk_08.parts.unk_0A = owner_motion->unk_08.parts.unk_0A + surface_pos[2];
        effect->unk_2C.parts.unk_2E.u16 = motion->unk_08.parts.unk_0A;
    }

    {
        S_func_81886800_12 *effect_flags = effect->unk_04;
        if ((effect_flags->unk_00 & 0x80) == 0) {
            break;
        }
        if ((effect->unk_12 & 4) == 0) {
            register_node((u8 *)effect - 0x20, project_sprite_chain);
            sprite->unk_10 = 0x20;
            sprite->unk_0C.parts.unk_0E = 0x80;
            sprite->unk_0C.parts.unk_0D = 0x80;
            sprite->unk_0C.parts.unk_0C = 0x80;
            sprite->unk_14 |= 0xC;
            effect->unk_12 |= 4;
        }
    }

    if (owner->unk_60 != 0) {
        {
            S_func_81886800_10 *target_data;

            target_data =
                ((S_func_81886800_13 *)((u8 *)(owner->unk_60) - 0x18))->unk_00;
            effect->unk_0C = target_data->unk_02;
            effect->unk_0E = target_data->unk_06;
            {
                u8 target_kind;
                u8 *height_offsets;

                height_offsets = entity_height_offsets;
                target_kind = ((S_func_81886800_8 *)(owner->unk_60))->unk_13;
                effect->unk_10.u16 =
                    target_data->unk_08.parts.unk_0A - height_offsets[target_kind];
            }
            {
                s16 direction;
                u8 tile_coord;
                direction = effect->unk_16.s16;
                target_data = ((S_func_81886800_13 *)((u8 *)(owner) - 0x14))->unk_00;
                tile_coord = target_data->unk_24 +
                        ((u8 *)dir_step_x)[(s32)direction * 2];
                effect->unk_1C.parts.unk_1E.parts.unk_1E.u8 = tile_coord;
                effect->unk_20.parts.unk_20 = tile_coord;
            }
            {
                s16 direction;
                u8 tile_coord;
                direction = effect->unk_16.s16;
                tile_coord = target_data->unk_25 +
                        ((u8 *)dir_step_y)[(s32)direction * 2];
                effect->unk_1C.parts.unk_1E.parts.unk_1F.u8 = tile_coord;
                effect->unk_20.parts.unk_21 = tile_coord;
            }
            {
#ifdef __mips__
                s32 owner_tile;
#else
                s32 owner_tile;
                s32 state;
#endif
                s32 tile_distance;
                owner_tile = owner->unk_70.parts.unk_72.s8;
                state = target_data->unk_24;
                if (owner_tile == state) {
                    owner_tile = owner->unk_70.parts.unk_73.s8;
                    state = target_data->unk_25;
                    tile_distance = owner_tile - state;
                } else {
                    tile_distance = owner_tile - state;
                }
                tile_distance = abs(tile_distance);
                effect->unk_14 = tile_distance + 1;
            }
        }
    } else {
        effect->unk_14 = 8;
        effect->unk_0C = motion->unk_00.parts.unk_02.u16;
        effect->unk_0E = motion->unk_04.parts.unk_06.u16;
        effect->unk_10.u16 = owner->unk_88.u16 - 80;
    }
    {
        u8 *x_offsets = ((u8 *)dir_step_x);
        s16 direction = effect->unk_16.s16;
        motion->unk_0C.parts.unk_0E.u16 =
            ((S_func_81886800_14 *)(x_offsets + (s32)direction * 2))->unk_00 * 8;
        {
            u8 *y_offsets = ((u8 *)dir_step_y);
            s16 y_direction = effect->unk_16.s16;
            motion->unk_10.parts.unk_12.u16 =
                ((S_func_81886800_14 *)(y_offsets + (s32)y_direction * 2))->unk_00 * 8;
        }
    }
    effect->unk_0A.u16++;
    break;

    case 2:
    {
        s32 x_velocity;
        motion->unk_00.s32 += motion->unk_0C.s32;
        x_velocity = motion->unk_0C.s32 + (motion->unk_0C.s32 >> 4);
        motion->unk_0C.s32 = x_velocity;
        if ((x_velocity < 0 ? -x_velocity : x_velocity) > 0x200000) {
            x_velocity = x_velocity > 0 ? 0x200000 : -0x200000;
            motion->unk_0C.s32 = x_velocity;
        }
    }
    {
        s32 y_velocity;
        motion->unk_04.s32 += motion->unk_10.s32;
        y_velocity = motion->unk_10.s32 + (motion->unk_10.s32 >> 4);
        motion->unk_10.s32 = y_velocity;
        if ((y_velocity < 0 ? -y_velocity : y_velocity) > 0x200000) {
            y_velocity = y_velocity > 0 ? 0x200000 : -0x200000;
            motion->unk_10.s32 = y_velocity;
        }
    }
    {
        s32 height = effect->unk_2C.s32;
        height += (((s32)effect->unk_10.s16 << 16) - height) >> 4;
        effect->unk_2C.s32 = height;
        height = motion->unk_08.s32;
        height += (((s32)effect->unk_10.s16 << 16) - height) >> 4;
        motion->unk_08.s32 = height;
    }
    {
        s32 bob_offset = func_800644B8((s32)effect->unk_18.s16 << 7);
        motion->unk_08.s32 += bob_offset << 6;
    }
    handle_retail_n_818875_e_8_callee_80024_de_8_creates_fade_updated_each_frame_callee_80024_d_70_start(motion, sprite);
    {
        s32 tile_coord = motion->unk_00.parts.unk_02.s16;
        if (tile_coord < 0) {
            tile_coord += 63;
        }
        effect->unk_1C.parts.unk_1E.parts.unk_1E.u8 = tile_coord >> 6;
        tile_coord = motion->unk_04.parts.unk_06.s16;
        effect->unk_1C.parts.unk_1E.parts.unk_1F.u8 = (tile_coord / 64);
    }
    if (effect->unk_20.s16 == effect->unk_1C.parts.unk_1E.s16) {
        break;
    }
    if (owner->unk_60 != 0) {
        if (effect->unk_58 == 0) {
            s32 target_distance = set_item_w0(
                ((S_func_81886800_1 *)(effect))->unk_1C.parts.unk_1E.parts.unk_1E.u8,
                ((S_func_81886800_1 *)(effect))->unk_1C.parts.unk_1E.parts.unk_1F.u8,
                ((S_func_81886800_8 *)(owner))->unk_70.parts.unk_72.u8,
                ((S_func_81886800_8 *)(owner))->unk_70.parts.unk_73.u8);
            target_distance = (s16)target_distance;
            if (target_distance < 5) {
                effect->unk_58 = 1;
                play_sound_if_enabled(0x300);
            }
        }
    }
    if (owner->unk_60 != 0) {
        if ((((S_func_81886800_8 *)(owner))->unk_70.u32 & 0xFFFF0000) ==
            (((S_func_81886800_1 *)(effect))->unk_1C.u32 & 0xFFFF0000)) {
            S_func_81886800_11 *snapped_motion;

            snapped_motion = motion;
            {
                s32 coordinate = owner->unk_70.parts.unk_72.s8;
                motion->unk_00.parts.unk_02.s16 = (coordinate << 6) + 0x20;
            }
            {
                s32 coordinate = owner->unk_70.parts.unk_73.s8;
                motion->unk_04.parts.unk_06.s16 = (coordinate << 6) + 0x20;
            }
            motion->unk_08.parts.unk_0A = effect->unk_10.u16;
            handle_retail_n_818875_e_8_callee_80024_de_8_creates_fade_updated_each_frame_callee_80024_d_70_start(snapped_motion, sprite);
            {
                u16 next_state = effect->unk_0A.u16;
                u16 target_id =
                    ((S_func_81886800_8 *)(owner->unk_60))->unk_88.u16;
                next_state++;
                effect->unk_0A.u16 = next_state;
                ((S_func_81886800_15 *)(D_80026878))->unk_00 = target_id;
            }
            break;
        }
    }

    {
        u8 x = effect->unk_1C.parts.unk_1E.parts.unk_1E.u8;
        u8 y = effect->unk_1C.parts.unk_1E.parts.unk_1F.u8;
        s32 timer = effect->unk_14 - 1;
        s32 collision;
        effect->unk_14 = timer;
        effect->unk_20.parts.unk_20 = x;
        effect->unk_20.parts.unk_21 = y;
        if ((timer << 16) != 0) {
            s32 world_x = (((s32)effect->unk_1C.parts.unk_1E.parts.unk_1E.s8 << 6) + 0x20) & 0xFFE0;
            s32 world_y = (((s32)effect->unk_1C.parts.unk_1E.parts.unk_1F.s8 << 6) + 0x20) & 0xFFE0;
            collision = check_left_tile_and_center_height(world_x, world_y, effect->unk_2C.parts.unk_2E.s16);
            if ((collision << 16) == 0) {
                break;
            }
        }
        effect->unk_0A.u16 = 16;
        break;
    }

    case 3:
    func_80065F90(motion->unk_0C.parts.unk_0E.s16, motion->unk_10.parts.unk_12.s16);
    target_object = owner->unk_60;
    effect->unk_28 = create_an_copies_three_source_fields_child_runs_n_16_child_setup(
        effect, motion, target_object->unk_88.s16, target_object);
    if (effect->unk_28 == 0) {
        break;
    }
    effect->unk_0A.u16++;
    case 4:
    {
        sprite->unk_0C.parts.unk_0C -= sprite->unk_0C.parts.unk_0C >> 2;
        sprite->unk_0C.parts.unk_0D -= sprite->unk_0C.parts.unk_0D >> 2;
        sprite->unk_0C.parts.unk_0E -= sprite->unk_0C.parts.unk_0E >> 2;
        if ((((S_func_81886800_16 *)(effect->unk_28))->unk_1E & 0x8000) == 0) {
            break;
        }
        if (owner->unk_60 != 0) {
            check_the_target_using_scaled_low_byte_conditionally_applies_global_800_e_1_d_01(owner->unk_60,
                          effect->unk_09, owner);
        }
        effect->unk_0A.u16 = 17;
        break;
    }

    case 16:
    {
#ifdef __mips__
#else
        S_func_81886800_11 *motion;
#endif
        motion->unk_00.s32 += motion->unk_0C.s32;
        motion->unk_04.s32 += motion->unk_10.s32;
        {
            s32 target_height = (s32)effect->unk_10.s16 << 16;
            s32 height = motion->unk_08.s32;
            height += (target_height - height) >> 4;
            motion->unk_08.s32 = height;
        }
        sprite->unk_0C.parts.unk_0C -= sprite->unk_0C.parts.unk_0C >> 1;
        sprite->unk_0C.parts.unk_0D -= sprite->unk_0C.parts.unk_0D >> 1;
        sprite->unk_0C.parts.unk_0E -= sprite->unk_0C.parts.unk_0E >> 1;
        handle_retail_n_818875_e_8_callee_80024_de_8_creates_fade_updated_each_frame_callee_80024_d_70_start(motion, sprite);
        if (sprite->unk_0C.parts.unk_0C < 2) {
            effect->unk_0A.u16++;
        }
        break;
    }

    case 17:
    if (((S_func_81886800_17 *)(&D_80026326))->unk_00.s16 != 0) {
        break;
    }
    ((S_func_81886800_18 *)(((u8 *)(&g_dungeon_status.active_actor))))->unk_00 = 0;
    ((S_func_81886800_12 *)((u8 *)effect - 2))->unk_00 |= 0x8000;
    ((S_func_81886800_19 *)(((u8 *)(&object_flag_block))))->unk_00 |= 0x8000;

    }
    {
        u16 frame_count = effect->unk_18.u16;
        ((S_func_81886800_17 *)(&D_80026326))->unk_00.u16 = 0;
        effect->unk_18.u16 = frame_count + 1;
    }
}

#include "dungeon/effect/sprite/create_radial_effect_from_source.h"
#include "modules/dungeon_native_abi.h"
#include "common.h"
#include "shared/object_flags.h"


typedef struct {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    s16 z;
} Vec3s;

typedef struct {
    void *object;
    u8 pad4[6];
    s16 state;
    u8 padC[0xC];
    s16 timer;
    u16 ticks;
} EffectState;

typedef struct {
    u8 pad0[0xC];
    u8 r;
    u8 g;
    u8 b;
} ColorObject;

typedef struct {
    u8 pad0[0x1C];
    u32 flags;
} Object;

extern u8 last_frame_ticks[];

extern void create_a_sprite_effect_position_randomized_rotation(s16 x, s16 y, s16 z);
extern void create_quad_fragments_vertex_grid_randomized_motion_rotation(void);
extern s32 func_80069EF8(void);

/* Advances the effect through color buildup, flicker, and fade, then restores the object color. */
void create_radial_effect_from_source(EffectState *effect, Vec3s *pos)
{
    Object *object;
    ColorObject *color;
    s32 burst_index;
    s32 state;
    s32 channel_value;

    D_80026326++;
    state = effect->state;
    switch (state) {
    case 0:
        object = effect->object;
        object->flags |= 0x10000000;
        effect->state++;


    case 1:
        color = *(ColorObject **)((u8 *)effect->object - 0x14);
        channel_value = color->r - 1;
        color->r = channel_value;
        if ((u8)channel_value < 0x40) {
            color->r = 0x40;
        }
        channel_value = color->g - 1;
        color->g = channel_value;
        if ((u8)channel_value < 0x40) {
            color->g = 0x40;
        }
        channel_value = color->b + 1;
        color->b = channel_value;
        if ((u8)channel_value >= 0xC1) {
            color->b = 0xC0;
        }
        if (D_80026328[0] != 0) {
            effect->state++;
        }
        break;

    case 2:
    {
        u8 *primary_rgb;
        u8 *secondary_rgb;

        effect->timer++;
        D_80026470[0] = effect->timer * 2;
        primary_rgb = D_80026470;
        primary_rgb[1] = effect->timer * 4;
        primary_rgb[2] = effect->timer * 14;
        D_80026474[0] = effect->timer * 10;
        secondary_rgb = D_80026474;
        secondary_rgb[1] = effect->timer * 11;
        secondary_rgb[2] = effect->timer * 14;

        for (burst_index = 0; burst_index < 4; burst_index++) {
            create_a_sprite_effect_position_randomized_rotation(pos->x, pos->y, pos->z);
        }
        if (effect->timer >= 0x10) {
            effect->timer = 0xA0;
            effect->state++;
        }
        break;
    }

    case 3:
    {
        u8 *random_rgb;

        D_80026474[0] = (func_80069EF8() % 0x3F) - 0x80;
        random_rgb = D_80026474;
        random_rgb[1] = (func_80069EF8() % 0x3F) - 0x80;
        effect->timer -= last_frame_ticks[0];
        if (effect->timer <= 0) {
            create_quad_fragments_vertex_grid_randomized_motion_rotation();
            effect->timer = 0x10;
            effect->state++;
        }
        break;
    }

    case 4:
    {
        u8 *primary_rgb;
        u8 *secondary_rgb;

        D_80026470[0] += -(s32)D_80026470[0] / effect->timer;
        primary_rgb = D_80026470;
        primary_rgb[1] += -(s32)primary_rgb[1] / effect->timer;
        primary_rgb[2] += -(s32)primary_rgb[2] / effect->timer;
        D_80026474[0] += -(s32)D_80026474[0] / effect->timer;
        secondary_rgb = D_80026474;
        secondary_rgb[1] += -(s32)secondary_rgb[1] / effect->timer;
        secondary_rgb[2] += -(s32)secondary_rgb[2] / effect->timer;
    }

        {
            s32 neutral_level;
            s32 effect_count;
            u32 flags;
            u32 clear_effect_mask;
            Object *fade_object;

            color = *(ColorObject **)((u8 *)effect->object - 0x14);
            neutral_level = 0x80;
            color->r += (neutral_level - color->r) / effect->timer;
            color->g += (neutral_level - color->g) / effect->timer;
            color->b += (neutral_level - color->b) / effect->timer;
            effect->timer--;
            if (effect->timer <= 0) {
                clear_effect_mask = 0xEFFFFFFF;
                color->r = neutral_level;
                color->g = neutral_level;
                color->b = neutral_level;
                fade_object = effect->object;
                effect_count = D_80026324[0];
                flags = fade_object->flags;
                effect_count--;
                D_80026324[0] = effect_count;
                flags &= clear_effect_mask;
                fade_object->flags = flags;
                ((u16 *)effect)[-1] |= 0x8000;
                object_flag_block.flags |= 0x8000;
            }
            break;
        }
    }
    effect->ticks++;
}
#include "dungeon/effect/sprite/create_radial_effect_from_source.h"
#include "modules/dungeon_native_abi.h"
#include "common.h"

/* Creates an object, copies three source fields to its child, and runs 16 child setup steps. */
void *create_an_copies_three_source_fields_child_runs_n_16_child_setup(s32 value, void *source, s32 unused, s32 context)
{
    register u32 saved_context;
    s32 adjusted_value;
    s32 step;
    void *child;
    void *object;
    u16 counter;

    saved_context = context;
    adjusted_value = value - 0x20;
    object = allocate_list_node(2, adjusted_value);
    if (object != 0) {
        counter = D_80026324[0];
        *(s32 **)((u8 *)object + 0x10) = create_radial_effect_from_source;
        D_80026324[0] = counter + 1;
        register_node(object, build_shaded_quads_adjacent_vertex_rows_adds_them_ordering_table);

        child = *(void **)((u8 *)object + 8);
        *(u16 *)((u8 *)child + 2) = *(u16 *)((u8 *)source + 2);
        step = 0;
        *(u16 *)((u8 *)child + 6) = *(u16 *)((u8 *)source + 6);
        *(u16 *)((u8 *)child + 0xA) = *(u16 *)((u8 *)source + 0xA);
        source = (void *)adjusted_value;
        *(s32 *)((u8 *)object + 0x20) = saved_context;

        do {
            create_object_offset(child, (s16)(step << 8), 0x40, -0x100, source);
            step += 1;
        } while (step < 0x10);
    }
    return object;
}
#include "dungeon/effect/sprite/create_radial_effect_from_source.h"
#include "modules/dungeon_native_abi.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"

extern u16 D_80026326;



/* Retail 81887570 (handle_retail_n_81887570_callee_80024_d_70_fade_colour_n_1_n_8_per_call_mark): fade the colour by 1/8 per call and mark the effect (header and global
 * flags) finished once red falls below eight.  effect is the effect's record; its header precedes it. */
void handle_retail_n_81887570_callee_80024_d_70_fade_colour_n_1_n_8_per_call_mark(void *effect, s32 unused, EffectColor *color) {
    u8 red;
    u8 green;
    u8 blue;

    D_80026326++;

    red = color->red;
    green = color->green;
    color->red = red - (red >> 3);
    blue = color->blue;
    color->green = green - (green >> 3);
    color->blue = blue - (blue >> 3);

    if (color->red < 8) {
        ((ObjectNodeHeader *)effect - 1)->flags |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
#include "dungeon/effect/sprite/create_radial_effect_from_source.h"
#include "shared/sprite_frame_state.h"
#include "modules/dungeon_native_abi.h"
#include "common.h"
#include "modules/dungeon_native_abi.h"
#include "shared/object_node.h"

extern void handle_retail_n_81887570_callee_80024_d_70_fade_colour_n_1_n_8_per_call_mark();
extern u8 D_800CEEFC[];

/* One 4-byte slot of the fade record: only the second halfword is used. */
typedef struct FadeChannel {
    u16 unused;
    u16 value;
} FadeChannel;

typedef struct FadeDelta {
    u16 unused;
    s16 value;
} FadeDelta;

/* The fade's working record (the object header's unk_08 payload). */
typedef struct FadeTransition {
    FadeChannel start[3];
    FadeDelta delta[3];     /* start - end per channel */
} FadeTransition;

/* Start values followed by end values, one FadeChannel each. */
typedef struct FadeEndpoints {
    FadeChannel start[3];
    FadeChannel end[3];
} FadeEndpoints;

/* Settings block: copied field by field into the object's own settings record (the header's unk_0C payload). */
typedef struct FadeSettings {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} FadeSettings;

/* Retail 818875E8 (handle_retail_n_818875_e_8_callee_80024_de_8_creates_fade_updated_each_frame_callee_80024_d_70_start): creates a fade object (updated each frame by handle_retail_n_81887570_callee_80024_d_70_fade_colour_n_1_n_8_per_call_mark) with its start
 * values, per-channel start - end differences and a copy of the settings. */
ObjectNodeHeader *handle_retail_n_818875_e_8_callee_80024_de_8_creates_fade_updated_each_frame_callee_80024_d_70_start(FadeEndpoints *endpoints, FadeSettings *settings) {
    FadeTransition *transition;
    ObjectNodeHeader *object;
    SpriteFrameState *object_settings;

    object = allocate_flagged_object_node(0x202);
    if (object != NULL) {
        object->unk_10 = (void *)handle_retail_n_81887570_callee_80024_d_70_fade_colour_n_1_n_8_per_call_mark;
        register_node(object, (s32)&D_800CEEFC);
        transition = object->unk_08;
        transition->start[0].value = endpoints->start[0].value;
        transition->start[1].value = endpoints->start[1].value;
        transition->start[2].value = endpoints->start[2].value;
        transition->delta[0].value = endpoints->start[0].value - endpoints->end[0].value;
        transition->delta[1].value = endpoints->start[1].value - endpoints->end[1].value;
        transition->delta[2].value = endpoints->start[2].value - endpoints->end[2].value;
        object_settings = object->unk_0C;
        object_settings->scale_x = settings->unk_1C;
        object_settings->scale_y = settings->unk_1E;
        object_settings->color.word = settings->unk_0C;
        object_settings->source = settings->unk_08;
        object_settings->flags = settings->unk_14;
    }
    return object;
}
#include "dungeon/effect/sprite/create_radial_effect_from_source.h"
#include "common.h"
#include "shared/game_work.h"

typedef struct Scratch {
    u8 pad0[0x18];
    u8 *current;
    u8 pad1c[4];
    u32 *table;
    u8 pad24[0x4c];
    u32 value70;
    u16 half74;
    u8 pad76[2];
    u32 value78;
    u16 half7c;
    u8 pad7e[2];
    u32 value80;
    u16 half84;
    u8 pad86[2];
    u32 value88;
    u16 half8c;
    u8 pad8e[2];
    u32 out90;
    u32 out94;
    u8 pad98[0x28];
    u32 index;
} Scratch;

typedef struct Entry {
    u8 bytes[0x24];
} Entry;

typedef struct EmptyCallArg {
} EmptyCallArg;


extern u32 func_800654B0(
    void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, ...);
extern void func_80066708(void *);

/* Builds shaded quads from adjacent vertex rows and adds them to the ordering table. */
s32 build_shaded_quads_adjacent_vertex_rows_adds_them_ordering_table(void)
{
    s32 quad_index = 0;
    Scratch *scratch = (Scratch *)0x1F800000;
    u8 *state = g_game_work.draw_buffer;
    u8 *primitive_start = *(u8 **)(state + 0x8D0);
    u32 *vertices;
    u8 *vertex_record;

    scratch->table = (u32 *)(state + 0xB0);
    scratch->current = primitive_start;

            /* This address is needed only by the loop's terminal writeback. */
    {
        u8 **state_slot = &g_game_work.draw_buffer;

        if (D_8002632A > 0) {
            vertices = D_80026478;
            vertex_record = (u8 *)vertices;

            do {
                Entry *quad;
                u32 *near_vertex;
                u32 *near_next_vertex;
                u32 *far_vertex;
                u32 *far_next_vertex;
                u32 *next_row;
                u32 *far_next_ptr;
                u32 far_next_xy;
                s32 row_start;
                s32 far_index;
                u16 near_z;
                u16 far_z;
                EmptyCallArg late_stores;

                near_vertex = &scratch->value70;
                row_start = quad_index & ~0xF;
                quad = (Entry *)scratch->current;
                near_next_vertex = &scratch->value78;
                far_vertex = &scratch->value80;
                scratch->current = (u8 *)quad + 0x24;
                scratch->value70 = *(u32 *)vertex_record;
                scratch->value78 = vertices[
                    ((u32)row_start + (u32)((quad_index + 1) & 0xF)) * 2];
                next_row = vertices + 0x20;
                far_next_ptr = (u32 *)(((u32)row_start + (u32)((quad_index + 1) & 0xF)) * 8 + (u32)next_row);
                scratch->value80 = next_row[quad_index * 2];
                far_next_xy = *far_next_ptr;
                far_next_vertex = &scratch->value88;
                near_z = *(u16 *)(vertex_record + 4);
                scratch->half74 = near_z;
                scratch->half7c = near_z;
                far_index = quad_index + 16;
                far_z = ((u16 *)vertices)[(far_index * 4) + 2];

                scratch->index = func_800654B0(
                    near_vertex, near_next_vertex, far_vertex, far_next_vertex,
                    (u32 *)((u8 *)quad + 8), (u32 *)((u8 *)quad + 16),
                    (u32 *)((u8 *)quad + 24), (u32 *)((u8 *)quad + 32),
                    &scratch->out90, &scratch->out94,
                    (scratch->value88 = far_next_xy,
                     scratch->half84 = far_z,
                     scratch->half8c = far_z,
                     late_stores));
                scratch->index -= 8;

                if (scratch->index < 0x1E0U) {
                    if ((quad_index % 32) < 16) {
                        *(u32 *)((u8 *)quad + 12) = (*(u32 *)D_80026470);
                        *(u32 *)((u8 *)quad + 4) = (*(u32 *)D_80026470);
                        *(u32 *)((u8 *)quad + 28) = (*(u32 *)D_80026474);
                        *(u32 *)((u8 *)quad + 20) = (*(u32 *)D_80026474);
                    } else {
                        *(u32 *)((u8 *)quad + 28) = (*(u32 *)D_80026470);
                        *(u32 *)((u8 *)quad + 20) = (*(u32 *)D_80026470);
                        *(u32 *)((u8 *)quad + 12) = (*(u32 *)D_80026474);
                        *(u32 *)((u8 *)quad + 4) = (*(u32 *)D_80026474);
                    }

                    func_80066708(quad);
                    quad->bytes[7] |= 2;
                    func_8006658C(scratch->table + scratch->index, quad);

                    {
                        u8 *draw_mode = scratch->current;
                        scratch->current = draw_mode + 0x0C;
                        func_80067F20(draw_mode, 0, 0,
                                      (u16)func_80066460(0, 1, 0, 0), 0);
                        func_8006658C(scratch->table + scratch->index,
                                      (Entry *)draw_mode);
                    }
                }

                vertex_record += 8;
                quad_index++;
            } while (quad_index < D_8002632A);
        }
        *(u8 **)(*state_slot + 0x8D0) = scratch->current;
    }
    return 0;
}
#include "dungeon/effect/sprite/create_radial_effect_from_source.h"
#include "modules/dungeon_native_abi.h"
#include "common.h"
#include "shared/object_flags.h"

typedef struct S_80025160_0_pre {
    u16 unk_00;
} S_80025160_0_pre;   /* the 0x2 bytes before arg0 in advance_the_effect_state_updates_motion_sets_display_color, addressed as arg0[-1] */

typedef struct S_80025160_0 {
    u8 pad_00[0xA];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0xA];
    s16 unk_16;
    union { u16 s; u16 u; s16 p; } unk_18;   /* accessed as both */
    u16 unk_1A;
    union { u16 s; u16 u; } unk_1C;   /* accessed as both */
    u8 pad_1E[0x4];
    s16 unk_22;
} S_80025160_0;   /* arg0 in advance_the_effect_state_updates_motion_sets_display_color */

typedef struct S_80025160_1 {
    u8 pad_00[0x6];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_80025160_1;   /* arg2 in advance_the_effect_state_updates_motion_sets_display_color */

typedef struct S_80025160_2 {
    u8 pad_00[0x6328];
    s16 unk_6328;
} S_80025160_2;   /* flag_page in advance_the_effect_state_updates_motion_sets_display_color */

typedef struct S_80025160_3 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_80025160_3;   /* flags_page in advance_the_effect_state_updates_motion_sets_display_color */


#define COUNTER D_80026326

typedef struct Global26326 {
    u16 counter;
    s16 flag;
    u16 unused[3];
} Global26326;

typedef struct Global26328 {
    s16 flag;
    u16 unused[4];
} Global26328;

typedef struct Global814A0 {
    s32 flags;
    s32 unused[2];
} Global814A0;


/* Advances the effect state, updates its motion, and sets its display color. */
void advance_the_effect_state_updates_motion_sets_display_color(void *effect, s32 context, S_80025160_1 *visual) {
    s16 state;
    u16 value;
    u16 angle;
    u16 damped_value;
    s32 effect_param;
    s32 angle_shifted;
    void *owner;
    u8 *flag_page;
    u8 *flags_page;

    COUNTER = COUNTER + 1;
    state = ((S_80025160_0 *)effect)->unk_0A.s;

    switch (state) {
    case 0:
        value = visual->unk_06.s + 0x80;
        visual->unk_06.s = value;
        if ((s16)value > 0x100) {
            visual->unk_06.s = 0x100;
            if (((S_80025160_0 *)effect)->unk_22 < 0x61) {
                damped_value = ((S_80025160_0 *)effect)->unk_18.s;
                angle = ((S_80025160_0 *)effect)->unk_1C.s;
                effect_param = ((S_80025160_0 *)effect)->unk_16;
                damped_value = damped_value - ((s32)(damped_value << 16) >> 19);
                ((S_80025160_0 *)effect)->unk_18.u = damped_value;
                angle = angle + 0x80;
                owner = (u8 *)effect - 0x20;
                ((S_80025160_0 *)effect)->unk_1C.u = angle;
                angle_shifted = angle << 16;
                create_object_offset(context, effect_param, ((S_80025160_0 *)effect)->unk_18.p,
                              angle_shifted >> 16, owner);
            }
            ((S_80025160_0 *)effect)->unk_0A.u++;
            if (((S_80025160_0 *)effect)->unk_22 == 0x6F) {
                D_80026328[0] = 1;
            }
        }
        break;
    case 1:
        flag_page = (u8 *)0x80020000;
        if (((S_80025160_2 *)flag_page)->unk_6328 != 0) {
            visual->unk_06.u = -0x100;
            ((S_80025160_0 *)effect)->unk_1A = 0x10;
            ((S_80025160_0 *)effect)->unk_0A.u++;
        }
        break;
    case 2:
        value = ((S_80025160_0 *)effect)->unk_1A - 1;
        ((S_80025160_0 *)effect)->unk_1A = value;
        if ((value << 16) > 0) {
            break;
        }
        ((S_80025160_0 *)effect)->unk_0A.u++;
                        /* fall through */
    case 3:
        value = visual->unk_06.s + 0x80;
        visual->unk_06.s = value;
        if ((value << 16) >= 0) {
            flags_page = (u8 *)0x80080000;
            ((S_80025160_0_pre *)effect)[-1].unk_00 |= 0x8000;
            ((S_80025160_3 *)flags_page)->unk_14A0 |= 0x8000;
        }
        break;
    default:
        break;
    }
    visual->unk_0C = 0x20;
    visual->unk_0D = 0x40;
    visual->unk_0E = 0xE0;
}
#include "dungeon/effect/sprite/create_radial_effect_from_source.h"
#include "modules/dungeon_native_abi.h"
#include "common.h"
#include "shared/game_work.h"
typedef struct
{
    u8 *value;
    u8 pad[8];
}
Global83160;
typedef struct
{
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
}
TableEntry;
extern s32 func_80065420(void *, void *, void *, void *);
/* Build and enqueue interpolated, depth-sorted shaded lines for a linked list. */
s32 build_and_enqueue_interpolated_depth_sorted_shaded_lines_linked_list(void *first_owner, void *first_vertices, void *first_line)
{
    {
        u8 *render_data = g_game_work.draw_buffer;
        void *owner = first_owner;
        void *vertex_data = first_vertices;
        void *line_data = first_line;
        u8 *scratch = (u8 *) 0x1F800000;
        u8 *line_packet;
        u8 *packet;
        u16 red_blue;
        u8 green;
        void *next_node;
        s32 avg_depth;
        s16 blend;
        s32 point_index;
        s32 color_word;
        register u8 **render_state = (u8 **) ((Global83160 *)&g_game_work);
        *(u8 **)(scratch + 0x18) = *(u8 **)(render_data + 0x8D0);
        *(u8 **)(scratch + 0x20) = render_data + 0xB0;
        for (;;) {
            line_packet = *(u8 **)(scratch + 0x18);
            *(u8 **)(scratch + 0x18) = line_packet + 0x14;
            blend = *(s16 *)((u8 *) line_data + 6);
            if (blend >= 0) {
                *(u16 *)(scratch + 0) = *(u16 *)((u8 *) vertex_data + 0xE);
                *(u16 *)(scratch + 2) = *(u16 *)((u8 *) vertex_data + 0x12);
                *(u16 *)(scratch + 4) = *(u16 *)((u8 *) vertex_data + 0x16);
                *(s32 *)(scratch + 0xC0) = func_80065420(scratch, line_packet + 8, scratch + 0x90, scratch + 0x94);
                *(u16 *)(scratch + 0) =
                    (*(u16 *)((u8 *) vertex_data + 0xE)) + ((((*(s16 *)((u8 *) vertex_data + 2))
                        - (*(s16 *)((u8 *) vertex_data + 0xE))) * (*(s16 *)((u8 *) line_data + 6))) >> 8);
                *(u16 *)(scratch + 2) =
                    (*(u16 *)((u8 *) vertex_data + 0x12)) + ((((*(s16 *)((u8 *) vertex_data + 6))
                        - (*(s16 *)((u8 *) vertex_data + 0x12))) * (*(s16 *)((u8 *) line_data + 6))) >> 8);
                *(u16 *)(scratch + 4) =
                    (*(u16 *)((u8 *) vertex_data + 0x16)) + ((((*(s16 *)((u8 *) vertex_data + 0xA))
                        - (*(s16 *)((u8 *) vertex_data + 0x16))) * (*(s16 *)((u8 *) line_data + 6))) >> 8);
                point_index = (*(s16 *)((u8 *) owner + 0x22)) + 0x10;
                if (D_8002632A < point_index) {
                    register TableEntry *point_table = (TableEntry *) D_80026478;
                    s32 table_index;
                    u16 coord;
                    point_table[point_index].x = *(u16 *)(scratch + 0);
                    table_index = *(s16 *)((u8 *) owner + 0x22);
                    coord = *(u16 *)(scratch + 2);
                    table_index += 0x10;
                    point_table[table_index].y = coord;
                    table_index = *(s16 *)((u8 *) owner + 0x22);
                    coord = *(u16 *)(scratch + 4);
                    table_index += 0x10;
                    point_table[table_index].z = coord;
                }
            }
            else {
                *(u16 *)(scratch + 0) = (*(u16 *)((u8 *) vertex_data + 2)) - ((((*(s16 *)((u8 *) vertex_data + 0xE))
                    - (*(s16 *)((u8 *) vertex_data + 2))) * blend) >> 8);
                *(u16 *)(scratch + 2) =
                    (*(u16 *)((u8 *) vertex_data + 6)) - ((((*(s16 *)((u8 *) vertex_data + 0x12))
                        - (*(s16 *)((u8 *) vertex_data + 6))) * (*(s16 *)((u8 *) line_data + 6))) >> 8);
                *(u16 *)(scratch + 4) =
                    (*(u16 *)((u8 *) vertex_data + 0xA)) - ((((*(s16 *)((u8 *) vertex_data + 0x16))
                        - (*(s16 *)((u8 *) vertex_data + 0xA))) * (*(s16 *)((u8 *) line_data + 6))) >> 8);
                *(s32 *)(scratch + 0xC0) = func_80065420(scratch, line_packet + 8, scratch + 0x90, scratch + 0x94);
                *(u16 *)(scratch + 0) = *(u16 *)((u8 *) vertex_data + 2);
                *(u16 *)(scratch + 2) = *(u16 *)((u8 *) vertex_data + 6);
                *(u16 *)(scratch + 4) = *(u16 *)((u8 *) vertex_data + 0xA);
            }
            avg_depth = ((*(s32 *)(scratch + 0xC0)) + func_80065420(scratch, line_packet + 0x10, scratch + 0x90,
                scratch + 0x94)) >> 1;
            *(s32 *)(scratch + 0xC0) = avg_depth;
            if (((u32) avg_depth) < 0x1E0U) {
                packet = line_packet;
                *(u8 *)(packet + 3) = (color_word = *(s32 *)((u8 *) line_data + 0xC), 4);
                *(s32 *)(packet + 4) = color_word;
                red_blue = *(u8 *)(packet + 4);
                *(u8 *)(packet + 7) = 0x52;
                green = *(u8 *)(packet + 5);
                red_blue >>= 1;
                *(u8 *)(packet + 0xC) = red_blue;
                red_blue = *(u8 *)(packet + 6);
                green >>= 1;
                *(u8 *)(packet + 0xD) = green;
                red_blue >>= 1;
                *(u8 *)(packet + 0xE) = red_blue;
                func_8006658C((*(u8 **)(scratch + 0x20)) + ((*(s32 *)(scratch + 0xC0)) * 4), packet);
                vertex_data = *(u8 **)(scratch + 0x18);
                *(u8 **)(scratch + 0x18) = ((u8 *) vertex_data) + 0xC;
                func_80067F20(vertex_data, 0, 0, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
                func_8006658C((*(u8 **)(scratch + 0x20)) + ((*(s32 *)(scratch + 0xC0)) * 4), vertex_data);
            }
            next_node = *(void **)((u8 *) owner + (-8));
            if (next_node != 0) {
                owner = ((u8 *) next_node) + 0x20;
                vertex_data = *(void **)((u8 *) next_node + 8);
                line_data = *(void **)((u8 *) next_node + 0xC);
                continue;
            }
            break;
        }
        *(u8 **)(*render_state + 0x8D0) = *(u8 **)(scratch + 0x18);
        return 0;
    }
}
#include "dungeon/effect/sprite/create_radial_effect_from_source.h"
#include "modules/dungeon_native_abi.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_8002569C_6 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_8002569C_6;


                  /* extern */

s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern s16 D_8002632A;
extern u8 D_80026478[];
extern u8 D_80026878[];

typedef struct S_8002569C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
} S_8002569C_0;

typedef struct S_8002569C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_8002569C_1;

   /* arg0 in create_object_offset */

typedef struct S_8002569C_3 {
    u8 pad_00[0x16];
    s16 unk_16;
    s16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
    u8 pad_1E[0x4];
    u16 unk_22;
} S_8002569C_3;

typedef struct S_8002569C_4 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_8002569C_4;

typedef struct S_8002569C_5 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_8002569C_5;

/* Create an object offset from an origin and record its starting position. */
void *create_object_offset(MovingPosition *origin, s16 angle, s16 radius, s16 height_offset, s32 alloc_arg) {
    s16 height;
    u16 slot_index;
    u16 origin_x;
    u16 origin_z;
    u16 origin_y;
    S_8002569C_4 *position_slot;
    u8 *position_table;
    S_8002569C_1 *positions;
    void *object;
    S_8002569C_5 *paired_slot;
    S_8002569C_3 *object_data;

    object = allocate_list_node(0x202, alloc_arg);
    if (object != NULL) {
        ((S_8002569C_0 *)object)->unk_10 = (s32 *)advance_the_effect_state_updates_motion_sets_display_color;
        register_node(object, (s32 *)build_and_enqueue_interpolated_depth_sorted_shaded_lines_linked_list);
        positions = ((S_8002569C_0 *)object)->unk_08;
        positions->unk_02 = (s16) (origin->unk_02 + ((s32) (func_80064584(angle) * radius) >> 0xF));
        positions->unk_06 = (s16) (origin->unk_06 + ((s32) (func_800644B8(angle) * radius) >> 0xF));
        height = origin->unk_0A + ((s32) (height_offset << 0x10) >> 0x13);
        positions->unk_0A = height;
        if ((*(s16 *)D_80026878) < height) {
            positions->unk_0A = (*(s16 *)D_80026878);
        }
        positions->unk_0E = (u16) origin->unk_02;
        positions->unk_12 = (u16) origin->unk_06;
        positions->unk_16 = (u16) origin->unk_0A;
        object_data = (void *) 0xE04020;
        (*(s32 *)((u8 *)(((S_8002569C_6 *)object)->unk_0C) + 0xC)) = (s32) object_data;
        slot_index = (u16)D_8002632A;
        object_data = object + 0x20;
        object_data->unk_16 = angle;
        object_data->unk_1C = height_offset;
        object_data->unk_18 = radius;
        object_data->unk_22 = slot_index;
        if ((s16) slot_index < 0x71) {
            position_table = D_80026478;
            position_slot = &position_table[(s16) slot_index * 8];
            origin_x = positions->unk_0E;
            paired_slot = &position_table[((s16) slot_index + 0x10) * 8];
            position_slot->unk_00 = origin_x;
            paired_slot->unk_00 = origin_x;
            origin_y = positions->unk_12;
            position_slot->unk_02 = origin_y;
            paired_slot->unk_02 = origin_y;
            origin_z = positions->unk_16;
            D_8002632A = slot_index + 1;
            position_slot->unk_04 = origin_z;
            paired_slot->unk_04 = origin_z;
        }
    }
    return object;
}
#include "dungeon/effect/sprite/create_radial_effect_from_source.h"
#include "modules/dungeon_native_abi.h"
#include "common.h"
#include "shared/object_flags.h"

typedef struct Actor {
    u8 pad00[0x1A];
    u16 timer;
} Actor;

typedef struct Motion {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} Motion;



extern u16 D_80026326;
extern void advance_sprite_animation_and_textures(void *color);


/* Advance and fade the effect, flagging expiration when its timer runs out. */
void advance_and_fade_effect_flagging_expiration_timer_runs_out(Actor *actor, Motion *motion, EffectColor *color)
{
    u16 *counter = &D_80026326;
    u16 timer;
    u8 red;
    u8 green;
    u8 blue;

    counter[0]++;

    motion->x += motion->dx;
    motion->y += motion->dy;
    motion->z += motion->dz;
    motion->dx -= motion->dx >> 3;
    motion->dy -= motion->dy >> 3;
    motion->dz += 0x4000;

    red = color->red;
    green = color->green;
    color->red = red - (red >> 2);
    blue = color->blue;
    color->green = green - (green >> 2);
    color->blue = blue - (blue >> 2);

    advance_sprite_animation_and_textures(color);

    timer = actor->timer - 1;
    actor->timer = timer;
    if ((s16)timer <= 0) {
        *(u16 *)((u8 *)actor - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
#include "dungeon/effect/sprite/create_radial_effect_from_source.h"
#include "shared/sprite_frame_state.h"
#include "modules/dungeon_native_abi.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

struct Dst;
struct Elem;

extern void select_record_entry_and_value(struct Dst *state, struct Elem *entries, short index);  /* extern */

s32 rand();                                /* extern */
extern M2C_UNK D_800263F8;

typedef struct S_8002596C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x2];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
    u8 pad_14[0x2];
    s16 unk_16;
} S_8002596C_1;

/* Create a sprite effect at the given position with a randomized rotation. */
void create_a_sprite_effect_position_randomized_rotation(s16 x, s16 y, s16 z) {
    S_8002596C_1 *transform;
    SpriteFrameState *sprite;
    ObjectNodeHeader *effect;

    effect = allocate_flagged_object_node(0x202);
    if (effect != NULL) {
        effect->unk_10 = (s32 *)advance_and_fade_effect_flagging_expiration_timer_runs_out;
        register_node(effect, project_sprite_chain);
        transform = effect->unk_08;
        transform->unk_02 = x;
        transform->unk_06 = y;
        transform->unk_0A = z;
        transform->unk_0E = 0;
        transform->unk_12 = 0;
        transform->unk_16 = (s16) (rand() & 7);
        sprite = effect->unk_0C;
        sprite->color.word = 0x808080;
        select_record_entry_and_value(sprite, &D_800263F8, 0);
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->tpage_abr = 0x20;
        sprite->flags = (u16) (sprite->flags | 0xC);
        ((s16 *)(effect + 1))[0x1A / 2] = 0x10;
    }
}
#include "dungeon/effect/sprite/create_radial_effect_from_source.h"
#include "modules/dungeon_native_abi.h"
#include "common.h"
#include "shared/object_flags.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern void func_800649A0(s32);
extern void func_80064A40(void);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern void func_80065320(void *, void *, void *);
extern void func_80065820(void *, void *);

/* Rotate and move an effect quad, fade its colors, and flag it when its lifetime ends. */
void handle_rotate_move_effect_quad_fade_colors_flag_lifetime_ends(void *effect, void *motion_data, void *rotation_data)
{
    u16 angles[3];
    s32 matrix[8];
    u16 *scratch = (u16 *)0x1F800000;
    void *motion = motion_data;
    u16 *globals_page;
    s32 origin_z;
    u16 vertex_z;
    u16 update_count;
    u16 relative_z;
    s16 ticks_left;
    s32 ticks_test;

    scratch[0x70 / 2] = U16_AT(effect, 0x30) - U16_AT(motion, 2);
    scratch[0x78 / 2] = U16_AT(effect, 0x38) - U16_AT(motion, 2);
    scratch[0x80 / 2] = U16_AT(effect, 0x40) - U16_AT(motion, 2);
    scratch[0x88 / 2] = U16_AT(effect, 0x48) - U16_AT(motion, 2);
    scratch[0x72 / 2] = U16_AT(effect, 0x32) - U16_AT(motion, 6);
    scratch[0x7A / 2] = U16_AT(effect, 0x3A) - U16_AT(motion, 6);
    scratch[0x82 / 2] = U16_AT(effect, 0x42) - U16_AT(motion, 6);
    scratch[0x8A / 2] = U16_AT(effect, 0x4A) - U16_AT(motion, 6);
    scratch[0x74 / 2] = U16_AT(effect, 0x34) - U16_AT(motion, 0xA);
    scratch[0x7C / 2] = U16_AT(effect, 0x3C) - U16_AT(motion, 0xA);
    globals_page = (u16 *)0x80020000;

    update_count = globals_page[0x6326 / 2];
    vertex_z = U16_AT(effect, 0x44);
    origin_z = U16_AT(motion, 0xA);
    update_count++;
    relative_z = vertex_z - origin_z;
    globals_page[0x6326 / 2] = update_count;
    scratch[0x84 / 2] = relative_z;
    scratch[0x8C / 2] = U16_AT(effect, 0x4C) - U16_AT(motion, 0xA);
    func_800649A0(origin_z);

    angles[0] = U16_AT(rotation_data, 0x16);
    angles[1] = U16_AT(rotation_data, 0x18);
    angles[2] = 0;
    matrix[7] = 0;
    matrix[6] = 0;
    matrix[5] = 0;
    func_80065820(angles, matrix);
    func_80064D80(matrix);
    func_80064CF0(matrix);

    func_80065320(scratch + 0x70 / 2, scratch + 0x98 / 2,
                  scratch + 0x94 / 2);
    func_80065320(scratch + 0x78 / 2, scratch + 0xA0 / 2,
                  scratch + 0x94 / 2);
    func_80065320(scratch + 0x80 / 2, scratch + 0xA8 / 2,
                  scratch + 0x94 / 2);
    func_80065320(scratch + 0x88 / 2, scratch + 0xB0 / 2,
                  scratch + 0x94 / 2);
    func_80064A40();

    S32_AT(motion, 0) = S32_AT(motion, 0) + S32_AT(motion, 0xC);
    S32_AT(motion, 4) = S32_AT(motion, 4) + S32_AT(motion, 0x10);
    S32_AT(motion, 8) = S32_AT(motion, 8) + S32_AT(motion, 0x14);

    U16_AT(effect, 0x30) = scratch[0x98 / 2] + U16_AT(motion, 2);
    U16_AT(effect, 0x38) = scratch[0xA0 / 2] + U16_AT(motion, 2);
    U16_AT(effect, 0x40) = scratch[0xA8 / 2] + U16_AT(motion, 2);
    U16_AT(effect, 0x48) = scratch[0xB0 / 2] + U16_AT(motion, 2);
    U16_AT(effect, 0x32) = scratch[0x9A / 2] + U16_AT(motion, 6);
    U16_AT(effect, 0x3A) = scratch[0xA2 / 2] + U16_AT(motion, 6);
    U16_AT(effect, 0x42) = scratch[0xAA / 2] + U16_AT(motion, 6);
    U16_AT(effect, 0x4A) = scratch[0xB2 / 2] + U16_AT(motion, 6);
    U16_AT(effect, 0x34) = scratch[0x9C / 2] + U16_AT(motion, 0xA);

    U16_AT(effect, 0x3C) = scratch[0xA4 / 2] + U16_AT(motion, 0xA);
    U16_AT(effect, 0x44) = scratch[0xAC / 2] + U16_AT(motion, 0xA);
    U16_AT(effect, 0x4C) = scratch[0xB4 / 2] + U16_AT(motion, 0xA);
    U8_AT(effect, 0x50) -= U8_AT(effect, 0x50) / S16_AT(effect, 0x1A);
    U8_AT(effect, 0x51) -= U8_AT(effect, 0x51) / S16_AT(effect, 0x1A);
    U8_AT(effect, 0x52) -= U8_AT(effect, 0x52) / S16_AT(effect, 0x1A);
    U8_AT(effect, 0x54) -= U8_AT(effect, 0x54) / S16_AT(effect, 0x1A);
    U8_AT(effect, 0x55) -= U8_AT(effect, 0x55) / S16_AT(effect, 0x1A);
    U8_AT(effect, 0x56) -= U8_AT(effect, 0x56) / S16_AT(effect, 0x1A);
    ticks_left = (u16)S16_AT(effect, 0x1A) - 1;
    S16_AT(effect, 0x1A) = ticks_left;
    ticks_test = ticks_left << 16;

    if (ticks_test <= 0) {
        U16_AT(effect, -2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
#include "dungeon/effect/sprite/create_radial_effect_from_source.h"
#include "modules/dungeon_native_abi.h"
#include "common.h"
#include "shared/game_work.h"

typedef struct S_80025E4C_0 {
    u8 pad_00[0x18];
    void * unk_18;
    u8 pad_1C[0x4];
    void * unk_20;
    u8 pad_24[0x4C];
    void * unk_70;
    u16 unk_74;
    u8 pad_76[0x2];
    void * unk_78;
    u16 unk_7C;
    u8 pad_7E[0x2];
    void * unk_80;
    u16 unk_84;
    u8 pad_86[0x2];
    void * unk_88;
    u16 unk_8C;
    u8 pad_8E[0x32];
    u32 unk_C0;
} S_80025E4C_0;   /* scratch in handle_project_linked_quads_queue_shaded_primitives_draw_modes_depth */

typedef struct S_80025E4C_1_pre {
    s32 unk_00;
    u8 pad_04[0x4];
} S_80025E4C_1_pre;   /* the 0x8 bytes before arg0 in handle_project_linked_quads_queue_shaded_primitives_draw_modes_depth, addressed as arg0[-1] */

typedef struct S_80025E4C_1 {
    u8 pad_00[0x30];
    void * unk_30;
    u16 unk_34;
    u8 pad_36[0x2];
    void * unk_38;
    u16 unk_3C;
    u8 pad_3E[0x2];
    void * unk_40;
    u16 unk_44;
    u8 pad_46[0x2];
    void * unk_48;
    u16 unk_4C;
    u8 pad_4E[0x2];
    s32 unk_50;
    s32 unk_54;
} S_80025E4C_1;   /* arg0 in handle_project_linked_quads_queue_shaded_primitives_draw_modes_depth */

typedef struct S_80025E4C_2 {
    u8 pad_00[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x4];
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80025E4C_2;   /* obj in handle_project_linked_quads_queue_shaded_primitives_draw_modes_depth */



extern s32 func_80066460(s32, s32, s32, s32);
extern void func_8006658C(void *, void *);

extern void func_80067F20(void *, s32, s32, u16, s32);

typedef struct GlobalState {
    u8 pad[0x8D0];
    void *next;
} GlobalState;


/* Project linked quads and queue their shaded primitives and draw modes by depth. */
s32 handle_project_linked_quads_queue_shaded_primitives_draw_modes_depth(void *quad) {
    GlobalState **render_states = ((GlobalState * *)(&g_game_work));
    u8 *scratch = (u8 *)0x1F800000;
    void *packet;
    u32 depth_bucket;
    s32 first_color;
    s32 second_color;
    s32 next_node;
    void *vertex3_xy;
    GlobalState *render_state;

    render_state = render_states[0];
    (*(void * *)((u8 *)scratch + 0x20)) = (u8 *)render_state + 0xB0;
    ((S_80025E4C_0 *)scratch)->unk_18 = render_state->next;
    do {
        packet = ((S_80025E4C_0 *)scratch)->unk_18;
        ((S_80025E4C_0 *)scratch)->unk_18 = (u8 *)packet + 0x24;
        ((S_80025E4C_0 *)scratch)->unk_70 = ((S_80025E4C_1 *)quad)->unk_30;
        ((S_80025E4C_0 *)scratch)->unk_78 = ((S_80025E4C_1 *)quad)->unk_38;
        ((S_80025E4C_0 *)scratch)->unk_80 = ((S_80025E4C_1 *)quad)->unk_40;
        vertex3_xy = ((S_80025E4C_1 *)quad)->unk_48;
        ((S_80025E4C_0 *)scratch)->unk_74 = ((S_80025E4C_1 *)quad)->unk_34;
        ((S_80025E4C_0 *)scratch)->unk_7C = ((S_80025E4C_1 *)quad)->unk_3C;
        ((S_80025E4C_0 *)scratch)->unk_84 = ((S_80025E4C_1 *)quad)->unk_44;
        ((S_80025E4C_0 *)scratch)->unk_88 = vertex3_xy;
        ((S_80025E4C_0 *)scratch)->unk_8C = ((S_80025E4C_1 *)quad)->unk_4C;
        depth_bucket = func_800654B0(scratch + 0x70, scratch + 0x78,
                              scratch + 0x80, scratch + 0x88,
                              (u8 *)packet + 8, (u8 *)packet + 0x10,
                              (u8 *)packet + 0x18, (u8 *)packet + 0x20,
                              scratch + 0x90, scratch + 0x94) - 8;
        ((S_80025E4C_0 *)scratch)->unk_C0 = depth_bucket;
        if (depth_bucket < 0x1E0U) {
            first_color = ((S_80025E4C_1 *)quad)->unk_50;
            ((S_80025E4C_2 *)packet)->unk_0C = first_color;
            ((S_80025E4C_2 *)packet)->unk_04.at00.v = first_color;
            second_color = ((S_80025E4C_1 *)quad)->unk_54;
            ((S_80025E4C_2 *)packet)->unk_1C = second_color;
            ((S_80025E4C_2 *)packet)->unk_14 = second_color;
            func_80066708(packet);
            ((S_80025E4C_2 *)packet)->unk_04.at03.v = (u8)(((S_80025E4C_2 *)packet)->unk_04.at03.v | 2);
            func_8006658C((u8 *)((S_80025E4C_0 *)scratch)->unk_20 +
                          (((S_80025E4C_0 *)scratch)->unk_C0 * 4), packet);
            packet = ((S_80025E4C_0 *)scratch)->unk_18;
            ((S_80025E4C_0 *)scratch)->unk_18 = (u8 *)packet + 0xC;
            func_80067F20(packet, 0, 0,
                          (u16)func_80066460(0, 1, 0, 0), 0);
            func_8006658C((u8 *)((S_80025E4C_0 *)scratch)->unk_20 +
                          (((S_80025E4C_0 *)scratch)->unk_C0 * 4), packet);
        }
        next_node = ((S_80025E4C_1_pre *)quad)[-1].unk_00;
        if (next_node == 0) {
            break;
        }
        quad = (void *)(next_node + 0x20);
    } while (1);
    render_states[0]->next =
        ((S_80025E4C_0 *)scratch)->unk_18;
    return 0;
}

#include "dungeon/effect/sprite/create_radial_effect_from_source.h"
#include "shared/sprite_frame_state.h"
#include "modules/dungeon_native_abi.h"
#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_func_81888810_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_func_81888810_1;

typedef struct S_func_81888810_3 {
    u8 pad_00[0x1A];
    s16 unk_1A;
    u8 pad_1C[0x14];
    s32 unk_30;
    u16 unk_34;
    u8 pad_36[0x2];
    s32 unk_38;
    u16 unk_3C;
    u8 pad_3E[0x2];
    s32 unk_40;
    u16 unk_44;
    u8 pad_46[0x2];
    s32 unk_48;
    u16 unk_4C;
    u8 pad_4E[0x2];
    s32 unk_50;
    s32 unk_54;
} S_func_81888810_3;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} Cell;

extern s32 rand(void);

extern s16 D_8002632A;
extern u8 D_80026470[];
extern u8 D_80026474[];
extern u8 D_80026478[];
extern Cell D_800264F8[];

#define SET_COUNT_PAGE() (count_page = (u8 *)&D_8002632A)
#define READ_COUNT_PAGE() (*(s16 *)count_page)

/* Create quad fragments from the vertex grid with randomized motion and rotation. */
void create_quad_fragments_vertex_grid_randomized_motion_rotation(void) {
    Cell *vertices;
    Cell *lower_right;
    Cell *lower_left;
    Cell *upper_right;
    ObjectNodeHeader *fragment;
    S_func_81888810_1 *motion;
    SpriteFrameState *angles;
    S_func_81888810_3 *quad;
    s32 quad_index;
    s32 row_start;
    s32 column_or_coord;
    s32 right_offset;
    s32 upper_right_y;
    s32 lower_left_y;
    s32 lower_right_y;
    s32 object_or_x;
    s32 upper_right_z;
    s32 lower_left_z;
    s32 lower_right_z;
    s32 addr_or_coord;
    s32 biased_index;
    u8 *count_page;

    for (quad_index = 0; quad_index < (s16)D_8002632A; quad_index++) {
        vertices = (Cell *)D_80026478;
        fragment = allocate_flagged_object_node(0x202);
        if (fragment != NULL) {
            object_or_x = (s32)fragment;
            fragment->unk_10 = handle_rotate_move_effect_quad_fade_colors_flag_lifetime_ends;
            register_node((void *)object_or_x, (s32)handle_project_linked_quads_queue_shaded_primitives_draw_modes_depth);

            row_start = quad_index & ~0xF;
            column_or_coord = (quad_index + 1) & 0xF;
            right_offset = (row_start + column_or_coord) * 8;
            upper_right = (Cell *)((unsigned long)right_offset + (unsigned long)vertices);
            lower_left = (Cell *)((unsigned long)((quad_index + 0x10) * 8) + (unsigned long)vertices);

            motion = fragment->unk_08;
            object_or_x = (vertices[quad_index].x + upper_right->x + lower_left->x + (lower_right = &vertices[row_start + 0x10 + column_or_coord])->x) >> 2;
            upper_right_y = (vertices[quad_index].y + upper_right->y + lower_left->y + lower_right->y) >> 2;
            lower_left_y = (vertices[quad_index].z + upper_right->z + lower_left->z + lower_right->z) >> 2;
            motion->unk_02 = object_or_x;
            motion->unk_06 = upper_right_y;
            motion->unk_0A = lower_left_y;

            motion->unk_0C = ((rand() & 0xF) - 8) << 0x10;
            motion->unk_10 = ((rand() & 0xF) - 8) << 0x10;
            motion->unk_14 = ((rand() & 0xF) - 8) << 0x10;

            angles = fragment->unk_0C;
            angles->angle_x = (rand() & 0x1FF) - 0x100;
            angles->angle_y = (rand() & 0x1FF) - 0x100;

            quad = (S_func_81888810_3 *)((u8 *)fragment + 0x20);
            quad->unk_1A = 0x20;
            quad->unk_30 = *(s32 *)&vertices[quad_index];
            quad->unk_34 = vertices[quad_index].z;
            quad->unk_38 = *(s32 *)upper_right;
            quad->unk_3C = upper_right->z;
            quad->unk_40 = *(s32 *)&D_800264F8[quad_index];
            quad->unk_44 = lower_left->z;
            quad->unk_48 = *(s32 *)((u8 *)D_800264F8 + right_offset);
            quad->unk_4C = lower_right->z;

            if ((quad_index % 32) < 0x10) {
                *(s32 *)((u8 *)quad + 0x50) = (*(s32 *)D_80026470);
                quad->unk_54 = (*(s32 *)D_80026474);
            } else {
                *(s32 *)((u8 *)quad + 0x54) = (*(s32 *)D_80026470);
                quad->unk_50 = (*(s32 *)D_80026474);
            }
        }
    }
    D_8002632A = 0;
}
#include "dungeon/effect/sprite/create_radial_effect_from_source.h"
#include "modules/dungeon_native_abi.h"
#include "common.h"

extern s32 try_trigger_target_record_effect(s32, s32);
extern s32 set_or_clear_actor_status_slot(s32, s32, s32);
extern void adjust_source_value_and_finalize(s32, void *);
extern u8 D_800E1D01[9];

/* Checks the target using a scaled low-byte value and conditionally applies D_800E1D01. */
void check_the_target_using_scaled_low_byte_conditionally_applies_global_800_e_1_d_01(s32 target, s32 value, void *unused) {
    u8 pinnedValue = value;
    if (try_trigger_target_record_effect(target, 2) == 0) {
        u32 scaledLowByte = pinnedValue;
        scaledLowByte >>= 2;
        if ((set_or_clear_actor_status_slot(target, 0x16, scaledLowByte + 4) << 16) != 0) {
            adjust_source_value_and_finalize(target, D_800E1D01);
        }
    }
}
