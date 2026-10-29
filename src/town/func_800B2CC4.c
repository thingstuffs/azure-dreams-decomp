#include "common.h"
#include "town/shop/item.h"

extern s32 invoke_item_menu_offset_handler();

/* Dispatch the request's payload according to its result code. */
void dispatch_item_menu_request_result(void *request) {
    s32 result_code;

    result_code = invoke_item_menu_offset_handler(((s32 *)request)[1], ((s32 *)request)[3]);
    if (result_code == 1) {
        set_item_menu_secondary_handler(((s32 *)request)[2]);
        return;
    }
    if (result_code == 2) {
        set_item_menu_data_pointer(((s32 *)request)[2]);
        return;
    }
}
