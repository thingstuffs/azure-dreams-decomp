#include "shared/audio_commands.h"
/* Actor-relative motion effects, trailing particles, and rising and landing sprite sequences. */
#include "modules/dungeon_ovl_199c800.h"
#include "dungeon/actor/motion.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_D_80082E80.h"
#include "shared/sprite_source.h"
#include "m2c_compat.h"
#include "sdk/libc.h"

typedef struct S_FUNC_8197C800_BODY_0_pre {
    u16 unk_00;
} S_FUNC_8197C800_BODY_0_pre;   /* the 0x2 bytes before arg0 in update_directional_actor_effect, addressed as arg0[-1] */

typedef struct S_FUNC_8197C800_BODY_0 {
    void * unk_00;
    void * unk_04;
    u8 unk_08;
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x44];
    union { u16 s; s16 u; } unk_50;   /* accessed as both */
    union { s16 s; u16 u; } unk_52;   /* accessed as both */
} S_FUNC_8197C800_BODY_0;   /* arg0 in update_directional_actor_effect */

typedef struct S_FUNC_8197C800_BODY_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_FUNC_8197C800_BODY_2;   /* arg1 in update_directional_actor_effect */

typedef struct S_FUNC_8197C800_BODY_3 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_FUNC_8197C800_BODY_3;   /* root in update_directional_actor_effect */

typedef struct S_FUNC_8197C800_BODY_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_FUNC_8197C800_BODY_5;   /* obj in update_directional_actor_effect */

typedef struct S_FUNC_8197C800_BODY_6 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_FUNC_8197C800_BODY_6;   /* src_position in update_directional_actor_effect */

typedef struct S_FUNC_8197C800_BODY_7 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_FUNC_8197C800_BODY_7;   /* dst_position in update_directional_actor_effect */

typedef struct S_FUNC_8197C800_BODY_8 {
    void * unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0x2];
    void * unk_08;
    void * unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_FUNC_8197C800_BODY_8;   /* node in update_directional_actor_effect */

typedef struct S_FUNC_8197C800_BODY_9 {
    u8 pad_00[0x4];
    void * unk_04;
} S_FUNC_8197C800_BODY_9;   /* D_800DEDB0 in update_directional_actor_effect */

typedef struct S_FUNC_8197C800_BODY_10 {
    u8 pad_00[0x4C];
    u16 unk_4C;
} S_FUNC_8197C800_BODY_10;   /* tail in update_directional_actor_effect */

typedef struct S_FUNC_8197C800_BODY_13 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_FUNC_8197C800_BODY_13;   /* image0 in update_directional_actor_effect */

typedef struct S_FUNC_8197C800_BODY_14 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_FUNC_8197C800_BODY_14;   /* position in update_directional_actor_effect */

typedef struct S_FUNC_8197C800_BODY_15 {
    u8 pad_00[0x4];
    void * unk_04;
} S_FUNC_8197C800_BODY_15;   /* template in update_directional_actor_effect */

typedef struct S_FUNC_8197C800_BODY_17 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_FUNC_8197C800_BODY_17;   /* image in update_directional_actor_effect */

typedef struct S_FUNC_8197C800_BODY_19 {
    u8 pad_00[0xA];
    u16 unk_0A;
    u32 unk_0C;
} S_FUNC_8197C800_BODY_19;   /* status in update_directional_actor_effect */

typedef struct S_FUNC_8197C800_BODY_20 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_FUNC_8197C800_BODY_20;   /* ((S_FUNC_8197C800_BODY_3 *)root)->unk_08 in update_directional_actor_effect */

typedef struct S_FUNC_8197C800_BODY_21 {
    u16 unk_00;
} S_FUNC_8197C800_BODY_21;   /* ((S_FUNC_8197C800_BODY_0 *)arg0)->unk_04 in update_directional_actor_effect */

typedef struct S_FUNC_8197C800_BODY_22 {
    u8 pad_00[0x8];
    void * unk_08;
} S_FUNC_8197C800_BODY_22;   /* ((S_FUNC_8197C800_BODY_3 *)root)->unk_0C in update_directional_actor_effect */

typedef struct S_FUNC_8197C800_BODY_25 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_FUNC_8197C800_BODY_25;   /* ((S_FUNC_8197C800_BODY_5 *)obj)->unk_08 in update_directional_actor_effect */

extern u8 rising_sprite_entries[];
extern u8 countdown_sprite_entries[];
extern u8 directional_sprite_entries[];

