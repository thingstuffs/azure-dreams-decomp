#include "common.h"
#include "m2c_compat.h"

void dungeonSetObjectDataPointer();                         /* extern */
void dungeonStoreUniqueTextRecord();               /* extern */
s32 func_80026CCC();                             /* extern */
s32 strcmp();                     /* extern */

typedef struct S_8002573C_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
} S_8002573C_0;   /* arg0 in dungeonProcessChangedItemText */

typedef struct S_8002573C_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x8];
    s32 unk_28;
} S_8002573C_1;   /* temp_s2 in dungeonProcessChangedItemText */

/* Process changed text, then finalize its context. */
s32 dungeonProcessChangedItemText(void *context) {
    s32 text;
    S_8002573C_1 *text_state;

    text_state = ((S_8002573C_0 *)context)->unk_14 + 0x20;
    text = func_80026CCC(text_state->unk_28);
    if (strcmp(text, context + 0x78) != 0) {
        dungeonStoreUniqueTextRecord(text, ((S_8002573C_0 *)context)->unk_0C, text_state->unk_1C);
    }
    dungeonSetObjectDataPointer(((S_8002573C_0 *)context)->unk_14);
    return 1;
}
