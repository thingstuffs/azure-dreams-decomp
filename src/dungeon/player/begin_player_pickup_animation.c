#include "shared/dungeon_actor_callbacks.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/game_work.h"
#include "dungeon/player.h"
#ifndef NULL
#define NULL 0
#endif

extern void set_sprite_animation_frame(void *a0, s16 a1, s16 a2, s32 a3);
extern void *create_item_render_object(s32 parent, s32 sprite_source, s16 x, s32 y, s16 z);
extern void play_sound_if_enabled(s32 a0);

extern u8 player_carry_frames[8];
extern s32 player_item_render_update_address;

/* Create an effect at the target and initialize its state and sound. */
void begin_player_pickup_animation(u8 *actor, s32 effect_arg, u8 *target, u8 *source) {
    u16 flags;
    s32 direction;
    ObjectNodeHeader *effect;
    ObjectPosition *transform;
    u8 *effect_state;
    s32 sound_id;

    *(s8 *)(actor + 0x9A) = 0x23;
    *(s8 *)(actor + 0x9B) = 0;
    *(void **)(actor + 0x8C) = NULL;

    flags = *(u16 *)(actor + 0xA2);
    *(u16 *)(actor + 0xA2) = flags & 0xFF7F;

    *(u8 **)(target + 0x2C) = &player_carry_frames[0];

    direction = ((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)(source + 0x2A) + 0x100) >> 9) & 7;
    set_sprite_animation_frame(target, player_carry_frames[direction], 0, 1);

    effect = create_item_render_object(actor - 0x20, *(void **)(actor + 0xBC), 0, 0, 0);
    *(void **)(actor + 0x124) = effect;
    if (effect != NULL) {
        effect->update_callback = &player_item_render_update_address;
        transform = *(u8 * *)&effect->position;
        transform->x.w.i = (s16)((target[0x24] << 6) + 0x20);
        transform->y.w.i = (s16)((target[0x25] << 6) + 0x20);
        effect_state = ((u8 *)effect) + 0x20;
        transform->z.w.i = *(u16 *)(source + 0x88);
        *(s16 *)(effect_state + 0xAA) = 1;
        *(s16 *)(effect_state + 0xA8) = 0x1E;
        *(u8 **)(effect_state + 0x90) = target;
        *(s32 *)(effect_state + 0x8C) = effect_arg;
        *(u8 **)(effect_state + 0x9C) = ((u8 *)effect) + 0xB8;

        sound_id = 0x505;
        if (*(u8 *)(*(u8 **)(actor + 0xBC) + 1) == 0xE) {
            sound_id = 0x516;
        }
        play_sound_if_enabled(sound_id);

        *(s16 *)(effect_state + 0xAE) = (s16)(*(u16 *)(source + 0x46) == 1);
        *(u16 *)(actor + 0x46) = 0;
        return;
    }
    *(void **)(actor + 0x8C) = handle_player_input;
}
