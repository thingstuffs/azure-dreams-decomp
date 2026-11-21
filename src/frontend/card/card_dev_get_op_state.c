#include "common.h"
#include "frontend/card.h"
#include "frontend/card/service/operation_state_data.h"

/* Returns the current card UI operation state. */
s32 card_dev_get_op_state(void) {
    return card_ui_operation_state;
}
