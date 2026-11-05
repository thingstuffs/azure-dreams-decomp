#include "sdk/libc.h"
/* Timed target effects, jittered intermediate points, and linked trail quad rendering. */
#include "modules/dungeon_ovl_19c6800.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/effect/sprite.h"
#include "shared/dungeon_projectile_views.h"
#include "dungeon/effect/sprite/intermediate_point_effect.h"
#include "dungeon/effect/sprite/jittered_trail_segment.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_status.h"
#include "dungeon/item.h"
#include "engine/scene.h"
#include "sdk/libgpu.h"
#include "slus.h"
#include "dungeon/system.h"

typedef struct JitteredPointSequenceState {
    void *unk_00;
    void *unk_04;
    u8 unk_08;
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;
    u8 pad_0C[0x44];
    union { s16 s; u16 u; } unk_50;
    union { s16 s; u16 u; } unk_52;
} JitteredPointSequenceState;

typedef struct S_func_819A6800_2 {
    u8 pad_00[8];
    void *unk_08;
    void *unk_0C;
    void *unk_10;
    u8 pad_14[0x0C];
    void *unk_20;
    u8 unk_24;
    u8 unk_25;
} S_func_819A6800_2;

typedef struct S_func_819A6800_3 {
    u8 pad_00[0x60];
    union { void *p; u32 u; } unk_60;
    u8 pad_64[0x0E];
    u8 unk_72;
    u8 unk_73;
} S_func_819A6800_3;

typedef struct S_func_819A6800_4 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x7A];
    u16 unk_A6;
    u8 unk_A8;
    u8 pad_A9[0x4B];
    u32 unk_F4;
    u8 pad_F8[0x0A];
    u8 unk_102;
} S_func_819A6800_4;

typedef struct S_func_819A6800_5 {
    union {
        u32 u;
        s32 s;
        struct { u8 pad_00[2]; u16 unk_02; } h;
    } unk_00;
    union {
        u32 u;
        s32 s;
        struct { u8 pad_04[2]; u16 unk_06; } h;
    } unk_04;
    union {
        u32 u;
        s32 s;
        struct { u8 pad_08[2]; u16 unk_0A; } h;
    } unk_08;
} S_func_819A6800_5;

typedef struct S_func_819A6800_6 {
    u16 unk_00;
} S_func_819A6800_6;

typedef struct S_func_819A6800_7 {
    u8 pad_00[0x0C];
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u8 pad_12[0x1E];
    u16 unk_30;
    u16 unk_32;
    void *unk_34;
    u32 unk_38;
    u16 unk_3C;
    u16 unk_3E;
    u16 unk_40;
    u16 unk_42;
    u8 pad_44[8];
    u16 unk_4C;
} S_func_819A6800_7;

typedef struct S_func_819A6800_9 {
    u8 pad_00[4];
    u32 unk_04;
} S_func_819A6800_9;

extern u8 primary_actor_record[16];
struct S_800244BC_2;
s32 update_segment(void *);
extern u8 moving_sprite_entries[];
extern u32 D_800814A0[];

#define GLOBAL_OBJECT (*(void **)primary_actor_record)

extern void apply_attack_power_and_element_effects(void *, s32, s32, s32, s32, void *, s32);

/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol add_flag_adjusted_target_value).  The state table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */

void (*const dungeon_19c6800_entry)(void *, void *) = run_jittered_point_sequence;


