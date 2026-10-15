#include "modules/main_server_ship.h"
#include "common.h"

extern void func_8005FE18(s32);
extern void format(s32);


/* Format the selected memory card and return its completion status. */
s32 func_80021A84(s32 card_slot) {
    s32 *card_device;
    s32 status;
    s32 result;

    _card_wait(0);
    _card_wait(1);
    func_80021538();
    card_device = &D_80027F18[0];
    if (card_slot != 0) {
        card_device = &D_80027F18[1];
    }
    format(*card_device);
    do {
        status = func_800214FC();
        if (status == 0) {
            func_8005FE18(0);
        }
    } while (status == 0);
    if (status != 1) {
        if (status == 3) {
            status = 4;
        } else {
            status = 5;
        }
    }
    result = status;
    return result;
}
