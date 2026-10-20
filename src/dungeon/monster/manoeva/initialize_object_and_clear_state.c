#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"


extern void select_sprite_entry();
extern s32 has_pending_dungeon_activity();

extern u8 D_80176670[16];


typedef struct S_80173C40_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
} S_80173C40_2;   /* arg0 in initialize_object_and_clear_state */

/* Initialize the entity action and select its directional animation when ready. */
void initialize_object_and_clear_state(void *action, void *unused, void *animation, EntityRec *entity) {

    if (g_dungeon_status.flags & 0x2000) {
        entity->unk_71 &= 0x7F;
        return;
    }

    if ((has_pending_dungeon_activity(entity) << 16) == 0) {
        s32 direction;

        ((S_80173C40_2 *)action)->unk_9A = 0x17;
        ((S_80173C40_2 *)action)->unk_9B = 0;
        ((S_80173C40_2 *)action)->unk_8C = 0;
        *(u8 **)((u8 *)animation + 0x2C) = D_80176670;

        direction = ((g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7;
        select_sprite_entry(animation, D_80176670[direction], 0);

        ((S_80173C40_2 *)action)->unk_96 = 0;
        entity->flags1C |= 0x10000000;
        g_dungeon_status.unk_0A++;
        entity->unk_46 &= 0x7FFF;
    }
}
