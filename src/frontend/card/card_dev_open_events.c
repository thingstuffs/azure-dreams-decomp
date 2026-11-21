#include "common.h"
#include "frontend/card.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"


/* Opens and enables memory card events, asserting that each operation succeeds. */
void card_dev_open_events(void) {
    s32 event_handle;
    EnterCriticalSection_8007CA38();
    event_handle = OpenEvent_8007C998(0xF4000001, 4, 0x2000, 0);
    dev_card_sw_done_event = event_handle;
    if (event_handle == -1) {
        printf_8007C040(card_server_assert_format, dev_server_filename, 0xB4);
        exit_8007BEF0(1);
    }
    event_handle = OpenEvent_8007C998(0xF4000001, 0x8000, 0x2000, 0);
    dev_card_sw_error_event = event_handle;
    if (event_handle == -1) {
        printf_8007C040(card_server_assert_format, dev_server_filename, 0xB6);
        exit_8007BEF0(1);
    }
    event_handle = OpenEvent_8007C998(0xF4000001, 0x100, 0x2000, 0);
    dev_card_sw_timeout_event = event_handle;
    if (event_handle == -1) {
        printf_8007C040(card_server_assert_format, dev_server_filename, 0xB8);
        exit_8007BEF0(1);
    }
    event_handle = OpenEvent_8007C998(0xF4000001, 0x2000, 0x2000, 0);
    dev_card_sw_new_event = event_handle;
    if (event_handle == -1) {
        printf_8007C040(card_server_assert_format, dev_server_filename, 0xBA);
        exit_8007BEF0(1);
    }
    event_handle = OpenEvent_8007C998(0xF0000011, 4, 0x1000, card_dev_event_ioe_handler_804009C0);
    dev_card_hw_done_event = event_handle;
    if (event_handle == -1) {
        printf_8007C040(card_server_assert_format, dev_server_filename, 0xBD);
        exit_8007BEF0(1);
    }
    event_handle = OpenEvent_8007C998(0xF0000011, 0x8000, 0x1000, card_dev_event_error_handler_804009D4);
    dev_card_hw_error_event = event_handle;
    if (event_handle == -1) {
        printf_8007C040(card_server_assert_format, dev_server_filename, 0xBF);
        exit_8007BEF0(1);
    }
    event_handle = OpenEvent_8007C998(0xF0000011, 0x100, 0x1000, card_dev_event_timeout_handler_804009E8);
    dev_card_hw_timeout_event = event_handle;
    if (event_handle == -1) {
        printf_8007C040(card_server_assert_format, dev_server_filename, 0xC1);
        exit_8007BEF0(1);
    }
    event_handle = OpenEvent_8007C998(0xF0000011, 0x2000, 0x1000, card_dev_event_new_handler_804009FC);
    dev_card_hw_new_event = event_handle;
    if (event_handle == -1) {
        printf_8007C040(card_server_assert_format, dev_server_filename, 0xC3);
        exit_8007BEF0(1);
    }
    ExitCriticalSection_8007CA48();
    if (EnableEvent_8007C9D8(dev_card_sw_done_event) == 0) {
        printf_8007C040(card_server_assert_format, dev_server_filename, 0xCF);
        exit_8007BEF0(1);
    }
    if (EnableEvent_8007C9D8(dev_card_sw_error_event) == 0) {
        printf_8007C040(card_server_assert_format, dev_server_filename, 0xD1);
        exit_8007BEF0(1);
    }
    if (EnableEvent_8007C9D8(dev_card_sw_timeout_event) == 0) {
        printf_8007C040(card_server_assert_format, dev_server_filename, 0xD3);
        exit_8007BEF0(1);
    }
    if (EnableEvent_8007C9D8(dev_card_sw_new_event) == 0) {
        printf_8007C040(card_server_assert_format, dev_server_filename, 0xD5);
        exit_8007BEF0(1);
    }
    if (EnableEvent_8007C9D8(dev_card_hw_done_event) == 0) {
        printf_8007C040(card_server_assert_format, dev_server_filename, 0xD7);
        exit_8007BEF0(1);
    }
    if (EnableEvent_8007C9D8(dev_card_hw_error_event) == 0) {
        printf_8007C040(card_server_assert_format, dev_server_filename, 0xD9);
        exit_8007BEF0(1);
    }
    if (EnableEvent_8007C9D8(dev_card_hw_timeout_event) == 0) {
        printf_8007C040(card_server_assert_format, dev_server_filename, 0xDB);
        exit_8007BEF0(1);
    }
    if (EnableEvent_8007C9D8(dev_card_hw_new_event) == 0) {
        printf_8007C040(card_server_assert_format, dev_server_filename, 0xDD);
        exit_8007BEF0(1);
    }
}