/* Runs a timed object creation sequence with visual effects and final cleanup. */
void run_jittered_point_sequence(JitteredPointSequenceState *sequence, void *out_position_arg)
{
    S_func_819A6800_5 *out_position = out_position_arg;
    S_func_819A6800_3 *owner = sequence->unk_00;
    S_func_819A6800_2 *record = ((S_func_819A6800_2 *)((u8 *)owner - 0x20))->unk_0C;
    S_func_819A6800_2 *owner_object = (S_func_819A6800_2 *)((u8 *)owner - 0x20);
    u16 timer;
    s32 state;
    S_func_819A6800_2 *new_object;
    S_func_819A6800_4 *counter_object;
    s16 position_offset[3];
    S_func_819A6800_7 *effect_data;
    SpriteFrameState *sprite;
    u8 *global_slot;
    S_func_819A6800_4 *global_object;
    PlayerRecord *reloaded_object;

    timer = sequence->unk_50.u - 1;
    state = sequence->unk_0A.s;
    sequence->unk_50.u = timer;
    switch (state) {
    case 0:
        global_slot = (u8 *)&D_800814A0[2];
        global_object = *(void **)global_slot;
        global_object->unk_102 = 1;
        reloaded_object = *(void **)global_slot;
        reloaded_object->unk_F4 = 0;

        out_position->unk_00.u = ((S_func_819A6800_5 *)(owner_object->unk_08))->unk_00.u;
        out_position->unk_04.u = ((S_func_819A6800_5 *)(owner_object->unk_08))->unk_04.u;
        out_position->unk_08.u = ((S_func_819A6800_5 *)(owner_object->unk_08))->unk_08.u;

        new_object = scan_actor_along_heading(&reloaded_object->actor,
                                   reference_tile_object.tile_position.parts.tile_x,
                                   reference_tile_object.tile_position.parts.tile_y,
                                   reloaded_object->actor.facing,
                                   7);
        owner->unk_60.p = new_object;
        if (new_object == 0) {
            owner->unk_72 = record->unk_24;
            owner->unk_73 = record->unk_25;
        } else {
            sprite = ((S_func_819A6800_2 *)((u8 *)new_object - 0x20))->unk_0C;
            owner->unk_72 = sprite->tile_x;
            owner->unk_73 = sprite->tile_y;
        }

        sequence->unk_0A.u++;
    case 1:
        if ((((S_func_819A6800_6 *)(sequence->unk_04))->unk_00 & 0x80) == 0) {
            return;
        }

        counter_object = GLOBAL_OBJECT;
        sequence->unk_50.u = 10;
        counter_object->unk_A6--;
        counter_object->unk_A8 = sequence->unk_08;
        new_object = allocate_list_node(0x312, &scene_object_list_anchor.next);
        record = new_object;
        if (record != 0) {
            if (resolve_record_orientation_or_fallback(((ObjectNodeHeader *)owner_object->unk_0C)->position,
                              owner_object->unk_0C, position_offset, 0) == 0) {
                position_offset[2] = 0;
                position_offset[1] = 0;
                position_offset[0] = 0;
            }
            record->unk_10 = advance_target_chasing_emitter;
            register_node(record, project_sprite_chain);
            sprite = record->unk_0C;

            (((ObjectPosition *)record->unk_08))->x.v =
                ((S_func_819A6800_5 *)(owner_object->unk_08))->unk_00.s + ((s32)position_offset[0] << 16);
            (((ObjectPosition *)record->unk_08))->y.v =
                ((S_func_819A6800_5 *)(owner_object->unk_08))->unk_04.s + ((s32)position_offset[1] << 16);
            (((ObjectPosition *)record->unk_08))->z.v =
                ((S_func_819A6800_5 *)(owner_object->unk_08))->unk_08.s + ((s32)position_offset[2] << 16);

            effect_data = (S_func_819A6800_7 *)((u8 *)record + 0x20);
            effect_data->unk_0C = *(u16 *)&(((ObjectPosition *)record->unk_08))->x.w.i;
            effect_data->unk_0E = *(u16 *)&(((ObjectPosition *)record->unk_08))->y.w.i;
            effect_data->unk_10 = *(u16 *)&(((ObjectPosition *)record->unk_08))->z.w.i;

            sprite->scale_y = 0x1000;
            sprite->scale_x = 0x1000;
            sprite->tpage_abr = 0x20;
            sprite->flags |= 0x0C;
            sprite->unk_00 = moving_sprite_entries;
            sprite->source = ((S_func_819A6800_9 *)(moving_sprite_entries))->unk_04;
            sprite->unk_04 = 0;
            sprite->frame_ticks = 0;
            sprite->color.word = 0x00606060;
            record->unk_20 = sequence;
            effect_data->unk_4C = 0;
        }
        sequence->unk_0A.u++;
        return;

    case 2:
        if ((s16)sequence->unk_50.u > 0) {
            return;
        }
        {
            s32 mode = read_sound_mode_blocking_status(4);
            if (mode != 2) {
                mode = 0x300;
            } else {
                mode = 0x4300;
            }
            play_sound_if_enabled(mode);
        }
        {
            u16 next_state = sequence->unk_0A.u;
            u16 ticks;
            ticks = 10;
            sequence->unk_50.u = ticks;
            sequence->unk_0A.u = next_state + 1;
        }
        return;

    case 3:
    {
        s16 timer_left = sequence->unk_50.s;
        if (timer_left == 7) {
            if (owner->unk_60.p != 0) {
                record = allocate_list_node(0x302, &scene_object_list_anchor.next);
                if (record != 0) {
                    S_func_819A6800_7 *child_data = (S_func_819A6800_7 *)((u8 *)record + 0x20);
                    void *target_object;
                    record->unk_10 = update_jittered_effect_points;
                    register_node(record, update_segment);
                    target_object = owner->unk_60.p;
                    child_data->unk_3C = 0;
                    child_data->unk_3E = 0;
                    child_data->unk_32 = 0x1F;
                    child_data->unk_30 = 0x1F;
                    child_data->unk_34 = target_object;
                    child_data->unk_40 = GetTPage(0, 1, 0x2C0, 0x100);
                    child_data->unk_42 = GetClut(0x60, 0x1F8);
                    child_data->unk_38 = 0x00404040;
                    record->unk_20 = sequence;
                }
            }
        }
    }
        if (sequence->unk_50.s == 4) {
            apply_attack_power_and_element_effects(owner->unk_60.p,
                          10,
                          sequence->unk_09,
                          12,
                          ((S_func_819A6800_4 *)(GLOBAL_OBJECT))->unk_2A,
                          owner,
                          2);
        }
        if ((reference_tile_object.sprite_flags & 0x8000) == 0 &&
            sequence->unk_50.s >= 0) {
            return;
        }
        {
            u16 next_state5 = sequence->unk_0A.u;
            u16 cleanup_delay;
            cleanup_delay = 20;
            sequence->unk_50.u = cleanup_delay;
            sequence->unk_0A.u = next_state5 + 1;
        }
        return;

    case 4:
        if ((s16)sequence->unk_50.u > 0) {
            return;
        }
        sequence->unk_0A.u++;
        return;

    case 5:
    {
        s16 signed_flags = sequence->unk_52.s;
        u16 flags = sequence->unk_52.u;
        if ((signed_flags & 0x8000) != 0) {
            sequence->unk_52.u = flags & 0x7FFF;
            return;
        }
    }
        {
            g_dungeon_status.active_actor = 0;
            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        NODE_HEADER(sequence)->flags |= 0x8000;
        D_800814A0[0] |= 0x8000;

        return;
    }
}

#include "modules/dungeon_ovl_19c6800.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/object_flags.h"



typedef struct S_800244BC_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_800244BC_1;

typedef struct S_800244BC_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
} S_800244BC_2;   /* arg1 in func_800244BC */





