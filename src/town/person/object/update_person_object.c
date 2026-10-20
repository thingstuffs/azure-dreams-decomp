/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082D58.h"
#include "records/Rec_D_80082E80.h"
#include "shared/object_links.h"
void unlink_node_if_registered(void *block_data);
void func_8003DB94();
void func_800478B8();
void unlink_scene_list_node();
s32 update_state_when_active();
s32 classify_object_against_bounds();
s32 quantize_heading_to_sector();
s32 check_heading_past_half_sector();


   /* the 0x2 bytes before arg0 in update_person_object, addressed as arg0[-1] */


/* Updates an object and its display state, or removes it when requested. */
void update_person_object(void *object, s32 update_ctx, Rec_D_80082E80 *display) {
    s32 frame_index;
    s8 *active_flag;

    if (classify_object_against_bounds(object, update_ctx) != 0) {
        unlink_scene_list_node(object);
        active_flag = ((Rec_D_80082D58 *)object)->unk_98.as_ps8;
        if (active_flag != 0) {
            *active_flag = 0;
        }
        unlink_node_if_registered(object);
        ((ObjectRetirementFlags *)object)[-1].unk_00 = (u16) (((ObjectRetirementFlags *)object)[-1].unk_00 | 0x8000);
        object_flag_block.flags = object_flag_block.flags | 0x8000;
        return;
    }
    update_state_when_active(update_ctx);
    ((Rec_D_80082D58 *)object)->unk_50.as_xcdccad(object, object, update_ctx, display);
    if (!(((ObjectRetirementFlags *)object)[-1].unk_00 & 0x8000)) {
        frame_index = quantize_heading_to_sector(((Rec_D_80082D58 *)object)->unk_72, ((Rec_D_80082D58 *)object)->unk_64);
        if (((Rec_D_80082D58 *)object)->unk_74 != frame_index) {
            func_8003DB94(display, ((Rec_D_80082D58 *)object)->unk_78[frame_index], display->unk_04.as_s8);
            ((Rec_D_80082D58 *)object)->unk_74 = frame_index;
        }
        {
            s32 display_flags;

            if ((check_heading_past_half_sector(((Rec_D_80082D58 *)object)->unk_72, ((Rec_D_80082D58 *)object)->unk_64) << 0x10) != 0) {
                display_flags = display->unk_14.at00_u16.v | 1;
            } else {
                display_flags = display->unk_14.at00_u16.v & 0xFFFE;
            }
            display->unk_14.at00_u16.v = (u16) display_flags;
        }
        func_800478B8(display);
    }
}
