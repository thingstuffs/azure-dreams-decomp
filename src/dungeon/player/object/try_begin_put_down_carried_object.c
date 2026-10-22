#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "dungeon/player/object.h"

void set_sprite_animation_frame();
s32 check_movement_clearance_and_height();
void append_packed_action_record();
s32 check_layer_offset_height();
s32 find_valid_floor_item_position();
extern u8 held_item_kind_alias;
extern u8 D_800DD0D0[];

/* Updates actor state and animation when the position checks succeed. */
void try_begin_put_down_carried_object(void *state, EntityRec *target, SpriteFrameState *sprite, u32 actor_or_can) {
    EntityRec *actor = (void *)actor_or_can;
    s16 probe_a;
    s16 probe_b;
    s16 probe_c;
    s32 direction_offset;

    actor_or_can = 0;
    if (held_item_kind_alias == 0x13) {
        s32 animate_result = check_movement_clearance_and_height(actor->facing, sprite, actor, 0x20);
        animate_result <<= 0x10;
        actor_or_can = animate_result > 0;
    } else if ((check_layer_offset_height(((u16)target->x.w.i), ((u16)target->y.w.i), actor->unk_88, actor->facing) << 0x10) == 0) {
        direction_offset = ((u16) actor->facing >> 8) & 0xE;
        if ((find_valid_floor_item_position((s16) (sprite->unk_24 + *(u16 *)(((u8 *)dir_step_x) + direction_offset)),
            (s16) (sprite->unk_25 + *(u16 *)(((u8 *)dir_step_y) + direction_offset)), actor->unk_88,
            &probe_a, &probe_b, &probe_c) << 0x10) != 0) {
            actor_or_can = 1;
        }
    }
    if (actor_or_can != 0) {
        ((Rec_func_8008ACDC_arg0 *)state)->unk_9A.as_s8 = 0x1F;
        ((Rec_func_8008ACDC_arg0 *)state)->unk_9B.as_s8 = 0;
        ((Rec_func_8008ACDC_arg0 *)state)->unk_8C.as_s32 = 0;
        sprite->frameTable = D_800DD0D0;
        set_sprite_animation_frame(sprite, D_800DD0D0[(((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100)) >> 9) & 7], 0, 1);
        g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1;
        append_packed_action_record(actor, 0x28, 0, 0);
    }
}
