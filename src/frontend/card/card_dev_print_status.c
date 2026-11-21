#include "common.h"
#include "frontend/card.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"
#include "frontend/card/service/operation_state_data.h"
#include "frontend/card/service/selected_channel_data.h"
#include "frontend/card/service/event_mode_data.h"

/* Print stored card state and both channel status values. */
void card_dev_print_status(void) {
    card_diagnostic_printf_8003FA78(dev_card_channel_format, (u32)card_selected_channel);
    card_diagnostic_printf_8003FA78(dev_card_operation_state_format, card_ui_operation_state);
    card_diagnostic_printf_8003FA78(dev_card_event_mode_format, (long)card_ui_event_mode);
    card_diagnostic_printf_8003FA78(dev_card_hardware_status_format, card_dev_hardware_status);
    card_diagnostic_printf_8003FA78(dev_card_channel_zero_status_format, (u32)_card_status_80408644(0));
    card_diagnostic_printf_8003FA78(dev_card_channel_one_status_format, (u32)_card_status_80408644(1));
}
