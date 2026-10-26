#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/animation_views.h"
#include "engine/graphics.h"
#include "engine/texture.h"

/* one byte (the next named symbol is D_80080A85); an extern, so absolute in ASPSX */
extern u8 animation_tick_scale;

/* Selects and dispatches a frame, stores its scaled leading value, and clears flags 0x6000. */
void set_sprite_animation_frame(SpriteFrameState *obj, s16 frame_group, s16 frame_index, s32 slot_index) {
    u16 frame_value;
    u8 divisor;

    texture_handle_installs_selected_animation_frame_secondary_pointer_updates_animation_flags((struct S_800489F4_Obj *)obj, frame_group, frame_index, slot_index);
    register_sprite_slot(obj, slot_index);

    frame_value = ((AnimationFrameRate *)obj->unk_00)->value;
    divisor = animation_tick_scale;
    obj->flags = obj->flags & 0x9FFF;
    obj->frame_ticks = (u8)((s32)frame_value / (s32)divisor);
}