typedef struct {
    u8 pad[0xC];
    u32 word0;
    u32 word1;
} CopySource __attribute__((packed));

typedef struct {
    u8 pad[0x24];
    u32 word0;
    u32 word1;
} CopyDestination __attribute__((packed));

/* cfail-repair: tf7-phase1-cache-v3 */
s32 rsin(s32, s16 *); /* extern */

/* Move toward the target while spawning effects, then mark the sequence complete. */
void advance_target_chasing_emitter(void *object, S_800244BC_2 *position, SpriteFrameState *context) {
    s16 target_pos[3];
    s16 phase;
    s32 effects_left;
    IntermediatePointEffectBody *effect_data;
    ObjectNodeHeader *effect;
    S_800244BC_1 *owner;

    owner = ((JitteredPointSequenceBody *)object)->unk_00;
    ((JitteredPointSequenceBody *)object)->unk_48 = (u16) (((JitteredPointSequenceBody *)object)->unk_48 - 1);
    owner->unk_52 = (u16) (owner->unk_52 | 0x8000);
    phase = ((JitteredPointSequenceBody *)object)->unk_4C.s;
    switch (phase) {
    case 0:
        ((JitteredPointSequenceBody *)object)->unk_48 = 0xAU;
        ((JitteredPointSequenceBody *)object)->unk_4C.s = (s16) ((u16) ((JitteredPointSequenceBody *)object)->unk_4C.s + 1);
                        /* fall through */
    case 1:
        if (resolve_record_orientation_or_fallback(reference_tile_object.sprite_source, ((s32 *)(&reference_tile_object)), target_pos, 0) != 0) {
            advance_sprite_animation_and_textures(context);
            position->unk_00.at00.v = (s32) (position->unk_00.at00.v + (((target_pos[0] + view_reference_entity.x.w.i)
                - position->unk_00.at02.v) << 0xE));
            position->unk_04.at00.v = (s32) (position->unk_04.at00.v + (((target_pos[1] + view_reference_entity.y.w.i)
                - position->unk_04.at02.v) << 0xE));
            position->unk_08.at00.v = (s32) (position->unk_08.at00.v + (((target_pos[2] + view_reference_entity.z.w.i)
                - position->unk_08.at02.v) << 0xE));
            effects_left = 0;
            position->unk_08.at00.v = (s32) (position->unk_08.at00.v
                - (rsin(((s16) ((JitteredPointSequenceBody *)object)->unk_48 << 0xB) / 10, ((s16 *)(&view_reference_entity))) << 9));
            do {
                effect = allocate_list_node(0x302, &scene_object_list_anchor.next);
                effect_data = NODE_BODY(effect);
                if (effect != 0) {
                    effect->update_callback = update_randomized_intermediate_points;
                    effect_data->unk_3C.s = 0;
                    effect_data->unk_3E.s = (s16) ((rand() & 3) + 2);
                    effect_data->unk_32 = 0x1F;
                    effect_data->unk_30 = 0x1F;
                    effect_data->unk_40 = GetTPage(0, 1, 0x2C0, 0x100);
                    effect_data->unk_38 = 0x404040;
                    memcpy((u8 *) effect + 0x24, (u8 *) object + 0xC, 8);
                    effect_data->point_slots[4].x.u = (u16) position->unk_00.at02.v;
                    effect_data->point_slots[4].y.u = (u16) position->unk_04.at02.v;
                    effect_data->point_slots[4].z.u = (u16) position->unk_08.at02.v;
                    effect_data->unk_00 = ((JitteredPointSequenceBody *)object)->unk_00;
                }
                effects_left -= 1;
            } while (effects_left >= 0);
        }
        if ((s16) ((JitteredPointSequenceBody *)object)->unk_48 <= 0) {
            ((JitteredPointSequenceBody *)object)->unk_48 = 8U;
            ((JitteredPointSequenceBody *)object)->unk_4C.s = (s16) ((u16) ((JitteredPointSequenceBody *)object)->unk_4C.s + 1);
        }
        break;
    case 2:
        if (resolve_record_orientation_or_fallback(reference_tile_object.sprite_source, ((s32 *)(&reference_tile_object)), target_pos, 0) != 0) {
            advance_sprite_animation_and_textures(context);
            position->unk_00.at00.v = (s32) (position->unk_00.at00.v + (((target_pos[0] + view_reference_entity.x.w.i)
                - position->unk_00.at02.v) << 0xF));
            position->unk_04.at00.v = (s32) (position->unk_04.at00.v + (((target_pos[1] + view_reference_entity.y.w.i)
                - position->unk_04.at02.v) << 0xF));
            position->unk_08.at00.v = (s32) (position->unk_08.at00.v + (((target_pos[2] + view_reference_entity.z.w.i)
                - position->unk_08.at02.v) << 0xF));
        }
        if ((s16) ((JitteredPointSequenceBody *)object)->unk_48 <= 0) {
            NODE_HEADER(object)->flags = (u16) (NODE_HEADER(object)->flags | 0x8000);
            object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
        }
        break;
    }
}

