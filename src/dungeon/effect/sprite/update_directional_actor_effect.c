/* Timed target effects, textured quad rendering, scattered fragments, and segment animation. */
#include "shared/sprite_frame_state.h"
#include "dungeon/effect/sprite/update_directional_actor_effect.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/effect/sprite/update_directional_actor_effect.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor.h"

typedef s32 M2C_UNK;

typedef struct S_81988800_0 {
    void * unk_00;
    void * unk_04;
    u8 unk_08;
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x44];
    union { u16 u; s16 s; } unk_50;   /* accessed as both */
    union { s16 s; u16 u; } unk_52;   /* accessed as both */
} S_81988800_0;   /* state in update_directional_actor_effect */

typedef struct S_81988800_2 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_81988800_2;   /* out in update_directional_actor_effect */

typedef struct S_81988800_3 {
    void * unk_00;
    s16 unk_04;
    s16 unk_06;
    union { void * p32; u16 u16; } unk_08;   /* accessed as both */
    void * unk_0C;
    struct {
        s16 unk_00;
        s16 unk_02;
        s16 unk_04;
    } entries[8];
    s16 unk_40;
} S_81988800_3;   /* work in update_directional_actor_effect */

typedef struct S_81988800_4 {
    u8 pad_00[0xA6];
    u16 unk_A6;
    u8 unk_A8;
} S_81988800_4;   /* global in update_directional_actor_effect */

typedef struct S_81988800_5 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0x8];
    s32 unk_1C;
    void * unk_20;
} S_81988800_5;   /* object in update_directional_actor_effect */

typedef struct S_81988800_6 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
} S_81988800_6;   /* spawn_fields in update_directional_actor_effect */

typedef struct S_81988800_8 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_81988800_8;   /* base in update_directional_actor_effect */

typedef struct S_81988800_10 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_81988800_10;   /* ((S_81988800_3 *)work)->unk_08.p32 in update_directional_actor_effect */

typedef struct S_81988800_11 {
    u16 unk_00;
} S_81988800_11;   /* ((S_81988800_0 *)state)->unk_04 in update_directional_actor_effect */

typedef struct S_81988800_12 {
    u8 pad_00[0x8];
    void * unk_08;
} S_81988800_12;   /* ((S_81988800_3 *)work)->unk_0C in update_directional_actor_effect */

extern M2C_UNK D_80024D58;

extern s32 resolve_record_orientation_or_fallback();
extern s32 read_sound_mode_blocking_status();
extern void apply_attack_power_and_element_effects();

void update_directional_actor_effect(void *state_data, void *position_data);

/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol add_flag_adjusted_target_value).  The phase table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */
void (*const dungeon_19a8800_entry)(void *, void *) = update_directional_actor_effect;

