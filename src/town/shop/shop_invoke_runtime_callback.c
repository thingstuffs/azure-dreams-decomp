#include "common.h"

typedef struct S_80702640_0 {
    u8 pad_00[0x60];
    s32 (*unk_60)(s32);
} S_80702640_0;   /* *(void **)0x807030B8 in shop_invoke_runtime_callback */


/* Invoke the runtime callback at offset 0x60 with zero. */
void invoke_runtime_callback(void) {
    ((S_80702640_0 *)(*(void **)0x807030B8))->unk_60(0);
}
