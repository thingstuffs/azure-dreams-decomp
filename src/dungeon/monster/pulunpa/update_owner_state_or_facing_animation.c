#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"

extern s32 update_actor_transform_from_parent(void *, void *, void *, void *);
extern s32 check_actor_floor_trap(void *, void *);
extern void select_sprite_entry(void *, u8, s32);

extern u8 D_80158F20[];
extern u8 D_8015BB98[];
extern u8 D_8015E2C8[];
extern u8 D_8015E300[];
extern u8 D_8015E328[];
extern u8 D_8015E360[];

/* Update the owner state or select an animation frame from the facing direction. */
void update_owner_state_or_facing_animation(void *owner_arg, void *context, void *anim_obj_arg, void *state_arg) {
    void *owner = owner_arg;
    SpriteFrameState *anim_obj= anim_obj_arg;
    void *state = state_arg;
    void *current_table;

    if (update_actor_transform_from_parent(owner_arg, context, anim_obj_arg, state_arg) != 0) {
        if ((check_actor_floor_trap(anim_obj, state) << 0x10) > 0) {
            if (*(u8 *)((u8 *)owner + 0xA7) != 0) {
                *(void **)((u8 *)owner + 0x8C) = D_8015BB98;
            } else {
                *(void **)((u8 *)owner + 0x8C) = D_80158F20;
            }
        }
        return;
    }

    current_table = anim_obj->frameTable;
    if (current_table == D_8015E300) {
        if (*(s32 *)((u8 *)state + 0x1C) & 0x208) {
            return;
        }
        anim_obj->frameTable = D_8015E2C8;
        select_sprite_entry(anim_obj, D_8015E2C8[((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)((u8 *)state + 0x2A) + 0x100)
            >> 9) & 7], 0);
    } else if (current_table == D_8015E360) {
        if (*(s32 *)((u8 *)state + 0x1C) & 0x208) {
            return;
        }
        anim_obj->frameTable = D_8015E328;
        select_sprite_entry(anim_obj, D_8015E328[((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)((u8 *)state + 0x2A) + 0x100)
            >> 9) & 7], 0);
    } else {
        return;
    }

}
