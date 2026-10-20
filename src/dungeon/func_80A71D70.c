#include "modules/dungeon_resource07_slot0.h"
#include "shared/sprite_frame_state.h"

void advance_stored_path_motion(void *action, s32 action_id, SpriteFrameState *entity, void *move_state) {
    void *state = move_state;
    s32 tile_mask;
    s16 move_result;
    s16 direction;
    s16 x;
    s32 y;
    s32 step_count;
    u8 new_x;
    u8 new_y;

    if (((R07_80171570_S_80171570_0 *)state)->unk_71.s <= 0) {
        return;
    }
    if (((R07_80171570_S_80171570_0 *)state)->unk_71.u <= ((R07_80171570_S_80171570_0 *)state)->unk_8A) {
        return;
    }

    if (*(u8 * *)&entity->frameTable != ((u8 *)D_80174138)) {
        entity->frameTable = ((u8 *)D_80174138);
        select_sprite_entry(
            entity,(s16)(((u8 *)D_80174138)[((g_game_work.view.viewAngle + ((R07_80171570_S_80171570_0 *)state)->unk_2A + 0x100) >> 9) & 7]),(s16)(0));
    }

    x = entity->unk_24;
    y = entity->unk_25;
    tile_mask = 0x3000;
    if (((R07_80171570_S_80171570_0 *)state)->unk_1C & 0x2000) {
        tile_mask = 0x300;
    }
    update_map_cell_flags_with_item_limit(x, y, tile_mask);

    direction = ((s16)get_rounded_facing_and_rounding_flag((s16)(x),(s16)(y),(s16)(((R07_80171570_S_80171570_3 *)((u8 *)state + ((R07_80171570_S_80171570_0 *)state)->unk_8A))->unk_74),(s16)(((R07_80171570_S_80171570_3 *)((u8 *)state + ((R07_80171570_S_80171570_0 *)state)->unk_8A))->unk_7C),
        (u8 *)action + 0x98));
    move_result = ((s16)check_movement_clearance_and_height((s16)(direction), entity, state, 0x20));

    entity->unk_24 =
        ((R07_80171570_S_80171570_3 *)((u8 *)state + ((R07_80171570_S_80171570_0 *)state)->unk_8A))->unk_74;
    tile_mask = 0x3000;
    entity->unk_25 =
        ((R07_80171570_S_80171570_3 *)((u8 *)state + ((R07_80171570_S_80171570_0 *)state)->unk_8A))->unk_7C;
    ((R07_80171570_S_80171570_0 *)state)->unk_8A = (u16)((R07_80171570_S_80171570_0 *)state)->unk_8A + 1;

    new_x = entity->unk_24;
    new_y = entity->unk_25;
    if (((R07_80171570_S_80171570_0 *)state)->unk_1C & 0x2000) {
        tile_mask = 0x300;
    }
    cycle_map_cell_flags((s16)(new_x),(s16)(new_y),(u16)(tile_mask));
    ((R07_80171570_S_80171570_0 *)state)->unk_2A = direction;

    if (move_result == 3 && !(g_dungeon_status.flags & 0x80)
        && !(entity->flags & 0x8000)) {
        initialize_opposite_facing_effect(action, action_id, entity, state);
        ((R07_80171570_S_80171570_2 *)action)->unk_8C = 0;
    } else {
        ((R07_80171570_S_80171570_2 *)action)->unk_9A = 0x0F;
        ((R07_80171570_S_80171570_2 *)action)->unk_8C = 0;
    }
    (*(s32 *)((u8 *)state + 0x1C)) |= 0x40000000;
    if (g_dungeon_status.flags & 0x80) {
        ((R07_80171570_S_80171570_2 *)action)->unk_96 = 0;
        return;
    }

    ((R07_80171570_S_80171570_2 *)action)->unk_96 = 8;
    step_count = ((R07_80171570_S_80171570_0 *)state)->unk_71.u;
    if (step_count > 0) {
        ((R07_80171570_S_80171570_2 *)action)->unk_96 = 8 / step_count;
    }
}
