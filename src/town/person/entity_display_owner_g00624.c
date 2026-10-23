/* Entity display owner (G00624). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B678C, CL:town/func_800B6858, CL:town/func_800B6980, CL:town/func_800B6A28, CL:town/func_800B6BF0, CL:town/func_800B6C88, CL:town/func_800B6D34. */
#include "town/person/entity_display_owner_g00624.h"

/* Initializes two child entries with data addresses and coordinate offsets. */
void initialize_dual_child_entries(S_800B4350_0 *owner) {
    *((S_800B4350_2 *)(((S_800B4350_1 *)owner)->unk_5C))->unk_78 = owner->unk_20 + 0x48;
    ((S_800B4350_5 *)(((S_800B4350_3 *)(((S_800B4350_2 *)(((S_800B4350_1 *)owner)->unk_5C))->unk_78))->unk_04))->unk_08 =
        -0x20;
    ((S_800B4350_5 *)(((S_800B4350_3 *)(((S_800B4350_2 *)(((S_800B4350_1 *)owner)->unk_5C))->unk_78))->unk_04))->unk_0A =
        -0x18;
    *((S_800B4350_2 *)(((S_800B4350_1 *)owner)->unk_5C))->unk_7C = owner->unk_20 + 0x90;
    ((S_800B4350_6 *)(((S_800B4350_4 *)(((S_800B4350_2 *)(((S_800B4350_1 *)owner)->unk_5C))->unk_7C))->unk_04))->unk_08 =
        -0x70;
    ((S_800B4350_6 *)(((S_800B4350_4 *)(((S_800B4350_2 *)(((S_800B4350_1 *)owner)->unk_5C))->unk_7C))->unk_04))->unk_0A =
        -0x18;
}

/* Processes three data blocks and five table entries for the object. */
void initialize_object_data_blocks_and_entries(Rec_func_800B3FB8_arg0 *object) {
    s8 *entry_data;
    s32 entry_index;

    entry_index = 0;
    copy_contiguous_display_blocks((void *)(object->unk_20));
    copy_display_template_blocks(object->unk_20 + 0x48);
    func_800B426C(object->unk_20 + 0x90);
    upload_three_color_gradient_palette(0x10, &D_800D175C, &D_800D175C, &D_800D175C, 0, 0xA);
    entry_data = &D_800D1658;
    do {
        update_four_slot_element_values_and_positions(object, (struct S_800B3FB8_2 *)(entry_data), entry_index);
        entry_index += 1;
        entry_data += 0x14;
    } while (entry_index < 5);
    initialize_dual_child_entries((struct S_800B4350_0 *)(object));
}

/* Sets the record's base value, offset value, and data pointer. */
void set_record_base_and_data_pointer_alt(void *record_values, s32 base_value) {
    ((S_800B4494_0 *)((u8 *)record_values - 0x10))->unk_14 = base_value;
    ((S_800B4494_0 *)((u8 *)record_values - 0x10))->unk_10 = (s32) (base_value + 0x20);
    ((S_800B4494_0 *)((u8 *)record_values - 0x10))->unk_00 = &D_800B3E68;
}

/*
 * Sets the record base and data pointer, binds three embedded display parts, and initializes the
 * owner data blocks and entries.
 */
void initialize_entity_display_owner(u8 *owner, s32 base_value) {
    set_record_base_and_data_pointer_alt(owner, base_value);
    initialize_entity_display_parts(owner + 0x4C, owner + 0x24, owner + 0x34);
    initialize_object_data_blocks_and_entries((struct Rec_func_800B3FB8_arg0 *)(owner));
}
