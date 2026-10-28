#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "engine/node/allocation.h"
#include "engine/node.h"

typedef struct ActionState ActionState;
typedef struct ActorMotion ActorMotion;
typedef struct ActorSprite ActorSprite;
typedef struct CreatureState CreatureState;

typedef struct S_80FD5000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x6C];
    ActorActionHandler unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x11];
    s16 unk_AE;
} S_80FD5000_1;

typedef struct S_80FD5000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80FD5000_2;

typedef struct S_80FD5000_4 {
    u8 unk_00;
    u8 pad_01[0x5];
    u16 unk_06;
} S_80FD5000_4;

s32 MoveImage(void *, s32, s32);
s16 set_or_clear_actor_status_slot(); /* extern */
s32 generate_random_value(void);
extern M2C_UNK D_8014CB40;
void update_creature_action_and_animation(ActorRecord *self_object, ObjectPosition *aux_entity, SpriteFrameState *sprite, ActorRecord *entity);
extern M2C_UNK D_80151258;
extern M2C_UNK D_80151298;

typedef void (*Callback)(void);
typedef struct {
    Callback callbacks[27];
    u8 config[56];
} ActorDefinition;

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect;

/* Creates a monster actor and initializes its state, placement, and palette. */
/* Creates Mandara with frames at D_80151258, copies its palette row and four strips, and attempts tile
 * placement. */
void *spawn_mandara_slot_a(s16 spawn_flags, s16 tile_x, s16 tile_y, s32 heading)
{
    s32 kind;
    S_80FD5000_1 *actor_state;
    ObjectNodeHeader *created;
    ObjectPosition *position;
    SpriteFrameState *monster;
    S_80FD5000_1 *actor;
    Rect palette_strip;
    s32 appearance_id;
    s32 palette_y;
    S_80FD5000_4 *entry;
    s32 entry_index;
    s32 twice_index;
    Rect *palette_rect;
    S_80FD5000_4 *selected;
    S_80FD5000_4 *selected2;
    S_80FD5000_4 *selected3;

    actor_state = 0;
    created = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (created != 0) {
        actor_state = (S_80FD5000_1 *)((u8 *)created + 0x20);
        created->update_callback = &D_8014CB40;
        actor_state->unk_13 = MONSTER_MANDARA;
        register_node(created, project_sprite_chain);

        position = created->position;
        position->z.w.i = heading;
        monster = created->sprite;
        kind = spawn_flags & 3;
        monster->tile_y = tile_y;
        actor = actor_state;
        monster->frameTable = &D_80151258;
        monster->tile_x = tile_x;

        if (kind == 1) {
            actor_state->unk_14 |= (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            actor_state->unk_1C |= (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
        } else if (kind >= 2) {
            actor_state->unk_14 |= ACTOR_CLASS_ENABLED;
            actor_state->unk_1C |= ACTOR_PLAYER_SIDE;
        } else if (((spawn_flags & -4) << 16) == 0) {
            if ((actor_state->unk_14 & ACTOR_RESIST_SLEEP) == 0) {
                if ((generate_random_value() & 1) != 0) {
                    actor_state->unk_1C |= ACTOR_ASLEEP;
                    set_or_clear_actor_status_slot(actor_state, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
                    monster->frameTable = &D_80151298;
                }
            }
        }

        initialize_actor_sprite_and_animation(created, position, monster, spawn_flags);

        entry_index = 0;
        appearance_id = monster->clut;
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &update_creature_action_and_animation;
        actor->unk_AE = appearance_id;

        entry = monster->source;
        while (1) {
            twice_index = entry_index << 1;
            if (!(entry->unk_00 & 0x20)) {
                break;
            }
            entry = (S_80FD5000_4 *)((u8 *)entry + 12);
            entry_index++;
        }

        palette_rect = &palette_strip;
        selected = (S_80FD5000_4 *)(twice_index + entry_index);
        selected2 = (S_80FD5000_4 *)((s32)selected * 4);
        selected3 = (S_80FD5000_4 *)((u8 *)selected2 + (s32)*(u8 * *)&monster->source);
        palette_y = selected3->unk_06 >> 6;
        palette_strip.x = 0;
        palette_strip.y = palette_y;
        palette_strip.w = 0x100;
        palette_strip.h = 1;
        MoveImage(palette_rect, 0, palette_y - 1);

        palette_strip.w = 0x10;
        palette_strip.x = 0x30;
        palette_strip.y--;
        do {
            MoveImage(&palette_strip, palette_strip.x - 0x30, palette_strip.y);
            palette_strip.x += 0x40;
        } while (palette_strip.x < 0x100);

        try_move_actor_to_valid_position(actor, position, monster, actor_state);
    }

    return actor_state;
}
