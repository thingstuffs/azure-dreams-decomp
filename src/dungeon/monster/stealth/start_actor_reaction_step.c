#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct S_801721A4_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0xA];
    u16 unk_A6;
} S_801721A4_1;   /* owner in start_actor_reaction_step */

extern void select_sprite_entry(void *, s32, s32);
#include "dungeon/player/object/action_state.h"
extern void play_sound_if_enabled(s32);
extern s32 generate_random_value(void);

extern u8 D_80173D88[9];

/* Start the actor's reaction step: clear its 0x71 busy bit and, when the global 0x2000 mode is off and the ready query says 0, randomise its facing, arm state 0x17, cue 0x811 and point the part at the direction table. */
void start_actor_reaction_step(S_801721A4_1 *owner, void *unused, SpriteFrameState *part, EntityRec *actor)
{

    actor->unk_71 &= 0x7F;
    if (!(g_dungeon_status.flags & 0x2000) &&
        ((has_pending_dungeon_activity(actor) << 16) == 0)) {
        if (((u32)actor->flags1C) & ACTOR_CONFUSED) {
            s32 link;

            link = actor->flags14;
            if (!(link & 0x80000000)) {
                link |= 0x80000000;
                actor->flags14 = link;
                (*(u16 *)&actor->facing) +=
                    (generate_random_value() & 7) << 9;
            }
        }

        owner->unk_9A = 0x17;
        owner->unk_8C = 0;
        owner->unk_9B = 0;
        owner->unk_A6 = 1;
        owner->unk_96 = 0;

        part->flags |= 0xC;
        part->clut -= 0x80;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
        (*(u8 *)&actor->unk_6D)--;
        part->frameTable = D_80173D88;
        part->color.word = 0xFFFFFF;
        part->tpage_abr = 0x60;
        play_sound_if_enabled(0x811);
        select_sprite_entry(part,
            (*(u8 **)&part->frameTable)[
                ((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
    }
}