#include "modules/dungeon_ovl_19c6800.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"



typedef struct S_80024810_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_80024810_1;

/* micro-lane E 2026-08-14: true base 0x80024810 (delta 0x7E65D800) */

/* Update the effect's jittered points between endpoints and advance its animation. */
void update_jittered_effect_points(JitteredBoltSegmentBody *effect) {
    u16 coord_delta[3];
    s32 phase;
    s32 point_index;

    S_80024810_1 *owner;
    ObjectNodeHeader *target;

    owner = effect->owner;
    target = NODE_HEADER(effect->unk_34);
    owner->unk_52 = (u16) (owner->unk_52 | 0x8000);
    effect->unk_24 = (u16) target->position->x.unsigned_parts.integer;
    effect->unk_26 = (u16) target->position->y.unsigned_parts.integer;
    effect->unk_28 = (s16) (target->position->z.unsigned_parts.integer - 0x20);
    effect->unk_04 = (u16) view_reference_entity.x.w.i;
    effect->unk_06 = (u16) view_reference_entity.y.w.i;
    effect->unk_08 = (u16) view_reference_entity.z.w.i;
    if (resolve_record_orientation_or_fallback(reference_tile_object.sprite_source, ((s32 *)(&reference_tile_object)), coord_delta, 0) != 0) {
        effect->unk_04 = (u16) (effect->unk_04 + coord_delta[0]);
        effect->unk_06 = (u16) (effect->unk_06 + coord_delta[1]);
        effect->unk_08 = (u16) (effect->unk_08 + coord_delta[2]);
    }
    coord_delta[0] = (u16) ((s32) ((s16) effect->unk_24 - (s16) effect->unk_04)
        >> 2);
    point_index = 1;
    coord_delta[1] = (u16) ((s32) ((s16) effect->unk_26 - (s16) effect->unk_06)
        >> 2);
    coord_delta[2] = (u16) ((s32) (effect->unk_28 - (s16) effect->unk_08) >> 2);
    do {
        (*(s16 *)((u8 *)effect + (point_index * 8) + 4)) = (s16) ((effect->unk_04
            + ((s16) coord_delta[0] * point_index) + (rand() & 0x3F)) - 0x20);
        (*(s16 *)((u8 *)effect + (point_index * 8) + 6)) = (s16) ((effect->unk_06
            + ((s16) coord_delta[1] * point_index) + (rand() & 0x3F)) - 0x20);
        (*(s16 *)((u8 *)effect + (point_index * 8) + 8)) = (s16) ((effect->unk_08
            + ((s16) coord_delta[2] * point_index)) - (rand() & 0x3F));
        point_index += 1;
    } while (point_index < 4);
    effect->unk_2C = (s16) (((effect->unk_3E & 3) << 5) + 0x80);
    effect->unk_2E = (s16) (((s32) (effect->unk_3E << 0x10) >> 0x12) << 5);
    phase = effect->unk_3C;
    switch (phase) {
    case 0:
        effect->unk_24 = (u16) (effect->unk_04
            + ((s32) ((s16) effect->unk_24 - (s16) effect->unk_04) >> 1));
        effect->unk_26 = (u16) (effect->unk_06
            + ((s32) ((s16) effect->unk_26 - (s16) effect->unk_06) >> 1));
        effect->unk_28 = (s16) (effect->unk_08
            + ((s32) (effect->unk_28 - (s16) effect->unk_08) >> 1));
        effect->unk_3C = (s16) ((u16) effect->unk_3C + 1);
                        /* fallthrough */
    case 1:
        if ((s16) effect->unk_3E >= 6) {
            effect->unk_3E = 2U;
            effect->unk_3C = (s16) ((u16) effect->unk_3C + 1);
        }
        break;
    case 2:
        if ((s16) effect->unk_3E >= 8) {
            NODE_HEADER(effect)->flags = (u16) (NODE_HEADER(effect)->flags | 0x8000);
            object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
        }
        break;
    }
    effect->unk_3E = (u16) (effect->unk_3E + 1);
}


