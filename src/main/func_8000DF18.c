#include "modules/main_server_ship.h"
#include "common.h"
#include "main.h"

extern s32 CloseEvent(void *event);












/* Closes memory card events, exiting if any close fails. */
void card_boot_close_events(void)
{
    func_8006A084();
    if (CloseEvent((*(void * *)(&card_sw_done_event))) == 0) {
        printf(D_80020000, card_server_filename, 0x107);
        exit(1);
    }
    if (CloseEvent((*(void * *)(&card_sw_error_event))) == 0) {
        printf(D_80020000, card_server_filename, 0x109);
        exit(1);
    }
    if (CloseEvent((*(void * *)(&card_sw_timeout_event))) == 0) {
        printf(D_80020000, card_server_filename, 0x10B);
        exit(1);
    }
    if (CloseEvent((*(void * *)(&card_sw_new_event))) == 0) {
        printf(D_80020000, card_server_filename, 0x10D);
        exit(1);
    }
    if (CloseEvent((*(void * *)(&card_hw_done_event))) == 0) {
        printf(D_80020000, card_server_filename, 0x10F);
        exit(1);
    }
    if (CloseEvent((*(void * *)(&card_hw_error_event))) == 0) {
        printf(D_80020000, card_server_filename, 0x111);
        exit(1);
    }
    if (CloseEvent((*(void * *)(&card_hw_timeout_event))) == 0) {
        printf(D_80020000, card_server_filename, 0x113);
        exit(1);
    }
    if (CloseEvent((*(void * *)(&card_hw_new_event))) == 0) {
        printf(D_80020000, card_server_filename, 0x115);
        exit(1);
    }
    func_8006A094();
}
