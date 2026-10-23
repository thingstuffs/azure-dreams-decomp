/* Warp sequencing, camera effects, linked sprite pieces, particle trails, and color fades. */
#include "modules/dungeon_ovl_19cc800.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
void (*const dungeon_19cc800_entry)(struct EventState *event) = func_80024020;
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct EventState {
    u8 pad00[0xA];
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

extern s32 D_8002744C;
extern u8 D_80028260[];
extern u8 D_80028780[];
extern s16 D_800287A0;
extern u8 D_800287A2;
extern s32 D_800287A4;

extern void upload_vram_row_and_cache(void *, s32, s32, s32);
extern void decode_and_upload_image(void *, void *);

/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol add_flag_adjusted_target_value).  The state table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */

/* Advances a dungeon event through setup, activation, timed color fades, and cleanup. */
void func_80024020(EventState *event) {
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
        D_8002744C = 0;
        D_800287A2 = event_option;
        D_800287A4 = *(s32 *)event;
        ((PlayerRecord *)object)->unk_F4 = 0;
        object->unk_A8 = ((u8 *)event)[8];
        ((PlayerRecord *)primary_actor_record)->unk_102 = 1;
        event->state++;
    }
    case 1:
        if ((**(u16 **)((u8 *)event + 4) & 0x80) == 0) {
            break;
        }
        event->result = (s32)allocate_initialized_effect_object(*(void **)(*(u8 **)event - 0x18), *(void **)event);
        if (event->result == 0) {
            break;
        }
        event->mode20 = -1;
        event->timer22 = 0x20;
        event->timer1C = 0x10;
        ((DungeonObject *)primary_actor_record)->countA6--;
        event->state++;
        play_sound_if_enabled(0x300);
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
        if (*(s16 *)D_80027452 == 0) {
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
    *(s16 *)D_80027452 = 0;
}

#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "records/Rec_func_800249DC_arg0.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_819ACB28_0_pre {
    u16 unk_00;
} S_819ACB28_0_pre;   /* the 0x2 bytes before object in advance_effect_phases, addressed as object[-1] */

typedef struct S_819ACB28_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x18];
    u16 unk_24;
    u16 unk_26;
    union { s16 s; u16 u; } unk_28;   /* accessed as both */
    u8 pad_2A[0x2];
    union { s16 s; u16 u; } unk_2C;   /* accessed as both */
    s16 unk_2E;
} S_819ACB28_0;   /* object in advance_effect_phases */

typedef struct S_819ACB28_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_819ACB28_1;   /* data_ptr in advance_effect_phases */

   /* offsets in advance_effect_phases */

typedef struct S_819ACB28_4 {
    u8 pad_00[0xC];
    union { u8 u8; u32 u32; } unk_0C;   /* accessed as both */
} S_819ACB28_4;   /* packed_value in advance_effect_phases */

