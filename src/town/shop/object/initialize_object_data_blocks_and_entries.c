#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B3FB8_arg0.h"
void upload_three_color_gradient_palette(s32 palette_slot, u8 *rgb_start, u8 *rgb_mid, u8 *rgb_end, s32 blend_row, s32 semitrans_end); /* extern */
void update_four_slot_element_values_and_positions();      /* extern */
void copy_contiguous_display_blocks();                         /* extern */
void copy_display_template_blocks();                         /* extern */
void func_800B426C(void *);                         /* extern */
void initialize_dual_child_entries();                      /* extern */
extern M2C_UNK D_800D1658;
extern M2C_UNK D_800D175C;


/* Processes three data blocks and five table entries for the object. */
void initialize_object_data_blocks_and_entries(Rec_func_800B3FB8_arg0 *object) {
    s8 *entry_data;
    s32 entry_index;

    entry_index = 0;
    copy_contiguous_display_blocks(object->unk_20);
    copy_display_template_blocks(object->unk_20 + 0x48);
    func_800B426C(object->unk_20 + 0x90);
    upload_three_color_gradient_palette(0x10, &D_800D175C, &D_800D175C, &D_800D175C, 0, 0xA);
    entry_data = &D_800D1658;
    do {
        update_four_slot_element_values_and_positions(object, entry_data, entry_index);
        entry_index += 1;
        entry_data += 0x14;
    } while (entry_index < 5);
    initialize_dual_child_entries(object);
}
