#include "common.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"

extern void select_sprite_entry(void *, u8, s32);
extern void advance_status_timers(void *);
extern u8 D_801739E0[];


static __inline__ void dispatch_table(void *sprite, EntityRec *actor, u8 *direction_table) {
    u32 direction_entry;
    *(void **)((u8 *)sprite + 0x2C) = direction_table;
    direction_entry = (((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7);
    direction_entry = direction_entry + (u32)direction_table;
    select_sprite_entry(sprite, *(u8 *)direction_entry, 0);
}

/* Reset state and select a direction-dependent sprite entry from one of four tables. */
void start_actor_directional_action(Rec_func_800A9E70_arg0 *state, void *unused, void *sprite, EntityRec *actor) {
    s32 table_kind;
    u32 direction_entry;
    u8 *direction_table;

    actor->unk_71 = (s8) (actor->unk_71 & 0x7F);
    table_kind = state->unk_AC;
    state->unk_9A.as_s8 = 0x18;
    state->unk_8C = 0;
    state->unk_9B.as_s8 = 0;
    switch (table_kind) {
    case 0:
        dispatch_table(sprite, actor, D_801739E0 + 0);
        break;
    case 1:
        dispatch_table(sprite, actor, D_801739E0 + 8);
        break;
    case 2:
        dispatch_table(sprite, actor, D_801739E0 + 16);
        break;
    case 3:
        dispatch_table(sprite, actor, D_801739E0 + 24);
        break;
    }
    advance_status_timers(actor);
    actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
}
