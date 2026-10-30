#include "shared/audio_commands.h"
#include "sdk/libc.h"
#include "dungeon/actor/status.h"
#include "dungeon/level.h"
#include "slus.h"
/* Map surface queries, particle bursts, owner-following effects, and linked mesh rendering. */

struct ObjectPosition;
#include "dungeon/effect/particle/impact.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/effect.h"

void (*const dungeon_19de800_entry)(struct S_func_80026418_0 *effect) = advance_particle_fade_and_cleanup;
typedef struct { s16 x, y; } BankDirections;
const BankDirections impact_grid_offsets[9] = {{-1,-1},{0,-1},{1,-1},{-1,0},{0,0},{1,0},{-1,1},{0,1},{1,1}};
const OffsetTable D_80024028 = {{{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}}};
#include "dungeon/effect/particle/impact.h"
#include "common.h"
#include "shared/game_work.h"

typedef struct S_func_80024064_0 {
    u8 pad_00[0x140];
    union { s16 s; u16 u; } unk_140;   /* accessed as both */
    union { s16 s; u16 u; } unk_142;   /* accessed as both */
    s32 unk_144;
    s32 unk_148;
    s32 unk_14C;
    s16 unk_150;
    union { s16 s; u16 u; } unk_152;   /* accessed as both */
    union {
        struct { u32 v; } at00;
        struct { s16 v; } at00u;
        struct { u16 v; } at00p;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_154;   /* overlapping accesses */
    union {
        struct { u32 v; } at00;
        struct { s16 v; } at00u;
        struct { u16 v; } at00p;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_158;   /* overlapping accesses */
    union {
        struct { u32 v; } at00;
        struct { s16 v; } at00u;
        struct { u16 v; } at00p;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_15C;   /* overlapping accesses */
    union {
        struct { u32 v; } at00;
        struct { s16 v; } at00u;
        struct { u16 v; } at00p;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_160;   /* overlapping accesses */
} S_func_80024064_0;   /* scratch in func_80024064 */

typedef struct S_func_80024064_2 {
    u16 unk_00;
    u16 unk_02;
} S_func_80024064_2;   /* map_entry in func_80024064 */

typedef struct S_func_80024064_3 {
    u8 pad_00[0x10];
    u16 unk_10;
} S_func_80024064_3;   /* best in func_80024064 */

typedef struct S_func_80024064_4 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    u8 pad_08[0x8];
    u16 unk_10;
    u8 pad_12[0x4];
    u8 unk_16;
    union { u8 u; s8 s; } unk_17;   /* accessed as both */
} S_func_80024064_4;   /* current in func_80024064 */

typedef struct S_func_80024064_5 {
    u32 unk_00;
} S_func_80024064_5;   /* copy_vertex in func_80024064 */

typedef struct S_func_80024064_6 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
} S_func_80024064_6;   /* plane_ptr in func_80024064 */

typedef struct S_func_80024064_7 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
} S_func_80024064_7;   /* dot_vertex in func_80024064 */

typedef struct S_func_80024064_8 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_func_80024064_8;   /* planes + ((S_func_80024064_3 *)best)->unk_10 * 8 in func_80024064 */

typedef struct S_func_80024064_9 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_func_80024064_9;   /* planes + ((S_func_80024064_4 *)current)->unk_10 * 8 in func_80024064 */

extern s32 are_quad_corner_turns_within_half_revolution(void *);

/* Finds a map polygon at the query position using containment and plane height. */
void *find_impact_surface_polygon(s32 world_x, s32 world_y, s16 min_height) {
    u8 *scratch;
    u8 *polygon;
    u8 *vertices;
    u8 *planes;
    u8 *best_polygon;
    u8 *map_entry;
    u8 *vertex;
    u8 *plane_vertex;
    MapGrid *map_data;
    u8 *plane;
    s16 cell_index;
    s32 height;
    u16 cell_x;
    u16 cell_y;

    scratch = (u8 *)0x1F800000;
    ((S_func_80024064_0 *)scratch)->unk_148 = 0x400;
    ((S_func_80024064_0 *)scratch)->unk_140.s = world_x & 0x3F;
    ((S_func_80024064_0 *)scratch)->unk_142.s = world_y & 0x3F;
    ((S_func_80024064_0 *)scratch)->unk_14C = min_height;

    cell_index = (u16)world_x >> 6;
    ((S_func_80024064_0 *)scratch)->unk_150 = cell_index;
    map_data = &g_game_work.map;
    cell_index += ((u16)world_y >> 6) << map_data->shiftX;
    (*(s16 *)((u8 *)scratch + 0x150)) = cell_index;
    map_entry = (u8 *)((long)cell_index * 6 +
                       (unsigned long)*(u8 **)((u8 *)(&g_game_work.map)));
    vertices = ((u8 *)map_data->vertices);
    planes = ((u8 *)map_data->surface_planes);
    best_polygon = 0;
    if (((S_func_80024064_2 *)map_entry)->unk_00 != 0) {
        ((S_func_80024064_0 *)scratch)->unk_152.s = -((S_func_80024064_2 *)map_entry)->unk_02;
        best_polygon = (*(u8 **)((u8 *)(((u8 **)map_data->cell_faces))
            + ((S_func_80024064_2 *)map_entry)->unk_00 * 4));
        polygon = best_polygon;
        if (((S_func_80024064_8 *)(planes + ((S_func_80024064_3 *)best_polygon)->unk_10 * 8))->unk_04
            < -0x7FF) {
            do {
                if ((((S_func_80024064_4 *)polygon)->unk_17.u & 1) == 0) {
                    cell_x = ((S_func_80024064_0 *)scratch)->unk_140.u;
                    cell_y = ((S_func_80024064_0 *)scratch)->unk_142.u;

                    vertex =
                        (u8 *)((unsigned long)((S_func_80024064_4 *)polygon)->unk_00 * 8 +
                               (unsigned long)vertices);
                    ((S_func_80024064_0 *)scratch)->unk_154.at00.v =
                        ((S_func_80024064_5 *)vertex)->unk_00;
                    ((S_func_80024064_0 *)scratch)->unk_154.at00u.v =
                        ((S_func_80024064_0 *)scratch)->unk_154.at00p.v - cell_x;
                    ((S_func_80024064_0 *)scratch)->unk_154.at02.v =
                        ((S_func_80024064_0 *)scratch)->unk_154.at02u.v - cell_y;

                    vertex =
                        (u8 *)((unsigned long)((S_func_80024064_4 *)polygon)->unk_02 * 8 +
                               (unsigned long)vertices);
                    ((S_func_80024064_0 *)scratch)->unk_158.at00.v =
                        ((S_func_80024064_5 *)vertex)->unk_00;
                    ((S_func_80024064_0 *)scratch)->unk_158.at00u.v =
                        ((S_func_80024064_0 *)scratch)->unk_158.at00p.v - cell_x;
                    ((S_func_80024064_0 *)scratch)->unk_158.at02.v =
                        ((S_func_80024064_0 *)scratch)->unk_158.at02u.v - cell_y;

                    vertex =
                        (u8 *)((unsigned long)((S_func_80024064_4 *)polygon)->unk_06 * 8 +
                               (unsigned long)vertices);
                    ((S_func_80024064_0 *)scratch)->unk_15C.at00.v =
                        ((S_func_80024064_5 *)vertex)->unk_00;
                    ((S_func_80024064_0 *)scratch)->unk_15C.at00u.v =
                        ((S_func_80024064_0 *)scratch)->unk_15C.at00p.v - cell_x;
                    ((S_func_80024064_0 *)scratch)->unk_15C.at02.v =
                        ((S_func_80024064_0 *)scratch)->unk_15C.at02u.v - cell_y;

                    vertex =
                        (u8 *)((unsigned long)((S_func_80024064_4 *)polygon)->unk_04 * 8 +
                               (unsigned long)vertices);
                    ((S_func_80024064_0 *)scratch)->unk_160.at00.v =
                        ((S_func_80024064_5 *)vertex)->unk_00;
                    ((S_func_80024064_0 *)scratch)->unk_160.at00u.v =
                        ((S_func_80024064_0 *)scratch)->unk_160.at00p.v - cell_x;
                    ((S_func_80024064_0 *)scratch)->unk_160.at02.v =
                        ((S_func_80024064_0 *)scratch)->unk_160.at02u.v - cell_y;

                    if (are_quad_corner_turns_within_half_revolution(scratch) != 0) {
                        plane =
                            (u8 *)((unsigned long)((S_func_80024064_4 *)polygon)->unk_10 *
                                   8 +
                                   (unsigned long)planes);
                        plane_vertex =
                            (u8 *)((unsigned long)((S_func_80024064_4 *)polygon)->unk_00 * 8 +
                                   (unsigned long)vertices);
                        height =
                            (((S_func_80024064_6 *)plane)->unk_00 *
                             (((S_func_80024064_7 *)plane_vertex)->unk_00 -
                              (s16)((S_func_80024064_0 *)scratch)->unk_140.u) +
                             ((S_func_80024064_6 *)plane)->unk_02 *
                             (((S_func_80024064_7 *)plane_vertex)->unk_02 -
                              (s16)((S_func_80024064_0 *)scratch)->unk_142.u) +
                             ((S_func_80024064_6 *)plane)->unk_04 *
                             ((S_func_80024064_7 *)plane_vertex)->unk_04) /
                            ((S_func_80024064_6 *)plane)->unk_04;
                        ((S_func_80024064_0 *)scratch)->unk_144 = height;
                        height += (s16)((S_func_80024064_0 *)scratch)->unk_152.u;
                        ((S_func_80024064_0 *)scratch)->unk_144 = height;
                        if (height >= ((S_func_80024064_0 *)scratch)->unk_14C &&
                            height < ((S_func_80024064_0 *)scratch)->unk_148) {
                            best_polygon = polygon;
                            ((S_func_80024064_0 *)scratch)->unk_148 = height;
                        }
                    }
                }

                if ((((S_func_80024064_4 *)polygon)->unk_16 & 0xF) == 1) {
                    if (((S_func_80024064_4 *)polygon)->unk_17.s < 0) {
                        break;
                    }
                    if ((((S_func_80024064_4 *)polygon)->unk_16 & 0xF0) != 0) {
                        polygon +=
                            ((((S_func_80024064_4 *)polygon)->unk_16 >> 4) * 3) * 8 + 0x18;
                        continue;
                    }
                }
                polygon += 0x18;
            } while (((S_func_80024064_9 *)(planes + ((S_func_80024064_4 *)polygon)->unk_10 * 8))->unk_04 <
                     -0x7FF);
        }
    }

    return best_polygon;
}

#include "common.h"
#include "shared/object_flags.h"

typedef struct S_80024398_0_pre {
    u16 unk_00;
} S_80024398_0_pre;   /* the 0x2 bytes before arg0 in scale_effect_by_phase, addressed as arg0[-1] */

typedef struct S_80024398_0 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0x4];
    union { s16 s; u16 u; } unk_28;   /* accessed as both */
} S_80024398_0;   /* arg0 in scale_effect_by_phase */

