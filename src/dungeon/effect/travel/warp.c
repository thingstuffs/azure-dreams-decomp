#include "shared/object_node.h"
#include "shared/gpu_packets.h"
#include "shared/dungeon_effect_status.h"
#include "shared/object_node_flags.h"
#include "shared/audio_commands.h"
/* Warp sequencing, camera effects, linked sprite pieces, particle trails, and color fades. */
#include "modules/dungeon_ovl_19cc800.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "dungeon/effect.h"
#include "dungeon/item/position.h"
#include "dungeon/system.h"

void (*const dungeon_19cc800_entry)(struct EventState *event) = run_warp_effect_sequence;
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct EventState {
    void *source;
    u8 pad04[6];
    s16 state;
    s32 result;
    u8 pad10[0xA];
    s16 timer1A;
    s16 timer1C;
    u8 pad1E[2];
    s16 mode20;
    s16 timer22;
} EventState;

typedef struct DungeonObject {
    u8 pad00[0xA6];
    u16 countA6;
    u8 colorA8;
    u8 padA9;
    u8 colorAA;
    u8 padAB[0x49];
    s32 resultF4;
    u8 padF8[0xA];
    u8 flag102;
} DungeonObject;

extern u8 D_80028260[];
extern u8 D_80028780[];
extern s16 D_800287A0;

extern void upload_vram_row_and_cache(void *, s32, s32, s32); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern s32 decode_and_upload_image(void *, void *);

/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol add_flag_adjusted_target_value).  The state table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */

