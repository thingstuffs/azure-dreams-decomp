/* Shop state initialization (G00599). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B0888, CL:town/func_800B0994, CL:town/func_800B09E8, CL:town/func_800B0B44. */
#include "shared/object_node.h"
#include "town/shop/shop_state_initialization_g00599.h"
#include "shared/object_flags.h"

/* Copy a global state word and a 17-word block into the record. */
void copy_global_state_and_record_block(s32 *record) {
    s32 *base = (s32 *)&runtime_script_state;

    record[0xC] = base[0x20];
    *(Record68 *)(record + 0xD) = *(Record68 *)(base + 0x32);
}

/* Initialize town state from the source value and block, clearing two state fields. */
void initialize_state_from_source(Source *source) {
    runtime_script_state.value38 = source->value;
    runtime_script_state.valueA8 = source->value;
    runtime_script_state.valueBA = 0;
    runtime_script_state.value9C = 0;
    runtime_script_state.block = source->block;
}

/* open_shop: Allocate and initialize the shop and its resources, cleaning up if either resource fails. */
void *open_shop(s32 unused, s32 primary_param, s32 secondary_param, s32 shared_param) {
    s32 second_resource;
    S_800AE1AC_0 *shop_state;
    ObjectNodeHeader *shop;

    shop = allocate_flagged_object_node(0);
    if (shop != 0) {
        shop_state = ((void *)shop) + 0x20;
        shop_state->unk_20 = shared_param;
        shop_state->unk_18 = primary_param;
        shop_state->unk_1C = secondary_param;
        shop_state->unk_14 = 6;
        refresh_paged_selection_state(shop_state);
        shop->update_callback = &advance_dispatch_when_countdown_expires;
        shop_state->unk_28 = allocate_paged_shop_item_list(shop, shop_state->unk_04, shop_state->unk_08, shop_state->unk_0C,
            shop_state->unk_10, shop_state->unk_20, primary_param);
        second_resource = create_dual_buffer_object(shop, 0x48, -0xC);
        shop_state->unk_2C = second_resource;
        if ((shop_state->unk_28 == 0) || (second_resource == 0)) {
            process_record_and_apply_flags((struct FuncArg *)(shop_state));
            shop = 0;
        }
        copy_global_state_and_record_block((s32 *)(shop_state));
    }
    return shop;
}

/* Marks the shop record for cleanup, updates its child handlers, and restores shared shop state. */
void process_record_and_apply_flags(FuncArg *record) {
    s32 firstUpdateValue;
    *(u16 *)((u8 *)record - 2) |= 0x8000;
    firstUpdateValue = record->field28;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    set_shop_object_data_if_present(firstUpdateValue);
    set_object_data_pointer_2(record->field2C);
    D_80082AB4[0] = record->field4;
    initialize_state_from_source((Source *)record);
}