typedef struct S_819ACB28_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_819ACB28_5;   /* ((S_819ACB28_0 *)object)->unk_08 in advance_effect_phases */

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
void advance_effect_phases(void *object, Rec_func_800249DC_arg0 *record, S_819ACB28_4 *packed_value)
{
    s16 mode;
    u16 mode_value;
    MovingPosition *offsets;
    S_819ACB28_1 *data_ptr;

    D_80027452[0] = D_80027452[0] + 1;
    mode = ((S_819ACB28_0 *)object)->unk_2C.s;
    mode_value = ((S_819ACB28_0 *)object)->unk_2C.u;

    if (mode == 0) {
        data_ptr = ((S_819ACB28_5 *)(((S_819ACB28_0 *)object)->unk_08))->unk_0C;
        if (((S_819ACB28_0 *)object)->unk_2E == 0) {
            if (resolve_record_orientation_or_fallback(data_ptr->unk_08, data_ptr,
                              (u8 *)object + 0x24, 0) == 0) {
                if (data_ptr->unk_14 & 0x8000) {
                    ((S_819ACB28_0 *)object)->unk_28.s = -0x40;
                }
            }
            ((S_819ACB28_0 *)object)->unk_2E = 1;
        }

        offsets = ((S_819ACB28_5 *)(((S_819ACB28_0 *)object)->unk_08))->unk_08;
        record->unk_00.at02_s16.v =
            offsets->unk_02 + ((S_819ACB28_0 *)object)->unk_24;
        record->unk_06 =
            offsets->unk_06 + ((S_819ACB28_0 *)object)->unk_26;
        record->unk_0A =
            offsets->unk_0A + ((S_819ACB28_0 *)object)->unk_28.u;
        if (move_effect_toward_target(record) != 0) {
            register_node((u8 *)object - 0x20, project_sprite_chain);
            ((S_819ACB28_0 *)object)->unk_2C.u = ((S_819ACB28_0 *)object)->unk_2C.u + 1;
            return;
        }
    } else if (mode == 1) {
        if (packed_value->unk_0C.u8 < 0xC0) {
            packed_value->unk_0C.u32 += 0x202020;
            return;
        }
        ((S_819ACB28_0 *)object)->unk_2C.u = mode_value + 1;
        return;
    } else if (mode == 2) {
        packed_value->unk_0C.u32 += 0xFFEFEFF0;
        if (packed_value->unk_0C.u8 == 0) {
            ((S_819ACB28_0_pre *)object)[-1].unk_00 |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
}

#include "shared/entity.h"
#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"
#include "shared/object_node.h"

#ifndef NULL
#define NULL 0
#endif

/* Position block (three 4-byte slots, only the second halfword of each is used). */

/* The effect's record (the object header precedes it). */
typedef struct EffectRecord {
    u8 pad_00[8];
    s32 unk_08;         /* set to offset_base - 0x20 */
} EffectRecord;

/* The render data the header's unk_0C points at. */

extern void draw_textured_ellipse();
extern u8 D_8002746C[9];

/* Allocate and initialize an effect object from the supplied part data. */
void *allocate_initialized_effect_object(EntityRec *source_pos, s32 offset_base) {
    s32 init_data[2];
    ObjectNodeHeader *object;
    ObjectPosition *pos;
    SpriteFrameState *sprite;
    void *result;

    object = allocate_flagged_object_node(0x12);
    if (object != NULL) {
        init_data[0] = 0x01000340;
        init_data[1] = 0x00200020;
        draw_textured_ellipse(D_8002746C, init_data, 1, 0);

        pos = object->position;
        object->unk_10 = advance_effect_phases;
        pos->x.w.i = (u16)source_pos->x.w.i;
        pos->y.w.i = (u16)source_pos->y.w.i;
        pos->z.w.i = (u16)source_pos->z.w.i;

        sprite = object->sprite;
        sprite->source = D_80027460;
        sprite->scale_y = 0xC00;
        sprite->scale_x = 0xC00;
        ((EffectRecord *)(object + 1))->unk_08 = offset_base - 0x20;
    }

    result = NULL;
    if (object != NULL) {
        result = object + 1;
    }
    return result;
}

#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"

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

    *(u16 *)D_80027452 = *(u16 *)D_80027452 + 1;

    switch (motion->state) {
    case 0:
        base.x = view_reference_entity.x.w.i;
        base.y = view_reference_entity.y.w.i;
        entity = dungeon_actor_ring_anchor;
        base.z = ((u16)entity->ground_height) - 0x50;
        index =
            ((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 7) & 0x1C;

        resolve_record_orientation_or_fallback(
            *(void **)(index + (s32)actor_direction_sprites),
            ((u8 *)(&reference_tile_object)), &delta, 0);

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
            update_object_movement_proximity_reactions(
                view_reference_entity.x.w.i + base.x,
                view_reference_entity.y.w.i + base.y,
                view_reference_entity.z.w.i + base.z,
                ((ActorRecord *)((u8 *)dungeon_actor_ring_anchor))->facing, 0);
        }

        motion->effect_timer--;
        if (motion->effect_timer > 0) {
            return;
        }
        create_linked_sprite_pieces(
            view_reference_entity.x.w.i,
            view_reference_entity.y.w.i,
            view_reference_entity.z.w.i - 0x20,
            ((ActorRecord *)((u8 *)dungeon_actor_ring_anchor))->facing);

        break;
    default:
        return;
    }

    (*(u16 *)((u8 *)motion + -2)) |= NODE_REMOVE;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
}

#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"
#include "shared/dungeon_moving_views.h"

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
void *move_effect_toward_target(MovingPosition *src)
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
    sub_handler = &D_80027460;
    last_index = 8;
    do {
        obj = allocate_flagged_object_node(18);
        if (obj != NULL) {
            obj->unk_10 = handler;
            register_node(obj, process_linked_mesh_states_mode_0);
            coords = obj->position;
            x = src->unk_02;
            part = ((void *)obj) + 0x20;
            coords->x.w.i = x;
            *((u16 *)&coords->velocity_x + 1) = x;
            part->unk_1C = x;
            y = src->unk_06;
            coords->y.w.i = y;
            *((u16 *)&coords->velocity_y + 1) = y;
            part->unk_1E = y;
            z = src->unk_0A;
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

#include "shared/entity.h"
#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"
#include "modules/dungeon_native_abi.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/dir_step.h"

/* 16.16 fixed-point coordinate: the whole part is the high halfword. */

/* The effect record the callback runs on (the object header precedes it). */

/* Update position, reduce movement speed, and flag completion when speed runs out. */
void advance_effect_motion_and_speed(MotionRecord *motion, ObjectPosition *position)
{
    s16 next_speed;
    u16 update_count = D_80027452[0];
    u16 z = position->z.w.i;
    u16 x = position->x.w.i;
    u16 y = position->y.w.i;

    D_80027452[0] = update_count + 1;
    if (position->z.w.i < (s16)sample_terrain_surface_height(x, y, z + 2)) {
        position->x.v -= (dir_step_x[motion->direction] * motion->speed) << 11;
        position->y.v -= (dir_step_y[motion->direction] * motion->speed) << 11;
        position->z.v += (0xC0 - motion->speed) << 10;
    }

    next_speed = (u16)motion->speed - 8;
    motion->speed = next_speed;
    if ((next_speed << 16) <= 0) {
        ((ObjectNodeHeader *)motion - 1)->flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

#include "shared/entity.h"
#include "modules/dungeon_ovl_19cc800.h"
#include "modules/dungeon_native_abi.h"
#include "shared/slus_callbacks.h"

extern u8 D_80027484[12];
extern s32 queue_linked_visible_rectangle_copies(void *, void *, s16 *);

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
            effect->unk_10 = advance_effect_motion_and_speed;
            register_node(effect, (s32)project_sprite_chain);
            record = (MotionRecord *)(effect + 1);
            effect->position->x.w.i = (source->position->x.w.i + (rand() & 0x3F)) - 0x20;
            effect->position->y.w.i = (source->position->y.w.i + (rand() & 0x3F)) - 0x20;
            effect->position->z.w.i = (source->position->z.w.i + (rand() & 0x3F)) - 0x20;
            sprite = effect->sprite;
            sprite->source = D_80027484;
            sprite->scale_y = 0x1000;
            sprite->scale_x = 0x1000;
            sprite->color.word = render_param;
            sprite->unk_06 = 8;
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
            effect->unk_10 = advance_effect_motion_and_speed;
            register_node(effect, (s32)queue_linked_visible_rectangle_copies);
            record = (MotionRecord *)(effect + 1);
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

#include "shared/entity.h"
#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"

/* Position block (three 4-byte slots, only the second halfword of each is used). */

/* Render data (the header's unk_0C); only the colour word is used here. */
typedef struct RenderData {
    u8 pad_00[0xC];
    s32 color;
} RenderData;

/* The follower's record (the object header precedes it): it tracks the object stored at +8. */

/* Copy the owner's position and colour; flag completion once the owner is finished. */
void copy_follower_owner_position_and_color(FollowerRecord *record, ObjectPosition *position, RenderData *render)
{
    ObjectNodeHeader *owner;
    ObjectPosition *owner_pos;
    s32 owner_done;

    owner = record->owner;
    owner_done = owner->flags & 0x8000;
    D_80027452[0]++;
    if (owner_done != 0) {
        ((ObjectNodeHeader *)record - 1)->flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
    render->color = owner->sprite->color.word;
    owner_pos = record->owner->position;
    position->x.w.i = (u16)owner_pos->x.w.i;
    position->y.w.i = (u16)owner_pos->y.w.i;
    position->z.w.i = (u16)owner_pos->z.w.i;
}

#include "shared/entity.h"
#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"
#include "modules/dungeon_native_abi.h"
#include "shared/slus_callbacks.h"

/* Position block (three 4-byte slots, only the second halfword of each is used). */

/* Render data the header's unk_0C points at. */

/* The follower's record (the object header precedes it). */

typedef struct Rect {
    s32 first;
    s32 second;
} Rect;

void draw_textured_ellipse();
extern u8 D_80027454[12];
extern u8 D_80027490[12];
extern u8 D_800274A8[12];

/* Creates an object at its owner's position and initializes its sprite and angle. */
void func_80024EF8(ObjectNodeHeader *owner, s16 angle) {
    Rect rect;
    ObjectNodeHeader *spawned;
    SpriteFrameState *sprite;
    FollowerRecord *record;

    spawned = allocate_list_node(0x212, &owner->next);
    if (spawned != 0) {
        spawned->unk_10 = (follower_position_update_fn)copy_follower_owner_position_and_color;
        register_node(spawned, (s32)project_sprite_chain);
        spawned->position->x.w.i = (u16)owner->position->x.w.i;
        spawned->position->y.w.i = (u16)owner->position->y.w.i;
        spawned->position->z.w.i = (u16)owner->position->z.w.i;
        sprite = spawned->sprite;
        sprite->source = D_80027454;
        sprite->scale_y = 0x2800;
        sprite->scale_x = 0x2800;
        sprite->unk_06 = 8;
        sprite->angle_z = angle + 0x400;
        record = (FollowerRecord *)(spawned + 1);
        sprite->color.word = 0x808080;
        record->owner = owner;
        record->angle = angle;
        rect.first = 0x01400340;
        rect.second = 0x200020;
        draw_textured_ellipse(D_80027490, &rect, 0, 0);
        draw_textured_ellipse(D_800274A8, &rect, 1, 0);
    }
}

#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_819AD81C_0_pre {
    u16 unk_00;
} S_819AD81C_0_pre;   /* the 0x2 bytes before entity in func_819AD81C, addressed as entity[-1] */

typedef struct S_819AD81C_0 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0x8];
    union { s16 s; u16 u; } unk_2C;   /* accessed as both */
    u8 pad_2E[0x2];
    s16 unk_30;
    u8 pad_32[0x2];
    s16 unk_34;
    s16 unk_36;
    s16 unk_38;
    u8 pad_3A[0x2];
    union {
        struct { s16 v; } at00;
        struct { s32 v; } at00u;
        struct { u16 v; } at00p;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_3C;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x2]; u16 v; } at02;
    } unk_40;   /* overlapping accesses */
    u16 unk_44;
    union { s16 s; u16 u; } unk_46;   /* accessed as both */
    s16 unk_48;
} S_819AD81C_0;   /* entity in func_819AD81C */

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

typedef struct S_819AD81C_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x7];
    s32 unk_0C;
    u8 pad_10[0x6];
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    u8 pad_22[0x2];
    u8 unk_24;
    u8 unk_25;
} S_819AD81C_4;   /* info in func_819AD81C */

   /* link in func_819AD81C */

