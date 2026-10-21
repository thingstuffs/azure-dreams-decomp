#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_80172620_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172620_0;   /* arg0 in advance_actor_attack_and_resolve_damage */

extern void select_sprite_entry(void *, u8, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void set_record_integer_tile_center(s32, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);

extern void *D_800E3DE8;
extern s32 D_80170E54;
extern u8 D_801739F0[];

/* Advance the actor's animation state and clean up when it finishes. */
void advance_actor_attack_and_resolve_damage(void *action, s32 actor_id, void *sprite, ActorRecord *actor) {
    s32 state;

    state = ((S_80172620_0 *)action)->unk_9B;
    ((S_80172620_0 *)action)->unk_96--;
    switch (state) {
    case 0:
        if (((SpriteFrameState *)sprite)->flags & 0x8000) {
            ((S_80172620_0 *)action)->unk_9B = 0xFF;
            ((SpriteFrameState *)sprite)->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }
        ((SpriteFrameState *)sprite)->frameTable = D_801739F0;
        select_sprite_entry(sprite,
            D_801739F0[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_80172620_0 *)action)->unk_9B++;
        return;

    case 1:
        if (((((SpriteFrameState *)sprite)->unk_04 == 6) &&
             (((SpriteFrameState *)sprite)->flags & 0x1000)) ||
            (((SpriteFrameState *)sprite)->flags & 0x8000)) {
            play_sound_if_enabled(0x808);
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            ((S_80172620_0 *)action)->unk_9B = 0xFF;
        }
        return;

    case 0xFF:
        if (((SpriteFrameState *)sprite)->flags & 0xE000) {
            set_record_integer_tile_center(actor_id, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
            spend_actor_mp(actor, 0x100);
            ((S_80172620_0 *)action)->unk_8C = &D_80170E54;
            g_dungeon_status.active_actor = 0;
            advance_status_timers(actor);
            if (actor->pending_turn_updates == 0) {
                actor->action_flags &= 0x7FFF;
                return;
            }
            D_800E3DE8 = (u8 *)actor - 0x20;
        }
        return;
    }
}
