#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_801726A4_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801726A4_0;   /* arg0 in advance_actor_sprite_action */

typedef struct S_801726A4_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801726A4_3;   /* arg1 in advance_actor_sprite_action */

extern void select_sprite_entry(void *, s32, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern void reduce_actor_food_meter(void *, s32);
extern void create_action_sprite_effect(void *);

extern u8 D_80170EE4[];
extern u8 D_80176600[];
extern u8 D_80176668[];

/* Advances an actor's animation sequence and handles its completion. */
void advance_actor_sprite_action(void *action, void *motion, void *sprite, EntityRec *actor)
{
    u16 sprite_flags;
    u16 frame_count;
    s32 state;

    state = ((S_801726A4_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        ((S_801726A4_0 *)action)->unk_98 |= 1;
        ((S_801726A4_0 *)action)->unk_9B++;
                        /* fall through */
    case 1:
        sprite_flags = ((SpriteFrameState *)sprite)->flags;
        if (sprite_flags & 0x8000) {
            ((S_801726A4_0 *)action)->unk_9B = 3;
            ((SpriteFrameState *)sprite)->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }

        if (sprite_flags & 0x6000) {
            ((S_801726A4_3 *)motion)->unk_0C =
                ((S_801726A4_3 *)motion)->unk_10 =
                ((S_801726A4_3 *)motion)->unk_14 = 0;
            ((SpriteFrameState *)sprite)->frameTable = D_80176600;
            select_sprite_entry(sprite,
                D_80176600[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            create_action_sprite_effect((u8 *)action - 0x20);
            ((S_801726A4_0 *)action)->unk_96 = 0;
            ((S_801726A4_0 *)action)->unk_9B++;
            play_sound_if_enabled(0x804);
            return;
        }
        break;
    case 2:
        frame_count = ((S_801726A4_0 *)action)->unk_96 + 1;
        ((S_801726A4_0 *)action)->unk_96 = frame_count;

        if ((s16)frame_count == state ||
            (((SpriteFrameState *)sprite)->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
        }

        if (((SpriteFrameState *)sprite)->flags & 0xE000) {
            ((SpriteFrameState *)sprite)->frameTable = D_80176668;
            select_sprite_entry(sprite,
                D_80176668[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_801726A4_0 *)action)->unk_9B++;
            ((S_801726A4_0 *)action)->unk_98 &= 0xFFFE;
            return;
        }
        break;
    case 3:
        if (((SpriteFrameState *)sprite)->flags & 0xE000) {
            reduce_actor_food_meter(actor, 0x100);
            ((S_801726A4_0 *)action)->unk_8C = D_80170EE4;
            g_dungeon_status.unk_0C = 0;
            (actor->unk_46) &= 0x7FFF;
            advance_status_timers(actor);
        }
    }
}