s32 rsin();
s32 rcos();
void PushMatrix();
void PopMatrix();
void RotTrans();
void apply_attack_power_and_element_effects();
s32 calculate_planar_heading();
s32 check_left_tile_and_center_height();
void spawn_opposite_offset_effect();
extern s8 D_8002758C[];
extern u8 D_800287A2;
extern s32 D_800287A4;

/* Per-frame homing-projectile step: fade in/out, fly toward the target tile, wake anything it passes and expire. */
void update_warp_camera_and_effects(void *entity, void *motion, void *gfx) {
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
    void *node;
    ObjectNodeHeader *attached;
    void *info;
    void *head;
    void *link;

    link = ((S_819AD81C_0 *)entity)->unk_20;
    if (link == 0) {
        phase = ((S_819AD81C_0 *)entity)->unk_2C.s;
        if (phase == 0) {
            tint = ((S_819AD81C_1 *)gfx)->unk_0C.at00.v;
            next_tint = tint + ((s32) (0x80 - tint) / ((S_819AD81C_0 *)entity)->unk_30);
            ((S_819AD81C_1 *)gfx)->unk_0C.at00.v = next_tint;
            ((S_819AD81C_1 *)gfx)->unk_0C.at01.v = next_tint;
            ((S_819AD81C_1 *)gfx)->unk_0C.at02.v = next_tint;
            fade_left = (u16) ((S_819AD81C_0 *)entity)->unk_30 - 1;
            ((S_819AD81C_0 *)entity)->unk_30 = fade_left;
            if ((fade_left << 0x10) <= 0) {
                ((S_819AD81C_1 *)gfx)->unk_0C.at00u.v = 0x808080;
                ((S_819AD81C_0 *)entity)->unk_2C.u = (u16) (((S_819AD81C_0 *)entity)->unk_2C.u + 1);
            }
        } else if (phase >= 2) {
            tint_out = ((S_819AD81C_1 *)gfx)->unk_0C.at00.v;
            next_tint_out = tint_out - ((s32) tint_out / (s16) ((S_819AD81C_0 *)entity)->unk_30);
            ((S_819AD81C_1 *)gfx)->unk_0C.at00.v = next_tint_out;
            ((S_819AD81C_1 *)gfx)->unk_0C.at01.v = next_tint_out;
            ((S_819AD81C_1 *)gfx)->unk_0C.at02.v = next_tint_out;
            fade_left_out = (u16) ((S_819AD81C_0 *)entity)->unk_30 - 1;
            ((S_819AD81C_0 *)entity)->unk_30 = fade_left_out;
            if ((fade_left_out << 0x10) <= 0) {
                ((S_819AD81C_1 *)gfx)->unk_0C.at00u.v = 0;
                (*(u16 *)((u8 *)entity + -2)) = (u16) (((S_819AD81C_0_pre *)entity)[-1].unk_00 | NODE_REMOVE);
                object_flag_block.flags |= OBJECT_REMOVE_PENDING;
                return;
            }
            if (((S_819AD81C_0 *)entity)->unk_2C.s >= 3) {
                return;
            }
        }
        ((S_819AD81C_2 *)motion)->unk_0C.at00.v = (s32) (rcos(((S_819AD81C_0 *)entity)->unk_34) << 8);
        ((S_819AD81C_2 *)motion)->unk_10.at00.v = (s32) (rsin(((S_819AD81C_0 *)entity)->unk_34) << 8);
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
        advance_animation_index_within_bounds(gfx, entity + 0x32, ((S_819AD81C_0 *)entity)->unk_38, ((S_819AD81C_0 *)entity)->unk_36);
        update_traveling(entity, ((S_819AD81C_1 *)gfx)->unk_00);
        if (((S_819AD81C_1 *)gfx)->unk_14 & 0x4000) {
            ((S_819AD81C_1 *)gfx)->unk_04 = 0;
        }
        if (((S_819AD81C_0 *)entity)->unk_46.s > 0) {
            ((S_819AD81C_0 *)entity)->unk_3C.at00.v = (s16) ((s16) ((S_819AD81C_2 *)motion)->unk_00.at02.v / 64);
            tile_y = (s16) ((S_819AD81C_2 *)motion)->unk_04.at02.v / 64;
            ((S_819AD81C_0 *)entity)->unk_3C.at02.v = (s16) tile_y;
            if (((S_819AD81C_0 *)entity)->unk_40.at00.v != ((S_819AD81C_0 *)entity)->unk_3C.at00u.v) {
                if ((check_left_tile_and_center_height(((((S_819AD81C_0 *)entity)->unk_3C.at00.v << 6) + 0x20) & 0xFFE0,
                    ((tile_y << 6) + 0x20) & 0xFFE0, ((S_819AD81C_2 *)motion)->unk_08.at02.v) << 0x10) != 0) {
                    ((S_819AD81C_0 *)entity)->unk_30 = 4;
                    ((S_819AD81C_0 *)entity)->unk_2C.s = 3;
                    return;
                }
                node = (void *) ((int)primary_actor_record);
                head = node;
                link = ((S_819AD81C_3 *)node)->unk_5C.p;
                node = link + 0x20;
                if (node != head) {
                    do {
                        info = ((ObjectNodeHeader *)((u8 *)node - 0x20))->sprite;
                        if (((S_819AD81C_4 *)info)->unk_24 == ((S_819AD81C_0 *)entity)->unk_3C.at00.v) {
                            if (((S_819AD81C_4 *)info)->unk_25 == ((S_819AD81C_0 *)entity)->unk_3C.at02.v) {
                                dz = ((S_819AD81C_3 *)node)->unk_88;
                                component = ((S_819AD81C_2 *)motion)->unk_08.at02.v;
                                dz -= component;
                                if (dz < 0) {
                                    dz = 0 - dz;
                                }
                                if (dz < 0x40) {
                                    /*
                                     * Original bug: Gaia Shoot passes water flags 0xA instead of wind flags 0xC, so
                                     * damage affinity and the impact effect use water.
                                     * Found and documented by the Azure Dreams community
                                     * (adrando.com/guide/bugs.html).
                                     */
                                    apply_attack_power_and_element_effects(node, 0xC, D_800287A2, 0xA,
                                        (s32) (s16) (((S_819AD81C_0 *)entity)->unk_44 << 9), D_800287A4, 2);
                                }
                            }
                        }
                        node = ((S_819AD81C_3 *)node)->unk_5C.i + 0x20;
                    } while (node != (void *) ((int)primary_actor_record));
                }
                saved_x = ((S_819AD81C_0 *)entity)->unk_3C.at00p.v;
                hits_left = ((S_819AD81C_0 *)entity)->unk_46.u;
                saved_y = ((S_819AD81C_0 *)entity)->unk_3C.at02u.v;
                hits_left -= 1;
                ((S_819AD81C_0 *)entity)->unk_46.s = hits_left;
                ((S_819AD81C_0 *)entity)->unk_40.at00u.v = saved_x;
                ((S_819AD81C_0 *)entity)->unk_40.at02.v = saved_y;
                if ((hits_left << 0x10) <= 0) {
                    ((S_819AD81C_0 *)entity)->unk_30 = 4;
                    ((S_819AD81C_0 *)entity)->unk_2C.s = (s16) ((u16) ((S_819AD81C_0 *)entity)->unk_2C.s + 1);
                }
            }
        }
        create_positioned_linked_mesh_effect(((S_819AD81C_2 *)motion)->unk_00.at02.v, ((S_819AD81C_2 *)motion)->unk_04.at02.v,
            ((S_819AD81C_2 *)motion)->unk_08.at02.v, ((S_819AD81C_0 *)entity)->unk_34);
        create_copied_effect_object(entity, motion, gfx);
        return;
    } else {
        attached = (void *) ((s32) link | 0x80000000);
        if (attached->flags & 0x8000) {
            (*(u16 *)((u8 *)entity + -2)) = (u16) (((S_819AD81C_0_pre *)entity)[-1].unk_00 | NODE_REMOVE);
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            return;
        }
        link = attached->position;
        info = attached->sprite;
        ((S_819AD81C_2 *)motion)->unk_00.at02.v = (s16) ((MovingPosition *)link)->unk_02;
        ((S_819AD81C_2 *)motion)->unk_04.at02.v = (s16) ((MovingPosition *)link)->unk_06;
        ((S_819AD81C_2 *)motion)->unk_08.at02.v = (s16) ((MovingPosition *)link)->unk_0A;
        ((S_819AD81C_1 *)gfx)->unk_16 = (u16) ((S_819AD81C_4 *)info)->unk_16;
        ((S_819AD81C_1 *)gfx)->unk_18 = (u16) ((S_819AD81C_4 *)info)->unk_18;
        ((S_819AD81C_1 *)gfx)->unk_1A = (u16) ((S_819AD81C_4 *)info)->unk_1A;
        ((S_819AD81C_1 *)gfx)->unk_1C = (u16) ((S_819AD81C_4 *)info)->unk_1C;
        ((S_819AD81C_1 *)gfx)->unk_1E = (u16) ((S_819AD81C_4 *)info)->unk_1E;
        ((S_819AD81C_1 *)gfx)->unk_20 = (u16) ((S_819AD81C_4 *)info)->unk_20;
        ((S_819AD81C_1 *)gfx)->unk_0C.at00u.v = ((S_819AD81C_4 *)info)->unk_0C;
        want_kind = D_8002758C[((S_819AD81C_0 *)entity)->unk_48];
        node = ((void *)attached) + 0x20;
        if ((want_kind >= 0) && (((S_819AD81C_4 *)info)->unk_04 == want_kind)) {
            PushMatrix(attached);
            build_install(entity, motion, gfx);
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
        set_animation_entry_address(gfx, ((S_819AD81C_4 *)info)->unk_04);
        update_traveling(entity, ((S_819AD81C_1 *)gfx)->unk_00);
    }
}

#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/dir_step.h"

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

typedef struct S_800255B8_3 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0xC];
    s16 unk_30;
    s16 unk_32;
    s16 unk_34;
    s16 unk_36;
    u8 pad_38[0x4];
    s16 unk_3C;
    s16 unk_3E;
    s16 unk_40;
    s16 unk_42;
    u8 pad_44[0x2];
    s16 unk_46;
    s16 unk_48;
} S_800255B8_3;   /* tail in create_linked_sprite_pieces */