typedef struct S_80024398_1 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_80024398_1;   /* parent in scale_effect_by_phase */

typedef struct S_80024398_2 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_80024398_2;   /* node in scale_effect_by_phase */

/* Adjusts node scale by countdown phase, restoring unity and setting completion flags at the end. */
void scale_effect_by_phase(void *effect)
{
    u32 scale_x;
    u32 scale_y;
    s32 ticks_left;
    s16 next_ticks;
    u16 old_scale;
    u16 new_scale;
    S_80024398_2 *node;

    ticks_left = ((S_80024398_0 *)effect)->unk_28.s;
    impact_effect_update_flag = 1;

    {
        S_80024398_1 *parent;

        parent = ((S_80024398_0 *)effect)->unk_20;
        node = parent->unk_0C;
    }

    if (ticks_left >= 0x1F) {
        scale_x = node->unk_1C;
        scale_y = node->unk_1E;
        scale_x += 0x88;
        scale_y += 0x88;
        node->unk_1C = scale_x;
        node->unk_1E = scale_y;
    } else if (ticks_left >= 0x19) {
        scale_x = node->unk_1C - 0x88;
        scale_y = node->unk_1E - 0x88;
        node->unk_1C = scale_x;
        node->unk_1E = scale_y;
    } else if (ticks_left >= 0x10) {
        scale_x = node->unk_1C + 0x88;
        scale_y = node->unk_1E + 0x88;
        node->unk_1C = scale_x;
        node->unk_1E = scale_y;
    } else if (ticks_left >= 0xA) {
        scale_x = node->unk_1C - 0x88;
        scale_y = node->unk_1E - 0x88;
        node->unk_1C = scale_x;
        node->unk_1E = scale_y;
    } else {
        old_scale = node->unk_1C;
        if (old_scale < 0x1000U) {
            new_scale = old_scale + 0x88;
            node->unk_1C = new_scale;
            if ((u16)new_scale >= 0x1001U) {
                node->unk_1C = 0x1000U;
            }
        }

        old_scale = node->unk_1E;
        if (old_scale < 0x1000U) {
            new_scale = old_scale + 0x88;
            node->unk_1E = new_scale;
            if ((u16)new_scale >= 0x1001U) {
                node->unk_1E = 0x1000U;
            }
        }
    }

    next_ticks = ((S_80024398_0 *)effect)->unk_28.u - 1;
    ((S_80024398_0 *)effect)->unk_28.s = next_ticks;
    if ((next_ticks << 16) <= 0) {
        node->unk_1E = 0x1000U;
        node->unk_1C = 0x1000U;
        ((S_80024398_0_pre *)effect)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

#include "shared/object_node.h"
#include "common.h"
#include "shared/slus_callbacks.h"

typedef struct S_800244BC_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x4];
    s16 unk_28;
    s16 unk_2A;
} S_800244BC_0;

typedef struct S_800244BC_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800244BC_3;   /* arg1 in func_800244BC */

/* Creates an object at the supplied position and initializes its state and appearance. */
void create_scaling_impact_sprite(s32 state_value, S_800244BC_3 *source_pos)
{
    ObjectNodeHeader *object;
    S_800244BC_0 *state;
    ObjectPosition *position;
    SpriteFrameState *appearance;
    u16 render_flags;

    object = allocate_flagged_object_node(0x212);
    if (object != 0) {
        state = (u8 *)object + 0x20;
        state->unk_28 = 0x27;
        state->unk_2A = 0x27;
        state->unk_20 = state_value;
        object->update_callback = (void *)scale_effect_by_phase;
        register_node(object, project_sprite_chain);
        position = object->position;
        position->x.v = source_pos->unk_00;
        position->y.v = source_pos->unk_04;
        position->z.v = source_pos->unk_08;
        appearance = object->sprite;
        render_flags = appearance->flags;
        appearance->scale_y = 0x1000;
        appearance->scale_x = 0x1000;
        appearance->color.c.b = 0x80;
        appearance->color.c.g = 0x80;
        appearance->color.c.r = 0x80;
        appearance->flags = render_flags | 0x80;
    }
}

/* Selector 72, retail file [0x19DED8C, 0x19DEEB0); complete callable clone. */
#include "common.h"


/* Returns a uniform random sample in [0, limit) by rejection: the rand() bits are masked down to the
 * smallest bit range that covers limit, and the draw repeats while it is out of range.  Zero when limit is zero. */
s32 update_palette_particle_transition(s32 limit) {
    s32 sample;

    sample = 0;
    if (limit != 0) {
        if (limit < 5) {
            do {
                sample = (rand() & 0xC) >> 2;
            } while (sample >= limit);
            return sample;
        }
        if (limit < 0x11) {
            do {
                sample = (rand() & 0xF0) >> 4;
            } while (sample >= limit);
            return sample;
        }
        if (limit < 0x41) {
            do {
                sample = (rand() & 0xFC) >> 2;
            } while (sample >= limit);
            return sample;
        }
        if (limit < 0x101) {
            do {
                sample = (rand() & 0xFF0) >> 4;
            } while (sample >= limit);
            return sample;
        }
        if (limit < 0x1001) {
            do {
                sample = rand() & 0xFFF;
            } while (sample >= limit);
            return sample;
        }
        do {
            sample = rand() & 0xFFFF;
        } while (sample >= limit);
    }

    return sample;
}

#include "common.h"
#include "shared/object_flags.h"

extern void advance_sprite_animation_and_textures(void *visual);

