#include "shared/dungeon_actor_callbacks.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/game_work.h"
#include "dungeon/player.h"
#include "dungeon/actor/effect.h"
#include "engine/graphics.h"
#ifndef NULL
#define NULL 0
#endif

extern void play_sound_if_enabled(s32 a0);

extern u8 player_carry_frames[8];
extern s32 player_item_render_update_address;

/* Create an effect at the target and initialize its state and sound. */
void begin_player_pickup_animation(ActorRecord *actor, s32 effect_arg, u8 *target, ActorRecord *source) {
    u16 flags;
    s32 direction;
    ObjectNodeHeader *effect;
    ObjectPosition *transform;
    u8 *effect_state;
    s32 sound_id;

    actor->action_id.s = 0x23;
    actor->action_phase.s = 0;
    actor->unk_8C.address = NULL;

    flags = actor->unk_A0.parts.high;
    actor->unk_A0.parts.high = flags & 0xFF7F;

    *(u8 **)(target + 0x2C) = &player_carry_frames[0];

    direction = ((g_game_work.view.camera_rotation.parts.viewAngle + source->facing + 0x100) >> 9) & 7;
    set_sprite_animation_frame(target, player_carry_frames[direction], 0, 1);

    effect = create_item_render_object(((ObjectNodeHeader *)actor - 1), *(void **)(((u8 *)actor) + 0xBC), 0, 0, 0);
    *(void **)(((u8 *)actor) + 0x124) = effect;
    if (effect != NULL) {
        effect->update_callback = &player_item_render_update_address;
        transform = effect->position;
        transform->x.w.i = (s16)((target[0x24] << 6) + 0x20);
        transform->y.w.i = (s16)((target[0x25] << 6) + 0x20);
        effect_state = ((u8 *)effect) + 0x20;
        transform->z.w.i = *(u16 *)(((u8 *)source) + 0x88);
        *(s16 *)(effect_state + 0xAA) = 1;
        *(s16 *)(effect_state + 0xA8) = 0x1E;
        *(u8 **)(effect_state + 0x90) = target;
        *(s32 *)(effect_state + 0x8C) = effect_arg;
        *(u8 **)(effect_state + 0x9C) = ((u8 *)effect) + 0xB8;

        sound_id = 0x505;
        if (*(u8 *)(*(u8 **)(((u8 *)actor) + 0xBC) + 1) == 0xE) {
            sound_id = 0x516;
        }
        play_sound_if_enabled(sound_id);

        *(s16 *)(effect_state + 0xAE) = (s16)(source->action_flags == 1);
        actor->action_flags = 0;
        return;
    }
    actor->unk_8C.address = handle_player_input;
}