extern u8 D_800274C0[];
extern u8 D_80027580[];

extern s32 has_enough_available_runtime_nodes(s32);

static __inline__ s16 dir_step(s16 *table, u16 offset) {
    return *(s16 *)(offset + (u32)table);
}

/* Creates twelve linked sprite pieces at an offset from the given position and angle. */
void *create_linked_sprite_pieces(s16 x, s16 y, s16 z, s16 heading) {
    void *objects[12];
    s32 piece_index;
    s16 *x_offsets;
    TileObject *color_table;
    u8 *effect_state;
    u8 *link_data;
    u8 *component_data;
    u8 color_first;
    u32 color_second;
    u32 offset_addr;
    s32 x_offset;
    s32 y_offset;
    u16 sprite_flags;

    if (has_enough_available_runtime_nodes(12) == 0) {
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
                template = ((u8 *)(&scene_object_list_anchor));
            }
            objects[piece_index] = allocate_list_node(2, template);
        }
        ((S_800255B8_0 *)objects[piece_index])->unk_10 = update_warp_camera_and_effects;
        register_node(objects[piece_index], draw_linked_model_chain);

        offset_addr = (heading >> 8) & 0xE;
        component_data = ((S_800255B8_0 *)objects[piece_index])->unk_08;
        x_offset = dir_step(x_offsets, offset_addr) << 5;
        ((S_800255B8_1 *)component_data)->unk_02 = x + x_offset;
        y_offset = dir_step(dir_step_y, offset_addr) << 5;
        ((S_800255B8_1 *)component_data)->unk_0A = z;
        ((S_800255B8_1 *)component_data)->unk_06 = y + y_offset;

        effect_state = ((S_800255B8_0 *)objects[piece_index])->unk_0C;
        ((S_800255B8_2 *)effect_state)->unk_20 = 0x1000;
        ((S_800255B8_2 *)effect_state)->unk_1E = 0x1000;
        ((S_800255B8_2 *)effect_state)->unk_1C = 0x1000;
        ((S_800255B8_2 *)effect_state)->unk_08 = D_800274C0 + (piece_index << 4);
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
            ((S_800255B8_3 *)effect_state)->unk_20 = (void *)link_value;
        }

        ((S_800255B8_3 *)effect_state)->unk_30 = 4;
        ((S_800255B8_3 *)effect_state)->unk_36 = 15;
        ((S_800255B8_3 *)effect_state)->unk_32 = 1;
        ((S_800255B8_3 *)effect_state)->unk_34 = heading;
        ((S_800255B8_3 *)effect_state)->unk_48 = piece_index;
        ((S_800255B8_3 *)effect_state)->unk_46 = 8;
        color_first = color_table->tile_position.parts.tile_x;
        ((S_800255B8_3 *)effect_state)->unk_3C = color_first;
        ((S_800255B8_3 *)effect_state)->unk_40 = color_first;
        color_second = color_table->tile_position.parts.tile_y;
        ((S_800255B8_3 *)effect_state)->unk_3E = color_second;
        ((S_800255B8_3 *)effect_state)->unk_42 = color_second;
        piece_index++;
    } while (piece_index < 12);

    return objects[0];
}