/* Advance a timed effect sequence, spawning objects and applying the effect to targets. */
void update_directional_actor_effect(void *state_data, void *position_data)
{
    s16 offset[3];
    ObjectNodeHeader *object;
    u8 *work;
    void *source;
    void *list_head;
    void *actor;
    u8 *unused_fields;
    s32 timer;

    timer = ((S_81988800_0 *)state_data)->unk_50.u;
    source = ((S_81988800_0 *)state_data)->unk_00;
    timer--;
    ((S_81988800_0 *)state_data)->unk_50.u = timer;
    work = (u8 *)source - 0x20;

    switch (((S_81988800_0 *)state_data)->unk_0A.s) {
    case 0:
        ((PlayerRecord *)primary_actor_record)->unk_102 = 1;
        ((PlayerRecord *)primary_actor_record)->unk_F4 = 0;
        ((S_81988800_2 *)position_data)->unk_00 = ((S_81988800_10 *)(((S_81988800_3 *)work)->unk_08.p32))->unk_00;
        ((S_81988800_2 *)position_data)->unk_04 = ((S_81988800_10 *)(((S_81988800_3 *)work)->unk_08.p32))->unk_04;
        ((S_81988800_2 *)position_data)->unk_08.at00.v =
            ((S_81988800_10 *)(((S_81988800_3 *)work)->unk_08.p32))->unk_08;
        ((S_81988800_0 *)state_data)->unk_0A.u++;
    case 1:
    {
        u8 *spawn_data;
        if (((S_81988800_11 *)(((S_81988800_0 *)state_data)->unk_04))->unk_00 & 0x80) {
            actor = primary_actor_record;
            ((S_81988800_0 *)state_data)->unk_50.u = 10;
            ((S_81988800_4 *)actor)->unk_A6--;
            ((S_81988800_4 *)actor)->unk_A8 = ((S_81988800_0 *)state_data)->unk_08;

            object = allocate_list_node(0x302, ((u8 *)(&scene_object_list_anchor)));
            if (object != 0) {
                if (resolve_record_orientation_or_fallback(((S_81988800_12 *)(((S_81988800_3 *)work)->unk_0C))->unk_08,
                                  ((S_81988800_3 *)work)->unk_0C, offset, 0) == 0) {
                    offset[2] = 0;
                    offset[1] = 0;
                    offset[0] = 0;
                }
                object->update_callback = update_effect_and_spawn_fragments;
                register_node(object, (s32)create_counted_sprite_effect);
                ((S_81988800_5 *)object)->unk_20 = state_data;
                spawn_data = (u8 *)object + 0x20;

                ((S_81988800_2 *)position_data)->unk_00 =
                    ((S_81988800_10 *)(((S_81988800_3 *)work)->unk_08.p32))->unk_00 +
                                      ((s32)offset[0] << 16);
                ((S_81988800_6 *)spawn_data)->unk_1C = ((S_81988800_2 *)position_data)->unk_00;
                ((S_81988800_2 *)position_data)->unk_04 =
                    ((S_81988800_10 *)(((S_81988800_3 *)work)->unk_08.p32))->unk_04 +
                                      ((s32)offset[1] << 16);
                ((S_81988800_6 *)spawn_data)->unk_20 = ((S_81988800_2 *)position_data)->unk_04;
                ((S_81988800_2 *)position_data)->unk_08.at00.v =
                    ((S_81988800_10 *)(((S_81988800_3 *)work)->unk_08.p32))->unk_08 +
                                      ((s32)offset[2] << 16);
                ((S_81988800_6 *)spawn_data)->unk_24 = ((S_81988800_2 *)position_data)->unk_08.at00.v;
            }
            ((S_81988800_0 *)state_data)->unk_0A.u++;
        }
        break;
    }

    case 2:
    {
        s32 effect_id;
        s32 variant;
        if (((S_81988800_0 *)state_data)->unk_50.s <= 0) {
            variant = read_sound_mode_blocking_status(4);
            effect_id = 0x4300;
            if (variant != 2) {
                effect_id = 0x300;
            }
            play_sound_if_enabled(effect_id);
            ((S_81988800_0 *)state_data)->unk_50.u = 13;
            ((S_81988800_0 *)state_data)->unk_0A.u++;
        }
        break;
    }

    case 3:
    {
        s32 entry_index;
        if (((S_81988800_0 *)state_data)->unk_50.s <= 0) {
            object = allocate_list_node(0x302, ((u8 *)(&scene_object_list_anchor)));
            if (object != 0) {
                object->update_callback = update_segment;
                register_node(object, (s32)&D_80024D58);
                actor = (void *)((u8 *)(&reference_tile_object));
                offset[0] = (((u16)primary_actor_record->facing) >> 9) & 7;
                work = (u8 *)object + 0x20;
                ((S_81988800_3 *)work)->unk_04 = (((u8 *)actor)[0x24] << 6) + 0x20;
                ((S_81988800_3 *)work)->unk_06 = (((u8 *)actor)[0x25] << 6) + 0x20;
                ((S_81988800_3 *)work)->unk_08.u16 = ((S_81988800_2 *)position_data)->unk_08.at02.v;
                for (entry_index = 7; entry_index >= 0; entry_index--) {
                    ((S_81988800_3 *)work)->entries[entry_index].unk_02 = 0;
                    ((S_81988800_3 *)work)->entries[entry_index].unk_00 = 0;
                }
                ((S_81988800_3 *)work)->unk_00 = state_data;
                ((S_81988800_3 *)work)->unk_40 = 0;
            }
            ((S_81988800_0 *)state_data)->unk_50.u = 0x3D;
            ((S_81988800_0 *)state_data)->unk_0A.u++;
        }
        break;
    }

    case 4:
    {
        if (((S_81988800_0 *)state_data)->unk_50.s == 8) {
            object = primary_actor_record;
            if (object != 0) {

                list_head = object;
                work = (u8 *)((u8 *)(&reference_tile_object));
loop:
                object = find_eligible_nearby_entry(work[0x24], work[0x25], list_head, object);
                if (object != 0) {
                    if (!(*(s32 *)&object->pad_1C & 0x2000)) {
                        apply_attack_power_and_element_effects(object, 0x10, ((S_81988800_0 *)state_data)->unk_09, 10,
                                      ((S_81988800_8 *)source)->unk_2A, source, 2);
                    }
                    goto loop;
                }
            }
        }

        if ((reference_tile_object.sprite_flags & 0x8000) || ((S_81988800_0 *)state_data)->unk_50.s < 0) {
            if (((S_81988800_0 *)state_data)->unk_52.s & 0x8000) {
                ((S_81988800_0 *)state_data)->unk_52.u &= 0x7FFF;
            } else {
                g_dungeon_status.active_actor = 0;
                g_dungeon_status.activity_counts.parts.pending_action_count--;
                (*(u16 *)((u8 *)state_data + -2)) |= NODE_REMOVE;
                object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            }
        }
        break;
    }
    }
}
#include "dungeon/effect/sprite/update_directional_actor_effect.h"
#include "shared/game_work.h"

