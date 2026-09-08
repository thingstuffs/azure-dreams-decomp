#include "common.h"
#include "m2c_compat.h"

s32 func_8004B404();                         /* extern */
M2C_UNK func_800B23C0();                      /* extern */
s32 func_800B2918();                                /* extern */
M2C_UNK func_800B2964();                    /* extern */
s32 func_800B29A4();                             /* extern */

typedef struct S_800B29D0_0 {
    u8 pad_00[0x38];
    s32 unk_38;
    u8 pad_3C[0x4];
    s32 unk_40;
    s32 unk_44;
} S_800B29D0_0;   /* arg0 in func_800B29D0 */

/* Acquires a resource and initializes its associated state on success. */
s32 func_800B29D0(void *state) {
    s32 resourceHandle;
    s32 resourceConfig;

    resourceHandle = func_8004B404(0x100);
    ((S_800B29D0_0 *)state)->unk_40 = resourceHandle;
    if (resourceHandle != 0) {
        resourceConfig = func_800B2918();
        ((S_800B29D0_0 *)state)->unk_44 = resourceConfig;
        func_800B2964(((S_800B29D0_0 *)state)->unk_40, resourceConfig);
        ((S_800B29D0_0 *)state)->unk_38 = func_800B29A4(((S_800B29D0_0 *)state)->unk_40);
        func_800B23C0(state + 0x2C);
    }
    return ((S_800B29D0_0 *)state)->unk_40;
}
