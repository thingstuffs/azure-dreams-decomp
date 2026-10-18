#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x8C];
    s32 field_8C;
} ActionStateFieldView_80DBD29C;

typedef struct {
    u8 pad_00[0x2C];
    u8 *field_2C;
} SpriteFieldView_80DBD29C;


typedef s32 M2C_UNK;


typedef struct S_80174A9C_1 {
    u8 pad_00[0x9A];
    s8 unk_9A;
    s8 unk_9B;
} S_80174A9C_1;   /* arg0 in begin_actor_directional_target_action */

typedef struct S_80174A9C_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80174A9C_2;   /* arg2 in begin_actor_directional_target_action */



M2C_UNK func_80047784();
s32 find_eligible_actor_at_tile_and_height();
s32 try_claim_dungeon_action_slot();
s32 advance_status_timers();
s32 apply_camera_offset_and_select_target();
extern u8 D_80175414;

/* Starts an actor action and selects its directional sprite and adjacent target. */
void begin_actor_directional_target_action(void *action_state, s32 action_context, void *sprite, EntityRec *actor) {
    s32 direction;

    actor->unk_71 = (u8)(actor->unk_71 & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            ((S_80174A9C_1 *)action_state)->unk_9A = 0x17;
            (((ActionStateFieldView_80DBD29C *)action_state)->field_8C) = 0;
            ((S_80174A9C_1 *)action_state)->unk_9B = 0;
            (((SpriteFieldView_80DBD29C *)sprite)->field_2C) = &D_80175414;
            func_80047784(sprite,
                          *(&D_80175414 + (((s32)(g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7)),
                          0);
            advance_status_timers(actor);
            actor->unk_6D = (u8)(((u8)actor->unk_6D) - 1);
            direction = ((u16)actor->facing >> 9) & 7;
            actor->target =
                find_eligible_actor_at_tile_and_height(actor,
                              (((S_80174A9C_2 *)sprite)->unk_24 + ((u16 *)dir_step_x)[direction]) & 0xFFFF,
                              (((S_80174A9C_2 *)sprite)->unk_25 + ((u16 *)dir_step_y)[direction]) & 0xFFFF,
                              actor->unk_88);
        }
    }
}