typedef struct S_81988C1C_0 {
    u8 pad_00[0x1E];
    u16 unk_1E;
    u8 pad_20[0x2];
    u16 unk_22;
    u8 pad_24[0x2];
    u16 unk_26;
    u8 pad_28[0x18];
    u8 unk_40;
    u8 pad_41[0x1];
    u8 unk_42;
    u8 pad_43[0x1];
    u8 unk_44;
    u8 pad_45[0x1];
    u8 unk_46;
    u8 pad_47[0x7];
    u16 unk_4E;
    u16 unk_50;
    u16 unk_52;
} S_81988C1C_0;   /* item in create_counted_sprite_effect */

typedef struct S_81988C1C_1 {
    u16 unk_00;
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
} S_81988C1C_1;   /* output in create_counted_sprite_effect */

typedef struct S_81988C1C_2 {
    union { void * s; u32 u; } unk_00;   /* accessed as both */
} S_81988C1C_2;   /* base in create_counted_sprite_effect */

typedef struct S_81988C1C_3 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_81988C1C_3;   /* pool in create_counted_sprite_effect */

typedef struct S_81988C1C_4 {
    u32 unk_00;
    s32 unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 pad_0E[0x4];
    u16 unk_12;
    u8 unk_14;
    u8 unk_15;
    u16 unk_16;
    u8 pad_18[0x2];
    u16 unk_1A;
    u8 unk_1C;
    u8 unk_1D;
    u8 pad_1E[0x4];
    u16 unk_22;
    u8 unk_24;
    u8 unk_25;
} S_81988C1C_4;   /* packet in create_counted_sprite_effect */

typedef struct S_81988C1C_5 {
    u8 pad_00[0xB0];
    u32 unk_B0;
} S_81988C1C_5;   /* (u8 *)index in create_counted_sprite_effect */

typedef struct S_81988C1C_6_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_81988C1C_6_pre;   /* the 0x8 bytes before node in create_counted_sprite_effect, addressed as node[-1] */

typedef struct S_81988C1C_7 {
    u8 pad_00[0xB0];
    u32 unk_B0;
} S_81988C1C_7;   /* (u8 *)(index + ((S_81988C1C_2 *)base)->unk_00.u) in create_counted_sprite_effect */

typedef struct {
    u8 pad[0x1FC];
    s32 unk1FC;
} S_800A1600_D80083160;

extern s32 RotTransPers();
extern void SetSemiTrans();
extern void SetPolyFT4();

