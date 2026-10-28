#include "common.h"
#include "frontend/card.h"
#include "frontend/libcard/interfaces.h"


#include "modules/main_server_ship_interfaces.h"
#include "frontend/libcard.h"
#include "main/data.h"
void func_800264D8(void *context);

/* Selects a state table or handler based on the context and current status. */
void route_save_slot_validation(void *context) {
    if (card_save_slot_metadata[*(s32 *)((s8 *)context + 0x2C)].words[0] != 0) {
        *(s32 **)((s8 *)context - 0x10) = D_8002644C;
        return;
    }
    if (card_boot_get_remaining_block_summary() >= 3) {
        *(s32 **)((s8 *)context - 0x10) = D_800263C0;
        return;
    }
    if (card_boot_count_cached_slots() != 0) {
        card_boot_enter_insufficient_space_advice(context);
        return;
    }
    func_800264D8(context);
}