#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"

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
void update_traveling(FrameState *dst, AnimEntry *src)
{
    s32 halfword;

    dst->words = src->words;
    halfword = src->field_10;
    dst->field_10 = halfword;
    dst->field_14 = src->field_12;
    dst->field_18 = src->field_13;
    dst->field_1C = src->field_14;
}

#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"

/* Animation player state; entry is the current entry in the owner's table (0x16-byte AnimEntry stride). */

/* Owner of the animation table. */

/* Resolve the current entry, apply an index step, and enforce the index bounds. */
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

#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"

/* Animation player state (see advance_animation_index_within_bounds): the first word is the current entry in the owner's table. */

/* Owner of the animation table. */

/* Sets the player's current entry address using a 22-byte stride. */
void set_animation_entry_address(AnimPlayer *player, s16 entry_index) {
    player->entry = ((AnimOwner *)player->owner)->table + (entry_index * 0x16);
}

#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"

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
} S_8002593C_0;   /* scratch in build_install */

typedef struct S_8002593C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8002593C_1;   /* arg1 in build_install */

typedef struct S_8002593C_2 {
    u8 pad_00[0x16];
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
} S_8002593C_2;   /* arg2 in build_install */

typedef struct MATRIX {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} MATRIX;

extern void CompMatrix(void *, void *, void *);
extern void ReadRotMatrix(void *);
extern void TransMatrix(void *, void *);
extern void SetRotMatrix(void *);
extern void SetTransMatrix(void *);
extern void RotMatrixX(u16, void *);
extern void RotMatrixY(u16, void *);
extern void RotMatrixZ(u16, void *);

