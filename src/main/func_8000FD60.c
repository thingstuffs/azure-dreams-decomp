#include "common.h"

typedef struct S_set_handler_0 {
    u8 pad_00[0x10];
    void * unk_10;
} S_set_handler_0;   /* out in set_handler */

typedef struct S_80022D60_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_80022D60_0;   /* context in cardBootCreateOrResetMessageDialog */

typedef struct S_80022D60_1 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_80022D60_1;   /* base in cardBootCreateOrResetMessageDialog */

typedef struct S_80022D60_2 {
    u8 pad_00[0x8C8];
    s32 unk_8C8;
} S_80022D60_2;   /* body in cardBootCreateOrResetMessageDialog */


#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 cardBootLinkMessageDisplayEntries(void *ptr);
extern void cardBootInitializeDialogDrawNodes(void *context, s32 value);
extern void cardBootInitializeMessageDialogLayout(void *body, s32 value_14, void *entry_index, void *value_0c, s32 value_20);
extern void cardBootCloseMessageDialog(s32 condition);
extern void *initializeSceneObjectInBuffer(s32 value0, void *ptr, s32 value2);
extern void func_8004491C(void *base, void *handler);
extern s32 findActiveListNode(void *base);
extern void bzero(void *ptr, s32 size);
extern u8 D_80022CD8[];
extern u8 D_80027DD0[];
extern u8 D_800287E8[];

static __inline__ void set_handler(u8 *base) {
    ((S_set_handler_0 *)base)->unk_10 = D_80022CD8;
}

/* Creates or resets the entity, initializes its nodes and record, and installs its handler. */
u8 *cardBootCreateOrResetMessageDialog(s32 value_14, void *entry_index, void *value_0c, s32 value_20) {
    u8 *base;
    u8 *context;

    base = D_800287E8;
    context = base + 0x20;
    if (findActiveListNode(base) == 0) {
        base = initializeSceneObjectInBuffer(0, base, 0x27A);
        func_8004491C(base, D_80027DD0);
    } else {
        cardBootCloseMessageDialog(((S_80022D60_0 *)context)->unk_0C != 2);
        ((S_80022D60_1 *)base)->unk_1E &= 0x7FFF;
        bzero(context, 0x9C8);
    }
    cardBootInitializeDialogDrawNodes(context, 7);
    {
        u8 *body = context;

        ((S_80022D60_1 *)base)->unk_0C = body + 0x8BC;
        ((S_80022D60_2 *)body)->unk_8C8 = cardBootLinkMessageDisplayEntries(body + 0x8CC);
        cardBootInitializeMessageDialogLayout(body, value_14, entry_index, value_0c, value_20);
    }
    set_handler(base);
    return base;
}
