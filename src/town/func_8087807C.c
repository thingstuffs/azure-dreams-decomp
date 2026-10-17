#include "common.h"
#include "m2c_compat.h"

void townShopSetIndexedFlag();                         /* extern */
void townShopClearIndexedFlag();                         /* extern */
s32 townShopTestIndexedFlag();                             /* extern */
extern u8 D_80700000[];

typedef struct S_8070207C_0 {
    u8 pad_00[0x1DCC];
    u16 unk_1DCC;
    u16 unk_1DCE;
} S_8070207C_0;

typedef struct S_8070207C_1 {
    u8 pad_00[0x1DCC];
    u16 unk_1DCC;
} S_8070207C_1;   /* (D_80700000 + final_index) in townShopDispatchEntryValue */

/* Dispatches the entry's second value based on its first, then processes the first. */
void townShopDispatchEntryValue(s32 entry_index) {
    s32 entry_offset;
    s32 saved_index;
    s32 final_offset;

    saved_index = entry_index;
    entry_offset = entry_index * 4;
    if (townShopTestIndexedFlag(((S_8070207C_0 *)(D_80700000 + entry_offset))->unk_1DCC) != 0) {
        townShopSetIndexedFlag(((S_8070207C_0 *)(D_80700000 + entry_offset))->unk_1DCE);
    } else {
        townShopClearIndexedFlag(((S_8070207C_0 *)(D_80700000 + saved_index * 4))->unk_1DCE);
    }
    final_offset = saved_index * 4;
    townShopSetIndexedFlag(((S_8070207C_1 *)(D_80700000 + final_offset))->unk_1DCC);
}