/* Projects linked items into textured quads and adds them to the ordering table. */
s32 create_counted_sprite_effect(void *first_item) {
    u16 world_pos[4];
    u8 screen_points[8];
    s32 projection_scratch;
    void *node = first_item;
    GameWork *render_state = &g_game_work;
    void *screen_base = screen_points;
    void *next_node;

    for (;;) {
        void *item = node;
        void *screen_point;
        s32 point_index;
        u32 depth_index;
        s32 half_width;
        u16 center_z;

        world_pos[0] = ((S_81988C1C_0 *)item)->unk_1E;
        world_pos[1] = ((S_81988C1C_0 *)item)->unk_22;
        center_z = ((S_81988C1C_0 *)item)->unk_26;
        world_pos[2] = center_z;
        world_pos[2] = center_z - ((s32)(((S_81988C1C_0 *)item)->unk_4E << 16) >> 17);

        point_index = 0;
        screen_point = screen_base;
        do {
            depth_index = RotTransPers(world_pos, screen_point, &projection_scratch, &projection_scratch) - 8;
            screen_point = (u8 *)screen_point + 4;
            point_index++;
            world_pos[2] += ((S_81988C1C_0 *)item)->unk_4E;
        } while (point_index < 2);

        half_width = (((S_81988C1C_1 *)screen_points)->unk_02.s - ((S_81988C1C_1 *)screen_points)->unk_06.s) >> 1;
        if (depth_index < 0x1E0U) {
            void *packet_pool;
            void *packet;
            register u8 tex_v;
            u8 tex_u;
            u8 tex_width;
            u16 screen_coord;
            u32 ot_slot;
            u32 depth_offset;
            u32 addr_mask = 0;
            u32 color_or_tag_mask = 0;

            packet_pool = render_state->draw_buffer;
            packet = ((S_81988C1C_3 *)packet_pool)->unk_8D0;
            ((S_81988C1C_3 *)packet_pool)->unk_8D0 = (u8 *)packet + 0x34;
            ((S_81988C1C_4 *)packet)->unk_04 = 0xA0A0A0;
            SetPolyFT4(packet);
            SetSemiTrans(packet, 1);

            ((S_81988C1C_4 *)packet)->unk_16 = ((S_81988C1C_0 *)item)->unk_50;
            (*(u16 *)((u8 *)packet + 0x0E)) = ((S_81988C1C_0 *)item)->unk_52;
            screen_coord = ((S_81988C1C_1 *)screen_points)->unk_00 + half_width;
            (*(u16 *)((u8 *)packet + 0x10)) = screen_coord;
            (*(u16 *)((u8 *)packet + 0x08)) = screen_coord;
            screen_coord = *(u16 *)&screen_points[0] - half_width;
            (*(u16 *)((u8 *)packet + 0x20)) = screen_coord;
            (*(u16 *)((u8 *)packet + 0x18)) = screen_coord;
            screen_coord = ((S_81988C1C_1 *)screen_points)->unk_02.u;
            ((S_81988C1C_4 *)packet)->unk_1A = screen_coord;
            ((S_81988C1C_4 *)packet)->unk_0A = screen_coord;
            screen_coord = ((S_81988C1C_1 *)screen_points)->unk_06.u;
            ((S_81988C1C_4 *)packet)->unk_22 = screen_coord;
            ((S_81988C1C_4 *)packet)->unk_12 = screen_coord;

            tex_u = ((S_81988C1C_0 *)item)->unk_40;
            addr_mask = 0xFFFFFF;
            ((S_81988C1C_4 *)packet)->unk_14 = tex_u;
            ((S_81988C1C_4 *)packet)->unk_0C = tex_u;
            tex_width = ((S_81988C1C_0 *)item)->unk_44;
            tex_u += tex_width;
            ((S_81988C1C_4 *)packet)->unk_24 = tex_u;
            ((S_81988C1C_4 *)packet)->unk_1C = tex_u;
            tex_v = ((S_81988C1C_0 *)item)->unk_42;
            depth_offset = depth_index << 2;
            ((S_81988C1C_4 *)packet)->unk_1D = tex_v;
            ((S_81988C1C_4 *)packet)->unk_0D = tex_v;
            tex_v += ((S_81988C1C_0 *)item)->unk_46;
            color_or_tag_mask = 0xFF000000;
            ((S_81988C1C_4 *)packet)->unk_25 = tex_v;
            ((S_81988C1C_4 *)packet)->unk_15 = tex_v;

            ((S_81988C1C_4 *)packet)->unk_00 =
                (((S_81988C1C_4 *)packet)->unk_00 & color_or_tag_mask) |
                (((S_81988C1C_7 *)((u8 *)(depth_offset + *(u32 *)&render_state->draw_buffer)))->unk_B0 & addr_mask);
            ot_slot = depth_offset + (u32)render_state->draw_buffer;
            ((S_81988C1C_5 *)((u8 *)ot_slot))->unk_B0 =
                (((S_81988C1C_5 *)((u8 *)ot_slot))->unk_B0 & color_or_tag_mask) |
                ((u32)packet & addr_mask);
        }

        next_node = ((S_81988C1C_6_pre *)node)[-1].unk_00;
        if (next_node == 0) {
            break;
        }
        node = (u8 *)next_node + 0x20;
    }

    return 0;
}
#include "dungeon/effect/sprite/update_directional_actor_effect.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/entity.h"

