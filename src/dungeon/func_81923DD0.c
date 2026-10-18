#include "common.h"
#include "shared/object_node.h"
/* Selector-image function at DUNGEON file [0x1943DD0, 0x1944338), true 0x800255D0
 * (rowbase img_1942998_80024198 delta 0x7E6E1800 continued).  Five-state handler:
 * spawn a directional effect object, follow it, then print the result message and
 * finish.  Reconstruction from r121_remnants continuation 5 (v8); the message
 * builder uses the engine's cursor idiom (message_end / message_start, as in
 * src/dungeon/func_800BB400.c and func_800940E4.c).  Evidence:
 * docs/evidence/r121_rem_opus.md. */
extern void func_8003DB94(void *, void *, short);
extern void * func_8003FD64(s32, void *);
extern s32 func_8004491C(void *, s32);
extern void func_80047784(void *, s16, s16);
extern void * get_unused_text_buffer(void);
extern void * expand_text_control_codes(void *, void *);
extern void * func_80099290(void *);
extern u8 *append_entity_display_text(void *, u8 *);
extern s16 set_or_clear_actor_status_slot(void *, s8, s8);
extern s32 display_text_with_fullwidth_adjustment(s8 *);
extern s32 generate_random_value(void);
typedef struct { s32 w[12]; } Packet48;
typedef struct { s16 x; u16 y; } DirectionPair;
typedef struct { DirectionPair v[8]; } DirectionTable;
extern DirectionTable D_80024004;
extern u8 D_80024024[];
extern u8 D_80024E5C[];
extern u8 D_80025B40[];
extern s16 D_80025B60;
extern u8 D_80045340[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
#include "shared/object_flags.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
extern u8 D_800DEC00[];

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

void process_resolved_item_value(void *effect_state, void *motion, void *sprite) {
    DirectionTable directions;
    s16 phase;
    s32 done_flag;
    u16 direction;
    s32 source_packet_end;
    u16 next_frame;
    u16 frame;
    void *spawn_state;
    void *owner_sprite;
    void *owner_motion;
    void *spawn_sprite;
    void *owner;
    void *source_sprite;
    void *owner_header;
    void *spawned;
    void *spawn_motion;
    void *follow_motion;
    void *packet_source;
    void *packet_destination;

    owner = (((ResolvedEffect *)effect_state)->owner);
    directions = D_80024004;
    phase = (((ResolvedEffect *)effect_state)->phase);
    owner_header = owner - 0x20;
    owner_motion = (((ObjectNodeHeader *)owner_header)->unk_08);
    source_sprite = (((ObjectNodeHeader *)owner_header)->unk_0C);
    switch (phase) {
    case 0:
        (((ResolvedSprite *)sprite)->color) = 0x808080;
        (((ResolvedSprite *)sprite)->scale_y) = 0x1000;
        (((ResolvedSprite *)sprite)->scale_x) = 0x1000;
        func_8003DB94(sprite, ((u32)D_800DEC00), 0);
        direction = (((ResolvedActor *)owner)->facing);
        D_80025B60 = 1;
        (((ResolvedEffect *)effect_state)->direction) = (direction >> 9) & 7;
        (((ResolvedEffect *)effect_state)->phase) = (s16) ((u16) (((ResolvedEffect *)effect_state)->phase) + 1);
        /* fallthrough */
    case 1:
        (((ResolvedMotion *)motion)->axes[0].half.whole) = (u16) (((ResolvedMotion *)owner_motion)->axes[0].half.whole);
        (((ResolvedMotion *)motion)->axes[1].half.whole) = (u16) (((ResolvedMotion *)owner_motion)->axes[1].half.whole);
        (((ResolvedMotion *)motion)->axes[2].half.whole) = (u16) (((ResolvedMotion *)owner_motion)->axes[2].half.whole);
        if (*(((ResolvedEffect *)effect_state)->animation_flags) & 0x80) {
            (((ResolvedEffect *)effect_state)->frame) = 0U;
            (((ResolvedEffect *)effect_state)->phase) = (u16) (((ResolvedEffect *)effect_state)->phase) + 1;
            return;
        }
    default:
        return;
    case 2:
        spawned = func_8003FD64(0x112, ((u32)&D_80083498));
        if (spawned != 0) {
            spawn_state = spawned + 0x20;
            (((ResolvedSpawn *)spawn_state)->velocity_x) = (s32) (directions.v[(((ResolvedEffect *)effect_state)->direction)].x << 0x10);
            (((ResolvedSpawn *)spawn_state)->velocity_y) = (s32) (directions.v[(((ResolvedEffect *)effect_state)->direction)].y << 0x10);
            (((ResolvedSpawn *)spawn_state)->phase) = 0;
            (((ResolvedSpawn *)spawn_state)->owner) = owner;
            (((ResolvedSpawn *)spawn_state)->target) = (s32) (((ResolvedActor *)owner)->target);
            (((ResolvedSpawn *)spawn_state)->controller) = effect_state;
            (((ResolvedSpawn *)spawn_state)->kind) = (u8) (((ResolvedEffect *)effect_state)->kind);
            (((ResolvedSpawn *)spawn_state)->direction) = (u16) (((ResolvedEffect *)effect_state)->direction);
            owner_sprite = (((ObjectNodeHeader *)(owner))[-1].unk_0C);
            (((ResolvedEffect *)effect_state)->tile_x) = (s8) ((((ResolvedSprite *)owner_sprite)->tile_x) + D_8006CCD8[((((ResolvedEffect *)effect_state)->direction) * 2)]);
            (((ResolvedEffect *)effect_state)->tile_y) = (s8) ((((ResolvedSprite *)owner_sprite)->tile_y) + D_8006CCE8[((((ResolvedEffect *)effect_state)->direction) * 2)]);
            if ((((ResolvedActor *)owner)->target) != 0) {
                (((ResolvedSpawn *)spawn_state)->target_x) = (s16) (s8) (((ResolvedActor *)owner)->tile_x);
                (((ResolvedSpawn *)spawn_state)->target_y) = (s16) (s8) (((ResolvedActor *)owner)->tile_y);
                (((ResolvedSpawn *)spawn_state)->origin_x) = (s16) (((ResolvedSprite *)owner_sprite)->tile_x);
                (((ResolvedSpawn *)spawn_state)->origin_y) = (s16) (((ResolvedSprite *)owner_sprite)->tile_y);
                (((ResolvedSpawn *)spawn_state)->has_target) = 1;
                (((ResolvedSpawn *)spawn_state)->timer) = 0;
                set_or_clear_actor_status_slot((((ResolvedActor *)owner)->target), 0x1D, (s8) (((u8) (((ResolvedEffect *)effect_state)->kind) >> 2) + 3 + (generate_random_value() & 3)));
                packet_source = source_sprite;
            } else {
                (((ResolvedSpawn *)spawn_state)->range) = 0x20;
                (((ResolvedSpawn *)spawn_state)->timer) = 0;
                (((ResolvedSpawn *)spawn_state)->has_target) = 0;
                packet_source = source_sprite;
            }
            source_packet_end = packet_source + 0x30;
            (((ResolvedEffect *)effect_state)->complete) = 0;
            spawn_sprite = (((ObjectNodeHeader *)spawned)->unk_0C);
            packet_destination = spawn_sprite;
            (((ResolvedSpriteColor *)spawn_sprite)->blue) = 0x80;
            (((ResolvedSpriteColor *)spawn_sprite)->green) = 0x80;
            (((ResolvedSpriteColor *)spawn_sprite)->red) = 0x80;
            (((ResolvedSprite *)spawn_sprite)->scale_y) = 0x1000;
            (((ResolvedSprite *)spawn_sprite)->scale_x) = 0x1000;
            *(Packet48 *)spawn_sprite = *(Packet48 *)source_sprite;
            (((ResolvedSprite *)spawn_sprite)->mode) = 0x20;
            (((ResolvedSprite *)spawn_sprite)->flags) = (u16) ((((ResolvedSprite *)spawn_sprite)->flags) | 0xC);
            (((ObjectNodeHeader *)spawned)->unk_10) = ((u32)D_80024E5C);
            func_8004491C(spawned, ((u32)D_80045340));
            (((ResolvedSprite *)spawn_sprite)->script) = ((u32)D_80025B40);
            func_80047784(spawn_sprite, D_80025B40[(((s32) (g_game_work.view.viewAngle + (s16) (((ResolvedActor *)owner)->facing) + 0x100) >> 9) & 7)], 0);
            spawn_motion = (((ObjectNodeHeader *)spawned)->unk_08);
            (((ResolvedMotion *)spawn_motion)->axes[0].fixed) = (s32) (((ResolvedMotion *)motion)->axes[0].fixed);
            (((ResolvedMotion *)spawn_motion)->axes[1].fixed) = (s32) (((ResolvedMotion *)motion)->axes[1].fixed);
            (((ResolvedMotion *)spawn_motion)->axes[2].fixed) = (s32) (((ResolvedMotion *)motion)->axes[2].fixed);
            (((ResolvedEffect *)effect_state)->spawned) = spawned;
            (((ResolvedEffect *)effect_state)->motion) = spawn_motion;
            (((ResolvedEffect *)effect_state)->value) = 0x63;
        }
        (((ResolvedEffect *)effect_state)->phase) = (s16) ((u16) (((ResolvedEffect *)effect_state)->phase) + 1);
        return;
    case 3:
        if ((((ResolvedEffect *)effect_state)->value) == 0x63) {
            spawned = (((ResolvedEffect *)effect_state)->spawned);
            follow_motion = (((ResolvedEffect *)effect_state)->motion);
            if ((((ObjectNodeHeader *)spawned)->flags) & 0x8000) {
                (((ResolvedEffect *)effect_state)->value) = 0;
            } else {
                (((ResolvedMotion *)motion)->axes[0].fixed) = (s32) (((ResolvedMotion *)follow_motion)->axes[0].fixed);
                (((ResolvedMotion *)motion)->axes[1].fixed) = (s32) (((ResolvedMotion *)follow_motion)->axes[1].fixed);
                (((ResolvedMotion *)motion)->axes[2].fixed) = (s32) (((ResolvedMotion *)follow_motion)->axes[2].fixed);
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
                    func_80099290(message_end);
                    display_text_with_fullwidth_adjustment((s8 *)message_start);
                }
                return;
            }
        }
        break;
    case 4:
        frame = (((ResolvedEffect *)effect_state)->frame);
        next_frame = frame + 1;
        (((ResolvedEffect *)effect_state)->frame) = next_frame;
        if ((s16) next_frame >= 0xB) {
            done_flag = D_80025B60;
            (((ResolvedEffect *)effect_state)->frame) = frame;
            if (done_flag == 0) {
                g_dungeon_status.unk_0C = 0;
                (((ObjectNodeHeader *)(effect_state))[-1].flags) = (u16) ((((ObjectNodeHeader *)(effect_state))[-1].flags) | 0x8000);
                object_flag_block.flags |= 0x8000;
                return;
            }
            D_80025B60 = 0;
        }
        break;
    }
}
