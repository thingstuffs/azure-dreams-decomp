/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

s32 func_80700304(s32, s32, s32, s32);                                /* extern */
s32 func_80700590();                               /* extern */

typedef struct {
    u8 pad[0x54];
    void (*callback)(s32);
} CallbackOwner;

extern s32 D_A0700000[];
__asm__(".set D_A0700000, 0xA0700000");

typedef struct S_808B2CB0_0 {
    u8 pad_00[0xE];
    u8 unk_0E;
} S_808B2CB0_0;   /* status in func_808B2CB0 */

/* Set the slot's bitmap bit once the query allows it and return the notifier's result. */
s32 func_808B2CB0(s32 slot, s32 query_b, s32 query_c, s32 query_d) {
    s32 raw_bit;
    register s32 scratch ASM_REG("$4");
    u8 *byte_ptr;
    S_808B2CB0_0 *status;
    u8 status_byte;

    if (func_80700304(slot, query_b, query_c, query_d) >= 2) {
        raw_bit = *(s16 *)((u8 *)D_A0700000 + (slot * 2) + 0xF34);
        scratch = raw_bit;
        if (raw_bit < 0) {
            scratch = raw_bit + 0x1F;
        }
        scratch >>= 5;
        byte_ptr = *(u8 **)((u8 *)D_A0700000 + 0xF40) + scratch;
        scratch = raw_bit - (scratch << 5);
        *byte_ptr |= 1 << scratch;
        return func_80700590(scratch, byte_ptr);
    }

    (*(CallbackOwner **)((u8 *)D_A0700000 + 0xF58))->callback(2);
    status = *(void **)((u8 *)D_A0700000 + 0xF40);
    status_byte = status->unk_0E;
    status->unk_0E = status_byte;
    do {
        return slot;
    } while (0);
}