/* Build and install a transform from position, rotation, and a base matrix. */
void build_install(void *base_matrix, S_8002593C_1 *position, S_8002593C_2 *rotation)
{
    u8 *scratch = (u8 *)0x1F800000;
    MATRIX matrix;

    ((S_8002593C_0 *)scratch)->unk_40 = position->unk_02;
    ((S_8002593C_0 *)scratch)->unk_44 = position->unk_06;
    ((S_8002593C_0 *)scratch)->unk_48 = position->unk_0A;
    ReadRotMatrix(&matrix);

    ((S_8002593C_0 *)scratch)->unk_50 = ((S_8002593C_0 *)scratch)->unk_58 =
        ((S_8002593C_0 *)scratch)->unk_60 = 0x1000;
    ((S_8002593C_0 *)scratch)->unk_52 = ((S_8002593C_0 *)scratch)->unk_54 =
        ((S_8002593C_0 *)scratch)->unk_56 = ((S_8002593C_0 *)scratch)->unk_5A =
        ((S_8002593C_0 *)scratch)->unk_5C = ((S_8002593C_0 *)scratch)->unk_5E = 0;

    RotMatrixX(rotation->unk_16, scratch + 0x50);
    RotMatrixZ(rotation->unk_1A, scratch + 0x50);
    RotMatrixY(rotation->unk_18, scratch + 0x50);
    TransMatrix(scratch + 0x50, scratch + 0x40);
    CompMatrix(scratch + 0x50, base_matrix, scratch + 0xD0);
    SetTransMatrix(scratch + 0xD0);
    SetRotMatrix(scratch + 0xD0);
}

