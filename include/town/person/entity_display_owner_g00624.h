#ifndef TOWN_PERSON_ENTITY_DISPLAY_OWNER_G00624_H
#define TOWN_PERSON_ENTITY_DISPLAY_OWNER_G00624_H
/* Entity display owner. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B678C, CL:town/func_800B6858, CL:town/func_800B6980, CL:town/func_800B6A28, CL:town/func_800B6BF0, CL:town/func_800B6C88, CL:town/func_800B6D34. */

#include "common.h"
#include "m2c_compat.h"
#include "town/shop/storage_menu.h"

/* extern */

typedef struct EntityDisplayLayout {
    char *unk_00;
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    void *unk_10;
} EntityDisplayLayout;

/* extern */

void upload_three_color_gradient_palette(s32 palette_slot, u8 *rgb_start, u8 *rgb_mid, u8 *rgb_end, s32 blend_row, s32 semitrans_end);
void update_four_slot_element_values_and_positions(StorageMenuObject *, EntityDisplayLayout *, s32);
/* extern */
void copy_contiguous_display_blocks(void *);
/* extern */
void copy_display_template_blocks();
/* extern */
void func_800B426C(void *);
/* extern */
extern EntityDisplayLayout D_800D1658[5];
extern M2C_UNK entity_display_gradient_color;
/* arg0 in set_record_base_and_data_pointer_alt; pointer addresses record offset 0x10 */
extern void D_800B3E68(void *);
extern void initialize_entity_display_parts();

/* Functions defined in this translation unit. */
void initialize_dual_child_entries(StorageMenuObject *owner);
void initialize_object_data_blocks_and_entries(StorageMenuObject *object);
void set_record_base_and_data_pointer_alt(void *record_values, s32 base_value);
void initialize_entity_display_owner(u8 *owner, s32 base_value);

#endif