typedef struct MainObject {
    void *link;
    u8 pad04[0x18];
    s32 x;
    s32 y;
    s32 z;
    u8 pad28[0x18];
    s16 tex_u;
    s16 tex_v;
    s16 size_a;
    s16 size_b;
    s16 age;
    s16 timer;
    s16 state;
    u16 angle;
    s16 value_a;
    s16 value_b;
} MainObject;

typedef struct LinkObject {
    u8 pad00[0x52];
    u16 flags;
} LinkObject;

typedef struct Vec3 {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

typedef struct ChildObject {
    void *resource;
    u8 byte04;
    u8 byte05;
    u8 pad06[2];
    void *resource_data;
    u32 color;
    u16 life;
    u8 pad12[2];
    u16 flags;
    u8 pad16[6];
    s16 scale_x;
    s16 scale_y;
} ChildObject;

typedef struct EffectObject {
    u8 pad00[8];
    Vec3 *position;
    ChildObject *child;
    void *callback;
    u8 pad14[12];
    void *owner;
    u8 pad24[0x48];
    s16 state;
} EffectObject;

typedef struct EffectTail {
    void *owner;
    u8 pad24[0x48];
    s16 state;
} EffectTail;

typedef struct Resource {
    u32 pad00;
    void *data;
} Resource;

extern u8 directional_sprite_entries[];

extern s32 resolve_record_orientation_or_fallback(void *, void *, s16 *, s32);
extern s32 rsin(s32);
extern s32 GetTPage(s32, s32, s32, s32);
extern s32 GetClut(s32, s32);
extern s32 rand(void);

/* Moves an animated effect toward the actor's sprite offset and emits randomized fragments until it ends. */
void update_effect_and_spawn_fragments(MainObject *obj)
{
    s16 hit[3];
    s32 state_count;
    s32 count;
    EffectObject *effect;
    volatile EffectTail *tail;
    SpriteFrameState *child;
    void *callback;
    Resource *resource;
    TileObject *call_data;
    s32 state;

    obj->age++;
    ((LinkObject *)obj->link)->flags |= 0x8000;
    state_count = -1;

    state = obj->state;
    switch (state) {
    case 0:
        obj->value_a = GetTPage(0, 1, 0x2C0, 0x100);
        obj->value_b = GetClut(0x80, 0x1F7);
        obj->size_b = 0x1F;
        obj->size_a = 0x1F;
        obj->age = 0;
        obj->angle = 0x30;
        obj->state++;
    case 1:
        state_count = 14;
        if (resolve_record_orientation_or_fallback(((void *)reference_tile_object.sprite_source), &reference_tile_object, hit, 0)) {
            obj->x += (hit[0] + view_reference_entity.x.w.i - *(s16 *)((u8 *)obj + 0x1E)) << 14;
            obj->y += (hit[1] + view_reference_entity.y.w.i - *(s16 *)((u8 *)obj + 0x22)) << 14;
            obj->z += (hit[2] + view_reference_entity.z.w.i - *(s16 *)((u8 *)obj + 0x26)) << 14;
            obj->z -= rsin((obj->age << 11) / 10) << 9;
        }
        if (obj->age >= 10) {
            obj->timer = 0x10;
            obj->state++;
        }
        break;
    case 2:
        state_count = 9;
        if (obj->age >= 11) {
            state_count = 4;
        }
        obj->angle += 2;
        if (resolve_record_orientation_or_fallback(((void *)reference_tile_object.sprite_source), &reference_tile_object, hit, 0)) {
            obj->x += (hit[0] + view_reference_entity.x.w.i - *(s16 *)((u8 *)obj + 0x1E)) << 15;
            obj->y += (hit[1] + view_reference_entity.y.w.i - *(s16 *)((u8 *)obj + 0x22)) << 15;
            obj->z += (hit[2] + view_reference_entity.z.w.i - *(s16 *)((u8 *)obj + 0x26)) << 15;
        }
        if (obj->age >= 13) {
            obj->age = 8;
        }
        obj->timer--;
        if (obj->timer <= 0 && obj->age == 12) {
            obj->state++;
        }
        break;
    case 3:
        state_count = 5;
        if (obj->age == 15) {
            ((u16 *)obj)[-1] |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }

    count = state_count;

    obj->tex_u = (obj->age & 3) << 5;
    obj->tex_v = ((s16)obj->age >> 2) * 32 + 0x80;

    if (count < 0) {
        return;
    }

    callback = mark_referenced_object_and_update_flags;
    resource = (Resource *)directional_sprite_entries;
    do {
        effect = (EffectObject *)allocate_list_node(0x312, ((u8 *)(&scene_object_list_anchor)));
        if (effect != (EffectObject *)0) {
            effect->callback = callback;
            register_node(effect, (s32)project_sprite_chain);
            child = effect->child;

            effect->position->x = obj->x +
                (((rand() & 0x3FF) - 0x1FF) << 12);
            effect->position->y = obj->y +
                (((rand() & 0x3FF) - 0x1FF) << 12);
            effect->position->z = obj->z +
                (((rand() & 0x3FF) - 0x1FF) << 11);

            child->scale_y = 0x1000;
            child->scale_x = 0x1000;
            child->tpage_abr = 0x60;
            child->unk_00 = resource;
            child->flags |= 0xC;
            child->source = resource->data;
            child->unk_04 = 0;
            child->frame_ticks = 0;
            child->color.word = 0x00808080;
            effect->owner = obj->link;
            tail = (EffectTail *)&effect->owner;
            tail->state = 0;
        }
    } while (--count >= 0);
}
#include "dungeon/effect/sprite/update_directional_actor_effect.h"
#include "shared/object_flags.h"

/* Marks the referenced object and updates entry and global flags based on target status. */
void mark_referenced_object_and_update_flags(void *entry, void *unused, SpriteFrameState *target) {
    void *object;

    object = *(void **)entry;
    *(u16 *)((u8 *)object + 0x52) =
        (u16)(*(u16 *)((u8 *)object + 0x52) | 0x8000);
    advance_sprite_animation_and_textures(target);
    if (target->flags & 0x6000) {
        *(u16 *)((u8 *)entry - 2) =
            (u16)(*(u16 *)((u8 *)entry - 2) | NODE_REMOVE);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
#include "dungeon/effect/sprite/update_directional_actor_effect.h"

typedef struct S_80024B20_0 {
    u8 pad_00[0x10];
    u16 unk_10;
} S_80024B20_0;   /* dst in update_segment */

typedef struct S_80024B20_1 {
    u8 pad_00[0x10];
    u16 unk_10;
} S_80024B20_1;   /* src in update_segment */

typedef struct S_80024B20_2_pre {
    u16 unk_00;
} S_80024B20_2_pre;   /* the 0x2 bytes before arg0 in update_segment, addressed as arg0[-1] */

typedef struct S_80024B20_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x2A];
    s16 unk_3A;
    u8 pad_3C[0x4];
    union { s16 s; u16 u; } unk_40;   /* accessed as both */
    union { u16 u; s16 s; } unk_42;   /* accessed as both */
} S_80024B20_2;   /* arg0 in update_segment */

typedef struct S_80024B20_3 {
    u8 pad_00[0x12];
    union { u16 v; s16 n; } unk_12;   /* accessed as both */
    s16 unk_14;
} S_80024B20_3;   /* p in update_segment */

typedef struct S_80024B20_4 {
    u8 pad_00[0x12];
    s16 unk_12;
} S_80024B20_4;   /* (u8 *)arg0 + offset in update_segment */

typedef struct S_80024B20_5 {
    u8 pad_00[0x14A0];
    u32 unk_14A0;
} S_80024B20_5;   /* page in update_segment */

extern s32 rsin();

/* Updates an eight-segment effect's samples, motion, color, and lifetime. */
void update_segment(void *effect) {
    s32 segment_index;
    u16 state;
    s32 base_speed;
    u8 *segment;
    {
        s32 doubled_index;
        segment_index = 0;
        do {
            s32 next_index;
            s32 word_offset, src_offset, dst_offset;
            u8 *src_segment;
            u8 *dst_segment;
            doubled_index = segment_index * 2;
            word_offset = doubled_index + segment_index;
            next_index = segment_index + 1;
            dst_offset = word_offset * 2;
            src_offset = next_index * 6;
            segment_index = next_index;
            src_segment = effect;
            dst_segment = effect;
            src_segment += src_offset;
            dst_segment += dst_offset;
            ((S_80024B20_0 *)dst_segment)->unk_10 = ((S_80024B20_1 *)src_segment)->unk_10;
        } while (segment_index < 7);
    }

    {
        u16 *segments = (u16 *)effect;
        for (segment_index = 7; segment_index >= 0; segment_index--) {
            segments[segment_index * 3 + 9] += segments[segment_index * 3 + 10];
        }
    }

    ((S_80024B20_2 *)effect)->unk_42.u--;
    switch (((S_80024B20_2 *)effect)->unk_40.s) {
    case 0:
        ((S_80024B20_2 *)effect)->unk_42.u = 0;
        ((S_80024B20_2 *)effect)->unk_0C = 0;
        ((S_80024B20_2 *)effect)->unk_40.s = ((S_80024B20_2 *)effect)->unk_40.u + 1;
                        /* fallthrough */
    case 1:
    {
        s32 color = ((S_80024B20_2 *)effect)->unk_0C;
        s32 phase = ((S_80024B20_2 *)effect)->unk_42.s;
        color += 0xC0C0C;
        ((S_80024B20_2 *)effect)->unk_0C = color;
        ((S_80024B20_2 *)effect)->unk_3A = rsin(phase << 9) >> 7;
        if (((S_80024B20_2 *)effect)->unk_0C > 0x60605F) {
            ((S_80024B20_2 *)effect)->unk_42.u = 0x38;
            ((S_80024B20_2 *)effect)->unk_40.u++;
            return;
        }
        return;
    }
    case 2:
    {
        segment_index = 7;
        base_speed = 0xD0;
        segment = (u8 *)effect + 0x2A;
        do {
            s32 index_squared = segment_index * segment_index;
            s32 speed_bias;
            segment_index--;
            speed_bias = base_speed - ((S_80024B20_2 *)effect)->unk_42.u;
            base_speed -= 0x18;
            ((S_80024B20_3 *)segment)->unk_14 = speed_bias + ((index_squared >> 2) * 0x14);
            segment -= 6;
        } while (segment_index >= 0);
    }
        {
            s32 gap_limit;
            segment_index = 6;
            gap_limit = 0x160;
            while (segment_index >= 0) {
                u16 position;

                base_speed = (segment_index + 1) * 6;
                segment = (u8 *)effect + segment_index * 6;
                position = ((S_80024B20_3 *)segment)->unk_12.v;
                if (gap_limit < (((S_80024B20_4 *)((u8 *)effect + base_speed))->unk_12
                    - ((S_80024B20_3 *)segment)->unk_12.n)) {
                    ((S_80024B20_3 *)segment)->unk_12.n = position + (gap_limit + (gap_limit >> 1));
                }
                gap_limit -= 0x10;
                segment_index--;
            }
        }
        if (((S_80024B20_2 *)effect)->unk_42.s < 8) {
            ((S_80024B20_2 *)effect)->unk_0C += (s32)0xFFF3F3F4;
        }
        if (((S_80024B20_2 *)effect)->unk_42.s <= 0) {
            state = ((S_80024B20_2 *)effect)->unk_40.u;
            state++;
            ((S_80024B20_2 *)effect)->unk_40.u = state;
            return;
        }
        return;
    case 3:
    {
        u32 globals_base = 0x80080000;
        ((S_80024B20_2_pre *)effect)[-1].unk_00 |= 0x8000;
        ((S_80024B20_5 *)globals_base)->unk_14A0 |= 0x8000;
    }
        return;
    default:
        return;
    }
}
