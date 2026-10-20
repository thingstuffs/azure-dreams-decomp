#include "common.h"
#include "frontend/libcard/interfaces.h"

extern s32 D_80083E98[];
extern s32 D_8002644C[];
extern s32 D_800263C0[];

#include "modules/main_server_ship_interfaces.h"
void func_800264D8(void *context);
void card_boot_enter_insufficient_space_advice(void *record_part);

/* Selects a state table or handler based on the context and current status. */
void route_save_slot_validation(void *context) {
    if (D_80083E98[*(s32 *)((s8 *)context + 0x2C) << 5] != 0) {
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
