#include "common.h"

extern s32 func_8009F6E4(void);
extern s32 func_8009FB2C();

/* set_item_w0: Packs four item parameter bytes and dispatches according to slot availability. */
s32 set_item_w0(s8 item_byte_0, s8 item_byte_1, s8 item_byte_2, s8 item_byte_3) {
    s8 item_bytes[4];
    s32 slot;
    s32 result;
    s8 *item_bytes_ptr;

    slot = func_8009F6E4();
    item_bytes_ptr = item_bytes;
    if (slot == -1) {
        result = 0;
    } else {
        item_bytes[0] = item_byte_0;
        item_bytes[1] = item_byte_1;
        item_bytes[2] = item_byte_2;
        item_bytes[3] = item_byte_3;
        result = func_8009FB2C(slot, item_bytes_ptr);
    }
    return result;
}
