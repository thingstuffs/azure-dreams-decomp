#include "common.h"
#include "town/shop.h"

typedef struct S_80702640_0 {
    u8 pad_00[0x60];
    s32 (*unk_60)(s32);
} S_80702640_0;   /* *(void **)0x807030B8 in shop_invoke_runtime_callback */


/* Invoke the runtime callback at offset 0x60 with zero.
 * Held as written: the method table at 0x807030B8 is copied in by the devkit image entry from its
 * host-supplied argument, no disc code stores +0x60 and nothing on the disc calls this function, so
 * the target's parameters (and any a1-a3 the retail call forwards) cannot be established. */
void invoke_runtime_callback(void) {
    ((S_80702640_0 *)(*(void **)0x807030B8))->unk_60(0);
}
