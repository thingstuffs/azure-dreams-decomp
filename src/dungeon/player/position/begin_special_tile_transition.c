#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/transition_slots.h"
#include "shared/game_work.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "records/Rec_func_8008D024_arg0.h"

extern u8 D_800DCFB0[8];
extern s16 D_800814E8;
extern s16 get_entity_effect_value(void *, s32);
extern void set_sprite_animation_frame(void *, u8, s32, s32);
extern s16 lookup_definition_pair_value(u8, u8);
extern s16 reserve_runtime_slot(s16 slot_id, s16 slot_value);
extern void mark_category_items_flag_400(s32);

extern void clear_player_linked_action_flags(void);
/* Initializes action state and animation, then handles the current tile type. */
void begin_special_tile_transition(Rec_func_8008D024_arg0 *state, s32 unused, SpriteFrameState *entity, EntityRec *actor) {
    s16 tile_type;
    s16 slot_index;

    state->unk_9A = 0x25;
    state->unk_9B.as_s8 = 0;
    state->unk_8C = 0;
    clear_player_linked_action_flags();
    if (get_entity_effect_value(actor, 0xA) == 0) {
        entity->frameTable = D_800DCFB0;
        set_sprite_animation_frame(entity, D_800DCFB0[((s32)(g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0, 1);
    }
    tile_type = lookup_definition_pair_value(entity->unk_24, entity->unk_25);
    if (tile_type == 3) {
        slot_index = reserve_runtime_slot(6, 0x20);
        D_800814E8 = slot_index;
        D_80083120[slot_index].unk_6 = 1;
        state->unk_9B.as_s8 = 0x10;
        return;
    }
    if (tile_type == 4) {
        *(s32 *)0x80012090 = 2;
        mark_category_items_flag_400(2);
    }
}
