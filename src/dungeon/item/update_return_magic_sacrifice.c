#include "shared/entity.h"
#include "shared/object_node_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_links.h"
#include "engine/node.h"
struct EntityLinkNode;

typedef struct S_800C2824_0 {
    void * unk_00;
    s16 unk_04;
    s16 unk_06;
} S_800C2824_0;   /* effect in update_return_magic_sacrifice */

   /* object_vertices in update_return_magic_sacrifice */

typedef struct S_800C2824_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_800C2824_3;   /* vertices in update_return_magic_sacrifice */

typedef struct S_800C2824_4 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    union {
        struct { s32 v; } at00;
        struct { s8 v; } at00u;
        struct { u8 pad[0x1]; s8 v; } at01;
        struct { u8 pad[0x2]; s8 v; } at02;
    } unk_0C;   /* overlapping accesses */
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800C2824_4;   /* sprite in update_return_magic_sacrifice */

typedef struct S_800C2824_5 {
    u8 pad_00[0xA93];
    s8 unk_A93;
} S_800C2824_5;   /* page_base + (object_slot * 0x54) in update_return_magic_sacrifice */

   /* the 0x14 bytes before c2_object in update_return_magic_sacrifice, addressed as c2_object[-1] */

typedef struct S_800C2824_6 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800C2824_6;   /* c2_object in update_return_magic_sacrifice */

   /* (void *)c2_coord in update_return_magic_sacrifice */

typedef struct S_800C2824_8 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_800C2824_8;   /* effect_object in update_return_magic_sacrifice */

typedef struct S_800C2824_10 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_800C2824_10;   /* c3_page in update_return_magic_sacrifice */

   /* object_coords in update_return_magic_sacrifice */

   /* the 0x14 bytes before c17_object in update_return_magic_sacrifice, addressed as c17_object[-1] */

typedef struct S_800C2824_12 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800C2824_12;   /* c17_object in update_return_magic_sacrifice */

   /* (void *)c17_coord in update_return_magic_sacrifice */

typedef struct S_800C2824_16 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800C2824_16;   /* ((S_800C2824_0 *)effect)->unk_00 in update_return_magic_sacrifice */

s32 get_entity_effect_value();
s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
void adjust_source_value_and_finalize(void *context, const void *source);
void unlink_entity_node(struct EntityLinkNode *node);
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
void *detach_record_and_update_slot_state();
s32 play_sound_if_enabled(s32 query_value);
s32 release_entity_slot_and_update_flags();
void draw_transformed_sprite_with_clip_rect();
void * create_five_point_effect(u8, u8, s16, void *, s32, s32, void *);
void retire_tracked_effect_by_id();
extern s32 return_magic_begin_address();
extern s32 D_800C27F0();
extern s32 linked_object_draw_address();
extern M2C_UNK D_800DF45C;
extern M2C_UNK return_magic_sprite_data;
extern void *return_magic_effect_object;
extern void *return_magic_fade_object;
extern u8 D_800E1640[55];

typedef struct {
    s32 clip_origin_xy;
    s32 clip_extent_wh;
    s16 screen_x;
    s16 screen_y;
} StackArgs;

enum ReturnSacrificeState {
    RETURN_SACRIFICE_INIT = 0,
    RETURN_SACRIFICE_FADE_OUT = 1,
    RETURN_SACRIFICE_RELEASE_ACTOR = 2,
    RETURN_SACRIFICE_PLAYER_EFFECT = 3,
    RETURN_SACRIFICE_ACTOR_EFFECT = 16,
    RETURN_SACRIFICE_WAIT_EFFECT = 17,
};

