#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/monster/golem.h"
#include "dungeon/actor/status.h"

extern s32 try_claim_dungeon_action_slot(void *);
extern void apply_camera_offset_and_select_target(void *,void *, s32, s32);
extern void select_sprite_entry(void *, u8, s32);

extern u8 D_80175F30[];

/* Initialize the entity's action state and directional animation when allowed. */
s32 initialize_directional_animation_action(void *state_ptr, void *action_arg, void *sprite_ptr, void *entity_ptr) {
    u8 *state = state_ptr;
    SpriteFrameState *sprite= sprite_ptr;
    u8 *entity = entity_ptr;

    entity[0x71] &= 0x7F;
    if (!(g_dungeon_status.flags & 0x2000)) {
        if ((*(u16 *)(entity + 0x46) & 0x8000) || !(g_dungeon_status.flags & 8)) {
            if ((try_claim_dungeon_action_slot(entity) << 16) == 0) {
                apply_camera_offset_and_select_target(entity - 0x20, action_arg, 8, 0x300);
                if ((try_claim_dungeon_action_slot(entity) << 16) == 0) {
                    state[0x9A] = 0x18;
                    state[0x9B] = 0;
                    *(s32 *)(state + 0x8C) = 0;
                    sprite->frameTable = D_80175F30;
                    select_sprite_entry(sprite, D_80175F30[((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)(entity + 0x2A) + 0x100)
                        >> 9) & 7], 0);
                    advance_status_timers(entity);
                    entity[0x6D]--;
                    return 0;
                }
            }
        }
    }
    return -1;
}
