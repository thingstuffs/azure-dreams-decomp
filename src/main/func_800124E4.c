#include "common.h"

typedef struct S_800254E4_0_pre {
    u8 * unk_00;
    u8 pad_04[0xC];
} S_800254E4_0_pre;   /* the 0x10 bytes before base in cardBootPrepareCopyDestinationMessage, addressed as base[-1] */

typedef struct S_800254E4_0 {
    u8 pad_00[0x28];
    s32 unk_28;
    u8 pad_2C[0x8];
    u8 * unk_34;
} S_800254E4_0;   /* base in cardBootPrepareCopyDestinationMessage */


typedef struct TableEntry {
    s32 value;
    u8 pad[0x7C];
} TableEntry;

extern s32 cardBootGetRemainingBlockSummary(void);
extern void cardBootShowInsufficientSpaceCardAdvice(void *value);
extern void cardBootShowOverwriteProtectedNotice(void *value);
extern void cardBootEnterCopyingProgress(void *object_data);

extern u8 D_80024FAC[];
extern u8 D_80024FFC[];
extern TableEntry D_80083E98[];

/* Selects a record update based on its table entry and status and assigns data pointers. */
void cardBootPrepareCopyDestinationMessage(void *context)
{
    u8 *record;
    s32 table_index;
    s32 status;

    record = context;
    table_index = ((S_800254E4_0 *)record)->unk_28;
    context = record - 0x20;

    if (D_80083E98[table_index].value == 0) {
        status = cardBootGetRemainingBlockSummary();
        context = 0;
        context = record - 0x20;
        if (status < 3) {
            ((S_800254E4_0 *)record)->unk_34 = D_80024FFC;
            cardBootShowInsufficientSpaceCardAdvice(context);
        } else {
            cardBootEnterCopyingProgress(record);
            return;
        }
    } else {
        ((S_800254E4_0 *)record)->unk_34 = D_80024FFC;
        cardBootShowOverwriteProtectedNotice(context);
    }

    ((S_800254E4_0_pre *)record)[-1].unk_00 = D_80024FAC;
}