#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"
#include "shared/object_flags.h"

/* Fade RGB toward black and set flags when red falls below eight. */
void fade_color_to_black(void *owner, s32 unused, void *color_data) {
    u8 red;
    u8 green;
    u8 blue;

    *(u16 *)D_80027452 = *(u16 *)D_80027452 + 1;
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

#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"

typedef struct Entry {
    s32 field_0;
    s8 field_4;
    u8 pad_5;
    s16 field_6;
    void *field_8;
} Entry;

extern u8 D_800274C0[];
extern void transform_shade_and_queue_model_quads(void *parent_matrix, void *translation, void *model, s16 depth_bias);

/* Processes twelve buffer slots for each entry in a linked state chain. */
s32 process_effect_buffer_chain(void *initial_state, s32 initial_value, Entry *initial_entry)
{
    void *state = initial_state;
    s32 value = initial_value;
    Entry *entry = initial_entry;
    u8 *slot_base;
    s32 slot_index;
    u8 *slot;
    void *entry_or_link;

    slot_base = D_800274C0;
    for (;;) {
        slot_index = 0;
        slot = slot_base;
        entry_or_link = entry;
        do {
            entry->field_8 = slot;
            slot += 0x10;
            set_animation_entry_address((Entry *)entry_or_link, entry->field_4);
            slot_index++;
            update_traveling(state, entry->field_0);
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

#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"
#include "shared/dungeon_moving_views.h"

#ifndef NULL
#define NULL 0
#endif

   /* arg1 in create_copied_effect_object */

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
} S_80025B78_4;   /* arg2 in create_copied_effect_object */

typedef struct Block32 {
    u8 bytes[0x20];
} Block32;

/* Creates an object and copies the supplied triplet, state fields, and 32-byte data block. */
void *create_copied_effect_object(void *source_data, MovingPosition *source_triplet, S_80025B78_4 *source_state)
{
    ObjectNodeHeader *object;
    MovingPosition *triplet;
    SpriteFrameState *state;

    object = allocate_flagged_object_node(0x202);
    if (object != NULL) {
        object->unk_10 = fade_color_to_black;
        register_node(object, process_effect_buffer_chain);
        triplet = object->position;
        triplet->unk_02 = source_triplet->unk_02;
        triplet->unk_06 = source_triplet->unk_06;
        triplet->unk_0A = source_triplet->unk_0A;
        state = object->sprite;
        state->scale_x = source_state->unk_1C;
        state->scale_y = source_state->unk_1E;
        state->unk_20 = source_state->unk_20;
        state->angle_x = source_state->unk_16;
        state->angle_y = source_state->unk_18;
        state->angle_z = source_state->unk_1A;
        state->color.word = source_state->unk_0C;
        state->flags = source_state->unk_14;
        state->unk_00 = source_state->unk_00;
        state->source = source_state->unk_08;
        state->tpage_abr = source_state->unk_10;
        state->unk_04 = source_state->unk_04;
        *(Block32 *)((u8 *)object + 0x20) = *(Block32 *)source_data;
    }
    return object;
}

#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"
#include "shared/object_flags.h"
#include "records/Rec_func_80025D28_arg0.h"

typedef struct S_80025D28_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80025D28_1;   /* arg1 in initialize_inventory_packet */

typedef struct S_80025D28_2 {
    u8 pad_00[0xD];
    u8 unk_0D;
} S_80025D28_2;   /* arg2 in initialize_inventory_packet */

extern s32 rsin();
extern s32 rcos();

/* Update two animated points, fade their intensity, and flag expiration. */
void initialize_inventory_packet(void *state, void *points, void *appearance) {
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

    phase_step = ((Rec_func_80025D28_arg0 *)state)->unk_38;
    phase_angle = (s16)(phase_step << 6);
    *(u16 *)D_80027452 = *(u16 *)D_80027452 + 1;
    start_wave_x = rsin(phase_angle);
    ((S_80025D28_1 *)points)->unk_00 = (((Rec_func_80025D28_arg0 *)state)->unk_1C << 0x10) +
        ((s32)(start_wave_x * rcos(((Rec_func_80025D28_arg0 *)state)->unk_36
            + 0x400) * ((Rec_func_80025D28_arg0 *)state)->unk_3E) >> 7);
    start_wave_y = rsin(phase_angle);
    ((S_80025D28_1 *)points)->unk_04 = (((Rec_func_80025D28_arg0 *)state)->unk_1E << 0x10) +
        ((s32)(start_wave_y * rsin(((Rec_func_80025D28_arg0 *)state)->unk_36
            + 0x400) * ((Rec_func_80025D28_arg0 *)state)->unk_3E) >> 7);
    ((S_80025D28_1 *)points)->unk_08 = (((Rec_func_80025D28_arg0 *)state)->unk_20 << 0x10) +
        ((rcos(phase_angle) * ((Rec_func_80025D28_arg0 *)state)->unk_3E) << 5);
    end_wave_x = rsin(phase_angle);
    direction_x = rcos(((Rec_func_80025D28_arg0 *)state)->unk_36 + 0x400);
    side_direction_x = rcos(((Rec_func_80025D28_arg0 *)state)->unk_36 + 0x800);
    radial_offset_x = end_wave_x * direction_x;
    do {
        radial_offset_x *= ((Rec_func_80025D28_arg0 *)state)->unk_3E;
    } while (0);
    side_offset_x = side_direction_x * ((Rec_func_80025D28_arg0 *)state)->unk_40;
    ((S_80025D28_1 *)points)->unk_0C = (((Rec_func_80025D28_arg0 *)state)->unk_1C << 0x10) +
        (radial_offset_x >> 7) + (side_offset_x << 6);
    end_wave_y = rsin(phase_angle, side_offset_x);
    direction_y = rsin(((Rec_func_80025D28_arg0 *)state)->unk_36 + 0x400);
    side_direction_y = rsin(((Rec_func_80025D28_arg0 *)state)->unk_36 + 0x800);
    radial_offset_y = end_wave_y * direction_y;
    do {
        radial_offset_y *= ((Rec_func_80025D28_arg0 *)state)->unk_3E;
    } while (0);
    side_offset_y = side_direction_y * ((Rec_func_80025D28_arg0 *)state)->unk_40;
    ((S_80025D28_1 *)points)->unk_10 = (((Rec_func_80025D28_arg0 *)state)->unk_1E << 0x10) +
        (radial_offset_y >> 7) + (side_offset_y << 6);
    ((S_80025D28_1 *)points)->unk_14 = (((Rec_func_80025D28_arg0 *)state)->unk_20 << 0x10) +
        ((rcos(phase_angle, side_offset_y) * ((Rec_func_80025D28_arg0 *)state)->unk_3E) << 5);
    ((Rec_func_80025D28_arg0 *)state)->unk_40 = (u16)((Rec_func_80025D28_arg0 *)state)->unk_40 + 2;
    ((Rec_func_80025D28_arg0 *)state)->unk_38 = (u16)((Rec_func_80025D28_arg0 *)state)->unk_38 + 1;
    intensity = ((S_80025D28_2 *)appearance)->unk_0D;
    ((S_80025D28_2 *)appearance)->unk_0D = intensity - (intensity >> 3);
    ticks_left = ((Rec_func_80025D28_arg0 *)state)->unk_30 - 1;
    ((Rec_func_80025D28_arg0 *)state)->unk_30 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        (*(u16 *)((u8 *)state + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    ((Rec_func_80025D28_arg0 *)state)->unk_34 = ((Rec_func_80025D28_arg0 *)state)->unk_34 + 1;
}

/* MECHANISM: Natural long-lived arguments and results produce the retail 0x30 frame and s5/s4/s3/s2/s1/s0 roles.
   A short raw signed-load local selects lh before the shift/truncation while preserving phase_angle in s1.
   Zero-operand scheduling barriers after both chained products reproduce retail multiply/mflo emission order. */

#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"


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
        effect->unk_10 = initialize_inventory_packet;
        register_node(effect, process_linked_mesh_states_mode_0);
        position = effect->position;
        effect_state = ((void *)effect) + 0x20;
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
        render_state->source = &D_80027460;
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

#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"

/* Colour bytes of the effect's render data. */
typedef struct EffectColor {
    u8 pad[12];
    u8 red;
    u8 green;
    u8 blue;
} EffectColor;

/* Fade the effect color and set flags when red falls below four. */
void fade_effect_color_to_black(void *record, s32 unused, EffectColor *color) {
    u8 red;
    u8 green;
    u8 blue;

    D_80027452[0]++;

    red = color->red;
    green = color->green;
    color->red = red - (red >> 2);
    blue = color->blue;
    color->green = green - (green >> 2);
    color->blue = blue - (blue >> 2);

    if (color->red < 4) {
        ((ObjectNodeHeader *)record - 1)->flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"
#include "shared/slus_callbacks.h"

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

extern Coord D_800287B0;

extern s32 rsin(s32);
extern s32 rcos(s32);

/* Spawns an effect actor or builds a curved trail toward the saved position. */
void *update_object_movement_proximity_reactions(s16 x, s16 y, s16 z, s16 angle, s16 spawn_actor) {
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
            actor->update = fade_effect_color_to_black;
            register_node(actor, project_sprite_chain);
            coord = actor->pos;
            coord->x.w.i = x;
            coord->y.w.i = y;
            coord->z.w.i = z;
            prim = actor->prim;
            prim->scale_y = 1024;
            prim->scale_x = 1024;
            prim->source = D_80027460;
            prim->color.word = 0x808080;
            prim->tpage_abr = 32;
            prim->flags |= 0xC;
            actor->unk50 = 16;
        }
    } else {
        if (D_80027450 == 3) {
            step_x = (D_800287B0.x - x) / 16;
            step_y = (D_800287B0.y - y) / 16;
            step_z = (D_800287B0.z - z) / 16;
            trail_x = x + step_x;
            trail_y = y + step_y;
            trail_z = z + step_z;
            for (trail_index = 0; trail_index < 16; trail_index++) {
                update_object_movement_proximity_reactions(trail_x + ((rcos(angle) * rsin(trail_index << 7)) >> 21),
                              trail_y + ((rsin(angle) * rsin(trail_index << 7)) >> 21),
                              trail_z, angle, 1);
                trail_x += step_x;
                trail_y += step_y;
                trail_z += step_z;
            }
        }
        if (D_80027450 == 0) {
            D_800287B0.x = x;
            D_800287B0.y = y;
            D_800287B0.z = z;
        }
        D_80027450 = D_80027450 + 1;
    }
    return actor;
}
