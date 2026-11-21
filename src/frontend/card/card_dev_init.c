#include "frontend/card/save_slot.h"
#include "common.h"
#include "frontend/card/decimal_format.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "frontend/libcard.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"
#include "frontend/card/service/operation_state_data.h"


/* Initializes memory card support when card_first_flg is clear and resets card server state. */
void card_dev_init(void) {
    printf_8007C040(card_decimal_format, card_first_flg_label, card_first_flg);
    if (card_first_flg == 0) {
        card_first_flg = 1;
        libcard_init(1);
        libcard_start();
        _bu_init_8007C958();
        ChangeClearPAD_8007CB08(0);
        dev_card_channel_completion_flags[0] = 0;
        dev_card_channel_completion_flags[1] = 0;
        bzero_8007BFE0(card_slot_header_cache, sizeof(card_slot_header_cache));
    }
    card_dev_open_events();
    card_stable_slot_state[0] = 0;
    card_stable_slot_state[1] = 0;
    card_debounced_channel_flags[0] = 0;
    card_debounced_channel_flags[1] = 0;
    card_ui_operation_state = 0;
}
