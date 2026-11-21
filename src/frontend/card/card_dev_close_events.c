#include "common.h"
#include "frontend/card.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"


/* Checks eight c_server entries and asserts on failed checks. */
void card_dev_close_events(void) {
    EnterCriticalSection_8007CA38();
    if (CloseEvent_8007C9A8(dev_card_sw_done_event) == 0) {
        printf_8007C040(card_server_assert_format, dev_server_filename, 0xFD);
        exit_8007BEF0(1);
    }
    if (CloseEvent_8007C9A8(dev_card_sw_error_event) == 0) {
        printf_8007C040(card_server_assert_format, dev_server_filename, 0xFF);
        exit_8007BEF0(1);
    }
    if (CloseEvent_8007C9A8(dev_card_sw_timeout_event) == 0) {
        printf_8007C040(card_server_assert_format, dev_server_filename, 0x101);
        exit_8007BEF0(1);
    }
    if (CloseEvent_8007C9A8(dev_card_sw_new_event) == 0) {
        printf_8007C040(card_server_assert_format, dev_server_filename, 0x103);
        exit_8007BEF0(1);
    }
    if (CloseEvent_8007C9A8(dev_card_hw_done_event) == 0) {
        printf_8007C040(card_server_assert_format, dev_server_filename, 0x105);
        exit_8007BEF0(1);
    }
    if (CloseEvent_8007C9A8(dev_card_hw_error_event) == 0) {
        printf_8007C040(card_server_assert_format, dev_server_filename, 0x107);
        exit_8007BEF0(1);
    }
    if (CloseEvent_8007C9A8(dev_card_hw_timeout_event) == 0) {
        printf_8007C040(card_server_assert_format, dev_server_filename, 0x109);
        exit_8007BEF0(1);
    }
    if (CloseEvent_8007C9A8(dev_card_hw_new_event) == 0) {
        printf_8007C040(card_server_assert_format, dev_server_filename, 0x10B);
        exit_8007BEF0(1);
    }
    ExitCriticalSection_8007CA48();
}
