#include "common.h"
#include "town/scene.h"


/* Forward values for code 0x1E, otherwise call the fallback handler. */
void dispatch_code_1_e_or_fallback(s32 first_value, s32 second_value, s32 code) {
    if (code != 0x1E) {
        select_data_pointer_based_result();
        return;
    }
    select_item_gift_response(first_value, second_value, 0x1E);
}
