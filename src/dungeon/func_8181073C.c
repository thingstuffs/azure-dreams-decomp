#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80025514();                         /* extern */
M2C_UNK func_800255FC();               /* extern */
s32 func_80026CCC();                             /* extern */
s32 strcmp();                     /* extern */

typedef struct S_8002573C_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
} S_8002573C_0;   /* arg0 in func_8002573C */

typedef struct S_8002573C_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x8];
    s32 unk_28;
} S_8002573C_1;   /* temp_s2 in func_8002573C */

/* Process changed text, then finalize its context. */
s32 func_8002573C(void *context) {
    s32 text;
    S_8002573C_1 *text_state;

    text_state = ((S_8002573C_0 *)context)->unk_14 + 0x20;
    text = func_80026CCC(text_state->unk_28);
    if (strcmp(text, context + 0x78) != 0) {
        func_800255FC(text, ((S_8002573C_0 *)context)->unk_0C, text_state->unk_1C);
    }
    func_80025514(((S_8002573C_0 *)context)->unk_14);
    return 1;
}
