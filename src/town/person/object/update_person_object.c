/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082D58.h"
#include "records/Rec_D_80082E80.h"
#include "shared/object_links.h"
#include "slus.h"
void unlink_node_if_registered(void *block_data);
void select_record_entry_and_value(void *state, void *entries, short index);
#include "town/scene/object/unlink_scene_list_node_api.h"
#include "town/person.h"
#include "town/scene/object.h"
s32 update_state_when_active();
struct func_8009F880_S_8009CFE0_0; s32 classify_object_against_bounds(struct func_8009F880_S_8009CFE0_0 *, void *);

   /* the 0x2 bytes before arg0 in update_person_object, addressed as arg0[-1] */

/* Updates an object and its display state, or removes it when requested. */
void update_person_object(void *object_arg, s32 update_ctx, SpriteFrameState *display) {
    Rec_D_80082D58 *object = object_arg;
    s32 frame_index;
    s8 *active_flag;

    if (classify_object_against_bounds(object_arg, (void *)(update_ctx)) != 0) {
        unlink_scene_list_node(object_arg);
        active_flag = object->unk_98.as_ps8;
        if (active_flag != 0) {
            *active_flag = 0;
        }
        unlink_node_if_registered(object);
        ((ObjectRetirementFlags *)object)[-1].flags = (u16) (((ObjectRetirementFlags *)object)[-1].flags | 0x8000);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
        return;
    }
    update_state_when_active(update_ctx);
    object->unk_50.as_xcdccad(object, object, update_ctx, display);
    if (!(((ObjectRetirementFlags *)object)[-1].flags & 0x8000)) {
        frame_index = quantize_heading_to_sector(object->unk_72, object->unk_64);
        if (object->unk_74 != frame_index) {
            select_record_entry_and_value(display, object->unk_78[frame_index], display->unk_04);
            object->unk_74 = frame_index;
        }
        {
            s32 display_flags;

            if ((check_heading_past_half_sector(object->unk_72, object->unk_64) << 0x10) != 0) {
                display_flags = display->flags | 1;
            } else {
                display_flags = display->flags & 0xFFFE;
            }
            display->flags = (u16) display_flags;
        }
        advance_sprite_animation_and_textures(display);
    }
}
