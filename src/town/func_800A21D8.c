#include "common.h"

extern s32 func_8009F830(s32, s32);
extern void func_8009F8EC(s32);

/* set_item_equip_00: Equips the selected item, returning -1 if no item is found. */
s32 set_item_equip_00(s32 first, s32 second) {
    s32 item;

    item = func_8009F830(first, second);
    if (item == 0) {
        return -1;
    }
    func_8009F8EC(item);
}
