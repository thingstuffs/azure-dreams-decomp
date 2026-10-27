#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "engine/graphics.h"

extern void func_80042518(void *slots, s32 type);
extern s32 get_entity_effect_value(void *entry, s32 effect_id);
extern void clear_slots_of_type(void *owner, s32 match_type);

/* Initializes actor state and selects a display variant for its facing direction. */
void begin_actor_display_action(void *actor, void *unused, SpriteFrameState *display, u8 *facing_variants) {
    *((u8 *) actor + 0x9A) = 8;
    *((u8 *) actor + 0x9B) = 0;
    *(s32 *) ((u8 *) actor + 0x8C) = 0;
    display->frameTable = facing_variants;
    if (facing_variants != 0) {
        select_sprite_entry(display, facing_variants[(s32) (g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *) ((u8 *) actor + 0x2A) + 0x100)
            >> 9 & 7], 0);
    }
    *(s32 *) ((u8 *) actor + 0x1C) = *(s32 *) ((u8 *) actor + 0x1C) | 0x04000000;
    clear_slots_of_type(actor, STATUS_PARALYSIS);
    if ((get_entity_effect_value(actor, STATUS_FROG) << 0x10) != 0) {
        *((u8 *) actor + 0x13) = *((u8 *) actor + 0xA8);
        func_80042518(actor, 0xA);
    }
    *(s16 *) ((u8 *) actor + 0x96) = 0x40;
}