/* Advance the object effect through fading, tile cleanup, and completion. */
void update_return_magic_sacrifice(void *effect, void *vertices, void *sprite) {
    StackArgs effect_args;
    s32 object_slot;
    s32 release_flags;
    s32 tile_flags;
    s16 fade_ticks;
    s16 wait_ticks;
    s32 state;
    u8 *flags_page;
    void *linked_object;
    s32 effect_param;
    s32 effect_flags;
    void *marked_object;
    s32 faded_shade;
    u16 vertex_x;
    u16 vertex_y;
    u16 vertex_z;
    u8 shade;
    MovingTile *object_coords;
    ObjectNodeHeader *object_base;
    void *source_object;

    ObjectPosition *object_vertices;
    void *finished_object;
    void *release_object;
    u32 release_coord;
    s32 release_status;
    s32 release_x;
    void *expired_object;
    u32 expired_coord;
    s32 expired_status;
    s32 expired_x;
    ObjectNodeHeader *final_object;
    u16 final_flags;
    void *effect_object;
    u8 *slots_page;

    state = ((S_800C2824_0 *)effect)->unk_04;
    switch (state) {
    case RETURN_SACRIFICE_INIT:
        if (!(((S_800C2824_16 *)(((S_800C2824_0 *)effect)->unk_00))->unk_14 & 0x4000)) {
            ((S_800C2824_0 *)effect)->unk_04 = RETURN_SACRIFICE_ACTOR_EFFECT;
            return;
        }
        effect_args.clip_origin_xy = 0x01800340;
        effect_args.clip_extent_wh = 0x400040;
        effect_args.screen_x = 0x360;
        effect_args.screen_y = 0x1B8;
        draw_transformed_sprite_with_clip_rect(((S_800C2824_0 *)effect)->unk_00, &effect_args.clip_origin_xy, &effect_args.screen_x, 1, 2);
        object_base = ((S_800C2824_0 *)effect)->unk_00 - 0x20;
        unlink_node(object_base);
        retire_tracked_effect_by_id(object_base);
        object_vertices = object_base->position;
        vertex_x = (u16)object_vertices->x.w.i;
        ((S_800C2824_3 *)vertices)->unk_02 = vertex_x;
        ((S_800C2824_3 *)vertices)->unk_0E = vertex_x;
        vertex_y = (u16)object_vertices->y.w.i;
        ((S_800C2824_3 *)vertices)->unk_06 = vertex_y;
        ((S_800C2824_3 *)vertices)->unk_12 = vertex_y;
        vertex_z = (u16)object_vertices->z.w.i;
        ((S_800C2824_3 *)vertices)->unk_0A = vertex_z;
        ((S_800C2824_3 *)vertices)->unk_16 = vertex_z;
        register_node(effect - 0x20, &linked_object_draw_address);
        ((S_800C2824_4 *)sprite)->unk_10 = 0x20;
        ((S_800C2824_4 *)sprite)->unk_08 = &return_magic_sprite_data;
        ((S_800C2824_4 *)sprite)->unk_0C.at00.v = 0x808080;
        ((S_800C2824_4 *)sprite)->unk_1E = 0x1000;
        ((S_800C2824_4 *)sprite)->unk_1C = 0x1000;
        ((S_800C2824_4 *)sprite)->unk_14 = (u16) (((S_800C2824_4 *)sprite)->unk_14 | 0xC);
        ((S_800C2824_0 *)effect)->unk_06 = 0x10;
        play_sound_if_enabled(1);
        ((S_800C2824_0 *)effect)->unk_04 = (s16) ((u16) ((S_800C2824_0 *)effect)->unk_04 + 1);
    case RETURN_SACRIFICE_FADE_OUT:
        shade = (u8) ((S_800C2824_4 *)sprite)->unk_0C.at00.v;
        faded_shade = shade - ((s32) shade / (s16) ((S_800C2824_0 *)effect)->unk_06);
        ((S_800C2824_4 *)sprite)->unk_0C.at00u.v = faded_shade;
        ((S_800C2824_4 *)sprite)->unk_0C.at02.v = faded_shade;
        ((S_800C2824_4 *)sprite)->unk_0C.at01.v = faded_shade;
        fade_ticks = (u16) ((S_800C2824_0 *)effect)->unk_06 - 1;
        ((S_800C2824_0 *)effect)->unk_06 = fade_ticks;
        if ((fade_ticks << 0x10) > 0) {
            return;
        }
        ((S_800C2824_0 *)effect)->unk_04 = (u16) ((S_800C2824_0 *)effect)->unk_04 + 1;
        return;
    case RETURN_SACRIFICE_RELEASE_ACTOR:
        linked_object = detach_record_and_update_slot_state(((S_800C2824_0 *)effect)->unk_00);
        if (linked_object != 0) {
            object_slot = release_entity_slot_and_update_flags(linked_object, 0);
            if (object_slot < 0x40) {
                slots_page = (u8 *)0x80010000;
                ((S_800C2824_5 *)(slots_page + (object_slot * 0x54)))->unk_A93 = 0;
                ((s32 *)0x80010980)[object_slot] = 0;
            }
        }
        if ((get_entity_effect_value(((S_800C2824_0 *)effect)->unk_00, STATUS_NO_TILE_OCCUPANCY) << 0x10) == 0) {
            release_object = ((S_800C2824_0 *)effect)->unk_00;
            release_status = ((S_800C2824_6 *)release_object)->unk_1C;
            release_coord = (u32)((ObjectNodeHeader *)((u8 *)release_object - 0x20))->sprite;
            release_status &= 0x2000;
            release_x = ((MovingTile *)((void *)release_coord))->tile_x;
            release_coord = ((MovingTile *)((void *)release_coord))->tile_y;
            release_flags = 0x3000;
            if (release_status) {
                release_flags = 0x300;
            }
            update_map_cell_flags_with_item_limit(release_x, release_coord, release_flags);
        }
        unlink_entity_node(((S_800C2824_0 *)effect)->unk_00);
        adjust_source_value_and_finalize(((S_800C2824_0 *)effect)->unk_00, D_800E1640);
        ((S_800C2824_0 *)effect)->unk_04 = (u16) ((S_800C2824_0 *)effect)->unk_04 + 1;
        return;
    case RETURN_SACRIFICE_PLAYER_EFFECT:
    {

        object_coords = ((u8 *)(&reference_tile_object));
        effect_object = dungeon_actor_ring_anchor;
        return_magic_effect_object = effect_object;
        if (create_five_point_effect(object_coords->tile_x, object_coords->tile_y,
            ((S_800C2824_8 *)effect_object)->unk_88, &D_800DF45C, 0x2800, 0x208020, &return_magic_begin_address) == 0) {
            return;
        }
        flags_page = (u8 *)0x80080000;
        marked_object = ((S_800C2824_0 *)effect)->unk_00;
        ((ObjectNodeHeader *)((u8 *)marked_object - 0x20))->flags = (u16) (((ObjectNodeHeader *)((u8 *)marked_object - 0x20))->flags
            | NODE_REMOVE);
        effect_flags = ((S_800C2824_10 *)flags_page)->unk_14A0;
        effect_flags |= 0x8000;
        ((S_800C2824_10 *)flags_page)->unk_14A0 = effect_flags;
        (*(u16 *)((u8 *)effect + -2)) = (u16) ((*(u16 *)((u8 *)effect + -2)) | 0x8000);
        ((S_800C2824_10 *)flags_page)->unk_14A0 = effect_flags;
        return;
    }
    case RETURN_SACRIFICE_ACTOR_EFFECT:
        source_object = ((S_800C2824_0 *)effect)->unk_00;
        object_coords = (((ObjectNodeHeader *)((u8 *)source_object - 0x20))->sprite);
        effect_object = source_object;
        effect_param = ((S_800C2824_8 *)effect_object)->unk_88;
        return_magic_effect_object = effect_object;
        if (create_five_point_effect(object_coords->tile_x, object_coords->tile_y,
            effect_param, &D_800DF45C, 0x2800, 0x208020, &D_800C27F0) == 0) {
            return;
        }
        ((S_800C2824_0 *)effect)->unk_06 = 0x3C;
        ((S_800C2824_0 *)effect)->unk_04 = (u16) ((S_800C2824_0 *)effect)->unk_04 + 1;
        return;
    case RETURN_SACRIFICE_WAIT_EFFECT:
        wait_ticks = (u16) ((S_800C2824_0 *)effect)->unk_06 - 1;
        ((S_800C2824_0 *)effect)->unk_06 = wait_ticks;
        if ((wait_ticks << 0x10) > 0) {
            return;
        }
        detach_record_and_update_slot_state(((S_800C2824_0 *)effect)->unk_00);
        if ((get_entity_effect_value(((S_800C2824_0 *)effect)->unk_00, STATUS_NO_TILE_OCCUPANCY) << 0x10) != 0) {
            unlink_entity_node(((S_800C2824_0 *)effect)->unk_00);
            finished_object = ((S_800C2824_0 *)effect)->unk_00;
            (*(u16 *)((u8 *)finished_object + -2)) = (u16) (((ObjectNodeHeader *)((u8 *)finished_object - 0x20))->flags | NODE_REMOVE);
            final_object = return_magic_fade_object;
            flags_page = (u8 *)0x80080000;
            effect_flags = ((S_800C2824_10 *)flags_page)->unk_14A0;
        } else {
            expired_object = ((S_800C2824_0 *)effect)->unk_00;
            expired_status = ((S_800C2824_12 *)expired_object)->unk_1C;
            expired_coord = (u32)((ObjectNodeHeader *)((u8 *)expired_object - 0x20))->sprite;
            expired_status &= 0x2000;
            expired_x = ((MovingTile *)((void *)expired_coord))->tile_x;
            expired_coord = ((MovingTile *)((void *)expired_coord))->tile_y;
            tile_flags = 0x3000;
            if (expired_status) {
                tile_flags = 0x300;
            }
            update_map_cell_flags_with_item_limit(expired_x, expired_coord, tile_flags);
            unlink_entity_node(((S_800C2824_0 *)effect)->unk_00);
            finished_object = ((S_800C2824_0 *)effect)->unk_00;
            (*(u16 *)((u8 *)finished_object + -2)) = (u16) (((ObjectNodeHeader *)((u8 *)finished_object - 0x20))->flags | NODE_REMOVE);
            final_object = return_magic_fade_object;
            flags_page = (u8 *)0x80080000;
            effect_flags = ((S_800C2824_10 *)flags_page)->unk_14A0;
        }
        ;
        final_flags = final_object->flags;
        effect_flags |= 0x8000;
        ((S_800C2824_10 *)flags_page)->unk_14A0 = effect_flags;
        final_object->flags = (u16)(final_flags | 0x8000);
        (*(u16 *)((u8 *)effect + -2)) = (u16) ((*(u16 *)((u8 *)effect + -2)) | 0x8000);
        ((S_800C2824_10 *)flags_page)->unk_14A0 = effect_flags;
        return;
    default:
        return;
    }
}