#include "modules/dungeon_ovl_19c6800.h"
#include "common.h"
#include "shared/game_work.h"
s32 RotTransPers(void *, s32 *, s32 *, s32 *);
void transform_rotated_vertices();
typedef struct
{
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
}
E_SVEC;
typedef union
{
    s32 word;
    struct { u16 x; u16 y; } half;
}
E_DVEC;
typedef struct
{
    void *p0;
    void *p1;
    s16 f08;
    s16 f0A;
    u16 f0C;
    s16 f0E;
    s16 f10;
    s16 f12;
    s16 f14;
    s16 f16;
    s16 f18;
    s16 f1A;
    s32 f1C;
}
E_PRIM;
/* Emit each chain node's four trail quads into the display list, depth-sorted into the OT. */
s32 update_segment(void *node)
{
    E_SVEC scratch;
    s32 otz[6];
    E_DVEC sxy[6];
    E_PRIM prim;
    s32 p;
    s32 i;
    s32 mid_otz;
    s32 slot_offset;
    GameWork *base;
    POLY_FT4 *poly;
    void *parent;
    void *obj;
    int dy;
    u8 colour_a;
    u8 colour_b;
    u8 colour_c;
    u8 colour_d;
    base = &g_game_work;
    do {
        obj = node;
        i = 4;
        do {
            otz[i] = (s32) (RotTransPers(((u8 *) obj) + ((i * 8) + 4), &sxy[i].word, &p, &p) - 8);
            i -= 1;
        }
        while (i >= 0);
        scratch.x = *((u16 *) (((s8 *) obj) + 4));
        scratch.y = *((u16 *) (((s8 *) obj) + 6));
        scratch.z = (u16) ((*((u16 *) (((s8 *) obj) + 8))) + 0x30);
        RotTransPers(&scratch, &sxy[5].word, &p, &p);
        scratch.x = 0;
        scratch.z = 0;
        prim.p1 = &scratch;
        prim.p0 = &scratch;
        prim.f0A = 0;
        prim.f08 = 0;
        prim.f14 = 0;
        prim.f12 = 0;
        prim.f10 = 0;
        prim.f1A = 0;
        prim.f18 = 1;
        dy = (s16) sxy[0].half.y;
        dy = dy - ((s16) sxy[5].half.y);
        scratch.y = (u16) abs((s32) dy);
        prim.f0C = ((u16)(base->view.camera_rotation.parts.viewAngle));
        transform_rotated_vertices(&prim, (s16) sxy[5].half.y);
        for (i = 0; i < 4; i++) {
            poly = *((void **) (((s8 *) (base->draw_buffer)) + 0x8D0));
            *((void **) (((s8 *) (base->draw_buffer)) + 0x8D0)) =  (((u8 *) poly) + 0x28);
            *((s32 *) (((s8 *) poly) + 4)) = *((s32 *) (((s8 *) obj) + 0x38));
            SetPolyFT4(poly);
            SetSemiTrans(poly, 1);
            poly->tpage = (u16) (*((u16 *) (((s8 *) obj) + 0x40)));
            poly->clut = (u16) (*((u16 *) (((s8 *) obj) + 0x42)));
            poly->x0 = (s16) (sxy[i].half.x - scratch.x);
            poly->x1 = (s16) (sxy[i + 1].half.x - scratch.x);
            poly->x2 = (s16) (sxy[i].half.x + scratch.x);
            poly->x3 = (s16) (sxy[i + 1].half.x + scratch.x);
            poly->y0 = (s16) (sxy[i].half.y - scratch.y);
            poly->y2 = (s16) (sxy[i].half.y + scratch.y);
            poly->y1 = (s16) (sxy[i + 1].half.y - scratch.y);
            poly->y3 = (s16) (sxy[i + 1].half.y + scratch.y);
            colour_a = *((u8 *) (((s8 *) obj) + 0x2C));
            poly->u2 = colour_a;
            poly->u0 = colour_a;
            colour_b = (u8) (colour_a + (*((u8 *) (((s8 *) obj) + 0x30))));
            poly->u3 = colour_b;
            poly->u1 = colour_b;
            colour_c = *((u8 *) (((s8 *) obj) + 0x2E));
            poly->v3 = colour_c;
            poly->v2 = colour_c;
            colour_d = (u8) (colour_c + (*((u8 *) (((s8 *) obj) + 0x32))));
            poly->v1 = colour_d;
            poly->v0 = colour_d;
            mid_otz = (s32) ((otz[i] + otz[i + 1]) >> 1);
            p = mid_otz;
            if (((u32) mid_otz) < 0x1E0U) {
                u32 low_mask = 0xFFFFFF;
                u32 high_mask = 0xFF000000;
                slot_offset = mid_otz * 4;
                poly->tag = (s32) ((poly->tag & high_mask)
                    | ((*((s32 *) (((s8 *) (((u8 *) slot_offset) + ((u32) (base->draw_buffer))))
                    + 0xB0))) & low_mask));
                *((s32 *) (((s8 *) (((u8 *) slot_offset) + ((u32) (base->draw_buffer)))) + 0xB0)) =
                    (s32) (((*((s32 *) (((s8 *) (((u8 *) slot_offset) + ((u32) (base->draw_buffer))))
                    + 0xB0))) & high_mask) | (((s32) poly) & low_mask));
            }
        }

        parent = *((void **) (((s8 *) node) + (-8)));
        if (parent == 0) {
            break;
        }
        node =  (((u8 *) parent) + 0x20);
    }
    while (1);
    return 0;
}

