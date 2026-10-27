#include "town/scene/entry_requests.h"
#include "town/shop/object/lshop_g00008.h"

/* The placed slot helper consumes only a0; the other registers are unused. */
void apply_four_values_and_refresh(s32 slot_index) {
    func_80018BE4(slot_index);
    func_80018C58();
}