extern s32 resolve_record_orientation_or_fallback(void *, void *, void *, s32);
extern s32 read_sound_mode_blocking_status(s32);
extern void apply_attack_power_and_element_effects(void *, s32, s32, s32, s16, void *, s32);

void update_directional_actor_effect(void *input, void *output);
extern int abs(int);
extern s32 secondary_sprite[];
extern s32 resolve_record_orientation_or_fallback(void *entry, void *table, void *scratch, s32 a3);
extern s32 rsin(s32 angle);
extern u8 homing_particle_sprite_entries[];
extern SpriteSourceEntry landing_sprite_entries[];

/* Converts the grid coordinate to units of 64 and adds random modulo 64. */
static __inline__ s32 jitter_coordinate_64(s32 grid, s32 random)
{
    return (grid << 6) + random % 64;
}

/*
 * Converts the grid coordinate to units of 64 and adds random modulo 32 plus a centered offset of
 * 16.
 */
static __inline__ s32 jitter_coordinate_32(s32 grid, s32 random)
{
    s32 scaled = grid << 6;
    s32 jitter = random % 32 + 16;

    return scaled + jitter;
}

/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol add_flag_adjusted_target_value).  The state table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */
void (*const dungeon_199c800_entry)(void *, void *) = update_directional_actor_effect;

