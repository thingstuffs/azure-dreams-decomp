#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_801725B8_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_801725B8_0;   /* arg0 in advance_directional_action_and_reset */

typedef struct S_801725B8_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801725B8_3;   /* arg1 in advance_directional_action_and_reset */

extern void select_sprite_entry(void *, s32, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern void reduce_actor_food_meter(void *, s32);

extern u8 D_80170F20;
extern u8 D_801762E8[];

/* Advances the actor's directional animation and resets its action state on completion. */
void advance_directional_action_and_reset(void *action, void *motion, void *anim, EntityRec *actor)
{
    switch (((S_801725B8_0 *)action)->unk_9B) {
    case 0:
        if (((SpriteFrameState *)anim)->flags & 0x8000) {
            ((S_801725B8_0 *)action)->unk_9B = 2;
            ((SpriteFrameState *)anim)->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, anim, actor->facing, 1);
            return;
        }
        {
            u8 *direction_table;

            ((S_801725B8_3 *)motion)->unk_14 = 0;
            ((S_801725B8_3 *)motion)->unk_10 = 0;
            ((S_801725B8_3 *)motion)->unk_0C = 0;
            direction_table = D_801762E8;
            ((SpriteFrameState *)anim)->frameTable = direction_table;
            select_sprite_entry(anim,
                direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_801725B8_0 *)action)->unk_9B++;
        }
        return;

    case 1:
        if (((SpriteFrameState *)anim)->unk_04 == 3 && (((SpriteFrameState *)anim)->flags & 0x1000)) {
            play_sound_if_enabled(0x808);
        }
        if (!((((SpriteFrameState *)anim)->unk_04 == 6 && (((SpriteFrameState *)anim)->flags & 0x1000)) ||
              (((SpriteFrameState *)anim)->flags & 0xE000))) {
            return;
        }
        resolve_attack_damage_and_effects(actor, anim, actor->facing, 1);
        ((S_801725B8_0 *)action)->unk_9B++;
                        /* fallthrough */
    case 2:
        if (!(((SpriteFrameState *)anim)->flags & 0xE000)) {
            return;
        }
        reduce_actor_food_meter(actor, 0x100);
        ((S_801725B8_0 *)action)->unk_8C = &D_80170F20;
        g_dungeon_status.active_actor = 0;
        (actor->unk_46) &= 0x7FFF;
        advance_status_timers(actor);
        return;
    }
}