/* Advance effect motion and animation, then mark it finished when its lifetime expires. */
void advance_effect_motion_and_animation(ImpactParticleWork *effect, ObjectPosition *position, SpriteFrameState *visual) {
    s32 accel_y;
    s32 accel_z;
    u16 frame_count;
    u16 frames_left;

    position->x.v += effect->velocity_x;
    position->y.v += effect->velocity_y;
    position->z.v += effect->velocity_z;
    accel_y = effect->accel_y;
    accel_z = effect->accel_z;
    effect->velocity_x += effect->accel_x;
    effect->velocity_y += accel_y;
    effect->velocity_z += accel_z;
    visual->scale_x -= 0xC8;
    visual->scale_y -= 0xC8;
    frame_count = effect->anim_ticks;
    impact_effect_update_flag = 1;
    frame_count += 1;
    effect->anim_ticks = frame_count;
    if (!(frame_count & 1)) {
        advance_sprite_animation_and_textures(visual);
    }
    frames_left = effect->ticks_left - 1;
    effect->ticks_left = frames_left;
    if ((frames_left << 0x10) <= 0) {
        *(u16 *)((u8 *)effect - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

#include "shared/object_node.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800247C0_0 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0x4];
    s16 unk_28;
} S_800247C0_0;   /* effect in shrink_effect_and_spawn_particles */

typedef struct S_800247C0_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_800247C0_1;   /* object in shrink_effect_and_spawn_particles */

typedef struct S_800247C0_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_800247C0_2;   /* origin in shrink_effect_and_spawn_particles */

typedef struct S_800247C0_5 {
    u8 pad_00[0x28];
    s16 unk_28;
    u8 pad_2A[0x5E];
    s32 unk_88;
    s32 unk_8C;
    s32 unk_90;
} S_800247C0_5;   /* particle_state in shrink_effect_and_spawn_particles */

typedef struct S_800247C0_7 {
    u8 pad_00[0x28];
    s8 unk_28;
    u8 pad_29[0x37];
    s32 unk_60;
    s16 unk_64;
} S_800247C0_7;   /* effect_state in shrink_effect_and_spawn_particles */


/* Shrink the effect, spawn inward-moving particles, and finish when its timer expires. */
void shrink_effect_and_spawn_particles(void *effect, void *origin)
{
    void *effect_state;
    u16 offset_x;
    s32 velocity_x;
    s16 next_timer;
    s16 color_channel;
    s16 particle_index;
    s32 offset_y;
    s32 offset_z;
    s32 random_bits;
    s32 completion_state;
    u16 next_scale_x;
    u16 next_scale_y;
    u32 scale_x;
    u16 scale_y;
    u16 timer;
    ObjectPosition *position;
    void *particle_state;
    SpriteFrameState *sprite;
    void *object;

    impact_effect_update_flag = 1;
    offset_x = (rand() & 0x3F) - 0x20;
    offset_y = (rand() & 0x3F) - 0x20;
    random_bits = rand();
    object = ((S_800247C0_0 *)effect)->unk_20;
    position = ((ObjectNodeHeader *)object)->position;
    sprite = ((ObjectNodeHeader *)object)->sprite;
    ((S_800247C0_2 *)origin)->unk_00.at00.v = position->x.v;
    ((S_800247C0_2 *)origin)->unk_04.at00.v = position->y.v;
    offset_z = (random_bits & 0x3F) - 0x20;
    ((S_800247C0_2 *)origin)->unk_08.at00.v = position->z.v;
    scale_x = sprite->scale_x;
    object += 0x20;
    effect_state = object;
    if (scale_x >= 0x801U) {
        next_scale_x = scale_x - 0x50;
        sprite->scale_x = next_scale_x;
        if ((u32)(next_scale_x & 0xFFFF) < 0x800U) {
            sprite->scale_x = 0x800U;
        }
    }
    scale_y = sprite->scale_y;
    if (scale_y >= 0x801U) {
        next_scale_y = scale_y - 0x50;
        sprite->scale_y = next_scale_y;
        if ((u32)(next_scale_y & 0xFFFF) < 0x800U) {
            sprite->scale_y = 0x800U;
        }
    }
    if (((S_800247C0_0 *)effect)->unk_28 >= 0xB) {
        particle_index = 0;
        for (; particle_index < 4; particle_index++) {
            object = allocate_flagged_object_node(0x212);
            if (object == NULL) {
                continue;
            }
            particle_state = object + 0x20;
            ((S_800247C0_5 *)particle_state)->unk_28 = 0x14;
            ((ObjectNodeHeader *)object)->update_callback = (void *)advance_effect_motion_and_animation;
            register_node(object, project_sprite_chain);
            sprite = ((ObjectNodeHeader *)object)->sprite;
            sprite->tpage_abr = 0x20;
            sprite->flags |= 0xC;
            position = ((ObjectNodeHeader *)object)->position;
            position->x.w.i =
                ((S_800247C0_2 *)origin)->unk_00.at02.v + offset_x;
            ((ObjectNodeHeader *)object)->position->y.w.i =
                ((S_800247C0_2 *)origin)->unk_04.at02.v + offset_y;
            ((ObjectNodeHeader *)object)->position->z.w.i =
                ((S_800247C0_2 *)origin)->unk_08.at02.v + offset_z - 0x10;
            velocity_x = 0 - ((s32)(offset_x << 0x10) >> 7);
            ((S_800247C0_5 *)particle_state)->unk_88 = velocity_x;
            ((S_800247C0_5 *)particle_state)->unk_8C =
                0 - ((s32)(offset_y << 0x10) >> 7);
            ((S_800247C0_5 *)particle_state)->unk_90 =
                0 - ((s32)(offset_z << 0x10) >> 7);
            sprite = ((ObjectNodeHeader *)object)->sprite;
            sprite->scale_y = 0x1000;
            sprite->scale_x = 0x1000;
            color_channel = update_palette_particle_transition(3);
            sprite->color.c.b = 0;
            sprite->color.c.g = 0;
            sprite->color.c.r = 0;
            if (color_channel == 0) {
                sprite->color.c.r = 0x10;
            }
            if (color_channel == 1) {
                sprite->color.c.g = 0x10;
            }
            if (color_channel == 2) {
                sprite->color.c.b = 0x10;
            }
            sprite->clut = 0x7DCF;
            sprite->flags |= 0x100;
            select_record_entry_and_value(sprite, effect_sprite_sources, 0);
        }
    }
    timer = ((S_800247C0_0 *)effect)->unk_28;
    next_timer = timer - 1;
    ((S_800247C0_0 *)effect)->unk_28 = next_timer;
    if ((next_timer << 0x10) <= 0) {
        ((S_800247C0_0 *)effect)->unk_28 = timer;
        if (g_dungeon_status.pending_display_owner == NULL) {
            g_dungeon_status.pending_display_owner = ((S_800247C0_0 *)effect)->unk_20;
        }
        object = ((S_800247C0_0 *)effect)->unk_20;
        set_or_clear_actor_status_slot(object + 0x20, 0x18, 0x14);
        ((S_800247C0_7 *)effect_state)->unk_28 = 0;
        completion_state = ((s32)dungeon_actor_ring_anchor);
        ((S_800247C0_7 *)effect_state)->unk_64 = -1;
        ((S_800247C0_7 *)effect_state)->unk_60 = completion_state;
        (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

#include "shared/object_node.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

extern void shrink_effect_and_spawn_particles(void *effect, void *origin);

typedef struct S_80024AE8_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x4];
    s16 unk_28;
    s16 unk_2A;
} S_80024AE8_0;

typedef struct S_80024AE8_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80024AE8_3;   /* arg1 in func_80024AE8 */

/* Create and initialize an effect at the supplied position. */
void create_shrinking_entry_particle_effect(s32 effect_value, S_80024AE8_3 *position) {
    ObjectNodeHeader *effect;
    S_80024AE8_0 *effect_state;
    ObjectPosition *effect_position;
    SpriteFrameState *render_state;

    effect = allocate_flagged_object_node(0x212);
    if (effect != 0) {
        effect_state = ((void *)effect) + 0x20;
        effect_state->unk_28 = 0x1E;
        effect_state->unk_2A = 0x1E;
        effect_state->unk_20 = effect_value;
        effect->update_callback = (void *)shrink_effect_and_spawn_particles;
        register_node(effect, project_sprite_chain);
        effect_position = effect->position;
        effect_position->x.v = (s32) position->unk_00;
        effect_position->y.v = (s32) position->unk_04;
        effect_position->z.v = (s32) position->unk_08;
        render_state = effect->sprite;
        render_state->flags = (u16) (render_state->flags | 0x80);
    }
}

/* Selector 72, retail file [0x19DF3A0, 0x19DF3F4); complete callable clone. */
#include "common.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"

/* Clears flag 0x2000 on every object in the circular list. */
void clear_circular_list_flags(void)
{
    ActorRecord *link;
    ObjectNodeHeader *object;
    ActorRecord *head;
    s32 link_value;
    s32 next;

    link = primary_actor_record;
    /* unk_5C links to the next object's header; its record follows the header */
    next = link->next_actor_header;
    link_value = (u32)link;
    next += 0x20;
    link = (ActorRecord *)next;
    if (link == (ActorRecord *)(u32)link_value) {
        return;
    }
    head = (ActorRecord *)(u32)link_value;
    do {
        object = (ObjectNodeHeader *)link - 1;
        next = object->flags;
        next &= 0xDFFF;
        object->flags = next;
        link_value = link->next_actor_header;
        link = (ActorRecord *)(link_value + 0x20);
    } while (link != head);
}

#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"

typedef struct S_80024BF4_0 {
    u8 pad_00[0x24];
    union { u8 * p; u32 * p2; } unk_24;   /* accessed as both */
    u16 unk_28;
    u8 pad_2A[0xA];
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    u8 pad_40[0x48];
    s32 unk_88;
    s32 unk_8C;
    s32 unk_90;
    u8 pad_94[0x10];
    u16 unk_A4;
    u16 unk_A6;
    u16 unk_A8;
    u8 pad_AA[0x6];
    u16 unk_B0;
    u16 unk_B2;
    u16 unk_B4;
    u8 pad_B6[0x2];
    u16 unk_B8;
    u16 unk_BA;
    u16 unk_BC;
    u8 pad_BE[0x2];
    u16 unk_C0;
    u16 unk_C2;
    u16 unk_C4;
    u8 pad_C6[0x2];
    u16 unk_C8;
    u16 unk_CA;
    u16 unk_CC;
    u8 pad_CE[0x32];
    s32 unk_100;
} S_80024BF4_0;   /* scratch in project_visible_textured_quad */



   /* *(u8 **)D_80083160 in project_visible_textured_quad */

typedef struct S_80024BF4_4 {
    u8 pad_00[0xC];
    u32 unk_0C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u8 pad_1C[0x1E];
    u8 unk_3A;
    u8 unk_3B;
    u16 unk_3C;
    u8 unk_3E;
    u8 unk_3F;
    u16 unk_40;
    u8 pad_42[0x2];
    u8 unk_44;
    u8 unk_45;
    u8 unk_46;
    u8 unk_47;
    u8 pad_48[0x2];
    u16 unk_4A;
    u16 unk_4C;
    u16 unk_4E;
    u16 unk_50;
    u16 unk_52;
    u16 unk_54;
    u16 unk_56;
    u16 unk_58;
    u16 unk_5A;
    u16 unk_5C;
    u16 unk_5E;
    u16 unk_60;
} S_80024BF4_4;   /* arg0 in project_visible_textured_quad */

typedef struct S_80024BF4_5 {
    u32 unk_00;
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
    u16 unk_08;
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u16 unk_0E;
    u32 unk_10;
    u16 unk_14;
    u16 unk_16;
    u8 unk_18;
    u8 unk_19;
    u16 unk_1A;
    u32 unk_1C;
    u16 unk_20;
    u16 unk_22;
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x2];
    u32 unk_28;
    u16 unk_2C;
    u16 unk_2E;
    u8 unk_30;
    u8 unk_31;
} S_80024BF4_5;   /* packet in project_visible_textured_quad */

typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} MATRIX;

extern void CompMatrix(void *, void *, void *);
extern void PushMatrix(void);
extern void PopMatrix(void);
extern void ReadRotMatrix(void *);
extern void SetRotMatrix(void *);
extern void SetTransMatrix(void *);
extern s32 RotAverage4(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void RotMatrix(void *, void *);
extern void SetPolyGT4(void *);

/* Projects a textured quad and adds it to the ordering table when visible. */
void project_visible_textured_quad(S_80024BF4_4 *quad, ObjectPosition *position, SpriteFrameState *render_state, s16 depth_bias)
{
    u8 *scratch = (u8 *)0x1F800000;
    u8 *packet;
    u8 *texture;
    s32 ot_index;
    u16 draw_flags;
    u8 texture_flags;
    MATRIX matrix;

    ((S_80024BF4_0 *)scratch)->unk_24.p = *(u8 **)&g_game_work.draw_buffer + 0xB0;
    ((S_80024BF4_0 *)scratch)->unk_88 = position->x.w.i;
    ((S_80024BF4_0 *)scratch)->unk_8C = position->y.w.i;
    ((S_80024BF4_0 *)scratch)->unk_90 = position->z.w.i;
    render_state->flags |= 0x8000;

    PushMatrix();

    ((S_80024BF4_0 *)scratch)->unk_3C = 0x2000;
    ((S_80024BF4_0 *)scratch)->unk_38 = 0x2000;
    ((S_80024BF4_0 *)scratch)->unk_34 = 0x2000;
    ((S_80024BF4_0 *)scratch)->unk_A4 = render_state->angle_x;
    ((S_80024BF4_0 *)scratch)->unk_A8 = render_state->angle_z;
    ((S_80024BF4_0 *)scratch)->unk_A6 = render_state->angle_y;
    RotMatrix(scratch + 0xA4, scratch + 0x74);
    ReadRotMatrix(&matrix);
    CompMatrix(&matrix, scratch + 0x74, scratch + 0x54);
    ScaleMatrix(scratch + 0x54, scratch + 0x34);
    SetTransMatrix(scratch + 0x54);
    SetRotMatrix(scratch + 0x54);

    texture = render_state->source;
    ((S_80024BF4_0 *)scratch)->unk_28 = render_state->flags;
    packet = ((GpuContext *)(*(u8 **)&g_game_work.draw_buffer))->packetCursor;
    ((GpuContext *)(*(u8 **)&g_game_work.draw_buffer))->packetCursor = packet + 0x34;

    ((S_80024BF4_0 *)scratch)->unk_B0 = quad->unk_4A;
    ((S_80024BF4_0 *)scratch)->unk_B8 = quad->unk_50;
    ((S_80024BF4_0 *)scratch)->unk_C0 = quad->unk_56;
    ((S_80024BF4_0 *)scratch)->unk_C8 = quad->unk_5C;
    ((S_80024BF4_0 *)scratch)->unk_B2 = quad->unk_4C;
    ((S_80024BF4_0 *)scratch)->unk_BA = quad->unk_52;
    ((S_80024BF4_0 *)scratch)->unk_C2 = quad->unk_58;
    ((S_80024BF4_0 *)scratch)->unk_CA = quad->unk_5E;
    ((S_80024BF4_0 *)scratch)->unk_B4 = quad->unk_4E;
    ((S_80024BF4_0 *)scratch)->unk_BC = quad->unk_54;
    ((S_80024BF4_0 *)scratch)->unk_C4 = quad->unk_5A;
    ((S_80024BF4_0 *)scratch)->unk_CC = quad->unk_60;

    ot_index = RotAverage4(scratch + 0xB0, scratch + 0xB8,
                             scratch + 0xC0, scratch + 0xC8,
                             packet + 8, packet + 0x14,
                             packet + 0x20, packet + 0x2C,
                             scratch + 0xD0, scratch + 0xD4) - depth_bias - 6;
    ((S_80024BF4_0 *)scratch)->unk_100 = ot_index;

    if ((u32)ot_index < 0x1E0) {
        if ((((u16)(((S_80024BF4_5 *)packet)->unk_08 + 0x20) < 0x181) &&
             ((u16)(((S_80024BF4_5 *)packet)->unk_0A + 0x20) < 0x121)) |
            (((u16)(((S_80024BF4_5 *)packet)->unk_14 + 0x20) < 0x181) &&
             ((u16)(((S_80024BF4_5 *)packet)->unk_16 + 0x20) < 0x121)) |
            (((u16)(((S_80024BF4_5 *)packet)->unk_20 + 0x20) < 0x181) &&
             ((u16)(((S_80024BF4_5 *)packet)->unk_22 + 0x20) < 0x121)) |
            (((u16)(((S_80024BF4_5 *)packet)->unk_2C + 0x20) < 0x181) &&
             ((u16)(((S_80024BF4_5 *)packet)->unk_2E + 0x20) < 0x121))) {
            render_state->flags &= 0x7FFF;
            ((S_80024BF4_5 *)packet)->unk_0E = quad->unk_3C;
            ((S_80024BF4_5 *)packet)->unk_1A = quad->unk_40;
            ((S_80024BF4_5 *)packet)->unk_0C = quad->unk_3A;
            ((S_80024BF4_5 *)packet)->unk_18 = quad->unk_3E;
            ((S_80024BF4_5 *)packet)->unk_24 = quad->unk_44;
            ((S_80024BF4_5 *)packet)->unk_30 = quad->unk_46;
            ((S_80024BF4_5 *)packet)->unk_0D = quad->unk_3B;
            ((S_80024BF4_5 *)packet)->unk_19 = quad->unk_3F;
            ((S_80024BF4_5 *)packet)->unk_25 = quad->unk_45;
            ((S_80024BF4_5 *)packet)->unk_31 = quad->unk_47;
            ((S_80024BF4_5 *)packet)->unk_04.at00.v = quad->unk_0C;
            ((S_80024BF4_5 *)packet)->unk_10 = quad->unk_10;
            ((S_80024BF4_5 *)packet)->unk_1C = quad->unk_14;
            ((S_80024BF4_5 *)packet)->unk_28 = quad->unk_18;

            SetPolyGT4(packet);

            texture_flags = texture[1];
            render_state->color.c.code = texture_flags;
            draw_flags = ((S_80024BF4_0 *)scratch)->unk_28;
            if (draw_flags & 8) {
                render_state->color.c.code = (draw_flags & 4) ?
                    (texture_flags | 2) : (texture_flags & 0xFD);
            }

            ((S_80024BF4_5 *)packet)->unk_04.at03.v |= render_state->color.c.code;
            ((S_80024BF4_5 *)packet)->unk_00 = (((S_80024BF4_5 *)packet)->unk_00 & 0xFF000000) |
                ((*(u32 *)((u8 *)(((S_80024BF4_0 *)scratch)->unk_24.p2)
                    + ((S_80024BF4_0 *)scratch)->unk_100 * 4)) & 0x00FFFFFF);

            (*(u32 *)((u8 *)(((S_80024BF4_0 *)scratch)->unk_24.p2) + ((S_80024BF4_0 *)scratch)->unk_100 * 4)) =
                ((*(u32 *)((u8 *)(((S_80024BF4_0 *)scratch)->unk_24.p2)
                    + ((S_80024BF4_0 *)scratch)->unk_100 * 4)) & 0xFF000000) |
                ((u32)packet & 0x00FFFFFF);
        }
    }

    PopMatrix();
}

/* Selector 72, retail file [0x19DF834, 0x19DF888); complete callable clone. */
#include "common.h"
#include "shared/object_node.h"

/* Draw each linked mesh with zero depth bias; follow the node stored before its mesh. */
s32 draw_linked_meshes(void *initial_mesh, void *transform, void *object) {
    void *mesh = initial_mesh;
    ObjectNodeHeader *node;

    for (;;) {
        project_visible_textured_quad(mesh, transform, object, 0);
        /* the preceding header's +0x18 holds the next node */
        node = ((ObjectNodeHeader *)mesh - 1)->chain_next;
        if (node == 0) {
            return 0;
        }
        mesh = node + 1;
        transform = node->position;
        object = node->sprite;
    }
}

#include "common.h"
#include "shared/object_flags.h"

extern void advance_sprite_animation_and_textures(void *render_state);

/* Updates motion and rotation and marks the object finished when flagged or expired. */
void advance_rotating_ballistic_particle_and_expire(ImpactParticleWork *state, ObjectPosition *position, SpriteFrameState *render_state) {
    s32 x_step;
    s32 y_step;
    s32 z_step;
    u16 end_flag;
    u16 ticks_left;
    u16 frame_count;

    frame_count = state->anim_ticks;
    impact_effect_update_flag = 1;
    frame_count = frame_count + 1;
    state->anim_ticks = frame_count;
    if (!(frame_count & 1)) {
        advance_sprite_animation_and_textures(render_state);
    }
    if (state->rotation_axis == 0) {
        render_state->angle_x = render_state->angle_x + 0x190;
    }
    if (state->rotation_axis == 1) {
        render_state->angle_z = render_state->angle_z + 0x190;
    }
    x_step = state->velocity_x;
    state->velocity_z += state->accel_z;
    if (x_step < 0) {
        x_step += 0xFFFF;
    }
    position->x.w.i = (u16)position->x.w.i + (x_step >> 16);
    y_step = state->velocity_y;
    if (y_step < 0) {
        y_step += 0xFFFF;
    }
    position->y.w.i = (u16)position->y.w.i + (y_step >> 16);
    z_step = state->velocity_z;
    if (z_step < 0) {
        z_step += 0xFFFF;
    }
    position->z.w.i = (u16)position->z.w.i + (z_step >> 16);
    end_flag = render_state->flags & 0x8000;
    render_state->flags = end_flag;
    if ((end_flag != 0) || (ticks_left = state->ticks_left - 1,
                            state->ticks_left = ticks_left,
                            ((ticks_left << 16) <= 0))) {
        *(u16 *)((u8 *)state - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

#include "shared/object_node.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"

typedef struct S_800251F4_0 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u8 unk_10;
    u8 unk_11;
    u8 unk_12;
    u8 pad_13[0x1];
    u8 unk_14;
    u8 unk_15;
    u8 unk_16;
    u8 pad_17[0x1];
    u8 unk_18;
    u8 unk_19;
    u8 unk_1A;
    u8 pad_1B[0xD];
    s16 unk_28;
    u8 pad_2A[0x2];
    s16 unk_2C;
    u8 pad_2E[0xC];
    u8 unk_3A;
    u8 unk_3B;
    u8 pad_3C[0x2];
    u8 unk_3E;
    u8 unk_3F;
    u8 pad_40[0x4];
    u8 unk_44;
    u8 unk_45;
    u8 unk_46;
    u8 unk_47;
    u8 pad_48[0x2];
    s16 unk_4A;
    s16 unk_4C;
    s16 unk_4E;
    s16 unk_50;
    s16 unk_52;
    s16 unk_54;
    s16 unk_56;
    s16 unk_58;
    s16 unk_5A;
    s16 unk_5C;
    s16 unk_5E;
    s16 unk_60;
    u8 pad_62[0x1A];
    s32 unk_7C;
    s32 unk_80;
    s32 unk_84;
    u8 pad_88[0x8];
    s32 unk_90;
} S_800251F4_0;   /* work in spawn_randomized_textured_particles */

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} RECT;
/* the 0x18-byte UV block func_80024064 returns, copied into the particle at +0x52 */
typedef struct {
    s16 v[12];
} QuadUV;


/* Spawns four textured particles with randomized positions, motion, and rotation. */
void spawn_randomized_textured_particles(s32 unused, s32 center_x, s16 center_y, s16 center_z)
{
    s32 saved_x;
    s16 iteration;
    ObjectNodeHeader *particle;
    u8 *particle_work;
    SpriteFrameState *transform;
    void *quad_template;
    s32 tile_u;
    s32 tile_v;
    s32 uv_span;
    s32 tile_size;
    s32 min_u;
    u16 end_u;
    s32 min_v;
    u16 end_v;
    s32 tile_offset;
    s32 uv_scratch;
    s32 tile_end_offset;
    s16 tile_max;
    s16 tile_min;
    s32 brightness;
    s32 position_jitter;
    s32 min_x;
    s16 quad_word_4;

    iteration = 0;
    saved_x = center_x;
    brightness = 0x80;
    do {
        particle = allocate_flagged_object_node(0x212);
        particle_work = (u8 *)particle + 0x20;
        if (particle != 0) {
            ((S_800251F4_0 *)particle_work)->unk_28 = 0x78;
            ((S_800251F4_0 *)particle_work)->unk_2C = rand() & 1;
            particle->update_callback = (void *)advance_rotating_ballistic_particle_and_expire;
            register_node(particle, draw_linked_meshes);

            transform = particle->sprite;
            transform->tpage_abr = 0x20;
            transform->flags |= 0xC;

            position_jitter = rand();
            min_x = saved_x - 0x20;
            (particle->position)->x.w.i = min_x + (position_jitter & 0x3F);
            position_jitter = rand() & 0x3F;
            quad_word_4 = center_y - 0x20;
            (particle->position)->y.w.i = quad_word_4 + position_jitter;
            (particle->position)->z.w.i = center_z;
            quad_template = find_impact_surface_polygon((u16)saved_x, (u16)center_y, center_z);
            *(QuadUV *)((u8 *)particle + 0x52) = *(QuadUV *)quad_template;

            if (((S_800251F4_0 *)particle_work)->unk_3A > ((S_800251F4_0 *)particle_work)->unk_44) {
                min_u = ((S_800251F4_0 *)particle_work)->unk_44;
                end_u = ((S_800251F4_0 *)particle_work)->unk_3A + 1;
            } else {
                min_u = ((S_800251F4_0 *)particle_work)->unk_3A;
                end_u = ((S_800251F4_0 *)particle_work)->unk_44 + 1;
            }

            if (((S_800251F4_0 *)particle_work)->unk_3B > ((S_800251F4_0 *)particle_work)->unk_3F) {
                min_v = ((S_800251F4_0 *)particle_work)->unk_3F;
                end_v = ((S_800251F4_0 *)particle_work)->unk_3B + 1;
            } else {
                min_v = ((S_800251F4_0 *)particle_work)->unk_3B;
                end_v = ((S_800251F4_0 *)particle_work)->unk_3F + 1;
            }

            tile_u = rand() & 3;
            tile_v = rand() & 3;
            uv_span = end_u - min_u;
            if (uv_span < 0) {
                uv_span += 3;
            }
            tile_offset = tile_u;
            uv_scratch = tile_offset + 1;
            tile_size = uv_span >> 2;
            tile_end_offset = uv_scratch * tile_size;
            tile_offset = tile_offset * tile_size;
            uv_span = end_v - min_v;
            uv_scratch = min_u;
            tile_max = uv_scratch + tile_end_offset;
            tile_max -= 1;
            ((S_800251F4_0 *)particle_work)->unk_3E = tile_max;
            ((S_800251F4_0 *)particle_work)->unk_3A = tile_max;
            tile_min = uv_scratch + tile_offset;
            ((S_800251F4_0 *)particle_work)->unk_46 = tile_min;
            ((S_800251F4_0 *)particle_work)->unk_44 = tile_min;

            if (uv_span < 0) {
                uv_span += 3;
            }
            tile_offset = tile_v;
            uv_scratch = tile_offset + 1;
            tile_size = uv_span >> 2;
            tile_end_offset = uv_scratch * tile_size;
            tile_offset = tile_offset * tile_size;
            uv_scratch = min_v;
            tile_max = uv_scratch + tile_end_offset;
            tile_max -= 1;
            ((S_800251F4_0 *)particle_work)->unk_47 = tile_max;
            ((S_800251F4_0 *)particle_work)->unk_3F = tile_max;
            tile_min = uv_scratch + tile_offset;
            ((S_800251F4_0 *)particle_work)->unk_45 = tile_min;
            ((S_800251F4_0 *)particle_work)->unk_3B = tile_min;

            transform = particle->sprite;
            transform->scale_y = 0x1000;
            transform->scale_x = 0x1000;

            ((S_800251F4_0 *)particle_work)->unk_4A = (rand() & 3) - 5;
            ((S_800251F4_0 *)particle_work)->unk_4C = (rand() & 3) - 2;
            ((S_800251F4_0 *)particle_work)->unk_4E = (rand() & 3) - 5;
            ((S_800251F4_0 *)particle_work)->unk_50 = (rand() & 3) + 1;
            ((S_800251F4_0 *)particle_work)->unk_52 = (rand() & 3) - 2;
            ((S_800251F4_0 *)particle_work)->unk_54 = (rand() & 3) - 5;
            ((S_800251F4_0 *)particle_work)->unk_56 = (rand() & 3) - 5;
            ((S_800251F4_0 *)particle_work)->unk_58 = (rand() & 3) - 2;
            ((S_800251F4_0 *)particle_work)->unk_5A = (rand() & 3) + 1;
            ((S_800251F4_0 *)particle_work)->unk_5C = (rand() & 3) + 1;
            ((S_800251F4_0 *)particle_work)->unk_5E = (rand() & 3) - 2;
            ((S_800251F4_0 *)particle_work)->unk_60 = (rand() & 3) + 1;

            ((S_800251F4_0 *)particle_work)->unk_0E = brightness;
            ((S_800251F4_0 *)particle_work)->unk_0D = brightness;
            ((S_800251F4_0 *)particle_work)->unk_0C = brightness;
            ((S_800251F4_0 *)particle_work)->unk_12 = brightness;
            ((S_800251F4_0 *)particle_work)->unk_11 = brightness;
            ((S_800251F4_0 *)particle_work)->unk_10 = brightness;
            ((S_800251F4_0 *)particle_work)->unk_16 = brightness;
            ((S_800251F4_0 *)particle_work)->unk_15 = brightness;
            ((S_800251F4_0 *)particle_work)->unk_14 = brightness;
            ((S_800251F4_0 *)particle_work)->unk_1A = brightness;
            ((S_800251F4_0 *)particle_work)->unk_19 = brightness;
            ((S_800251F4_0 *)particle_work)->unk_18 = brightness;

            transform->angle_x = rand() & 0xFFF;
            transform->angle_y = rand() & 0xFFF;
            transform->angle_z = rand() & 0xFFF;
            ((S_800251F4_0 *)particle_work)->unk_7C = ((rand() & 0x7FFF) - 0x4000) << 5;
            ((S_800251F4_0 *)particle_work)->unk_80 = ((rand() & 0x7FFF) - 0x4000) << 5;
            ((S_800251F4_0 *)particle_work)->unk_84 =
                (((rand() & 0x7FFF) - 0x6000) << 6) + (s32)0xFFFE0000;
            ((S_800251F4_0 *)particle_work)->unk_90 = 0x10000;

            transform->color.c.b = brightness;
            transform->color.c.g = brightness;
            transform->color.c.r = brightness;
            select_record_entry_and_value(transform, effect_sprite_sources, 0);
        }
        tile_max = iteration + 1;
        iteration = tile_max;
    } while (tile_max < 4);
}

#include "common.h"


/* Applies a coordinate update and triggers effects when the queried value is within bounds. */
void update_timed(s32 object, s32 raw_x, s32 raw_y, s32 raw_upper, s16 lower_bound) {
    s32 x = raw_x;
    s32 y = raw_y;
    u16 call_x = x;
    u16 call_y = y;
    s32 object_data = object + 0x20;
    s32 upper = (s16)raw_upper;
    s32 shifted_lower;
    s32 lower;
    s32 query_x;
    s32 query_y;
    s16 query_value;

    if (upper < 0x200) {
        query_x = call_x & 0xFFFF;
        query_y = call_y & 0xFFFF;
        shifted_lower = lower_bound << 16;
        lower = shifted_lower >> 16;
        query_value = sample_terrain_surface_height(query_x, query_y, lower);
        if (query_value < upper && query_value >= lower) {
            raw_x = (s16)x;
            raw_y = (s16)y;
            spawn_randomized_textured_particles(object_data, raw_x, raw_y, upper);
            initialize_timed_motion_step(6, 12);
            play_sound_if_enabled(0x50B);
        }
    }
}

#include "common.h"

typedef struct S_func_80025710_0 {
    u8 pad_00[0x8];
    void *unk_08;
    void *unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_func_80025710_0;

typedef struct S_func_80025710_1 {
    u8 pad_00[0x5C];
    s32 unk_5C;
} S_func_80025710_1;

typedef struct S_func_80025710_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_func_80025710_2;

typedef struct S_func_80025710_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_func_80025710_3;

/* Mark and process entries at the given coordinates with thresholds in the specified range. */
void process_entries_at_coordinates(void *list_head, s32 x, s32 y, s16 upper_bound, s16 lower_bound) {
    s32 match_x = x;
    s32 match_y = y;
    s32 upper_limit;
    s32 lower_limit;
    s16 threshold;
    u16 flags;
    S_func_80025710_2 *range_data;
    S_func_80025710_3 *position_data;
    S_func_80025710_0 *entry;
    S_func_80025710_1 *list_link;
    void *head;

    list_link = list_head;
    head = list_link;
    list_head = list_link->unk_5C;
    list_link = list_head + 0x20;
    list_head = list_link;
    if (list_link != head) {
        upper_limit = (s16)upper_bound;
        lower_limit = lower_bound;
        entry = (void *)list_head - 0x20;
        do {
            void *next_entry;
            position_data = ((S_func_80025710_0 *)((u8 *)list_link - 0x20))->unk_0C;
            range_data = entry->unk_08;
            if ((position_data->unk_24 == (match_x & 0xFFFF)) &&
                (position_data->unk_25 == (match_y & 0xFFFF))) {
                threshold = range_data->unk_0A;
                if ((upper_limit >= threshold) && (lower_limit < threshold)) {
                    flags = entry->unk_1E;
                    if (!(flags & 0x2000)) {
                        entry->unk_1E = flags | 0x2000;
                        create_shrinking_entry_particle_effect(entry, range_data);
                    }
                }
                next_entry = list_link->unk_5C;
                list_link = next_entry + 0x20;
            } else {
                next_entry = list_link->unk_5C;
                list_link = next_entry + 0x20;
            }
            entry = (void *)list_link - 0x20;
        } while (list_link != head);
    }
}

#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"

typedef struct {
    u16 x;
    u16 y;
} LocalPoint;

typedef struct {
    LocalPoint point[3][3];
} LocalPoints;

typedef struct {
    s32 value;
} __attribute__((packed)) PackedWord;

typedef struct {
    u8 bytes[16];
} __attribute__((packed)) Packed16;

typedef struct {
    s32 words[4];
} Aligned16;

#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))

extern void update_timed(s32 object, s32 raw_x, s32 raw_y, s32 raw_upper, s16 lower_bound);
extern void process_entries_at_coordinates(void *list_head, s32 x, s32 y, s16 upper_bound, s16 lower_bound);

extern s16 D_8002992C;


/* The leading 0x20 bytes receive the expanded sprite-entry transform. */
typedef struct OwnerFollowingWork {
    u8 transform[0x20];
    ObjectNodeHeader *owner;
    u8 pad_24[8];
    union { s16 s; u16 u; } state;
    u8 pad_2E[2];
    u16 move_ticks;
    u16 anim_ticks;
    s16 entry_step;
    u8 pad_36[2];
    s16 max_index;
    s16 min_index;
    u8 pad_3C[0x14];
    s32 rise_speed;
    u8 pad_54[8];
    s32 rise_accel;
} OwnerFollowingWork;

/* Updates an owner-following effect or its fade, wait, and rising phases. */
void update_owner_following_effect(OwnerFollowingWork *effect_in, ObjectPosition *position_in, SpriteFrameState *visual_in)
{
    LocalPoints offsets;
    u8 *copy_src;
    ObjectNodeHeader *owner;
    ObjectPosition *owner_pos;
    SpriteFrameState *owner_visual;
    u8 *world;
    s32 fade;
    s32 half_tile;
    u16 flags;
    s32 state;
    s32 rise_speed;
    s16 column;
    s16 row;
    s16 next_tick;
    s32 move_ticks;
    s32 anim_ticks;
    LocalPoint *point;

    copy_src = (u8 *)&impact_grid_offsets;
    offsets = *(LocalPoints *)copy_src;

    impact_effect_update_flag = 1;
    half_tile = 0x20;
    visual_in->tpage_abr = half_tile;
    visual_in->flags |= 0xC;
    owner = effect_in->owner;
    world = ((u8 *)primary_actor_record);

    if (owner == 0) {
        state = effect_in->state.s;
        switch (state) {
        case 0:
            move_ticks = effect_in->move_ticks;
            anim_ticks = effect_in->anim_ticks;
            move_ticks--;
            anim_ticks++;
            effect_in->anim_ticks = anim_ticks;
            anim_ticks = (anim_ticks << 16) >> 16;
            effect_in->move_ticks = move_ticks;
            if (anim_ticks < 0x19) {
                fade = anim_ticks << 8;
                visual_in->offset_x = fade;
                visual_in->scale_y = fade;
                visual_in->scale_x = fade;
                effect_in->min_index = 0;
                effect_in->max_index = 1;
                effect_in->entry_step = 1;
                resolve_and_step_entry_index(visual_in, &effect_in->entry_step,
                              effect_in->min_index, effect_in->max_index);
                copy_and_expand_effect_record(effect_in, visual_in->unk_00);
                break;
            }
            effect_in->move_ticks = 0;
            effect_in->anim_ticks = 0;
            effect_in->state.u = effect_in->state.u + 1;
            break;
        case 1:
            next_tick = effect_in->anim_ticks + 1;
            effect_in->anim_ticks = next_tick;
            if (next_tick & 1) {
                effect_in->min_index = state;
                effect_in->max_index = 0xF;
                effect_in->entry_step = state;
                resolve_and_step_entry_index(visual_in, &effect_in->entry_step,
                              effect_in->min_index, effect_in->max_index);
                copy_and_expand_effect_record(effect_in, visual_in->unk_00);
            }
            if ((s16)primary_actor_record->action_timer.u == 0) {
                effect_in->move_ticks = 0;
                effect_in->rise_speed = 0x200000;
                effect_in->rise_accel = 0;
                effect_in->state.u = effect_in->state.u + 1;
            }
            break;
        case 2:
        {
            s16 base_x;
            s16 base_y;
            s32 pos_x;
            s32 pos_y;
            s32 biased_x;
            s32 biased_y;

            position_in->velocity_z = position_in->z.v;
            rise_speed = effect_in->rise_speed + effect_in->rise_accel;
            effect_in->rise_speed = rise_speed;
            position_in->z.v += rise_speed;
            pos_x = position_in->x.w.i;
            biased_x = pos_x - 0x20;
            if (biased_x < 0) {
                biased_x = pos_x + 0x1F;
            }
            pos_y = position_in->y.w.i;
            biased_y = pos_y - 0x20;
            if (biased_y < 0) {
                biased_y = pos_y + 0x1F;
            }
            base_x = (u32)biased_x >> 6;
            base_y = (u32)biased_y >> 6;

            column = 0;
            do {
                row = 0;
                do {
                    s32 point_offset;
                    s32 offset_x;
                    u16 tile_x;
                    u16 tile_y;
                    point_offset = column * sizeof(LocalPoint) +
                                   row * 3 * sizeof(LocalPoint);
                    point = (LocalPoint *)((u8 *)&offsets + point_offset);
                    process_entries_at_coordinates(world,
                                  (tile_x = point->x, tile_x = (base_x + tile_x) & 0xFFFF),
                                  (tile_y = base_y + point->y),
                                  position_in->z.w.i,
                                  (s16)((u16)position_in->z.w.i - 0x40));
                    offset_x = (s16)point->x;
                    update_timed((u8 *)effect_in - 0x20,
                                  (s16)((u16)position_in->x.w.i + (offset_x << 6)),
                                  (s16)((u16)position_in->y.w.i + ((s32)(point->y << 16) >> 10)),
                                  position_in->z.w.i, S16_AT(position_in, 0x16));
                    row++;
                } while (row < 3);
            } while (++column < 3);

            next_tick = effect_in->move_ticks + 1;
            effect_in->move_ticks = next_tick;
            if (next_tick >= 0x28) {
                D_8002992C = 0;
                D_80028630 = 0;
                U16_AT(effect_in, -2) |= NODE_REMOVE;
                object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            }
        }
            break;
        }
    } else {
        if (owner->flags & 0x8000) {
            U16_AT(effect_in, -2) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            return;
        }
        owner_pos = owner->position;
        position_in->x.w.i = (u16)owner_pos->x.w.i;
        position_in->y.w.i = (u16)owner_pos->y.w.i;
        position_in->z.w.i = (u16)owner_pos->z.w.i;
        owner = effect_in->owner;
        flags = visual_in->flags;
        owner_visual = owner->sprite;
        flags |= 0xC;
        visual_in->flags = flags;
        visual_in->tpage_abr = half_tile;
        set_mesh_entry_address(visual_in, owner_visual->unk_04);
        copy_and_expand_effect_record(effect_in, visual_in->unk_00);
        visual_in->scale_x = owner_visual->scale_x;
        visual_in->scale_y = owner_visual->scale_y;
        visual_in->offset_x = owner_visual->offset_x;
        visual_in->color.word = owner_visual->color.word;
        visual_in->angle_x = owner_visual->angle_x;
        visual_in->angle_y = owner_visual->angle_y;
        visual_in->angle_z = owner_visual->angle_z;
    }
}

#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"

typedef unsigned long uptr;

typedef struct {
    u8 bytes[12];
} __attribute__((packed)) Copy12;

typedef struct {
    u8 bytes[8];
} __attribute__((packed)) Copy8;

typedef struct {
    Copy12 first;
    Copy12 second;
    Copy8 third;
} __attribute__((packed)) Copy32;

typedef struct {
    u8 pad0[8];
    void *part8;
    void *partC;
    void *part10;
} Object;

extern void *allocate_list_node(s32, void *);

extern u8 D_80028664[];
s32 draw_linked_model_chain(void *, s32, void *);

typedef struct S_80025CE8_0 {
    s16 unk_00;
    u16 unk_02;
    u8 pad_04[0x1C];
    Object * unk_20;
    u8 pad_24[0xC];
    s16 unk_30;
    u8 pad_32[0x4];
    u16 unk_36;
    s16 unk_38;
    s16 unk_3A;
} S_80025CE8_0;   /* entry in func_80025CE8 */



typedef struct S_80025CE8_3_pre {
    void * unk_00;
    u8 pad_04[0x79CC];
} S_80025CE8_3_pre;   /* the 0x79D0 bytes before alloc_page in func_80025CE8, addressed as alloc_page[-1] */

typedef struct S_80025CE8_4 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_80025CE8_4;   /* cleanup in func_80025CE8 */

/* Creates 21 linked objects at an angle-dependent offset, marking them for cleanup if allocation fails. */
s32 func_80025CE8(x, y, z, angle)
u16 x;
u16 y;
u16 z;
u16 angle;
{
    Object *objects[21];
    Copy32 direction_offsets;
    u8 *table_page;
    u32 object_index;
    Object **slot;
    ObjectNodeHeader *new_object;
    Object *cleanup_object;
    Object *current_object;
    ObjectPosition *position;
    SpriteFrameState *render;
    s32 x_offset;
    u16 y_offset;
    u8 *data_entry;
    u8 *data_entry_2;

    s32 slot_offset;

    s32 failure_index;
    s32 failure_test;
    s32 flag_work;
    s32 index_offset;
    s32 asset_offset;
    u16 render_flags;
    u16 cleanup_flags;
    s32 color;
    uptr alloc_parent;
    s32 predecessor_test;
    u8 *alloc_page;

    *(Copy32 *)&direction_offsets = *(Copy32 *)&D_80024028;
    object_index = 0;
    do {
        if (((u32)(u16)object_index << 16) != 0) {
            alloc_page = (u8 *)0x80080000;
            alloc_parent = (uptr)objects[0];
        } else {
            alloc_page = (u8 *)0x80080000;
            alloc_parent = (uptr)&scene_object_list_anchor;
        }
        new_object = allocate_list_node(0x12, (Object *)alloc_parent);
        index_offset = ((s32)(s16)object_index) << 2;
        slot = (Object **)((uptr)index_offset + (uptr)objects);
        *slot = new_object;
        if (new_object != 0) {
            color = 0x800000;
            new_object->update_callback = (void *)update_owner_following_effect;
            color |= 0x8080;
            data_entry_2 = (u8 *)&direction_offsets + ((angle >> 7) & 0x1C);
            x_offset = ((S_80025CE8_0 *)data_entry_2)->unk_00;
            position = (*slot)->part8;
            position->x.w.i = x + (x_offset << 7);
            y_offset = ((S_80025CE8_0 *)data_entry_2)->unk_02;
            position->z.w.i = z - 0x90;
            position->y.w.i = y + (((s32)y_offset << 16) >> 9);

            render = (*slot)->partC;
            asset_offset = (s32)(s16)object_index * 0x10;
            render->angle_z = angle - 0x400;
            render->angle_x = 0x400;
            render->offset_x = 0x1000;
            render->scale_y = 0x1000;
            render->scale_x = 0x1000;
            render->source = D_80028664 + asset_offset;
            render_flags = render->flags;
            render->tpage_abr = 0x20;
            render->color.word = color;
            render_flags |= 0xC;
            render->flags = render_flags;
            register_node(*slot, draw_linked_model_chain);

            current_object = *slot;
            data_entry = (u8 *)current_object + 0x20;
            if ((s16)object_index != 0) {
                ((S_80025CE8_0 *)data_entry)->unk_20 = objects[0];
            } else {
                alloc_page = (u8 *)&D_80028630 + 0x79D0;
                ((S_80025CE8_3_pre *)alloc_page)[-1].unk_00 = position;
            }
            render->scale_y = 0;
            render->scale_x = 0;
            render->offset_x = 0;
            ((S_80025CE8_0 *)data_entry)->unk_30 = 0x3C;
            ((S_80025CE8_0 *)data_entry)->unk_36 = angle;
            ((S_80025CE8_0 *)data_entry)->unk_3A = 0;
            ((S_80025CE8_0 *)data_entry)->unk_38 = 0xF;
        } else {
            failure_index = object_index - 1;
            failure_test = failure_index << 16;
            object_index = failure_index;
            failure_index = failure_test;
            if (failure_index >= 0) {
                do {
                    slot_offset = (s32)((u32)object_index << 16);
                    alloc_parent = object_index - 1;
                    predecessor_test = (s32)(alloc_parent << 16);
                    object_index = alloc_parent;
                    slot_offset >>= 14;
                    alloc_page = (u8 *)((uptr)slot_offset + (uptr)objects);
                    alloc_parent = predecessor_test;
                    cleanup_object = *(Object **)alloc_page;
                    cleanup_flags = ((S_80025CE8_4 *)cleanup_object)->unk_1E;
                    flag_work = object_flag_block.flags;
                    flag_work |= 0x8000;
                    object_flag_block.flags = flag_work;
                    cleanup_flags |= 0x8000;
                    ((S_80025CE8_4 *)cleanup_object)->unk_1E = cleanup_flags;
                } while ((s32)alloc_parent >= 0);
            }
            return 0;
        }
        failure_index = object_index + 1;
        object_index = failure_index;
        failure_index <<= 16;
    } while ((failure_index >> 16) < 21);
    return (s32)objects[0];
}

#include "common.h"

typedef struct {
    s32 words[4];
} __attribute__((packed)) Copy16;

typedef struct S_80025FB0_0 {
    u8 pad_00[0x10];
    s16 unk_10;
    s8 unk_12;
    s8 unk_13;
    s8 unk_14;
    s8 unk_15;
} S_80025FB0_0;   /* arg1 in copy_and_expand_effect_record */

typedef struct S_80025FB0_1 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
} S_80025FB0_1;   /* arg0 in copy_and_expand_effect_record */

/* Copy a compact record, widen its signed fields, and apply zero values when its flag is clear. */
void copy_and_expand_effect_record(S_80025FB0_1 *dst, S_80025FB0_0 *src) {
    s32 zero_args[4];
    s32 signed_field;

    *(Copy16 *)dst = *(Copy16 *)src;
    signed_field = src->unk_10;

    dst->unk_10 = signed_field;
    dst->unk_14 = (s32) src->unk_12;
    dst->unk_18 = (s32) src->unk_13;
    dst->unk_1C = (s32) src->unk_14;
    if (src->unk_15 == 0) {
        zero_args[2] = 0;
        zero_args[1] = 0;
        zero_args[0] = 0;
        ScaleMatrix(dst, zero_args);
    }
}

/* Selector 72, retail file [0x19E0860, 0x19E092C); complete callable clone. */
#include "common.h"

/* The owner's table of 0x16-byte entries. */
typedef struct Bank19de800_19e0860_EntryOwner {
    u8 pad_00[0xC];
    s32 entries;
} Bank19de800_19e0860_EntryOwner;

/* An object that tracks one entry of its owner's table. */
typedef struct Bank19de800_19e0860_EntryCursor {
    s32 entry;                      /* address of the current entry */
    s8 index;
    u8 pad_05[3];
    Bank19de800_19e0860_EntryOwner *owner;
    u8 pad_0C[8];
    u16 flags;                       /* 0x4000 = index clamped */
} Bank19de800_19e0860_EntryCursor;

/* Resolve the current entry, apply an index step, and enforce the index bounds. */
void resolve_and_step_entry_index(void *object, s16 *index_step, s32 min_index, s32 max_index) {
    s16 step;
    u32 clamp_flags;
    u8 index;
    Bank19de800_19e0860_EntryCursor *obj = object;
    s32 initial_index = obj->index;
    Bank19de800_19e0860_EntryOwner *owner = obj->owner;

    obj->entry =
        owner->entries + (initial_index * 22);
    step = *index_step;
    if (step > 0) {
        obj->index = obj->index + 1;
    } else if (step < 0) {
        obj->index =
            obj->index - 1;
    }
    index = (u8)obj->index;
    if ((s8)index < (s16)min_index) {
        clamp_flags = obj->flags | 0x4000;
        obj->index = min_index;
        obj->flags = clamp_flags;
        return;
    }
    if ((s8)index > (s16)max_index) {
        clamp_flags = obj->flags | 0x4000;
        obj->index = max_index;
        obj->flags = clamp_flags;
        return;
    }
    obj->flags &= 0xBFFF;
}

/* Selector 72, retail file [0x19E092C, 0x19E095C); complete callable clone. */
#include "common.h"

/* The owner's table of 0x16-byte entries. */
typedef struct Bank19de800_19e092c_EntryOwner {
    u8 pad_00[0xC];
    s32 entries;
} Bank19de800_19e092c_EntryOwner;

/* An object that tracks one entry of its owner's table. */
typedef struct Bank19de800_19e092c_EntryCursor {
    s32 entry;          /* address of the current entry */
    u8 pad_04[4];
    Bank19de800_19e092c_EntryOwner *owner;
} Bank19de800_19e092c_EntryCursor;

/* Sets the object entry address using a 22-byte stride. */
void set_mesh_entry_address(Bank19de800_19e092c_EntryCursor *object, s16 entry_index) {
    object->entry = object->owner->entries + entry_index * 0x16;
}

#include "common.h"
#include "shared/object_flags.h"

extern void advance_sprite_animation_and_textures(void *visual);

/* Updates effect motion and visual state, marking the effect inactive when its lifetime expires. */
void update_effect_motion_and_visual(ImpactParticleWork *effect, ObjectPosition *position, SpriteFrameState *visual) {
    s32 accel_y;
    s32 accel_z;
    u16 frame;
    u16 ticks_left;

    position->x.v += effect->velocity_x;
    position->y.v += effect->velocity_y;
    position->z.v += effect->velocity_z;
    accel_y = effect->accel_y;
    accel_z = effect->accel_z;
    effect->velocity_x += effect->accel_x;
    effect->velocity_y += accel_y;
    effect->velocity_z += accel_z;
    visual->scale_x -= 500;
    visual->scale_y -= 500;
    frame = effect->anim_ticks;
    impact_effect_update_flag = 1;
    frame += 1;
    effect->anim_ticks = frame;
    if (!(frame & 1)) {
        advance_sprite_animation_and_textures(visual);
    }
    ticks_left = effect->ticks_left - 1;
    effect->ticks_left = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        *(u16 *)((u8 *)effect - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

#include "shared/object_node.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/slus_callbacks.h"

typedef struct S_8002626C_0 {
    u8 pad_00[0x28];
    s16 unk_28;
    u8 pad_2A[0x2];
    s16 unk_2C;
    s16 unk_2E;
    s16 unk_30;
    u8 pad_32[0x56];
    s32 unk_88;
    s32 unk_8C;
    s32 unk_90;
} S_8002626C_0;

/* Creates a colored effect at an offset position with velocity toward its base. */
void create_offset_colored_effect(
    s32 unused_0, s32 unused_1, s32 unused_2, s32 unused_3,
    s32 offset_x, s32 offset_y, s32 offset_z, s32 base_x, s32 base_y, s32 base_z) {
    s16 color_channel;
    S_8002626C_0 *effect_state;
    SpriteFrameState *sprite;
    ObjectNodeHeader *effect;

    effect = allocate_flagged_object_node(0x212);
    if (effect != 0) {
        effect_state = ((void *)effect) + 0x20;
        effect_state->unk_28 = 0x14;
        effect->update_callback = (void *)update_effect_motion_and_visual;
        register_node(effect, project_sprite_chain);
        sprite = effect->sprite;
        sprite->tpage_abr = 0x40;
        sprite->flags = (u16) (sprite->flags | 0xC);
        (effect->position)->x.w.i =
            (s16) (s32) &((s8 *) base_x)[offset_x];
        (effect->position)->y.w.i =
            (s16) (s32) &((s8 *) base_y)[offset_y];
        (effect->position)->z.w.i = (s16) (base_z + offset_z);
        effect_state->unk_2C = (s16) base_x;
        effect_state->unk_2E = (s16) base_y;
        effect_state->unk_30 = (s16) base_z;
        effect_state->unk_88 = (s32) (0 - ((s32) (offset_x << 0x10) >> 7));
        effect_state->unk_8C = (s32) (0 - ((s32) (offset_y << 0x10) >> 7));
        effect_state->unk_90 = (s32) (0 - ((s32) (offset_z << 0x10) >> 7));
        sprite = effect->sprite;
        sprite->scale_y = 0x3000;
        sprite->scale_x = 0x3000;
        color_channel = update_palette_particle_transition(3);
        sprite->color.c.b = 0;
        sprite->color.c.g = 0;
        sprite->color.c.r = 0;
        if (color_channel == 0) {
            sprite->color.c.r = 0x10;
        }
        if (color_channel == 1) {
            sprite->color.c.g = 0x10;
        }
        if (color_channel == 2) {
            sprite->color.c.b = 0x10;
        }
        sprite->clut = 0x7DCF;
        sprite->flags = (u16) (sprite->flags | 0x100);
        select_record_entry_and_value(sprite, effect_sprite_sources, 0);
    }
}
/* MECHANISM: The ten-argument ABI and reused pointer local produce the retail
   0x38 frame, full hold set, and reload seam. The unk_88/unk_8C stores sit after
   the base stores: that lengthens offset_x/offset_y's lives past base_x..base_z,
   so global.c ranks them after the bases ($s6/$s7, offset_z last in $fp).
   Byte-pointer BASE[index] sums select retail addu operand order. */

#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} Position;

typedef struct {
    u8 pad0[0x2A];
    u16 unk2A;
    u8 pad2C[0x6A];
    s16 unk96;
    u8 pad98[0x0E];
    u16 unkA6;
    u8 unkA8;
    u8 unkA9;
    u8 unkAA;
    u8 pad_AB[0x49];
    s32 unk_F4;
    u8 pad_F8[0xA];
    u8 unk_102;
} GlobalObj;

typedef struct {
    u16 flags;
} ChildObj;

typedef struct S_func_80026418_0 {
    u8 pad_00[4];
    ChildObj *unk_04;
    u8 unk_08;
    u8 pad_09[1];
    union { s16 s; u16 u; } unk_0A;
    u8 pad_0C[0x10];
    union { s16 s; u16 u; } unk_1C;
    u8 pad_1E[6];
    s16 unk_24;
    u8 pad_26[2];
    union { s16 s; u16 u; } unk_28;
    u16 unk_2A;
} S_func_80026418_0;

extern u8 D_8006E8A0[];
extern u8 particle_fade_pixels[];

extern void clear_circular_list_flags(void);
extern void upload_vram_row_and_cache(void *, s32, s32, s32); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern s32 decode_and_upload_image(void *, void *);
extern void drain_audio_commands_and_service_channels(void);

/* Advances a particle effect through its timed color fade and cleanup states. */
void advance_particle_fade_and_cleanup(S_func_80026418_0 *effect)
{
    s32 rect[2];
    OffsetTable offsets = D_80024028;
    GameWork *colors = &g_game_work;
    s32 state;
    s32 rect_xy;
    s32 rect_size;
    GlobalObj *owner;
    ChildObj *child;
    u16 next_state;
    s32 reset_timer;

    state = effect->unk_0A.s;
    switch (state) {
    case 0:
        select_nearby_target_and_initialize_slot((u8 *)((GlobalObj *)primary_actor_record) - 0x20, ((Position *)&view_reference_entity), 8, 0x400);
        rect_xy = 0x010003A0;
        rect_size = 0x00400020;
        ((PlayerRecord *)primary_actor_record)->unk_102 = 1;
        rect[0] = rect_xy;
        rect[1] = rect_size;
        decode_and_upload_image(D_8006E8A0, rect);
        upload_vram_row_and_cache(particle_fade_pixels, 0x7AC0, 1, 2);
        clear_circular_list_flags();

        owner = ((GlobalObj *)primary_actor_record);
        owner->unk_F4 = 0;
        owner->unk96 = 30;
        next_state = effect->unk_0A.u;
        impact_effect_update_flag = 1;
        effect->unk_2A = 0;
        effect->unk_0A.u = next_state + 1;
    case 1:
        child = effect->unk_04;
        if ((child->flags & 0x80) == 0) {
            return;
        }
        play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
        drain_audio_commands_and_service_channels();
        effect->unk_28.u = 0;
        effect->unk_0A.u = effect->unk_0A.u + 1;
        return;

    case 2:
    {
        u16 timer = effect->unk_28.u;
        GlobalObj *effect_owner;
        ObjectPosition *position;
        OffsetPair *offset_base;
        u16 fade_state;
        u16 direction;
        s16 particle_index;

        effect->unk_28.u = timer + 1;
        if ((s16)timer >= 0x52) {
            effect_owner = ((GlobalObj *)primary_actor_record);
            effect->unk_1C.s = 0x21;
            effect_owner->unkA6 = effect_owner->unkA6 - 1;
            effect_owner->unkA8 = effect->unk_08;
            fade_state = effect->unk_0A.u;
            direction = ((u16)primary_actor_record->facing);
            effect->unk_0A.u = fade_state + 1;
            effect->unk_28.u = 0;
            effect->unk_24 = (direction >> 9) & 7;
        }

        particle_index = 0;
        if (effect->unk_28.s == 0x4A) {
            ObjectPosition *effect_position = &view_reference_entity;

            func_80025CE8((s16)((u16)effect_position->x.w.i),
                          (s16)((u16)effect_position->y.w.i),
                          (s16)((u16)effect_position->z.w.i),
                          (s16)((u16)primary_actor_record->facing));
        }

        effect->unk_24 = (((u16)primary_actor_record->facing) >> 9) & 7;
        position = &view_reference_entity;
        offset_base = offsets.entries;
        do {
            s32 spread_y;
            s32 spread_x;
            s32 spread_z;

            spread_y = (s16)((rand() & 0x7F) - 0x40);
            spread_x = (s16)((rand() & 0x7F) - 0x40);
            spread_z = (s16)((rand() & 0x7F) - 0x40);

            create_offset_colored_effect((u8 *)effect - 0x20, effect->unk_24,
                          0x00C0C0C0, 0x28, spread_y, spread_x, spread_z,
                          (s16)(((u16)position->x.w.i) + ({
                              OffsetPair *offset = (OffsetPair *)
                                  ((u8 *)offset_base +
                                   effect->unk_24 * 4);
                              offset->x;
                          }) * 128),
                          (s16)(((u16)position->y.w.i) + ({
                              OffsetPair *offset = (OffsetPair *)
                                  ((u8 *)offset_base +
                                   effect->unk_24 * 4);
                              (s32)(offset->y << 16) >> 9;
                          })),
                          (s16)(((u16)position->z.w.i) - 0x74));
            particle_index++;
        } while (particle_index < 2);

        if (colors->view.tint.parts.tint_r < 0x3D) {
            return;
        }
        colors->view.tint.parts.tint_r -= 2;
        colors->view.tint.parts.tint_g -= 2;
        colors->view.tint.parts.tint_b -= 2;
        return;
    }

    case 3:
        effect->unk_28.u = 0;
        effect->unk_0A.u = effect->unk_0A.u + 1;
    case 4:
        if (colors->view.tint.parts.tint_r >= 0x3D) {
            colors->view.tint.parts.tint_r -= 2;
            colors->view.tint.parts.tint_g -= 2;
            colors->view.tint.parts.tint_b -= 2;
        }
        effect->unk_1C.u = effect->unk_1C.u - 1;
        if (effect->unk_1C.s > 0) {
            return;
        }
        reset_timer = 0x3C;
        effect->unk_1C.s = reset_timer;
        effect->unk_0A.u = effect->unk_0A.u + 1;
        return;

    case 5:
    {
        s8 color = colors->view.tint.parts.tint_r;
        s32 dungeon_mode;

        if ((u8)color < 0x80) {
            colors->view.tint.parts.tint_r += 10;
            colors->view.tint.parts.tint_g += 10;
            colors->view.tint.parts.tint_b += 10;
        }
        if ((reference_tile_object.sprite_flags & 0x8000) == 0) {
            effect->unk_1C.u = effect->unk_1C.u - 1;
            if (effect->unk_1C.s >= 0) {
                return;
            }
        }
        dungeon_mode = impact_effect_update_flag;
        effect->unk_1C.s = 0;
        if (dungeon_mode == 0) {
            effect->unk_28.u = 0;
            effect->unk_0A.u = effect->unk_0A.u + 1;
            return;
        } else {
            impact_effect_update_flag = 0;
            return;
        }
    }

    case 6:
    {
        u16 timer = effect->unk_28.u;

        effect->unk_28.u = timer + 1;
        if ((s16)timer < 4) {
            return;
        }
        colors->view.tint.parts.tint_b = 0x80;
        colors->view.tint.parts.tint_g = 0x80;
        colors->view.tint.parts.tint_r = 0x80;
        {

            g_dungeon_status.active_actor = 0;
            g_dungeon_status.activity_counts.parts.pending_action_count =
                ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1;
        }
        reference_tile_object.depth_bias = 0;
        *(u16 *)((u8 *)effect - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    default:
        return;
    }
}
