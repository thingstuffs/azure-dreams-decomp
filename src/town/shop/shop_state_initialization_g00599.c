/* Shop state initialization. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B0888, CL:town/func_800B0994, CL:town/func_800B09E8, CL:town/func_800B0B44. */
#include "engine/message.h"
#include "engine/message/data.h"
#include "engine/script/vm.h"
#include "shared/object_node.h"
#include "town/shop/shop_state_initialization_g00599.h"
#include "shared/object_flags.h"
#include "town/shop.h"

typedef struct ShopMenu {
    GridMenuObject grid;
    u8 *resume_script;
    ScriptReturnStack returns;
} ShopMenu;

/* Save the address in variable 14 and the window's return stack. */
void save_shop_script_state(ShopMenu *shop) {
    shop->resume_script = script_address_from_word(runtime_script_state.variables[14]);
    shop->returns = runtime_script_state.window.returns;
}

/* Resume the saved script with its return stack. */
void restore_shop_script_state(ShopMenu *shop) {
    runtime_script_state.script_start = shop->resume_script;
    runtime_script_state.window.cursor = shop->resume_script;
    runtime_script_state.window.text_advance_mode = 0;
    runtime_script_state.window.message_handler = 0;
    runtime_script_state.window.returns = shop->returns;
}

/* open_shop: Allocate and initialize the shop and its resources, cleaning up if either resource fails. */
void *open_shop(s32 unused, s32 primary_param, s32 secondary_param, s32 shared_param) {
    s32 second_resource;
    ShopMenu *shop_state;
    ObjectNodeHeader *shop;

    shop = allocate_flagged_object_node(0);
    if (shop != 0) {
        shop_state = NODE_BODY(shop);
        shop_state->grid.entry_base = shared_param;
        shop_state->grid.field_18 = primary_param;
        shop_state->grid.dispatch_mode = secondary_param;
        shop_state->grid.repeat_ticks = 6;
        refresh_paged_selection_state(&shop_state->grid);
        shop->update_callback = &advance_dispatch_when_countdown_expires;
        shop_state->grid.subrecord = allocate_paged_shop_item_list(shop, shop_state->grid.selected_index, shop_state->grid.entry_count, shop_state->grid.selected_row,
            shop_state->grid.field_10, shop_state->grid.entry_base, primary_param);
        second_resource = (s32)(unsigned long)create_floating_number_widget(shop, 0x48, -0xC);
        shop_state->grid.field_2C = second_resource;
        if ((shop_state->grid.subrecord == 0) || (second_resource == 0)) {
            close_shop(shop_state);
            shop = 0;
        }
        save_shop_script_state(shop_state);
    }
    return shop;
}

/* Marks the shop record for cleanup, updates its child handlers, and restores shared shop state. */
void close_shop(ShopMenu *shop) {
    s32 firstUpdateValue;
    NODE_HEADER(shop)->flags |= 0x8000;
    firstUpdateValue = shop->grid.subrecord;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    set_shop_fade_out_callback(firstUpdateValue);
    set_advance_inner_value_callback(shop->grid.field_2C);
    runtime_script_state.variables[13] = shop->grid.selected_index;
    restore_shop_script_state(shop);
}
