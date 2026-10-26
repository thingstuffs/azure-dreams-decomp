#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "dungeon/actor.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/actor/animation.h"

typedef struct S_800A4B88_0_pre {
    s32 unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_800A4B88_0_pre;   /* the 0x18 bytes before arg0 in apply_entity_action_flags, addressed as arg0[-1] */





/* cfail-repair: tf7-phase1-cache-v3 */
void select_record_entry_and_value(void *state, void *entries, short index);     /* extern */
extern void func_8003E188(s32 field_index, s32 flag);            /* extern */
void apply_entity_effects(); /* Slot contract: loading images do not establish one callee contract. */                      /* extern */
void restore_player_control_callback(void *target, void *source);              /* extern */
void cycle_map_cell_flags(s16 x, s16 y, u16 flags);             /* extern */
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);             /* extern */
 /* extern */
extern s32 sprite_resource_pointer_slots[];
extern u8 actor_default_frames[];

/* Applies an action to the object's flags and tile state, then updates the object. */
void apply_entity_action_flags(void *object, s32 action) {
    s32 clear_mask;
    s32 enable_clear_mask;
    s32 set_mask;
    s32 disable_clear_mask;
    s32 action_index;
    s32 *reset_slot;
    s32 updated_flags;
    s32 reset_index;
    TileObject *update_state;
    u8 tile_x;
    u8 tile_y;
    void *position;

    action_index = (s16) (action - 1);
    switch (action_index) {
    case STATUS_SLEEP - 1:
        ((ActorRecord *)object)->flags1C = (s32) (((ActorRecord *)object)->flags1C | ACTOR_ASLEEP);
        break;
    case STATUS_CONFUSION - 1:
        ((ActorRecord *)object)->flags1C = (s32) (((ActorRecord *)object)->flags1C | ACTOR_CONFUSED);
        break;
    case STATUS_BLIND - 1:
        ((ActorRecord *)object)->flags1C = (s32) ((((ActorRecord *)object)->flags1C & ACTOR_PLAYER_AWARE_CLEAR_MASK) | 0x10);
        break;
    case STATUS_PARALYSIS - 1:
        ((ActorRecord *)object)->flags1C = (s32) (((ActorRecord *)object)->flags1C | ACTOR_PARALYZED);
        break;
    case STATUS_POISON - 1:
        ((ActorRecord *)object)->flags1C = (s32) (((ActorRecord *)object)->flags1C | ACTOR_POISONED);
        break;
    case STATUS_MAGIC_BIND - 1:
        ((ActorRecord *)object)->flags1C = (s32) (((ActorRecord *)object)->flags1C | ACTOR_MAGIC_BOUND);
        break;
    case STATUS_CURSE - 1:
        ((ActorRecord *)object)->flags1C = (s32) (((ActorRecord *)object)->flags1C | ACTOR_CURSED);
        break;
    case STATUS_ANGER - 1:
        ((ActorRecord *)object)->flags1C = (s32) (((ActorRecord *)object)->flags1C | ACTOR_ANGRY);
        break;
    case STATUS_NO_TILE_OCCUPANCY - 1:
        position = ((S_800A4B88_0_pre *)object)[-1].unk_04;
        tile_x = ((MovingTile *)position)->tile_x;
        tile_y = ((MovingTile *)position)->tile_y;
        clear_mask = 0x3000;
        if (((ActorRecord *)object)->flags1C & ACTOR_PLAYER_SIDE) {
            clear_mask = 0x300;
        }
        update_map_cell_flags_with_item_limit(tile_x, tile_y, clear_mask);
        break;
    case STATUS_PLAYER_SIDE - 1:
        position = ((S_800A4B88_0_pre *)object)[-1].unk_04;
        tile_x = ((MovingTile *)position)->tile_x;
        tile_y = ((MovingTile *)position)->tile_y;
        enable_clear_mask = 0x3000;
        if (((ActorRecord *)object)->flags1C & ACTOR_PLAYER_SIDE) {
            enable_clear_mask = 0x300;
        }
        update_map_cell_flags_with_item_limit(tile_x, tile_y, enable_clear_mask);
        updated_flags = ((ActorRecord *)object)->flags1C | ACTOR_PLAYER_SIDE;
        ((ActorRecord *)object)->flags1C = updated_flags;
        tile_x = ((MovingTile *)position)->tile_x;
        tile_y = ((MovingTile *)position)->tile_y;
        set_mask = 0x3000;
        if (updated_flags & ACTOR_PLAYER_SIDE) {
            set_mask = 0x300;
        }
        cycle_map_cell_flags(tile_x, tile_y, set_mask);
        break;
    case STATUS_BRAINWASH - 1:
        position = ((S_800A4B88_0_pre *)object)[-1].unk_04;
        tile_x = ((MovingTile *)position)->tile_x;
        tile_y = ((MovingTile *)position)->tile_y;
        disable_clear_mask = 0x3000;
        if (((ActorRecord *)object)->flags1C & ACTOR_PLAYER_SIDE) {
            disable_clear_mask = 0x300;
        }
        update_map_cell_flags_with_item_limit(tile_x, tile_y, disable_clear_mask);
        ((ActorRecord *)object)->flags1C = (s32) (((ActorRecord *)object)->flags1C & ~ACTOR_PLAYER_SIDE);
        tile_x = ((MovingTile *)position)->tile_x;
        tile_y = ((MovingTile *)position)->tile_y;
        set_mask = 0x3000;
        cycle_map_cell_flags(tile_x, tile_y, set_mask);
        break;
    case STATUS_FROG - 1:
        func_8003E188(0x2E, 0);
        if (((ActorRecord *)object)->flags14 & 0x20000000) {
            begin_actor_flagged_action(object, ((S_800A4B88_0_pre *)object)[-1].unk_00, ((S_800A4B88_0_pre *)object)[-1].unk_04,
                object);
            return;
        }
        reset_actor_animation_state(object);
        if (((ActorRecord *)object)->species != 0) {
            break;
        }
        restore_player_control_callback(object, object);
        update_state = &reference_tile_object;
        update_state->frame_table = actor_default_frames;
        select_record_entry_and_value(update_state, *(void **)(actor_default_frames + ((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + (((ActorRecord *)object)->facing) + 0x100) >> 7) & 0x1C))), 0);
        reset_index = 3;
        reset_slot = sprite_resource_pointer_slots;
        reset_slot += 3;
        do {
            *reset_slot = 0;
            reset_index -= 1;
            reset_slot -= 1;
        } while (reset_index >= 0);
    }
    apply_entity_effects(object);
    return;
}
