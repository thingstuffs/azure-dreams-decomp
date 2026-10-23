#include "common.h"
#include "shared/entity.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "records/Rec_func_8008ACDC_arg0.h"

extern void set_sprite_animation_frame(void *, u8, s32, s32);
extern s32 get_special_table_data_index(s32);
extern void append_packed_action_record(void *, s32, s16, s32);

extern u8 D_800DD130[];

/* Initializes object state and its directional display, then dispatches an action. */
void begin_familiar_deployment_change(void *obj, s32 unused, void *display, s32 mode, u16 variant) {
    u8 *direction_table = D_800DD130;
    s32 lookup_result;
    u16 saved_mode;

    ((Rec_func_8008ACDC_arg0 *)obj)->unk_9A.as_s8 = 0x26;
    ((Rec_func_8008ACDC_arg0 *)obj)->unk_9B.as_s8 = 0;
    ((Rec_func_8008ACDC_arg0 *)obj)->unk_8C.as_s32 = 0;
    (*(u8 **)((u8 *)display + 0x2C)) = direction_table;
    saved_mode = mode;
    set_sprite_animation_frame(
        display,
        direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((Rec_func_8008ACDC_arg0 *)obj)->unk_2A + 0x100) >> 9) & 7],
        0,
        1);

    ((Rec_func_8008ACDC_arg0 *)obj)->unk_72 = saved_mode;
    ((Rec_func_8008ACDC_arg0 *)obj)->unk_73 = (s8)variant;

    {
        s32 action_kind;
        register void *action_obj;
        s32 field_value;
        register s32 action_arg;

        if (reference_tile_object.selected_item != 0) {
            lookup_result = get_special_table_data_index(reference_tile_object.selected_item);
            action_obj = obj;
            action_kind = 0x68;
            field_value = ((Rec_func_8008ACDC_arg0 *)obj)->unk_8A;
            action_arg = (s16)lookup_result;
        } else {
            action_kind = 0x88;
            action_obj = obj;
            field_value = ((ActorRecord *)action_obj)->unk_8A;
            action_arg = 0;
        }
        append_packed_action_record(action_obj, action_kind, field_value, action_arg);
    }
}

