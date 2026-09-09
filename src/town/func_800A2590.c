#include "common.h"

extern s32 func_8009F6E4(void);
extern s32 func_8009FB2C();
extern s32 func_8009FD48();

/* set_item_w0: Packs four item parameter bytes and dispatches according to slot availability. */
void set_item_w0(s8 item_byte_0, s8 item_byte_1, s8 item_byte_2, s8 item_byte_3) {
    s8 item_bytes[4];
    s32 slot;
    s8 *item_bytes_ptr;

    slot = func_8009F6E4();
    item_bytes_ptr = item_bytes;
    if (slot == -1) {
        s32 result;

        ASM_KEEP(slot);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        result = 0;
        ASM_TAILSLOT_PIN_TIED(result);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_8009FD48(slot, item_bytes_ptr);
        return;
    }

    item_bytes[0] = item_byte_0;
    item_bytes[1] = item_byte_1;
    item_bytes[2] = item_byte_2;
    item_bytes[3] = item_byte_3;
    func_8009FB2C(slot, item_bytes_ptr);
}

/* MECHANISM: The four-byte args array and separate slot produce the retail 0x30 frame and s0-s3 saves.
   Fixed a0/a1 locals preserve the runtime slot and one shared stack-address setup across the failure edge.
   A tied v0 tail-slot pin lets LEAD 28 sink zero into the converted func_8009FD48 jump delay. */