#include "modules/dungeon_ovl_19c6800.h"
#include "common.h"
#include "shared/object_flags.h"




typedef struct S_819A764C_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_819A764C_1;   /* inner in func_819A764C */



s32 update_segment(void *);


/* Update randomized intermediate points and advance the effect state. */
void update_randomized_intermediate_points(IntermediatePointEffectBody *self)
{
    s16 point_step[3];
    s32 state;
    s32 point_index;
    void *object_base;
    S_819A764C_1 *linked_object;
    void *message;

    linked_object = self->unk_00;
    linked_object->unk_52 |= 0x8000;

    point_step[0] = (self->point_slots[4].x.s - self->point_slots[0].x.s) >> 2;
    point_step[1] = (self->point_slots[4].y.s - self->point_slots[0].y.s) >> 2;
    point_step[2] = (self->point_slots[4].z.s - self->point_slots[0].z.s) >> 2;
    point_index = 1;

    do {
        self->point_slots[point_index].x.s = self->point_slots[0].x.u + point_step[0] * point_index
        + (rand() & 0x3F) - 0x20;
        self->point_slots[point_index].y.s = self->point_slots[0].y.u + point_step[1] * point_index
        + (rand() & 0x3F) - 0x20;
        self->point_slots[point_index].z.s = self->point_slots[0].z.u + point_step[2] * point_index
        - (rand() & 0x3F);
        point_index++;
    } while (point_index < 4);

    self->unk_2C = ((self->unk_3E.u & 3) << 5) + 0x80;
    state = self->unk_3C.s;
    self->unk_2E = ((s16)self->unk_3E.u >> 2) << 5;

    switch (state) {
    case 0:
        object_base = NODE_HEADER(self);
        message = update_segment;

        register_node(object_base, message);
    case 1:
        self->unk_3E.u = (rand() & 3) + 2;
        self->unk_38 += 0xFFF7F7F8;
        self->unk_42 = GetClut((rand() & 0xF) << 4, 0x1F8);
        self->unk_3C.u++;
        return;
    case 2:
        NODE_HEADER(self)->flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        break;
    }
}
