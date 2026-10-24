#include "shared/actor_status_ids.h"
/* Directional item effects, moving sprite copies, and target completion messages. */
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
/* Selector-image function at DUNGEON file [0x1943DD0, 0x1944338), true 0x800255D0
 * (rowbase img_1942998_80024198 delta 0x7E6E1800 continued).  Five-state handler:
 * spawn a directional effect object, follow it, then print the result message and
 * finish.  Reconstruction from r121_remnants continuation 5 (v8); the message
 * builder uses the engine's cursor idiom (message_end / message_start, as in
 * src/dungeon/func_800BB400.c and func_800940E4.c).  Evidence:
 * docs/evidence/r121_rem_opus.md. */
extern void select_record_entry_and_value(void *, void *, short);
extern void * allocate_list_node(s32, void *);
extern s32 register_node(void *, void *);
extern void select_sprite_entry(void *, s16, s16);
extern void * get_unused_text_buffer(void);
extern void * expand_text_control_codes(void *, void *);
extern void * clear_byte_and_advance(void *);
extern u8 *append_entity_display_text(void *, u8 *);
extern s16 set_or_clear_actor_status_slot(void *, s8, s8);
extern s32 display_text_with_fullwidth_adjustment(s8 *);
extern s32 generate_random_value(void);
typedef struct { s32 w[12]; } Packet48;
typedef struct { s16 x; u16 y; } DirectionPair;
typedef struct { DirectionPair v[8]; } DirectionTable;
extern DirectionTable resolved_item_direction_table;
extern u8 D_80024024[];
extern u8 D_80024E5C[];
extern u8 D_80025B40[];
extern s16 shaded_effect_update_flag;
extern u8 sprite_chain_projector_address[];
extern u8 dir_step_x[];
extern u8 dir_step_y[];
#include "shared/object_flags.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
extern u8 directional_sprite_entries[];

typedef struct {
    void * owner;
    u16 * animation_flags;
    u8 reserved_08[0x1];
    u8 kind;
    s16 phase;
    u8 reserved_0c[0x72];
    s16 direction;
    u8 reserved_80[0x4];
    u16 frame;
    s16 complete;
    s16 value;
    u8 reserved_8a[0x16];
    s8 tile_x;
    s8 tile_y;
    u8 reserved_a2[0x6];
    void * spawned;
    void * motion;
} ResolvedEffect;
typedef struct {
    u8 reserved_00[0x8];
    void * packet;
    s32 color;
    s16 mode;
    u8 reserved_12[0x2];
    u16 flags;
    u8 reserved_16[0x6];
    s16 scale_x;
    s16 scale_y;
    u8 reserved_20[0x4];
    u8 tile_x;
    u8 tile_y;
    u8 reserved_26[0x6];
    s32 script;
} ResolvedSprite;
typedef struct {
    u8 reserved_00[0x2A];
    u16 facing;
    u8 reserved_2c[0x34];
    s32 target;
    u8 reserved_64[0xE];
    u8 tile_x;
    u8 tile_y;
} ResolvedActor;
typedef struct {
    u8 reserved_00[0x58];
    s16 phase;
    s16 timer;
    s16 range;
    u8 reserved_5e[0x2];
    s16 has_target;
    u8 reserved_62[0x8];
    u8 kind;
    u8 reserved_6b[0x1];
    u16 direction;
    u8 reserved_6e[0x16];
    void * owner;
    s32 target;
    void * controller;
    s16 target_x;
    s16 target_y;
    s16 origin_x;
    s16 origin_y;
    s32 velocity_x;
    s32 velocity_y;
} ResolvedSpawn;
typedef struct {
    u8 reserved_00[12];
    u8 red, green, blue;
} ResolvedSpriteColor;
typedef union {
    s32 fixed;
    struct { u16 fraction, whole; } half;
} ResolvedCoordinate;
typedef struct { ResolvedCoordinate axes[3]; } ResolvedMotion;

enum ResolvedEffectPhase {
    RESOLVED_EFFECT_INIT = 0,
    RESOLVED_EFFECT_FOLLOW_OWNER = 1,
    RESOLVED_EFFECT_SPAWN_COPY = 2,
    RESOLVED_EFFECT_FOLLOW_COPY = 3,
    RESOLVED_EFFECT_WAIT_SPRITES = 4,
};

/* Creates and follows a directional sprite copy, sets target status slot 29, and displays its
   completion message. */
