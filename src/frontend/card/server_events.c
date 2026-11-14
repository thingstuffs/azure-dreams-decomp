/* Card event service
 * Original-file evidence: proven (string literals) - J1:main/image_25c800#g0008.
 * J1:main/image_25c800#g0008
 */
#include "frontend/card.h"

/* Private declarations retained from the member sources. */
/* Card event service */
/* Original-file evidence: proven (string literals) - J1:main/image_25c800#g0008. */

#include "common.h"
#include "sdk/libapi.h"
#include "sdk/memory.h"
#include "modules/main_server_ship.h"
#include "main.h"

/* Opens and enables memory card events, exiting if any setup step fails. */
void card_boot_open_events(void) {
    int card_done_event;
    int card_error_event;
    int card_timeout_event;
    int card_new_event;
    int hw_done_event;
    int hw_error_event;
    int hw_timeout_event;
    int hw_new_event;

    func_8006A084();
    card_done_event = OpenEvent(0xF4000001, 4, 0x2000, 0);
    card_sw_done_event[0] = card_done_event;
    if (card_done_event == -1) {
        printf(card_event_error_format, card_server_filename, 0xB9);
        exit(1);
    }
    card_error_event = OpenEvent(0xF4000001, 0x8000, 0x2000, 0);
    card_sw_error_event[0] = card_error_event;
    if (card_error_event == -1) {
        printf(card_event_error_format, card_server_filename, 0xBB);
        exit(1);
    }
    card_timeout_event = OpenEvent(0xF4000001, 0x100, 0x2000, 0);
    card_sw_timeout_event[0] = card_timeout_event;
    if (card_timeout_event == -1) {
        printf(card_event_error_format, card_server_filename, 0xBD);
        exit(1);
    }
    card_new_event = OpenEvent(0xF4000001, 0x2000, 0x2000, 0);
    card_sw_new_event[0] = card_new_event;
    if (card_new_event == -1) {
        printf(card_event_error_format, card_server_filename, 0xBF);
        exit(1);
    }
    hw_done_event = OpenEvent(0xF0000011, 4, 0x1000, card_boot_latch_hw_done);
    card_hw_done_event[0] = hw_done_event;
    if (hw_done_event == -1) {
        printf(card_event_error_format, card_server_filename, 0xC2);
        exit(1);
    }
    hw_error_event = OpenEvent(0xF0000011, 0x8000, 0x1000, card_boot_latch_hw_error);
    card_hw_error_event[0] = hw_error_event;
    if (hw_error_event == -1) {
        printf(card_event_error_format, card_server_filename, 0xC4);
        exit(1);
    }
    hw_timeout_event = OpenEvent(0xF0000011, 0x100, 0x1000, card_boot_latch_hw_timeout);
    card_hw_timeout_event[0] = hw_timeout_event;
    if (hw_timeout_event == -1) {
        printf(card_event_error_format, card_server_filename, 0xC6);
        exit(1);
    }
    hw_new_event = OpenEvent(0xF0000011, 0x2000, 0x1000, card_boot_latch_hw_new_card);
    card_hw_new_event[0] = hw_new_event;
    if (hw_new_event == -1) {
        printf(card_event_error_format, card_server_filename, 0xC8);
        exit(1);
    }
    func_8006A094();
    if (EnableEvent(card_sw_done_event[0]) == 0) {
        printf(card_event_error_format, card_server_filename, 0xD4);
        exit(1);
    }
    if (EnableEvent(card_sw_error_event[0]) == 0) {
        printf(card_event_error_format, card_server_filename, 0xD6);
        exit(1);
    }
    if (EnableEvent(card_sw_timeout_event[0]) == 0) {
        printf(card_event_error_format, card_server_filename, 0xD8);
        exit(1);
    }
    if (EnableEvent(card_sw_new_event[0]) == 0) {
        printf(card_event_error_format, card_server_filename, 0xDA);
        exit(1);
    }
    if (EnableEvent(card_hw_done_event[0]) == 0) {
        printf(card_event_error_format, card_server_filename, 0xDC);
        exit(1);
    }
    if (EnableEvent(card_hw_error_event[0]) == 0) {
        printf(card_event_error_format, card_server_filename, 0xDE);
        exit(1);
    }
    if (EnableEvent(card_hw_timeout_event[0]) == 0) {
        printf(card_event_error_format, card_server_filename, 0xE0);
        exit(1);
    }
    if (EnableEvent(card_hw_new_event[0]) == 0) {
        printf(card_event_error_format, card_server_filename, 0xE2);
        exit(1);
    }
}

/* Initialize shared state once, run its update, and clear the reset fields. */
void card_boot_init_server(void) {
    MainCardPair *pair;

    if (card_server_initialized[0] == 0) {
        card_server_initialized[0] = 1;
        {
            MainCardPair *init_pair;
            card_slot_completion_flags.a = 0;
            init_pair = &card_slot_completion_flags;
            init_pair->b = 0;
            bzero(card_save_slot_metadata, 0x280);
        }
    }
    card_boot_open_events();
    card_filtered_status.a = 0;
    pair = &card_filtered_status;
    pair->b = 0;
    card_presence_flags.a = 0;
    pair = &card_presence_flags;
    pair->b = 0;
    card_operation_state.a = 0;
}

/* Closes memory card events, exiting if any close fails. */
void card_boot_close_events(void)
{
    func_8006A084();
    if (CloseEvent((*(void * *)(&card_sw_done_event))) == 0) {
        printf(card_event_error_format, card_server_filename, 0x107);
        exit(1);
    }
    if (CloseEvent((*(void * *)(&card_sw_error_event))) == 0) {
        printf(card_event_error_format, card_server_filename, 0x109);
        exit(1);
    }
    if (CloseEvent((*(void * *)(&card_sw_timeout_event))) == 0) {
        printf(card_event_error_format, card_server_filename, 0x10B);
        exit(1);
    }
    if (CloseEvent((*(void * *)(&card_sw_new_event))) == 0) {
        printf(card_event_error_format, card_server_filename, 0x10D);
        exit(1);
    }
    if (CloseEvent((*(void * *)(&card_hw_done_event))) == 0) {
        printf(card_event_error_format, card_server_filename, 0x10F);
        exit(1);
    }
    if (CloseEvent((*(void * *)(&card_hw_error_event))) == 0) {
        printf(card_event_error_format, card_server_filename, 0x111);
        exit(1);
    }
    if (CloseEvent((*(void * *)(&card_hw_timeout_event))) == 0) {
        printf(card_event_error_format, card_server_filename, 0x113);
        exit(1);
    }
    if (CloseEvent((*(void * *)(&card_hw_new_event))) == 0) {
        printf(card_event_error_format, card_server_filename, 0x115);
        exit(1);
    }
    func_8006A094();
}