/* Updates a timed effect, spawns particles, and completes its owner's action. */
void update_directional_actor_effect(void *input, void *output)
{
    s16 offsets[3];
    s32 state;
    void *owner_data;
    void *owner;
    void *particle_script;
    ActorRecord *scene;
    ObjectNodeHeader *particle;
    SpriteFrameState *sprite;
    S_FUNC_8197C800_BODY_6 *src_position;
    ObjectPosition *dst_position;
    ObjectPosition *dst_position_3;
    ObjectPosition *dst_position_2;
    void *particle_data;
    s32 remaining;
    s32 result;
    void *particle_script_debris;
    TileObject *debris_origin;
    s32 height;
    s32 offset_index;
    s32 random_value;
    u16 angle;
    u16 tail_state;
    u16 tail_timer;
    TileObject *burst_origin;
    u16 timer;

    s32 step;

    timer = ((S_FUNC_8197C800_BODY_0 *)input)->unk_50.s;
    owner_data = ((S_FUNC_8197C800_BODY_0 *)input)->unk_00;
    state = ((S_FUNC_8197C800_BODY_0 *)input)->unk_0A.s;
    timer -= 1;
    ((S_FUNC_8197C800_BODY_0 *)input)->unk_50.s = timer;
    owner = (u8 *)owner_data - 0x20;

    switch (state) {
    case 0:
    ((PlayerRecord *)(primary_actor_record))->unk_F4 = 0;
    ((S_FUNC_8197C800_BODY_2 *)output)->unk_00 =
        ((S_FUNC_8197C800_BODY_20 *)(((S_FUNC_8197C800_BODY_3 *)owner)->unk_08))->unk_00;
    ((S_FUNC_8197C800_BODY_2 *)output)->unk_04 =
        ((S_FUNC_8197C800_BODY_20 *)(((S_FUNC_8197C800_BODY_3 *)owner)->unk_08))->unk_04;
    ((S_FUNC_8197C800_BODY_2 *)output)->unk_08 =
        ((S_FUNC_8197C800_BODY_20 *)(((S_FUNC_8197C800_BODY_3 *)owner)->unk_08))->unk_08;
    ((S_FUNC_8197C800_BODY_0 *)input)->unk_0A.u += 1;

    case 1:
    if (!(((S_FUNC_8197C800_BODY_21 *)(((S_FUNC_8197C800_BODY_0 *)input)->unk_04))->unk_00 & 0x80)) {
        return;
    }

    scene = primary_actor_record;
    ((S_FUNC_8197C800_BODY_0 *)input)->unk_50.s = 10;
    ((u16 *)&scene->unk_A4.value)[1] -= 1;
    scene->unk_A8.byte = ((S_FUNC_8197C800_BODY_0 *)input)->unk_08;
    particle = allocate_list_node(0x312, &scene_object_list_anchor.next);
    if (particle != 0) {
        if (resolve_record_orientation_or_fallback(((S_FUNC_8197C800_BODY_22 *)(((S_FUNC_8197C800_BODY_3 *)owner)->unk_0C))->unk_08,
                          ((S_FUNC_8197C800_BODY_3 *)owner)->unk_0C, offsets, 0) == 0) {
            offsets[2] = 0;
            offsets[1] = 0;
            offsets[0] = 0;
        }
        particle_data = (u8 *)particle + 0x20;
        particle->update_callback = (void *)build_and_enqueue_five_translucent_quads_between_interpolated_points;
        register_node(particle, project_sprite_chain);
        random_value = 0x00800000u;
        sprite = particle->sprite;
        offset_index = offsets[0];
        src_position = ((S_FUNC_8197C800_BODY_3 *)owner)->unk_08;
        dst_position_2 = particle->position;
        result = src_position->unk_00 + (offset_index << 16);
        ((S_FUNC_8197C800_BODY_2 *)output)->unk_00 = result;
        dst_position_2->x.v = result;
        offset_index = offsets[1];
        src_position = ((S_FUNC_8197C800_BODY_3 *)owner)->unk_08;
        dst_position = particle->position;
        result = src_position->unk_04 + (offset_index << 16);
        ((S_FUNC_8197C800_BODY_2 *)output)->unk_04 = result;
        dst_position->y.v = result;
        offset_index = offsets[2];
        src_position = ((S_FUNC_8197C800_BODY_3 *)owner)->unk_08;
        dst_position_3 = particle->position;
        result = src_position->unk_08 + (offset_index << 16);
        ((S_FUNC_8197C800_BODY_2 *)output)->unk_08 = result;
        dst_position_3->z.v = result;
        sprite->scale_y = 0x800;
        sprite->scale_x = 0x800;
        sprite->tpage_abr = 0x20;
        sprite->unk_00 = rising_sprite_entries;
        sprite->flags |= 0xC;
        sprite->source = ((S_FUNC_8197C800_BODY_9 *)rising_sprite_entries)->unk_04;
        random_value |= 0x8080u;
        sprite->unk_04 = 0;
        sprite->frame_ticks = 0;
        sprite->color.word = (void *)random_value;
        ((S_FUNC_8197C800_BODY_5 *)particle)->unk_20 = input;
        ((S_FUNC_8197C800_BODY_10 *)particle_data)->unk_4C = 0;
    }
    tail_state = ((S_FUNC_8197C800_BODY_0 *)input)->unk_0A.u + 1;

    ((S_FUNC_8197C800_BODY_0 *)input)->unk_0A.u = tail_state;
    return;

    case 2:
    if (((S_FUNC_8197C800_BODY_0 *)input)->unk_50.u > 0) {
        return;
    }
    result = read_sound_mode_blocking_status(4);
    if (result != 2) {
        play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
    } else {
        play_sound_if_enabled(AUDIO_RESUME_CD);
    }
    tail_state = ((S_FUNC_8197C800_BODY_0 *)input)->unk_0A.u;

    tail_timer = 16;
    ((S_FUNC_8197C800_BODY_0 *)input)->unk_50.s = tail_timer;
    tail_state += 1;
    ((S_FUNC_8197C800_BODY_0 *)input)->unk_0A.u = tail_state;
    return;

    case 3:
    if (((S_FUNC_8197C800_BODY_0 *)input)->unk_50.u < 3) {
        remaining = 1;
        height = (s16)sample_terrain_surface_height((u16)view_reference_entity.x.w.i, (u16)view_reference_entity.y.w.i, (s16)(view_reference_entity.z.w.i - 0x80));
        particle_script = (void *)move_sprite_until_animation_ends;
        burst_origin = &reference_tile_object;
        do {
            particle = allocate_list_node(0x312, &scene_object_list_anchor.next);
            if (particle != 0) {
                particle->update_callback = particle_script;
                register_node(particle, project_sprite_chain);
                sprite = particle->sprite;
                particle_data = (u8 *)particle + 0x20;
                random_value = rand();
                angle = ((ActorRecord *)(primary_actor_record))->facing;
                step = angle;
                step <<= 16;
                step >>= 25;
                result = (s32)dir_step_x;
                {
                    s32 grid_coord;
                    ObjectPosition *position;
                    step *= 2;
                    step += result;
                    result = burst_origin->tile_position.parts.tile_x;
                    step = *(s16 *)step;
                    grid_coord = result + step;
                    position = particle->position;
                    result = jitter_coordinate_32(grid_coord, random_value);
                    position->x.w.i = result;
                }
                random_value = rand();
                angle = ((ActorRecord *)(primary_actor_record))->facing;
                step = angle;
                step <<= 16;
                step >>= 25;
                result = (s32)dir_step_y;
                {
                    s32 grid_coord;
                    ObjectPosition *position;
                    step *= 2;
                    step += result;
                    result = burst_origin->tile_position.parts.tile_y;
                    step = *(s16 *)step;
                    grid_coord = result + step;
                    position = particle->position;
                    result = jitter_coordinate_32(grid_coord, random_value);
                    position->y.w.i = result;
                }
                {
                    u32 color;
                    void *sprite_template = 0;
                    ObjectPosition *position;
                    color = 0x00600000u;
                    position = particle->position;
                    sprite_template = countdown_sprite_entries;
                    position->z.w.i = height;
                    sprite->scale_x = 0x1800;
                    sprite->scale_y = 0x2000;
                    sprite->tpage_abr = 0x60;
                    {
                        u16 flags;
                        flags = sprite->flags;
                        sprite->unk_00 = sprite_template;
                        flags |= 0xC;
                        sprite->flags = flags;
                        sprite->source = ((S_FUNC_8197C800_BODY_15 *)sprite_template)->unk_04;
                    }
                    sprite->unk_04 = 0;
                    sprite->frame_ticks = 0;
                    sprite->color.word = (void *)(color | 0x6060u);
                    ((S_FUNC_8197C800_BODY_5 *)particle)->unk_20 = input;
                    ((S_FUNC_8197C800_BODY_10 *)particle_data)->unk_4C = 0;
                }
            }
            remaining -= 1;
        } while (remaining >= 0);

        remaining = 9;
        particle_script_debris = (void *)update_rising_landing_effect;
        debris_origin = &reference_tile_object;
        do {
            particle = allocate_list_node(0x312, &scene_object_list_anchor.next);
            if (particle != 0) {
                particle->update_callback = particle_script_debris;
                register_node(particle, project_sprite_chain);
                sprite = particle->sprite;
                particle_data = (u8 *)particle + 0x20;
                random_value = rand();
                angle = ((ActorRecord *)(primary_actor_record))->facing;
                step = angle;
                step <<= 16;
                step >>= 25;
                result = (s32)dir_step_x;
                {
                    s32 grid_coord;
                    ObjectPosition *position;
                    step *= 2;
                    step += result;
                    result = debris_origin->tile_position.parts.tile_x;
                    step = *(s16 *)step;
                    grid_coord = result + step;
                    position = particle->position;
                    result = jitter_coordinate_64(grid_coord, random_value);
                    position->x.w.i = result;
                }
                random_value = rand();
                angle = ((ActorRecord *)(primary_actor_record))->facing;
                step = angle;
                step <<= 16;
                step >>= 25;
                result = (s32)dir_step_y;
                {
                    s32 grid_coord;
                    ObjectPosition *position;
                    step *= 2;
                    step += result;
                    result = debris_origin->tile_position.parts.tile_y;
                    step = *(s16 *)step;
                    grid_coord = result + step;
                    position = particle->position;
                    result = jitter_coordinate_64(grid_coord, random_value);
                    position->y.w.i = result;
                }
                result = rand();
                (particle->position)->z.w.i =
                    height - (result & 0x1F);
                result = rand();
                {
                    u32 color;
                    void *sprite_template = 0;
                    color = 0x00100000u;
                    (particle->position)->velocity_z =
                        (s32)0xFFE60000 - (result << 2);
                    sprite->scale_y = 0x800;
                    sprite->scale_x = 0x800;
                    sprite->tpage_abr = 0x20;
                    {
                        u16 flags;
                        flags = sprite->flags;
                        sprite_template = directional_sprite_entries;
                        sprite->unk_00 = sprite_template;
                        flags |= 0xC;
                        sprite->flags = flags;
                        sprite->source = ((S_FUNC_8197C800_BODY_15 *)sprite_template)->unk_04;
                    }
                    sprite->unk_04 = 0;
                    sprite->frame_ticks = 0;
                    sprite->color.word = (void *)(color | 0x1010u);
                    ((S_FUNC_8197C800_BODY_5 *)particle)->unk_20 = input;
                    ((S_FUNC_8197C800_BODY_10 *)particle_data)->unk_4C = 0;
                }
            }
            remaining -= 1;
        } while (remaining >= 0);
    }
    if (((S_FUNC_8197C800_BODY_0 *)input)->unk_50.u > 0) {
        return;
    }
    tail_timer = 32;
    tail_state = ((S_FUNC_8197C800_BODY_0 *)input)->unk_0A.u;
store_timer:
    ((S_FUNC_8197C800_BODY_0 *)input)->unk_50.s = tail_timer;
    tail_state += 1;
store_state:
    ((S_FUNC_8197C800_BODY_0 *)input)->unk_0A.u = tail_state;
    return;

    case 4:
    if (!(reference_tile_object.sprite_flags & 0x8000) && ((S_FUNC_8197C800_BODY_0 *)input)->unk_50.u >= 0) {
        return;
    }
    if (((S_FUNC_8197C800_BODY_0 *)input)->unk_52.s & 0x8000) {
        ((S_FUNC_8197C800_BODY_0 *)input)->unk_52.u &= 0x7FFF;
        return;
    }
    apply_attack_power_and_element_effects(((ActorRecord *)(primary_actor_record))->target, 8,
                  ((S_FUNC_8197C800_BODY_0 *)input)->unk_09, 10,
                  ((EntityRec *)owner_data)->facing, owner_data, 2);
    g_dungeon_status.active_actor = 0;
    g_dungeon_status.activity_counts.parts.pending_action_count -= 1;
    ((S_FUNC_8197C800_BODY_0_pre *)input)[-1].unk_00 |= 0x8000;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

typedef union {
    s32 word;
    struct {
        u16 low;
        u16 coord;
    } half;
} CoordWord;

typedef struct Vec3 {
    CoordWord x;
    CoordWord y;
    CoordWord z;
} Vec3;

typedef struct Sprite {
    u8 pad0[0x14];
    u16 flags;
    u8 pad16[6];
    u16 top;
    u16 bottom;
} Sprite;

typedef struct {
    s32 field0;
    u8 field4;
    u8 field5;
    u8 pad6[2];
    s32 field8;
    s32 fieldC;
    s16 field10;
    u8 pad12[2];
    u16 flags14;
    u8 pad16[6];
    u16 field1C;
    u16 field1E;
} SpawnState;

typedef struct {
    void *parent;
    u8 pad4[0x48];
    u16 field4C;
} SpawnChild;

typedef struct {
    u8 pad0[8];
    Vec3 *position;
    SpriteFrameState *state;
    void *callback;
    u8 pad14[0xC];
    SpawnChild child;
} Spawn;

typedef struct Actor {
    void *field0;
    u8 pad4[0x3C];
    s16 field40;
    s16 field42;
    u8 pad44[4];
    u16 counter;
    u8 pad4A[2];
    u16 state;
} Actor;

typedef struct {
    u8 pad0[8];
    void *entry;
} EntryTable;

/* Advance the actor animation, move toward the entry position, and spawn trailing particles. */
void build_and_enqueue_five_translucent_quads_between_interpolated_points(Actor *actor, Vec3 *target, Sprite *sprite) {
    u16 entry_pos[3];
    u16 start_pos[3];

    actor->counter = actor->counter + 1;
    ((u16 *)actor->field0)[0x29] = ((u16 *)actor->field0)[0x29] | 0x8000;
    advance_sprite_animation_and_textures(sprite);
    start_pos[0] = target->x.half.coord;
    start_pos[1] = target->y.half.coord;
    start_pos[2] = target->z.half.coord;

    switch ((s16)actor->state) {
    default:
        break;
    case 0:
        if ((s16)actor->counter < 8) {
            sprite->bottom = sprite->bottom + 0x78;
            sprite->top = sprite->bottom;
        }
        if (resolve_record_orientation_or_fallback(((void *)reference_tile_object.sprite_source), ((EntryTable *)&reference_tile_object), entry_pos, 0) != 0) {
            target->x.word += ((((s16)entry_pos[0] + view_reference_entity.x.w.i) - (s16)target->x.half.coord) << 14);
            target->y.word += ((((s16)entry_pos[1] + view_reference_entity.y.w.i) - (s16)target->y.half.coord) << 14);
            target->z.word += ((((s16)entry_pos[2] + view_reference_entity.z.w.i) - (s16)target->z.half.coord) << 14);
            target->z.word -= (rsin(((s16)actor->counter << 11) / 10) << 9);
        }
        if ((s16)actor->counter >= 10) {
            sprite->flags = sprite->flags | 0x800;
            actor->state = actor->state + 1;
        }
        break;
    case 1:
        if (resolve_record_orientation_or_fallback(((void *)reference_tile_object.sprite_source), ((EntryTable *)&reference_tile_object), entry_pos, 0) != 0) {
            target->x.word += ((((s16)entry_pos[0] + view_reference_entity.x.w.i) - (s16)target->x.half.coord) << 15);
            target->y.word += ((((s16)entry_pos[1] + view_reference_entity.y.w.i) - (s16)target->y.half.coord) << 15);
            target->z.word += ((((s16)entry_pos[2] + view_reference_entity.z.w.i) - (s16)target->z.half.coord) << 15);
        }
        if ((s16)actor->counter >= 0x12) {
            sprite->flags = sprite->flags & 0xF7FF;
            sprite->bottom = sprite->bottom + 0x50;
            sprite->top = sprite->bottom;
        }
        if ((s16)actor->counter >= 0x1C) {
            u16 actor_bits;
            u16 actor_bits_2;
            s32 global_flags;
            actor_bits_2 = ((u16 *)actor)[-1];
            actor_bits_2 |= 0x8000;
            ((u16 *)actor)[-1] = actor_bits_2;
            actor_bits = actor->state;
            global_flags = object_flag_block.flags;
            actor_bits++;
            global_flags |= 0x8000;
            actor->state = actor_bits;
            object_flag_block.flags = global_flags;
        }
        break;
    }

    actor->field40 = (s16)(((actor->counter & 3) << 5) + 0x80);
    actor->field42 = (s16)(((((s32)(actor->counter << 16) >> 18) << 5)) + 0x80);

    {
        s32 remaining;
        s32 early_frames;
        u16 frame;
        early_frames = (s16)actor->counter < 8;
        frame = *(u16 *)&actor->counter;
        if (early_frames) {
            sprite = (Sprite *)4;
        } else if ((u32)(frame - 8) < 5U) {
            sprite = (Sprite *)0xC;
        } else {
            sprite = (Sprite *)3;
        }

        remaining = (s32)sprite;
        if (remaining >= 0) {
            void *particle_callback = (void *)move_sprite_until_animation_ends;
            s32 *particle_data = secondary_sprite;
            do {
                Spawn *spawn;
                spawn = allocate_list_node(0x312, &scene_object_list_anchor.next);
                if (spawn != 0) {
                    s32 coord_magnitude;
                    s32 x_offset;
                    s32 z_jitter;
                    s32 packed_color;
                    s32 data_word;
                    SpriteFrameState *state;
                    SpawnChild *child;
                    s32 target_y;
                    s32 start_y;
                    u16 start_y_bits;

                    spawn->callback = particle_callback;
                    register_node(spawn, project_sprite_chain);
                    state = spawn->state;
                    coord_magnitude = abs((s16)target->x.half.coord - (s16)start_pos[0]);
                    child = &spawn->child;
                    if (coord_magnitude == 0) {
                        coord_magnitude = 1;
                    }
                    x_offset = rand() % coord_magnitude;
                    spawn->position->x.half.coord = (s16)((((s16)target->x.half.coord + (s16)start_pos[0]) >> 1)
                        + x_offset - (coord_magnitude >> 1));
                    target_y = (s16)target->y.half.coord;
                    start_y = (s16)start_pos[1];
                    start_y_bits = start_pos[1];
                    coord_magnitude = abs(target_y + start_y);
                    if (coord_magnitude == 0) {
                        spawn->position->y.word = target->y.word;
                    } else {
                        ((Vec3 *)spawn->position)->y.half.coord =
                            (s16)(start_y_bits + ((target_y - start_y) * x_offset) / coord_magnitude);
                    }
                    spawn->position->x.word += (((rand() & 0x3FF) - 0x1FF) << 10);
                    spawn->position->y.word += (((rand() & 0x3FF) - 0x1FF) << 10);
                    z_jitter = rand();
                    spawn->position->z.word = target->z.word + (((z_jitter & 0x3FF) - 0x1FF) << 10);
                    state->scale_y = 0x1800;
                    state->scale_x = 0x1800;
                    state->tpage_abr = 0x60;
                    state->unk_00 = particle_data;
                    state->flags = state->flags | 0xC;
                    data_word = particle_data[1];
                    state->unk_04 = 0;
                    state->frame_ticks = 0;
                    state->color.word = (0xC00000 | 0x6060);
                    state->source = data_word;
                    data_word = (s32)actor->field0;
                    child->field4C = 0;
                    child->parent = (void *)data_word;
                }
                remaining = remaining - 1;
            } while (remaining >= 0);
        }
    }
}

typedef struct S_8197D3B8_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8197D3B8_0;   /* arg1 in func_80024BB8 */

typedef struct S_8197D3B8_1_pre {
    u16 unk_00;
} S_8197D3B8_1_pre;   /* the 0x2 bytes before arg0 in func_80024BB8, addressed as arg0[-1] */

typedef struct S_8197D3B8_1 {
    void * unk_00;
} S_8197D3B8_1;   /* arg0 in func_80024BB8 */

typedef struct S_8197D3B8_2 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_8197D3B8_2;   /* primitive in func_80024BB8 */

/* Applies motion deltas, marks the primitive, and propagates status flags. */
void move_sprite_until_animation_ends(void *render_entry, void *motion_data, void *render_status)
{
    S_8197D3B8_0 *motion = motion_data;
    SpriteFrameState *status = render_status;
    s32 delta_y;
    s32 delta_z;
    S_8197D3B8_2 *primitive;

    delta_y = motion->unk_10;
    delta_z = motion->unk_14;
    motion->unk_00 += motion->unk_0C;
    motion->unk_04 += delta_y;
    motion->unk_08 += delta_z;

    primitive = ((S_8197D3B8_1 *)render_entry)->unk_00;
    primitive->unk_52 |= 0x8000;

    advance_sprite_animation_and_textures(status);
    if (status->flags & 0x6000) {
        ((S_8197D3B8_1_pre *)render_entry)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

typedef struct S_8197D468_0_pre {
    u16 unk_00;
} S_8197D468_0_pre;   /* the 0x2 bytes before arg0 in update_rising_landing_effect, addressed as arg0[-1] */

typedef struct S_8197D468_0 {
    void * unk_00;
    u8 pad_04[0x44];
    u16 unk_48;
    u8 pad_4A[0x2];
    union { s16 s; u16 u; } unk_4C;   /* accessed as both */
} S_8197D468_0;   /* arg0 in update_rising_landing_effect */

typedef struct S_8197D468_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_8197D468_1;


typedef struct S_8197D468_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8197D468_4;   /* &D_800DE990 in update_rising_landing_effect */

typedef struct S_8197D468_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_8197D468_5;

typedef struct S_8197D468_8 {
    u8 pad_00[0x4C];
    s16 unk_4C;
} S_8197D468_8;

/* cfail-repair: tf7-phase1-cache-v3 */

/* Update a rising, expanding, and falling effect, spawning particles on landing. */
void update_rising_landing_effect(void *effect, ObjectPosition *motion, SpriteFrameState *sprite) {
    void *particle_work;
    s16 state;
    s16 ground_height;
    s32 particle_index;
    s32 particle_frames;
    s32 rise_random;
    s32 rise_velocity;
    s32 fall_random;
    s32 fall_velocity;
    u16 frames_left;
    u16 sprite_flags;
    s32 particle_color;
    void *sprite_frames;
    void *effect_data;
    SpriteFrameState *particle_sprite;
    void *owner;
    ObjectNodeHeader *particle;

    owner = ((S_8197D468_0 *)effect)->unk_00;
    ((S_8197D468_1 *)owner)->unk_52 = (u16) (((S_8197D468_1 *)owner)->unk_52 | 0x8000);
    if (sprite->flags & 0x6000) {
        sprite->unk_04 = 0;
        sprite->frame_ticks = 0;
        sprite->flags = (u16) (sprite->flags & 0x9FFF);
    }
    advance_sprite_animation_and_textures(sprite);
    state = ((S_8197D468_0 *)effect)->unk_4C.s;
    switch (state) {
    case 0:
        motion->z.v = (s32) (motion->z.v
            + motion->velocity_z);
        rise_random = rand();
        rise_velocity = motion->velocity_z + 0x1A000;
        rise_velocity += rise_random >> 1;
        motion->velocity_z = rise_velocity;
        if ((u8) sprite->color.c.r < 0x40) {
            sprite->color.word = (s32) ((s32) sprite->color.word + 0x40404);
        }
        if (motion->velocity_z > 0) {
            sprite->unk_00 = &landing_sprite_entries;
            sprite_frames = (void *) ((S_8197D468_4 *)(&landing_sprite_entries))->unk_04;
            sprite_flags = sprite->flags;
            sprite->unk_04 = 0;
            sprite->frame_ticks = 0;
            sprite->scale_y = 0x400U;
            sprite->scale_x = 0x400U;
            sprite->tpage_abr = 0;
            sprite->source = sprite_frames;
            sprite->flags = (u16) (sprite_flags | 2);
            ((S_8197D468_0 *)effect)->unk_48 = (u16) ((rand() & 3) + 4);
            ((S_8197D468_0 *)effect)->unk_4C.u = (u16) (((S_8197D468_0 *)effect)->unk_4C.u + 1);
            return;
        }
        break;
    case 1:
        sprite->color.word = 0x606060;
        sprite->scale_x = (u16) (sprite->scale_x + 0xC8);
        sprite->scale_y = (u16) (sprite->scale_y + 0xC8);
        frames_left = ((S_8197D468_0 *)effect)->unk_48 - 1;
        ((S_8197D468_0 *)effect)->unk_48 = frames_left;
        if ((frames_left << 0x10) <= 0) {
            ((S_8197D468_0 *)effect)->unk_4C.u = (u16) (((S_8197D468_0 *)effect)->unk_4C.u + 1);
            return;
        }
        break;
    case 2:
        if (sprite->flags & 0x6000) {
            sprite->unk_00 = &landing_sprite_entries;
            effect_data = (void *) ((S_8197D468_4 *)(&landing_sprite_entries))->unk_04;
            sprite->unk_04 = 0;
            sprite->frame_ticks = 0;
            sprite->source = effect_data;
        }
        motion->z.v = (s32) (motion->z.v
            + motion->velocity_z);
        fall_random = rand();
        fall_velocity = motion->velocity_z + 0x1C000;
        fall_velocity += fall_random >> 1;
        motion->velocity_z = fall_velocity;
        if ((u8) sprite->color.c.r < 0x80) {
            sprite->color.word = (s32) ((s32) sprite->color.word + 0x40404);
        }
        ground_height = sample_terrain_surface_height(((u16) motion->x.w.i), ((u16) motion->y.w.i),
            (s16) (((u16)view_reference_entity.z.w.i) - 0x80));
        if (motion->z.w.i >= (ground_height - 0x20)) {
            particle_index = 4;
            do {
                particle = allocate_list_node(0x312, &scene_object_list_anchor.next);
                if (particle != NULL) {
                    particle->update_callback = (void *)move_sprite_until_animation_ends;
                    register_node(particle, project_sprite_chain);
                    particle_sprite = particle->sprite;
                    (particle->position)->x.v =
                        (s32) (motion->x.v + (((rand() & 0x3FF) - 0x1FF) << 0xA));
                    (particle->position)->y.v =
                        (s32) (motion->y.v + (((rand() & 0x3FF) - 0x1FF) << 0xA));
                    (particle->position)->z.v =
                        (s32) (motion->z.v + (((rand() & 0x3FF) - 0x1FF) << 0xA));
                    (particle->position)->velocity_x =
                        (s32) (((rand() & 0x3FF) - 0x1FF) << 0xA);
                    (particle->position)->velocity_y =
                        (s32) (((rand() & 0x3FF) - 0x1FF) << 0xA);
                    particle_work = ((void *)particle) + 0x20;
                    (particle->position)->velocity_z =
                        (s32) (0 - ((rand() & 0x3FF) << 8));
                    particle_color = 0xC00000;
                    particle_sprite->scale_y = 0xC00;
                    particle_sprite->scale_x = 0xC00;
                    particle_sprite->tpage_abr = 0x20;
                    particle_sprite->unk_00 = homing_particle_sprite_entries;
                    particle_sprite->flags = (u16) (particle_sprite->flags | 0xC);
                    particle_frames = ((SpriteSourceEntry *)homing_particle_sprite_entries)->source;
                    particle_color |= 0x6060;
                    particle_sprite->unk_04 = 0;
                    particle_sprite->frame_ticks = 0;
                    particle_sprite->color.word = particle_color;
                    particle_sprite->source = particle_frames;
                    effect_data = ((S_8197D468_0 *)effect)->unk_00;
                    ((S_8197D468_5 *)particle)->unk_20 = effect_data;
                    ((S_8197D468_8 *)particle_work)->unk_4C = 0;
                }
                particle_index -= 1;
            } while (particle_index >= 0);
            (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_8197D468_0_pre *)effect)[-1].unk_00 | NODE_REMOVE);
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }
}