void process_resolved_item_value(ObjectNodeHeader *effect_state, void *motion, void *sprite) {
    DirectionTable directions;
    s16 phase;
    s32 done_flag;
    u16 direction;
    s32 source_packet_end;
    u16 next_frame;
    u16 frame;
    void *spawn_state;
    void *owner_sprite;
    ObjectPosition *owner_motion;
    SpriteFrameState *spawn_sprite;
    void *owner;
    void *source_sprite;
    ObjectNodeHeader *owner_header;
    ObjectNodeHeader *spawned;
    ObjectPosition *spawn_motion;
    ObjectPosition *follow_motion;
    void *packet_source;
    void *packet_destination;

    owner = (effect_state->next);
    directions = resolved_item_direction_table;
    phase = (((ResolvedEffect *)effect_state)->phase);
    owner_header = owner - 0x20;
    owner_motion = (owner_header->position);
    source_sprite = (owner_header->sprite);
    switch (phase) {
    case RESOLVED_EFFECT_INIT:
        (((ResolvedSprite *)sprite)->color) = 0x808080;
        (((ResolvedSprite *)sprite)->scale_y) = 0x1000;
        (((ResolvedSprite *)sprite)->scale_x) = 0x1000;
        select_record_entry_and_value(sprite, ((u32)directional_sprite_entries), 0);
        direction = (((ResolvedActor *)owner)->facing);
        shaded_effect_update_flag = 1;
        (((ResolvedEffect *)effect_state)->direction) = (direction >> 9) & 7;
        (((ResolvedEffect *)effect_state)->phase) = (s16) ((u16) (((ResolvedEffect *)effect_state)->phase) + 1);
        /* fallthrough */
    case RESOLVED_EFFECT_FOLLOW_OWNER:
        (((ResolvedMotion *)motion)->axes[0].half.whole) = (u16) (*(u16 *)&owner_motion->x.w.i);
        (((ResolvedMotion *)motion)->axes[1].half.whole) = (u16) (*(u16 *)&owner_motion->y.w.i);
        (((ResolvedMotion *)motion)->axes[2].half.whole) = (u16) (*(u16 *)&owner_motion->z.w.i);
        if (*(*(u16 * *)&effect_state->pprev) & 0x80) {
            (((ResolvedEffect *)effect_state)->frame) = 0U;
            (((ResolvedEffect *)effect_state)->phase) = (u16) (((ResolvedEffect *)effect_state)->phase) + 1;
            return;
        }
    default:
        return;
    case RESOLVED_EFFECT_SPAWN_COPY:
        spawned = allocate_list_node(0x112, ((u32)&scene_object_list_anchor));
        if (spawned != 0) {
            spawn_state = ((void *)spawned) + 0x20;
            (((ResolvedSpawn *)spawn_state)->velocity_x) = (s32) (directions.v[(((ResolvedEffect *)effect_state)->direction)].x << 0x10);
            (((ResolvedSpawn *)spawn_state)->velocity_y) = (s32) (directions.v[(((ResolvedEffect *)effect_state)->direction)].y << 0x10);
            (((ResolvedSpawn *)spawn_state)->phase) = 0;
            (((ResolvedSpawn *)spawn_state)->owner) = owner;
            (((ResolvedSpawn *)spawn_state)->target) = (s32) (((ResolvedActor *)owner)->target);
            (((ResolvedSpawn *)spawn_state)->controller) = effect_state;
            (((ResolvedSpawn *)spawn_state)->kind) = (u8) (((ResolvedEffect *)effect_state)->kind);
            (((ResolvedSpawn *)spawn_state)->direction) = (u16) (((ResolvedEffect *)effect_state)->direction);
            owner_sprite = (((ObjectNodeHeader *)(owner))[-1].sprite);
            (((ResolvedEffect *)effect_state)->tile_x) = (s8) ((((ResolvedSprite *)owner_sprite)->tile_x) + dir_step_x[((((ResolvedEffect *)effect_state)->direction) * 2)]);
            (((ResolvedEffect *)effect_state)->tile_y) = (s8) ((((ResolvedSprite *)owner_sprite)->tile_y) + dir_step_y[((((ResolvedEffect *)effect_state)->direction) * 2)]);
            if ((((ResolvedActor *)owner)->target) != 0) {
                (((ResolvedSpawn *)spawn_state)->target_x) = (s16) (s8) (((ResolvedActor *)owner)->tile_x);
                (((ResolvedSpawn *)spawn_state)->target_y) = (s16) (s8) (((ResolvedActor *)owner)->tile_y);
                (((ResolvedSpawn *)spawn_state)->origin_x) = (s16) (((ResolvedSprite *)owner_sprite)->tile_x);
                (((ResolvedSpawn *)spawn_state)->origin_y) = (s16) (((ResolvedSprite *)owner_sprite)->tile_y);
                (((ResolvedSpawn *)spawn_state)->has_target) = 1;
                (((ResolvedSpawn *)spawn_state)->timer) = 0;
                set_or_clear_actor_status_slot((((ResolvedActor *)owner)->target), STATUS_DAMAGE_GUARD, (s8) (((u8) (((ResolvedEffect *)effect_state)->kind) >> 2) + 3 + (generate_random_value() & 3)));
                packet_source = source_sprite;
            } else {
                (((ResolvedSpawn *)spawn_state)->range) = 0x20;
                (((ResolvedSpawn *)spawn_state)->timer) = 0;
                (((ResolvedSpawn *)spawn_state)->has_target) = 0;
                packet_source = source_sprite;
            }
            source_packet_end = packet_source + 0x30;
            (((ResolvedEffect *)effect_state)->complete) = 0;
            spawn_sprite = (spawned->sprite);
            packet_destination = spawn_sprite;
            spawn_sprite->color.c.b = 0x80;
            spawn_sprite->color.c.g = 0x80;
            spawn_sprite->color.c.r = 0x80;
            spawn_sprite->scale_y = 0x1000;
            spawn_sprite->scale_x = 0x1000;
            *(Packet48 *)spawn_sprite = *(Packet48 *)source_sprite;
            spawn_sprite->tpage_abr = 0x20;
            spawn_sprite->flags = (u16) (spawn_sprite->flags | 0xC);
            (spawned->update_callback) = ((u32)D_80024E5C);
            register_node(spawned, ((u32)sprite_chain_projector_address));
            spawn_sprite->frameTable = ((u32)D_80025B40);
            select_sprite_entry(spawn_sprite, D_80025B40[(((s32) (g_game_work.view.camera_rotation.parts.viewAngle + (s16) (((ResolvedActor *)owner)->facing) + 0x100) >> 9) & 7)], 0);
            spawn_motion = (spawned->position);
            (spawn_motion->x.v) = (s32) (((ResolvedMotion *)motion)->axes[0].fixed);
            (spawn_motion->y.v) = (s32) (((ResolvedMotion *)motion)->axes[1].fixed);
            (spawn_motion->z.v) = (s32) (((ResolvedMotion *)motion)->axes[2].fixed);
            (((ResolvedEffect *)effect_state)->spawned) = spawned;
            (((ResolvedEffect *)effect_state)->motion) = spawn_motion;
            (((ResolvedEffect *)effect_state)->value) = 0x63;
        }
        (((ResolvedEffect *)effect_state)->phase) = (s16) ((u16) (((ResolvedEffect *)effect_state)->phase) + 1);
        return;
    case RESOLVED_EFFECT_FOLLOW_COPY:
        if ((((ResolvedEffect *)effect_state)->value) == 0x63) {
            spawned = (((ResolvedEffect *)effect_state)->spawned);
            follow_motion = (((ResolvedEffect *)effect_state)->motion);
            if ((spawned->flags) & 0x8000) {
                (((ResolvedEffect *)effect_state)->value) = 0;
            } else {
                (((ResolvedMotion *)motion)->axes[0].fixed) = (s32) (follow_motion->x.v);
                (((ResolvedMotion *)motion)->axes[1].fixed) = (s32) (follow_motion->y.v);
                (((ResolvedMotion *)motion)->axes[2].fixed) = (s32) (follow_motion->z.v);
            }
        }
        if ((((ResolvedEffect *)effect_state)->complete) != 0) {
            (((ResolvedEffect *)effect_state)->frame) = 0U;
            (((ResolvedEffect *)effect_state)->phase) = (s16) ((u16) (((ResolvedEffect *)effect_state)->phase) + 1);
            if ((((ResolvedActor *)owner)->target) != 0) {
                {
                    u8 *message_end;
                    u8 *message_start;

                    message_end = get_unused_text_buffer();
                    message_start = message_end;
                    message_end = append_entity_display_text((((ResolvedActor *)owner)->target), message_end);
                    message_end = expand_text_control_codes(((u32)D_80024024), message_end);
                    clear_byte_and_advance(message_end);
                    display_text_with_fullwidth_adjustment((s8 *)message_start);
                }
                return;
            }
        }
        break;
    case RESOLVED_EFFECT_WAIT_SPRITES:
        frame = (((ResolvedEffect *)effect_state)->frame);
        next_frame = frame + 1;
        (((ResolvedEffect *)effect_state)->frame) = next_frame;
        if ((s16) next_frame >= 0xB) {
            done_flag = shaded_effect_update_flag;
            (((ResolvedEffect *)effect_state)->frame) = frame;
            if (done_flag == 0) {
                g_dungeon_status.active_actor = 0;
                ((effect_state)[-1].flags) = (u16) (((effect_state)[-1].flags) | 0x8000);
                object_flag_block.flags |= OBJECT_REMOVE_PENDING;
                return;
            }
            shaded_effect_update_flag = 0;
        }
        break;
    }
}
