#include "shared/sprite_frame_state.h"
#include "dungeon/monster/tyrant/advance_a_timed_actor_animation_applies_completion_effects.h"
#include "shared/sprite_frame_state.h"

/* Advances a timed actor animation and applies its completion effects. */
void advance_a_timed_actor_animation_applies_completion_effects(T_801727CC_Obj0 *action, s32 context, SpriteFrameState *sprite, T_801727CC_Obj3 *actor) {
    s16 ticks_left;
    s32 state;
    s32 volume;

    state = action->field9B;
    ticks_left = action->field96 - 1;
    action->field96 = ticks_left;
    switch (state) {
    case 0:
        if (sprite->flags & 0x8000) {
            action->field9B = 0xFF;
            sprite->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, actor->field2A, 1);
            return;
        }
        if (action->field98 & 0x8000) {
            sprite->frameTable = D_80174010;
            ticks_left = 10;
        } else {
            sprite->frameTable = D_80173FE8;
            ticks_left = 4;
        }
        action->field96 = ticks_left;
        select_sprite_entry(sprite, (*(u8 **)&sprite->frameTable)[(((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->field2A + 0x100) >> 9) & 7)],
            0);
        action->field9B++;
        return;
    case 1:
        if ((ticks_left << 16) > 0)
            return;
        play_sound_if_enabled(0x809);
        resolve_attack_damage_and_effects(actor, sprite, actor->field2A, 1);
        action->field9B = 0xFF;
        return;
    case 0xFF:
        if ((sprite->flags & 0xE000) == 0)
            return;
        set_record_integer_tile_center(context, sprite->unk_24, sprite->unk_25);
        volume = 0x100;
        if (action->field98 & 0x8000)
            volume = 0x800;
        spend_actor_mp(actor, volume);
        action->field8C = &update_dungeon_actor_behavior;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        if (actor->field6D == 0) {
            actor->field46 &= 0x7FFF;
            return;
        }
        *actor_update_node_cursor = (void *)((s8 *)actor - 0x20);

        return;
    default:
        return;
    }
}