/* Advances a dungeon event through setup, activation, timed color fades, and cleanup. */
void run_warp_effect_sequence(EventState *event) {
    s32 setup[2];
    GameWork *colors;
    s32 state;

    colors = &g_game_work;
    state = event->state;
    switch (state) {
    case 0:
    {
        ActorRecord *object;
        u8 event_option;

        setup[0] = 0x010003A0;
        setup[1] = 0x00400020;
        decode_and_upload_image(D_80028260, setup);
        upload_vram_row_and_cache(D_80028780, 0x7AC0, 1, 2);
        object = primary_actor_record;
        D_800287A0 = 1;
        event_option = ((u8 *)event)[9];
        warp_position_phase = 0;
        warp_attack_option = event_option;
        warp_attack_event = event->source;
        ((PlayerRecord *)object)->unk_F4 = 0;
        (*(u8 *)&object->unk_A8) = ((u8 *)event)[8];
        ((PlayerRecord *)primary_actor_record)->unk_102 = 1;
        event->state++;
    }
    case 1:
        if ((**(u16 **)((u8 *)event + 4) & 0x80) == 0) {
            break;
        }
        event->result = (s32)create_warp_phase_effect(*(void **)(*(u8 **)event - 0x18), event->source);
        if (event->result == 0) {
            break;
        }
        event->mode20 = -1;
        event->timer22 = 0x20;
        event->timer1C = 0x10;
        primary_actor_record->unk_A4.halves.high.u--;
        event->state++;
        play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
        break;

    case 2:
    {
        s16 wait_ticks;

        wait_ticks = (s16)(event->timer1C - 1);
        event->timer1C = wait_ticks;
        if (wait_ticks >= 0) {
            break;
        }
    }
        event->state++;
        break;

    case 3:
        D_800287A0 = 0;
        event->timer1A = 0x20;
        event->mode20 = 0;
        event->state++;
        break;

    case 4:
    {
        s16 fade_ticks;

        colors->view.tint.parts.tint_r += (u8)((0x80 - colors->view.tint.parts.tint_r) / event->timer1A);
        colors->view.tint.parts.tint_b += (u8)((0x80 - colors->view.tint.parts.tint_b) / event->timer1A);
        fade_ticks = (s16)(event->timer1A - 1);
        event->timer1A = fade_ticks;
        if (fade_ticks > 0) {
            break;
        }
        colors->view.tint.parts.tint_b = 0x80;
        colors->view.tint.parts.tint_r = 0x80;
    }
        event->state++;
        break;

    case 5:
        if (*(s16 *)warp_effect_counters == 0) {
            {
                g_dungeon_status.active_actor = 0;
                g_dungeon_status.activity_counts.parts.pending_action_count--;
            }
            *(u16 *)((u8 *)event - 2) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
    if (event->mode20 < 0) {
        s16 fade_ticks;

        colors->view.tint.parts.tint_r += (u8)((0x20 - colors->view.tint.parts.tint_r) / event->timer22);
        colors->view.tint.parts.tint_b += (u8)((0x20 - colors->view.tint.parts.tint_b) / event->timer22);
        fade_ticks = (s16)(event->timer22 - 1);
        event->timer22 = fade_ticks;
        if (fade_ticks <= 0) {
            event->mode20 = 0;
        }
    }
    *(s16 *)warp_effect_counters = 0;
}

#include "shared/slus_callbacks.h"
#include "records/Rec_func_800249DC_arg0.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/effect/travel/warp_phase_effect.h"


typedef struct S_819ACB28_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_819ACB28_1;   /* data_ptr in advance_effect_phases */

   /* offsets in advance_effect_phases */

typedef struct S_819ACB28_4 {
    u8 pad_00[0xC];
    u32 unk_0C;
} S_819ACB28_4;   /* packed_value in advance_effect_phases */

typedef struct S_819ACB28_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_819ACB28_5;   /* source_node in advance_effect_phases */

typedef struct CounterView {
    u16 value;
    u16 pad[5];
} CounterView;

typedef struct FlagsView {
    s32 value;
    s32 pad[2];
} FlagsView;

/* Follows the source sprite's offset, waits for target movement to finish, then brightens and fades
   the effect. */
void advance_effect_phases(WarpPhaseEffectBody *object, Rec_func_800249DC_arg0 *record, S_819ACB28_4 *packed_value)
{
    s16 mode;
    u16 mode_value;
    MovingPosition *offsets;
    S_819ACB28_1 *data_ptr;

    warp_effect_counters[0] = warp_effect_counters[0] + 1;
    mode = object->phase;
    mode_value = (u16)object->phase;

    if (mode == 0) {
        data_ptr = ((S_819ACB28_5 *)object->source_node_address)->unk_0C;
        if (object->initialized == 0) {
            if (resolve_record_orientation_or_fallback(data_ptr->unk_08, data_ptr,
                              &object->offset_x, 0) == 0) {
                if (data_ptr->unk_14 & 0x8000) {
                    object->offset_z = -0x40;
                }
            }
            object->initialized = 1;
        }

        offsets = ((S_819ACB28_5 *)object->source_node_address)->unk_08;
        record->unk_00.at02_s16.v =
            offsets->x + object->offset_x;
        record->unk_06 =
            offsets->y + object->offset_y;
        record->unk_0A =
            offsets->z + (u16)object->offset_z;
        if (spawn_nine_warp_trail_sprites(record) != 0) {
            register_node(NODE_HEADER(object), project_sprite_chain);
            object->phase = (u16)((u16)object->phase + 1);
            return;
        }
    } else if (mode == 1) {
        if ((u8)packed_value->unk_0C < 0xC0) {
            packed_value->unk_0C += 0x202020;
            return;
        }
        object->phase = mode_value + 1;
        return;
    } else if (mode == 2) {
        packed_value->unk_0C += 0xFFEFEFF0;
        if ((u8)packed_value->unk_0C == 0) {
            NODE_HEADER(object)->flags |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
}


#ifndef NULL
#define NULL 0
#endif

/* Position block (three 4-byte slots, only the second halfword of each is used). */

/* The render data the header's unk_0C points at. */

void draw_textured_ellipse(void *parameters, GpuRect *rectangle, u16 fill_rect, u16 draw_mode);
extern u8 D_8002746C[9];

/* Allocate and initialize an effect object from the supplied part data. */
void *create_warp_phase_effect(EntityRec *source_pos, s32 offset_base) {
    GpuRectBuffer init_data;
    ObjectNodeHeader *object;
    WarpPhaseEffectBody *record;
    ObjectPosition *pos;
    SpriteFrameState *sprite;
    void *result;

    object = allocate_flagged_object_node(0x12);
    if (object != NULL) {
        init_data.words[0] = 0x01000340;
        init_data.words[1] = 0x00200020;
        draw_textured_ellipse(D_8002746C, &init_data.rect, 1, 0);

        pos = object->position;
        object->update_callback = advance_effect_phases;
        pos->x.w.i = (u16)source_pos->x.w.i;
        pos->y.w.i = (u16)source_pos->y.w.i;
        pos->z.w.i = (u16)source_pos->z.w.i;

        sprite = object->sprite;
        sprite->source = warp_sprite_entries;
        sprite->scale_y = 0xC00;
        sprite->scale_x = 0xC00;
        record = NODE_BODY(object);
        record->source_node_address = offset_base - 0x20;
    }

    result = NULL;
    if (object != NULL) {
        result = NODE_BODY(object);
    }
    return result;
}

#include "shared/tile_object.h"
#include "shared/entity_objects.h"

typedef struct S_819ACDA0_1 {
    u8 pad_00[0x2C];
    u16 unk_2C;
} S_819ACDA0_1;   /* motion in func_819ACDA0 */

typedef struct Motion {
    u8 pad0[0x14];
    s16 target_x;
    s16 target_y;
    s16 target_z;
    u8 pad1A[2];
    s16 current_x;
    s16 current_y;
    s16 current_z;
    u8 pad22[0xA];
    s16 state;
    u8 pad2E[2];
    s16 timer;
    u8 pad32[2];
    s16 effect_timer;
    u8 pad36[2];
    s16 phase;
} Motion;

typedef struct Position {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    s16 z;
    u8 padC[2];
    s16 next_x;
    u8 pad10[2];
    s16 next_y;
    u8 pad14[2];
    s16 next_z;
} Position;

typedef struct Vec3u {
    u16 x;
    u16 y;
    u16 z;
} Vec3u;

extern void **actor_direction_sprites;

extern void spawn_blinking_sprite_flash(s16, s16, s16);

/* Run the warp cutscene: pick the exit point, ease the camera to it, fade out and fire the arrival effects. */
void run_warp_cutscene(Motion *motion, Position *position, u8 *color)
{
    Vec3u delta;
    Vec3u base;
    register ActorRecord *entity;
    TileObject *source;
    u16 final_state;
    s32 index;

    *warp_effect_counters = *warp_effect_counters + 1;

    switch (motion->state) {
    case 0:
        base.x = view_reference_entity.x.w.i;
        base.y = view_reference_entity.y.w.i;
        entity = dungeon_actor_ring_anchor;
        base.z = entity->ground_height - 0x50;
        index =
            ((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 7) & 0x1C;

        resolve_record_orientation_or_fallback(
            *(void **)(index + (long)actor_direction_sprites),
            ((&reference_tile_object)), &delta, 0);

        base.x += delta.x;
        motion->target_x = base.x;
        base.y += delta.y;
        motion->target_y = base.y;
        base.z += delta.z;
        motion->target_z = base.z;
        motion->state++;

    case 1:
        position->next_x +=
            (motion->current_x +
             ((motion->target_x - motion->current_x) / 8) *
                     (motion->phase + 1) -
             position->next_x) /
            motion->timer;

        position->next_y +=
            (motion->current_y +
             ((motion->target_y - motion->current_y) / 8) *
                     (motion->phase + 1) -
             position->next_y) /
            motion->timer;

        position->next_z +=
            (motion->current_z +
             ((motion->target_z - motion->current_z) / 8) *
                     (motion->phase + 1) -
             position->next_z) /
            motion->timer;

        motion->current_x += (position->next_x - motion->current_x) >> 2;
        position->x = motion->current_x;
        motion->current_y += (position->next_y - motion->current_y) >> 2;
        position->y = motion->current_y;
        motion->current_z += (position->next_z - motion->current_z) >> 2;
        position->z = motion->current_z;

        motion->timer--;
        if (motion->timer > 0) {
            return;
        }
        spawn_blinking_sprite_flash(motion->target_x, motion->target_y, motion->target_z);
        final_state = ((S_819ACDA0_1 *)motion)->unk_2C;
        motion->timer = 5;
        motion->state = final_state + 1;
        return;
    case 2:
        color[0xD] -= color[0xD] / motion->timer;
        motion->timer--;
        if (motion->timer > 0) {
            return;
        }
        if (motion->phase == 0) {
            color[0xD] = 0;
            motion->effect_timer = 4;
            D_80027450 = 0;
            motion->state++;
            return;
        }
        break;

    case 3:
        source = &reference_tile_object;
        if (resolve_record_orientation_or_fallback(((void *)source->sprite_source), source, &base, 0) != 0) {
            spawn_warp_trail_sprites(
                view_reference_entity.x.w.i + base.x,
                view_reference_entity.y.w.i + base.y,
                view_reference_entity.z.w.i + base.z,
                dungeon_actor_ring_anchor->facing, 0);
        }

        motion->effect_timer--;
        if (motion->effect_timer > 0) {
            return;
        }
        create_linked_sprite_pieces(
            view_reference_entity.x.w.i,
            view_reference_entity.y.w.i,
            view_reference_entity.z.w.i - 0x20,
            dungeon_actor_ring_anchor->facing);

        break;
    default:
        return;
    }

    (*(u16 *)((u8 *)motion + -2)) |= NODE_REMOVE;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
}


#ifndef NULL
#define NULL 0
#endif

   /* src in func_819AD1DC */

typedef struct S_819AD1DC_3 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    u8 pad_22[0xE];
    s16 unk_30;
    u8 pad_32[0x6];
    s16 unk_38;
} S_819AD1DC_3;   /* part in func_819AD1DC */

/* Spawn the nine trail sprites at the source position, the last one larger and all fading with distance. */
void *spawn_nine_warp_trail_sprites(MovingPosition *src)
{
    s32 i;
    s32 *handler;
    s32 *sub_handler;
    register s32 last_index;
    ObjectNodeHeader *obj;
    s32 shade;
    u16 scale;
    u16 x;
    u16 y;
    u16 z;
    SpriteFrameState *render;
    S_819AD1DC_3 *part;
    ObjectPosition *coords;

    i = 0;
    handler = run_warp_cutscene;
    sub_handler = &warp_sprite_entries;
    last_index = 8;
    do {
        obj = allocate_flagged_object_node(18);
        if (obj != NULL) {
            obj->update_callback = handler;
            register_node(obj, draw_linked_segment_aligned_quads);
            coords = obj->position;
            x = src->x;
            part = NODE_BODY(obj);
            coords->x.w.i = x;
            *((u16 *)&coords->velocity_x + 1) = x;
            part->unk_1C = x;
            y = src->y;
            coords->y.w.i = y;
            *((u16 *)&coords->velocity_y + 1) = y;
            part->unk_1E = y;
            z = src->z;
            coords->z.w.i = z;
            *((u16 *)&coords->velocity_z + 1) = z;
            part->unk_20 = z;
            render = obj->sprite;
            render->source = sub_handler;
            if (i != last_index) {
                render->scale_y = 0x200U;
            } else {
                render->scale_y = 0x800U;
            }
            shade = -0x80 - ((s32)((last_index - i) * 4));
            scale = render->scale_y;
            render->color.c.g = (u8)shade;
            render->scale_x = scale;
            part->unk_38 = i;
            if (i == last_index) {
                part->unk_38 = 7;
            }
            part->unk_30 = last_index;
        }
        i += 1;
    } while (i < 9);
    return obj;
}

#include "modules/dungeon_native_abi.h"
#include "shared/dir_step.h"

/*
 * Update position, reduce movement speed, and flag completion when speed runs out.
 *
 * 16.16 fixed-point coordinate: the whole part is the high halfword.
 *
 * The effect record the callback runs on (the object header precedes it).
 */
void advance_effect_motion_and_speed(MotionRecord *motion, ObjectPosition *position)
{
    s16 next_speed;
    u16 update_count = warp_effect_counters[0];
    u16 z = position->z.w.i;
    u16 x = position->x.w.i;
    u16 y = position->y.w.i;

    warp_effect_counters[0] = update_count + 1;
    if (position->z.w.i < (s16)sample_terrain_surface_height(x, y, z + 2)) {
        position->x.v -= (dir_step_x[motion->direction] * motion->speed) << 11;
        position->y.v -= (dir_step_y[motion->direction] * motion->speed) << 11;
        position->z.v += (0xC0 - motion->speed) << 10;
    }

    next_speed = (u16)motion->speed - 8;
    motion->speed = next_speed;
    if ((next_speed << 16) <= 0) {
        NODE_HEADER(motion)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}


extern u8 D_80027484[12];
extern s32 queue_linked_visible_rectangle_copies(void *, void *, SpriteFrameState *);

/* Position block (three 4-byte slots, only the second halfword of each is used). */

/* The effect record (the object header precedes it). */

/* Render data the header's unk_0C points at. */

/* Spawn two pairs of effects at random offsets around the source. */
void update_effect_position_and_color(ObjectNodeHeader *source, s16 effect_param, s32 render_param)
{
    s32 remaining;
    ObjectNodeHeader *effect;
    MotionRecord *record;
    SpriteFrameState *sprite;
    remaining = 2;
    do {
        effect = allocate_list_node(0x212, &source->next);
        if (effect != 0) {
            effect->update_callback = advance_effect_motion_and_speed;
            register_node(effect, project_sprite_chain);
            record = NODE_BODY(effect);
            effect->position->x.w.i = (source->position->x.w.i + (rand() & 0x3F)) - 0x20;
            effect->position->y.w.i = (source->position->y.w.i + (rand() & 0x3F)) - 0x20;
            effect->position->z.w.i = (source->position->z.w.i + (rand() & 0x3F)) - 0x20;
            sprite = effect->sprite;
            sprite->source = D_80027484;
            sprite->scale_y = 0x1000;
            sprite->scale_x = 0x1000;
            sprite->color.word = render_param;
            sprite->depth_bias = 8;
            record->direction = effect_param;
            record->speed = (rand() & 0xFF) | 0x80;
        }
        remaining--;
    }
    while (remaining > 0);
    remaining = 2;
    do {
        effect = allocate_list_node(0x212, &source->next);
        if (effect != 0) {
            effect->update_callback = advance_effect_motion_and_speed;
            register_node(effect, queue_linked_visible_rectangle_copies);
            record = NODE_BODY(effect);
            effect->position->x.w.i = (source->position->x.w.i + (rand() & 0x3F)) - 0x20;
            effect->position->y.w.i = (source->position->y.w.i + (rand() & 0x3F)) - 0x20;
            effect->position->z.w.i = (source->position->z.w.i + (rand() & 0x3F)) - 0x20;
            record->unk_00 = 0x20;
            record->unk_02 = 0x20;
            record->unk_04 = 1;
            record->unk_06 = 0;
            record->direction = effect_param;
            record->speed = (rand() & 0xFF) | 0x80;
        }
        remaining--;
    }
    while (remaining > 0);
}


/* Position block (three 4-byte slots, only the second halfword of each is used). */

/* Render data (the header's unk_0C); only the colour word is used here. */
typedef struct RenderData {
    u8 pad_00[0xC];
    s32 color;
} RenderData;

/*
 * Copy the owner's position and colour; flag completion once the owner is finished.
 *
 * The follower's record (the object header precedes it): it tracks the object stored at +8.
 */
void copy_follower_owner_position_and_color(FollowerRecord *record, ObjectPosition *position, RenderData *render)
{
    ObjectNodeHeader *owner;
    ObjectPosition *owner_pos;
    s32 owner_done;

    owner = record->owner;
    owner_done = owner->flags & 0x8000;
    warp_effect_counters[0]++;
    if (owner_done != 0) {
        NODE_HEADER(record)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
    render->color = owner->sprite->color.word;
    owner_pos = record->owner->position;
    position->x.w.i = (u16)owner_pos->x.w.i;
    position->y.w.i = (u16)owner_pos->y.w.i;
    position->z.w.i = (u16)owner_pos->z.w.i;
}


/* Position block (three 4-byte slots, only the second halfword of each is used). */

/* Render data the header's unk_0C points at. */

/* The follower's record (the object header precedes it). */

typedef struct Rect {
    s32 first;
    s32 second;
} Rect;

void draw_textured_ellipse(void *parameters, GpuRect *rectangle, u16 fill_rect, u16 draw_mode);
extern u8 D_80027454[12];
extern u8 D_80027490[12];
extern u8 D_800274A8[12];

/* Creates an object at its owner's position and initializes its sprite and angle. */
void create_warp_follower_sprite(ObjectNodeHeader *owner, s16 angle) {
    GpuRectBuffer rect;
    ObjectNodeHeader *spawned;
    SpriteFrameState *sprite;
    FollowerRecord *record;

    spawned = allocate_list_node(0x212, &owner->next);
    if (spawned != 0) {
        spawned->update_callback = (follower_position_update_fn)copy_follower_owner_position_and_color;
        register_node(spawned, project_sprite_chain);
        spawned->position->x.w.i = (u16)owner->position->x.w.i;
        spawned->position->y.w.i = (u16)owner->position->y.w.i;
        spawned->position->z.w.i = (u16)owner->position->z.w.i;
        sprite = spawned->sprite;
        sprite->source = D_80027454;
        sprite->scale_y = 0x2800;
        sprite->scale_x = 0x2800;
        sprite->depth_bias = 8;
        sprite->angle_z = angle + 0x400;
        record = NODE_BODY(spawned);
        sprite->color.word = 0x808080;
        record->owner = owner;
        record->angle = angle;
        rect.words[0] = 0x01400340;
        rect.words[1] = 0x200020;
        draw_textured_ellipse(D_80027490, &rect.rect, 0, 0);
        draw_textured_ellipse(D_800274A8, &rect.rect, 1, 0);
    }
}

#include "m2c_compat.h"


typedef struct S_819AD81C_1 {
    s32 unk_00;
    s8 unk_04;
    u8 pad_05[0x7];
    union {
        struct { u8 v; } at00;
        struct { s32 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
    } unk_0C;   /* overlapping accesses */
    u8 pad_10[0x4];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
} S_819AD81C_1;   /* gfx in func_819AD81C */

typedef struct S_819AD81C_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_0C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_10;   /* overlapping accesses */
    s32 unk_14;
} S_819AD81C_2;   /* motion in func_819AD81C */

typedef struct S_819AD81C_3 {
    u8 pad_00[0x34];
    s16 unk_34;
    u8 pad_36[0x26];
    union { void * p; s32 i; } unk_5C;   /* accessed as both */
    u8 pad_60[0x28];
    s16 unk_88;
} S_819AD81C_3;   /* node in func_819AD81C */

   /* info in func_819AD81C */

   /* link in func_819AD81C */

s32 rsin();
s32 rcos();
void PushMatrix();
void PopMatrix(void);
void RotTrans(void *, void *, s32 *);
void apply_attack_power_and_element_effects();
s32 check_left_tile_and_center_height(s32 x, s32 y, s32 z);
void spawn_opposite_offset_effect(void *source_data, u32 direction_bits);
extern s8 D_8002758C[];

/* Per-frame homing-projectile step: fade in/out, fly toward the target tile, wake anything it passes and expire. */
void update_warp_camera_and_effects(LinkedWarpProjectileBody *entity, void *motion, void *gfx) {
    typedef struct Local20 {
        s16 unk0;
        u16 unk2;
        s16 unk4;
        u16 unk6;
        s16 unk8;
        u16 unkA;
        s32 unkC;
        s32 unk10;
        s32 unk14;
    } Local20;
    typedef struct Local38 {
        s16 unk0;
        s16 unk2;
        s16 unk4;
        s16 pad;
    } Local38;
    Local20 warp_params;
    Local38 zero_vec;
    s32 rotated;
    s16 phase;
    s16 fade_left;
    s16 fade_left_out;
    s16 hits_left;
    s32 tile_y;
    s32 component;
    s32 dz;
    s8 level;
    s8 want_kind;
    u8 tint;
    u8 next_tint;
    u8 tint_out;
    u8 next_tint_out;
    u16 saved_x;
    u16 saved_y;
    ActorRecord *node;
    ObjectNodeHeader *attached;
    SpriteFrameState *info;
    void *head;
    void *link;

    link = entity->linked_node;
    if (link == 0) {
        phase = entity->phase;
        if (phase == 0) {
            tint = ((S_819AD81C_1 *)gfx)->unk_0C.at00.v;
            next_tint = tint + ((s32) (0x80 - tint) / entity->fade_ticks);
            ((S_819AD81C_1 *)gfx)->unk_0C.at00.v = next_tint;
            ((S_819AD81C_1 *)gfx)->unk_0C.at01.v = next_tint;
            ((S_819AD81C_1 *)gfx)->unk_0C.at02.v = next_tint;
            fade_left = (u16) entity->fade_ticks - 1;
            entity->fade_ticks = fade_left;
            if ((fade_left << 0x10) <= 0) {
                ((S_819AD81C_1 *)gfx)->unk_0C.at00u.v = 0x808080;
                entity->phase = (u16) ((u16) entity->phase + 1);
            }
        } else if (phase >= 2) {
            tint_out = ((S_819AD81C_1 *)gfx)->unk_0C.at00.v;
            next_tint_out = tint_out - ((s32) tint_out / (s16) entity->fade_ticks);
            ((S_819AD81C_1 *)gfx)->unk_0C.at00.v = next_tint_out;
            ((S_819AD81C_1 *)gfx)->unk_0C.at01.v = next_tint_out;
            ((S_819AD81C_1 *)gfx)->unk_0C.at02.v = next_tint_out;
            fade_left_out = (u16) entity->fade_ticks - 1;
            entity->fade_ticks = fade_left_out;
            if ((fade_left_out << 0x10) <= 0) {
                ((S_819AD81C_1 *)gfx)->unk_0C.at00u.v = 0;
                NODE_HEADER(entity)->flags = (u16) (NODE_HEADER(entity)->flags | NODE_REMOVE);
                object_flag_block.flags |= OBJECT_REMOVE_PENDING;
                return;
            }
            if (entity->phase >= 3) {
                return;
            }
        }
        ((S_819AD81C_2 *)motion)->unk_0C.at00.v = (s32) (rcos(entity->heading) << 8);
        ((S_819AD81C_2 *)motion)->unk_10.at00.v = (s32) (rsin(entity->heading) << 8);
        level = ((S_819AD81C_1 *)gfx)->unk_04;
        if (level < 3) {
            component = ((S_819AD81C_2 *)motion)->unk_0C.at00.v;
            component -= component >> (level + 1);
            ((S_819AD81C_2 *)motion)->unk_0C.at00.v = component;
            ((S_819AD81C_2 *)motion)->unk_10.at00.v -= ((S_819AD81C_2 *)motion)->unk_10.at00.v >> (((S_819AD81C_1 *)gfx)->unk_04 + 1);
        }
        ((S_819AD81C_2 *)motion)->unk_08.at00.v = (s32) (((S_819AD81C_2 *)motion)->unk_08.at00.v
            - ((S_819AD81C_2 *)motion)->unk_14);
        ((S_819AD81C_2 *)motion)->unk_00.at00.v = (s32) (((S_819AD81C_2 *)motion)->unk_00.at00.v
            + ((S_819AD81C_2 *)motion)->unk_0C.at00.v);
        ((S_819AD81C_2 *)motion)->unk_04.at00.v = (s32) (((S_819AD81C_2 *)motion)->unk_04.at00.v
            + ((S_819AD81C_2 *)motion)->unk_10.at00.v);
        ((S_819AD81C_2 *)motion)->unk_08.at00.v = (s32) (((S_819AD81C_2 *)motion)->unk_08.at00.v
            + ((S_819AD81C_2 *)motion)->unk_14);
        ((S_819AD81C_1 *)gfx)->unk_16 = 0x400U;
        ((S_819AD81C_1 *)gfx)->unk_1A = (u16) (calculate_planar_heading(0, 0, ((S_819AD81C_2 *)motion)->unk_0C.at02.v,
            ((S_819AD81C_2 *)motion)->unk_10.at02.v) - 0x400);
        advance_animation_index_within_bounds(gfx, &entity->animation_index, entity->animation_start, entity->animation_end);
        copy_anim_entry_and_widen_fields((struct FrameState *)entity, ((S_819AD81C_1 *)gfx)->unk_00);
        if (((S_819AD81C_1 *)gfx)->unk_14 & 0x4000) {
            ((S_819AD81C_1 *)gfx)->unk_04 = 0;
        }
        if (entity->hits_left > 0) {
            entity->current_tile.tile.x = (s16) ((s16) ((S_819AD81C_2 *)motion)->unk_00.at02.v / 64);
            tile_y = (s16) ((S_819AD81C_2 *)motion)->unk_04.at02.v / 64;
            entity->current_tile.tile.y = (s16) tile_y;
            if (entity->previous_tile.packed != entity->current_tile.packed) {
                if ((check_left_tile_and_center_height(((entity->current_tile.tile.x << 6) + 0x20) & 0xFFE0,
                    ((tile_y << 6) + 0x20) & 0xFFE0, ((S_819AD81C_2 *)motion)->unk_08.at02.v) << 0x10) != 0) {
                    entity->fade_ticks = 4;
                    entity->phase = 3;
                    return;
                }
                node = primary_actor_record;
                head = node;
                link = ((S_819AD81C_3 *)node)->unk_5C.p;
                node = NODE_BODY(link);
                if (node != head) {
                    do {
                        info = NODE_HEADER(node)->sprite;
                        if (info->tile_x == entity->current_tile.tile.x) {
                            if (info->tile_y == entity->current_tile.tile.y) {
                                dz = node->ground_height;
                                component = ((S_819AD81C_2 *)motion)->unk_08.at02.v;
                                dz -= component;
                                if (dz < 0) {
                                    dz = 0 - dz;
                                }
                                if (dz < 0x40) {
                                    /*
                                     * BUG: Gaia Shoot passes water flags 0xA instead of wind flags 0xC, so
                                     * damage affinity and the impact effect use water.
                                     * Found and documented by the Azure Dreams community
                                     * (adrando.com/guide/bugs.html).
                                     */
                                    apply_attack_power_and_element_effects(node, 0xC, warp_attack_option, 0xA,
                                        (s32) (s16) (entity->damage_power << 9), warp_attack_event, 2);
                                }
                            }
                        }
                        node = NODE_BODY(node->next_actor_header);
                    } while (node != (void *) (primary_actor_record));
                }
                saved_x = (u16) entity->current_tile.tile.x;
                hits_left = (u16) entity->hits_left;
                saved_y = (u16) entity->current_tile.tile.y;
                hits_left -= 1;
                entity->hits_left = hits_left;
                entity->previous_tile.tile.x = saved_x;
                entity->previous_tile.tile.y = saved_y;
                if ((hits_left << 0x10) <= 0) {
                    entity->fade_ticks = 4;
                    entity->phase = (s16) ((u16) entity->phase + 1);
                }
            }
        }
        create_positioned_linked_mesh_effect(((S_819AD81C_2 *)motion)->unk_00.at02.v, ((S_819AD81C_2 *)motion)->unk_04.at02.v,
            ((S_819AD81C_2 *)motion)->unk_08.at02.v, entity->heading);
        create_fading_copy_effect(entity, motion, gfx);
        return;
    } else {
        attached = (void *) ((s32) link | 0x80000000);
        if (attached->flags & 0x8000) {
            NODE_HEADER(entity)->flags = (u16) (NODE_HEADER(entity)->flags | NODE_REMOVE);
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            return;
        }
        link = attached->position;
        info = attached->sprite;
        ((S_819AD81C_2 *)motion)->unk_00.at02.v = (s16) ((MovingPosition *)link)->x;
        ((S_819AD81C_2 *)motion)->unk_04.at02.v = (s16) ((MovingPosition *)link)->y;
        ((S_819AD81C_2 *)motion)->unk_08.at02.v = (s16) ((MovingPosition *)link)->z;
        ((S_819AD81C_1 *)gfx)->unk_16 = (u16) info->angle_x;
        ((S_819AD81C_1 *)gfx)->unk_18 = (u16) info->angle_y;
        ((S_819AD81C_1 *)gfx)->unk_1A = (u16) info->angle_z;
        ((S_819AD81C_1 *)gfx)->unk_1C = (u16) info->scale_x;
        ((S_819AD81C_1 *)gfx)->unk_1E = (u16) info->scale_y;
        ((S_819AD81C_1 *)gfx)->unk_20 = (u16) info->offset_x;
        ((S_819AD81C_1 *)gfx)->unk_0C.at00u.v = info->color.word;
        want_kind = D_8002758C[entity->piece_index];
        node = NODE_BODY(attached);
        if ((want_kind >= 0) && (info->unk_04 == want_kind)) {
            PushMatrix(attached);
            set_effect_gte_matrix(entity, motion, gfx);
            zero_vec.unk0 = 0;
            zero_vec.unk2 = 0;
            zero_vec.unk4 = 0;
            RotTrans(&zero_vec, motion + 0xC, &rotated);
            PopMatrix();
            warp_params.unk2 = (u16) ((S_819AD81C_2 *)motion)->unk_0C.at00.v;
            warp_params.unk6 = (u16) ((S_819AD81C_2 *)motion)->unk_10.at00.v;
            warp_params.unkA = (u16) ((S_819AD81C_2 *)motion)->unk_14;
            warp_params.unkC = rcos(((S_819AD81C_3 *)node)->unk_34) * 0x10;
            warp_params.unk10 = rsin(((S_819AD81C_3 *)node)->unk_34) * 0x10;
            warp_params.unk14 = 0;
            spawn_opposite_offset_effect(&warp_params, ((S_819AD81C_3 *)node)->unk_34);
        }
        set_animation_entry_address(gfx, info->unk_04);
        copy_anim_entry_and_widen_fields((struct FrameState *)entity, ((S_819AD81C_1 *)gfx)->unk_00);
    }
}


typedef struct Obj Obj;

typedef struct S_800255B8_0 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
} S_800255B8_0;   /* *cur in create_linked_sprite_pieces */

typedef struct S_800255B8_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800255B8_1;   /* partA in create_linked_sprite_pieces */

typedef struct S_800255B8_2 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    s16 unk_16;
    u8 pad_18[0x2];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_800255B8_2;   /* partB in create_linked_sprite_pieces */

extern u8 D_80027580[];

extern s32 has_enough_available_nodes(s32 limit);

/* Reads the signed halfword at the supplied byte offset in the direction table. */
static __inline__ s16 dir_step(s16 *table, u16 offset) {
    return *(s16 *)(offset + (unsigned long)table);
}

/* Creates twelve linked sprite pieces at an offset from the given position and angle. */
void *create_linked_sprite_pieces(s16 x, s16 y, s16 z, s16 heading) {
    void *objects[12];
    s32 piece_index;
    s16 *x_offsets;
    TileObject *color_table;
    u8 *effect_state;
    u8 *link_data;
    S_800255B8_1 *component_data;
    u8 color_first;
    u32 color_second;
    u32 offset_addr;
    s32 x_offset;
    s32 y_offset;
    u16 sprite_flags;

    if (has_enough_available_nodes(12) == 0) {
        return 0;
    }

    piece_index = 0;
    x_offsets = dir_step_x;
    color_table = &reference_tile_object;
    do {
        {
            void *template;

            if (piece_index != 0) {
                template = objects[0];
            } else {
                template = ((&scene_object_list_anchor));
            }
            objects[piece_index] = allocate_list_node(2, template);
        }
        ((S_800255B8_0 *)objects[piece_index])->unk_10 = update_warp_camera_and_effects;
        register_node(objects[piece_index], draw_linked_model_chain);

        offset_addr = (heading >> 8) & 0xE;
        component_data = (S_800255B8_1 *)((S_800255B8_0 *)objects[piece_index])->unk_08;
        x_offset = dir_step(x_offsets, offset_addr) << 5;
        component_data->unk_02 = x + x_offset;
        y_offset = dir_step(dir_step_y, offset_addr) << 5;
        component_data->unk_0A = z;
        component_data->unk_06 = y + y_offset;

        effect_state = ((S_800255B8_0 *)objects[piece_index])->unk_0C;
        ((S_800255B8_2 *)effect_state)->unk_20 = 0x1000;
        ((S_800255B8_2 *)effect_state)->unk_1E = 0x1000;
        ((S_800255B8_2 *)effect_state)->unk_1C = 0x1000;
        ((S_800255B8_2 *)effect_state)->unk_08 = warp_piece_slots + (piece_index << 4);
        sprite_flags = ((S_800255B8_2 *)effect_state)->unk_14;
        ((S_800255B8_2 *)effect_state)->unk_10 = 0x20;
        ((S_800255B8_2 *)effect_state)->unk_16 = 0x400;
        ((S_800255B8_2 *)effect_state)->unk_1A = heading - 0x400;
        ((S_800255B8_2 *)effect_state)->unk_14 = sprite_flags | 0xC;

        effect_state = (u8 *)objects[piece_index] + 0x20;
        if (piece_index != 0) {
            u32 link_value;

            link_data = D_80027580 + piece_index;
            link_value = *link_data;
            if (link_value != 0) {
                link_data = (u8 *)0x7FFFFFFF;
                link_value = (u32)objects[link_value - 1] & (u32)link_data;
            } else {
                link_value = (u32)objects[piece_index - 1];
            }
            ((LinkedWarpProjectileBody *)effect_state)->linked_node = (void *)link_value;
        }

        ((LinkedWarpProjectileBody *)effect_state)->fade_ticks = 4;
        ((LinkedWarpProjectileBody *)effect_state)->animation_end = 15;
        ((LinkedWarpProjectileBody *)effect_state)->animation_index = 1;
        ((LinkedWarpProjectileBody *)effect_state)->heading = heading;
        ((LinkedWarpProjectileBody *)effect_state)->piece_index = piece_index;
        ((LinkedWarpProjectileBody *)effect_state)->hits_left = 8;
        color_first = color_table->tile_position.parts.tile_x;
        ((LinkedWarpProjectileBody *)effect_state)->current_tile.tile.x = color_first;
        ((LinkedWarpProjectileBody *)effect_state)->previous_tile.tile.x = color_first;
        color_second = color_table->tile_position.parts.tile_y;
        ((LinkedWarpProjectileBody *)effect_state)->current_tile.tile.y = color_second;
        ((LinkedWarpProjectileBody *)effect_state)->previous_tile.tile.y = color_second;
        piece_index++;
    } while (piece_index < 12);

    return objects[0];
}


/* The 0x20-byte current-frame block the entry is expanded into. */
typedef struct FrameState {
    PackedWords4 words;
    s16 field_10;
    s16 pad_12;
    s32 field_14;
    s32 field_18;
    s32 field_1C;
} FrameState;

/* Copies the animation entry, sign-extending its three byte fields into destination words. */
void copy_anim_entry_and_widen_fields(FrameState *dst, AnimEntry *src)
{
    s32 halfword;

    dst->words = src->words;
    halfword = src->field_10;
    dst->field_10 = halfword;
    dst->field_14 = src->field_12;
    dst->field_18 = src->field_13;
    dst->field_1C = src->field_14;
}


/*
 * Resolve the current entry, apply an index step, and enforce the index bounds.
 *
 * Animation player state; entry is the current entry in the owner's table (0x16-byte AnimEntry
 * stride).
 *
 * Owner of the animation table.
 */
void advance_animation_index_within_bounds(AnimPlayer *player, s16 *index_step, s32 min_index, s32 max_index) {
    s16 step;
    u32 clamp_flags;
    u8 index;
    s32 initial_index = (s8)player->index;
    AnimOwner *owner = player->owner;

    player->entry =
        owner->table + (initial_index * 22);
    step = *index_step;
    if (step > 0) {
        player->index = player->index + 1;
    } else if (step < 0) {
        player->index =
            player->index - 1;
    }
    index = player->index;
    if ((s8)index < (s16)min_index) {
        clamp_flags = player->flags | 0x4000;
        player->index = min_index;
        player->flags = clamp_flags;
        return;
    }
    if ((s8)index > (s16)max_index) {
        clamp_flags = player->flags | 0x4000;
        player->index = max_index;
        player->flags = clamp_flags;
        return;
    }
    player->flags &= 0xBFFF;
}


/*
 * Sets the player's current entry address using a 22-byte stride.
 *
 * Animation player state (see advance_animation_index_within_bounds): the first word is the
 * current entry in the owner's table.
 *
 * Owner of the animation table.
 */
void set_animation_entry_address(AnimPlayer *player, s16 entry_index) {
    player->entry = ((AnimOwner *)player->owner)->table + (entry_index * 0x16);
}


typedef struct S_8002593C_0 {
    u8 pad_00[0x40];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    u8 pad_4C[0x4];
    s16 unk_50;
    s16 unk_52;
    s16 unk_54;
    s16 unk_56;
    s16 unk_58;
    s16 unk_5A;
    s16 unk_5C;
    s16 unk_5E;
    s16 unk_60;
} S_8002593C_0;   /* scratch in set_effect_gte_matrix */

typedef struct S_8002593C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8002593C_1;   /* arg1 in set_effect_gte_matrix */

typedef struct S_8002593C_2 {
    u8 pad_00[0x16];
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
} S_8002593C_2;   /* arg2 in set_effect_gte_matrix */

#include "sdk/libgte_matrix.h"

extern void CompMatrix(void *, void *, void *);
extern void ReadRotMatrix(void *);
extern void TransMatrix(void *, void *);
extern void SetRotMatrix(void *);
extern void SetTransMatrix(void *);
extern void RotMatrixX(u16, void *);
extern void RotMatrixY(u16, void *);
extern void RotMatrixZ(u16, void *);

/* Build and install a transform from position, rotation, and a base matrix. */
void set_effect_gte_matrix(void *base_matrix, S_8002593C_1 *position, S_8002593C_2 *rotation)
{
    S_8002593C_0 *scratch = (S_8002593C_0 *)0x1F800000;
    MATRIX matrix;

    scratch->unk_40 = position->unk_02;
    scratch->unk_44 = position->unk_06;
    scratch->unk_48 = position->unk_0A;
    ReadRotMatrix(&matrix);

    scratch->unk_50 = scratch->unk_58 =
        scratch->unk_60 = 0x1000;
    scratch->unk_52 = scratch->unk_54 =
        scratch->unk_56 = scratch->unk_5A =
        scratch->unk_5C = scratch->unk_5E = 0;

    RotMatrixX(rotation->unk_16, &scratch->unk_50);
    RotMatrixZ(rotation->unk_1A, &scratch->unk_50);
    RotMatrixY(rotation->unk_18, &scratch->unk_50);
    TransMatrix(&scratch->unk_50, &scratch->unk_40);
    CompMatrix(&scratch->unk_50, base_matrix, (u8 *)scratch + 0xD0);
    SetTransMatrix((u8 *)scratch + 0xD0);
    SetRotMatrix((u8 *)scratch + 0xD0);
}


/* Fade RGB toward black and set flags when red falls below eight. */
void fade_warp_color_by_half(void *owner, ObjectPosition *unused, void *color_data) {
    u8 red;
    u8 green;
    u8 blue;

    *warp_effect_counters = *warp_effect_counters + 1;
    red = *((u8 *)color_data + 0xC);
    green = *((u8 *)color_data + 0xD);
    *((u8 *)color_data + 0xC) = red - (red >> 1);
    blue = *((u8 *)color_data + 0xE);
    *((u8 *)color_data + 0xD) = green - (green >> 1);
    *((u8 *)color_data + 0xE) = blue - (blue >> 1);
    if (*((u8 *)color_data + 0xC) < 8) {
        *((u16 *)owner - 1) |= 0x8000;
        *(u32 *)((u8 *)(&object_flag_block)) |= 0x8000;
    }
}


typedef struct Entry {
    s32 field_0;
    s8 field_4;
    u8 pad_5;
    s16 field_6;
    void *field_8;
} Entry;

extern void transform_shade_and_queue_model_quads(void *parent_matrix, void *translation, void *model, s16 depth_bias);

/* Processes twelve buffer slots for each entry in a linked state chain. */
s32 draw_warp_pieces(void *initial_state, s32 initial_value, Entry *initial_entry)
{
    void *state = initial_state;
    s32 value = initial_value;
    Entry *entry = initial_entry;
    u8 *slot_base;
    s32 slot_index;
    u8 *slot;
    Entry *entry_or_link;

    slot_base = warp_piece_slots;
    for (;;) {
        slot_index = 0;
        slot = slot_base;
        entry_or_link = entry;
        do {
            entry->field_8 = slot;
            slot += 0x10;
            set_animation_entry_address(entry_or_link, entry->field_4);
            slot_index++;
            copy_anim_entry_and_widen_fields(state, entry->field_0);
            transform_shade_and_queue_model_quads(state, value, entry, entry->field_6);
            entry_or_link = entry;
        } while (slot_index < 12);

    entry_or_link = *(void **)((u8 *)state - 8);
    if (entry_or_link == 0) {
        break;
    }
    state = (u8 *)entry_or_link + 0x20;
    value = *(s32 *)((u8 *)entry_or_link + 8);
    entry = *(Entry **)((u8 *)entry_or_link + 0xC);
}
return 0;
}


#ifndef NULL
#define NULL 0
#endif

   /* arg1 in create_fading_copy_effect */

typedef struct S_80025B78_4 {
    s32 unk_00;
    u8 unk_04;
    u8 pad_05[0x3];
    s32 unk_08;
    s32 unk_0C;
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
} S_80025B78_4;   /* arg2 in create_fading_copy_effect */

typedef struct Block32 {
    u8 bytes[0x20];
} Block32;

/* Creates an object and copies the supplied triplet, state fields, and 32-byte data block. */
void *create_fading_copy_effect(void *source_data, MovingPosition *source_triplet, S_80025B78_4 *source_state)
{
    ObjectNodeHeader *object;
    ObjectPosition *triplet;
    SpriteFrameState *state;

    object = allocate_flagged_object_node(0x202);
    if (object != NULL) {
        object->update_callback = fade_warp_color_by_half;
        register_node(object, draw_warp_pieces);
        triplet = object->position;
        triplet->x.w.i = source_triplet->x;
        triplet->y.w.i = source_triplet->y;
        triplet->z.w.i = source_triplet->z;
        state = object->sprite;
        state->scale_x = source_state->unk_1C;
        state->scale_y = source_state->unk_1E;
        state->offset_x = source_state->unk_20;
        state->angle_x = source_state->unk_16;
        state->angle_y = source_state->unk_18;
        state->angle_z = source_state->unk_1A;
        state->color.word = source_state->unk_0C;
        state->flags = source_state->unk_14;
        state->unk_00 = source_state->unk_00;
        state->source = source_state->unk_08;
        state->tpage_abr = source_state->unk_10;
        state->unk_04 = source_state->unk_04;
        *(Block32 *)NODE_BODY(object) = *(Block32 *)source_data;
    }
    return object;
}

#include "records/Rec_func_80025D28_arg0.h"

extern s32 rsin();
extern s32 rcos();

/* Update two animated points, fade their intensity, and flag expiration. */
void animate_waving_point_pair_and_fade(Rec_func_80025D28_arg0 *state, ObjectPosition *points, SpriteFrameState *appearance) {
    s32 phase_angle;
    s32 phase_step;
    s32 side_offset_x;
    s32 side_offset_y;
    s32 radial_offset_x;
    s32 radial_offset_y;
    s32 start_wave_x;
    s32 start_wave_y;
    s32 direction_x;
    s32 direction_y;
    s32 end_wave_x;
    s32 end_wave_y;
    s32 side_direction_x;
    s32 side_direction_y;
    u16 ticks_left;
    u8 intensity;

    phase_step = state->unk_38;
    phase_angle = (s16)(phase_step << 6);
    *warp_effect_counters = *warp_effect_counters + 1;
    start_wave_x = rsin(phase_angle);
    points->x.v = (state->unk_1C << 0x10) +
        ((s32)(start_wave_x * rcos(state->unk_36
            + 0x400) * state->unk_3E) >> 7);
    start_wave_y = rsin(phase_angle);
    points->y.v = (state->unk_1E << 0x10) +
        ((s32)(start_wave_y * rsin(state->unk_36
            + 0x400) * state->unk_3E) >> 7);
    points->z.v = (state->unk_20 << 0x10) +
        ((rcos(phase_angle) * state->unk_3E) << 5);
    end_wave_x = rsin(phase_angle);
    direction_x = rcos(state->unk_36 + 0x400);
    side_direction_x = rcos(state->unk_36 + 0x800);
    radial_offset_x = end_wave_x * direction_x;
    do {
        radial_offset_x *= state->unk_3E;
    } while (0);
    side_offset_x = side_direction_x * state->unk_40;
    points->velocity_x = (state->unk_1C << 0x10) +
        (radial_offset_x >> 7) + (side_offset_x << 6);
    end_wave_y = rsin(phase_angle, side_offset_x);
    direction_y = rsin(state->unk_36 + 0x400);
    side_direction_y = rsin(state->unk_36 + 0x800);
    radial_offset_y = end_wave_y * direction_y;
    do {
        radial_offset_y *= state->unk_3E;
    } while (0);
    side_offset_y = side_direction_y * state->unk_40;
    points->velocity_y = (state->unk_1E << 0x10) +
        (radial_offset_y >> 7) + (side_offset_y << 6);
    points->velocity_z = (state->unk_20 << 0x10) +
        ((rcos(phase_angle, side_offset_y) * state->unk_3E) << 5);
    state->unk_40 = (u16)state->unk_40 + 2;
    state->unk_38 = (u16)state->unk_38 + 1;
    intensity = appearance->color.c.g;
    appearance->color.c.g = intensity - (intensity >> 3);
    ticks_left = state->unk_30 - 1;
    state->unk_30 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        (*(u16 *)((u8 *)state + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    state->unk_34 = state->unk_34 + 1;
}

/* MECHANISM: Natural long-lived arguments and results produce the retail 0x30 frame and s5/s4/s3/s2/s1/s0 roles.
   A short raw signed-load local selects lh before the shift/truncation while preserving phase_angle in s1.
   Zero-operand scheduling barriers after both chained products reproduce retail multiply/mflo emission order. */


typedef struct S_80025FCC_3 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
    u8 pad_22[0xE];
    s16 unk_30;
    u8 pad_32[0x4];
    s16 unk_36;
    s16 unk_38;
    u8 pad_3A[0x4];
    s16 unk_3E;
    s16 unk_40;
} S_80025FCC_3;

/* Creates an effect at the supplied position and initializes its rendering and state. */
void *create_positioned_linked_mesh_effect(s16 x, s16 y, s16 z, s16 effect_param) {
    S_80025FCC_3 *effect_state;
    ObjectNodeHeader *effect;
    ObjectPosition *position;
    SpriteFrameState *render_state;

    effect = allocate_flagged_object_node(0x202);
    if (effect != NULL) {
        effect->update_callback = animate_waving_point_pair_and_fade;
        register_node(effect, draw_linked_segment_aligned_quads);
        position = effect->position;
        effect_state = NODE_BODY(effect);
        *((s16 *)&position->velocity_x + 1) = x;
        position->x.w.i = x;
        *((s16 *)&position->velocity_y + 1) = y;
        position->y.w.i = y;
        *((s16 *)&position->velocity_z + 1) = z;
        position->z.w.i = z;
        render_state = effect->sprite;
        render_state->scale_y = 0x200;
        render_state->scale_x = 0x200;
        render_state->color.c.g = 0x20;
        render_state->flags = 0xC;
        render_state->source = &warp_sprite_entries;
        render_state->tpage_abr = 0x20;
        effect_state->unk_30 = 0x20;
        effect_state->unk_3E = 0x10;
        effect_state->unk_36 = effect_param;
        effect_state->unk_40 = 0x18;
        effect_state->unk_38 = rand();
        effect_state->unk_1C = x;
        effect_state->unk_1E = y;
        effect_state->unk_20 = z;
    }
    return effect;
}


/* Colour bytes of the effect's render data. */
typedef struct EffectColor {
    u8 pad[12];
    u8 red;
    u8 green;
    u8 blue;
} EffectColor;

/* Fade the effect color and set flags when red falls below four. */
void fade_warp_color_by_quarter(void *record, ObjectPosition *unused, EffectColor *color) {
    u8 red;
    u8 green;
    u8 blue;

    warp_effect_counters[0]++;

    red = color->red;
    green = color->green;
    color->red = red - (red >> 2);
    blue = color->blue;
    color->green = green - (green >> 2);
    color->blue = blue - (blue >> 2);

    if (color->red < 4) {
        NODE_HEADER(record)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}


#ifndef NULL
#define NULL 0
#endif

typedef struct Coord {
    s16 unk0;
    s16 x;
    s16 unk4;
    s16 y;
    s16 unk8;
    s16 z;
} Coord;

typedef struct Prim {
    s32 unk0;
    s32 unk4;
    void *unk8;
    u32 color;
    s16 unk10;
    s16 unk12;
    u16 unk14;
    s16 unk16;
    s32 unk18;
    s16 unk1C;
    s16 unk1E;
} Prim;

typedef struct Actor {
    s32 unk0;
    s32 unk4;
    Coord *pos;
    Prim *prim;
    void *update;
    u8 pad14[0x50 - 0x14];
    s16 unk50;
} Actor;

extern Coord warp_motion_target;

extern s32 rsin(s32);
extern s32 rcos(s32);

/* Spawns an effect actor or builds a curved trail toward the saved position. */
void *spawn_warp_trail_sprites(s16 x, s16 y, s16 z, s16 angle, s16 spawn_actor) {
    Actor *actor;
    ObjectPosition *coord;
    SpriteFrameState *prim;
    s16 step_x;
    s16 step_y;
    s16 step_z;
    s16 trail_x;
    s16 trail_y;
    s16 trail_z;
    s32 trail_index;

    actor = NULL;
    if (spawn_actor != 0) {
        actor = allocate_flagged_object_node(530);
        if (actor != NULL) {
            actor->update = fade_warp_color_by_quarter;
            register_node(actor, project_sprite_chain);
            coord = actor->pos;
            coord->x.w.i = x;
            coord->y.w.i = y;
            coord->z.w.i = z;
            prim = actor->prim;
            prim->scale_y = 1024;
            prim->scale_x = 1024;
            prim->source = warp_sprite_entries;
            prim->color.word = 0x808080;
            prim->tpage_abr = 32;
            prim->flags |= 0xC;
            actor->unk50 = 16;
        }
    } else {
        if (D_80027450 == 3) {
            step_x = (warp_motion_target.x - x) / 16;
            step_y = (warp_motion_target.y - y) / 16;
            step_z = (warp_motion_target.z - z) / 16;
            trail_x = x + step_x;
            trail_y = y + step_y;
            trail_z = z + step_z;
            for (trail_index = 0; trail_index < 16; trail_index++) {
                spawn_warp_trail_sprites(trail_x + ((rcos(angle) * rsin(trail_index << 7)) >> 21),
                              trail_y + ((rsin(angle) * rsin(trail_index << 7)) >> 21),
                              trail_z, angle, 1);
                trail_x += step_x;
                trail_y += step_y;
                trail_z += step_z;
            }
        }
        if (D_80027450 == 0) {
            warp_motion_target.x = x;
            warp_motion_target.y = y;
            warp_motion_target.z = z;
        }
        D_80027450 = D_80027450 + 1;
    }
    return actor;
}
