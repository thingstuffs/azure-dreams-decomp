#include "common.h"

typedef struct S_80022CD8_0_pre {
    void ** unk_00;
    u8 pad_04[0xC];
} S_80022CD8_0_pre;   /* the 0x10 bytes before arg0 in cardBootActivateMessageDialog, addressed as arg0[-1] */

typedef struct S_80022CD8_0 {
    s32 * unk_00;
    u8 pad_04[0x4];
    s32 * unk_08;
    s32 * unk_0C;
} S_80022CD8_0;   /* arg0 in cardBootActivateMessageDialog */


extern void cardBootBuildMessageWindowPackets(void *buffer, void *layout);
extern void cardBootLayoutFiveEntryList(void *context);
extern void cardBootUpdateMessageChoiceHighlight(void *object);
extern u8 D_80022524[];
extern u8 D_800226A8[];
typedef struct S_800280B4 {
    u8 pad_00[0x15];
    u8 unk_15;
    u8 pad_16[0x2];
} S_800280B4;   /* 0x18-byte entries */

extern S_800280B4 D_800280B4[];

/* Initialize the object from its table entry and select its callback. */
void cardBootActivateMessageDialog(void *object)
{
    void *callback;
    s32 entry_index;

    cardBootBuildMessageWindowPackets((u8 *)object + 0x24, object);
    cardBootLayoutFiveEntryList(object);
    entry_index = ((S_80022CD8_0 *)object)->unk_08;
    ((S_80022CD8_0 *)object)->unk_00 = D_800280B4[entry_index].unk_15;
    cardBootUpdateMessageChoiceHighlight(object);
    if (((S_80022CD8_0 *)object)->unk_0C == 2) {
        callback = D_800226A8;
    } else {
        callback = D_80022524;
    }
    ((S_80022CD8_0_pre *)object)[-1].unk_00 = callback;
}
