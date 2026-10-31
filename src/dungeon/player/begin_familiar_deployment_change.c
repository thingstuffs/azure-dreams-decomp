#include "common.h"
#include "shared/entity.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "dungeon/item.h"
#include "engine/graphics.h"
#include "dungeon/player.h"

extern u8 familiar_summon_frames[];

/* Initializes object state and its directional display, then dispatches an action. */
void begin_familiar_deployment_change(ActorRecord *obj, s32 unused, void *display, s32 mode, u16 variant) {
    u8 *direction_table = familiar_summon_frames;
    s32 lookup_result;
    u16 saved_mode;

    obj->action_id.s = 0x26;
    obj->action_phase.s = 0;
    obj->unk_8C.word = 0;
    (*(u8 **)((u8 *)display + 0x2C)) = direction_table;
    saved_mode = mode;
    set_sprite_animation_frame(
        display,
        direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + obj->facing + 0x100) >> 9) & 7],
        0,
        1);

    obj->target_tile_x = saved_mode;
    obj->target_tile_y = (s8)variant;

    {
        s32 action_kind;
        register ActorRecord *action_obj;
        s32 field_value;
        register s32 action_arg;

        if (reference_tile_object.selected_item != 0) {
            lookup_result = get_special_table_data_index(reference_tile_object.selected_item);
            action_obj = obj;
            action_kind = 0x68;
            field_value = obj->unk_8A;
            action_arg = (s16)lookup_result;
        } else {
            action_kind = 0x88;
            action_obj = obj;
            field_value = action_obj->unk_8A;
            action_arg = 0;
        }
        append_packed_action_record(action_obj, action_kind, field_value, action_arg);
    }
}

