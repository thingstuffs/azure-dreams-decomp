#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"


typedef struct S_801720D8_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
} S_801720D8_1;   /* work in start_actor_hit_reaction */


extern void select_sprite_entry(void *, u8, s32);
extern s32 has_pending_dungeon_activity(void *);
extern s32 generate_random_value(void);
extern u8 D_80174AE4[];

/* Start the actor's hit reaction: clear its flags, give it a random spin and arm the matching sprite frame. */
void start_actor_hit_reaction(void *work, void *part_a, void *part_b, EntityRec *actor) {
    s32 value;

    actor->unk_71 = (u8)(actor->unk_71 & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((has_pending_dungeon_activity(actor) << 16) == 0)) {
        ((S_801720D8_1 *)work)->unk_8C = 0;
        ((S_801720D8_1 *)work)->unk_9A = 0x17;
        ((S_801720D8_1 *)work)->unk_9B = 0;
        if (actor->flags1C & 0x400) {
            value = actor->flags14;
            if (!(value & 0x80000000)) {
                value |= 0x80000000;
                actor->flags14 = (s32)value;
                actor->facing = (u16)(((u16)actor->facing) + ((generate_random_value() & 7) << 9));
            }
        }
        ((S_801720D8_1 *)work)->unk_96 = 0;
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16)(((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1);
        actor->unk_6D = (u8)(((u8)actor->unk_6D) - 1);
        (*(void * *)((u8 *)part_b + 0x2C)) = D_80174AE4;
        select_sprite_entry(part_b, D_80174AE4[((g_game_work.view.camera_rotation.parts.viewAngle + (s16)((u16)actor->facing) + 0x100) >> 9) & 7], 0);
    }
}
