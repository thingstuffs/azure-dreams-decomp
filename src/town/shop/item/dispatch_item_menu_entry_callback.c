#include "common.h"
#include "town/shop.h"
#include "town/shop/item.h"
#include "town/shop/item_menu_cursor_transition_g00601.h"

typedef s32 (*Func_800B0E0C_Callback)(s32);
extern Func_800B0E0C_Callback D_800D157C[];


/* Dispatch the callback selected by the byte at the current state offset and return its result. */
s32 dispatch_item_menu_entry_callback(ItemMenuTransition *state, s32 callback_arg) {
    return D_800D157C[*(u8 *)(state->entry_data_address +
                       state->end_row)](callback_arg);
}
