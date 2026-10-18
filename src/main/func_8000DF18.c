#include "modules/main_server_ship.h"
#include "common.h"

extern s32 CloseEvent(void *event);












/* Closes memory card events, exiting if any close fails. */
void card_boot_close_events(void)
{
    func_8006A084();
    if (CloseEvent((*(void * *)(&D_80028550))) == 0) {
        printf(D_80020000, D_80020028, 0x107);
        exit(1);
    }
    if (CloseEvent((*(void * *)(&D_80028554))) == 0) {
        printf(D_80020000, D_80020028, 0x109);
        exit(1);
    }
    if (CloseEvent((*(void * *)(&D_80028558))) == 0) {
        printf(D_80020000, D_80020028, 0x10B);
        exit(1);
    }
    if (CloseEvent((*(void * *)(&D_8002855C))) == 0) {
        printf(D_80020000, D_80020028, 0x10D);
        exit(1);
    }
    if (CloseEvent((*(void * *)(&D_80028560))) == 0) {
        printf(D_80020000, D_80020028, 0x10F);
        exit(1);
    }
    if (CloseEvent((*(void * *)(&D_80028564))) == 0) {
        printf(D_80020000, D_80020028, 0x111);
        exit(1);
    }
    if (CloseEvent((*(void * *)(&D_80028568))) == 0) {
        printf(D_80020000, D_80020028, 0x113);
        exit(1);
    }
    if (CloseEvent((*(void * *)(&D_8002856C))) == 0) {
        printf(D_80020000, D_80020028, 0x115);
        exit(1);
    }
    func_8006A094();
}
