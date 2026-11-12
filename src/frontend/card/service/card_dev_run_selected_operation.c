#include "common.h"
#include "frontend/card/decimal_format.h"
#include "frontend/card/service.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"
#include "frontend/card.h"

extern s32 func_8040153C(void);
extern s32 dev_card_paths[];


/* Starts the selected card operation and maps its completion status. */
s32 card_dev_run_selected_operation(s32 card_index) {
    s32 *card_entry;
    s32 count;
    s32 result;

    count = 0;
    _card_wait_80408654(0);
    _card_wait_80408654(1);
    card_dev_drain_sw_events();
    card_entry = dev_card_paths;
    if (card_index != 0) {
        card_entry++;
    }
    func_8007CAA8(*card_entry);
    while (1) {
        result = func_8040153C();
        if (result != 0) {
            break;
        }
        count++;
        func_800702F0(0);
    }
    func_8007C040(card_decimal_format, card_counter_label, count);
    if (result != 1) {
        if (result == 3) {
            result = 4;
        } else {
            result = 5;
        }
    }
    return result;
}
