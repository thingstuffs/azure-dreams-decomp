#include "common.h"
#include "shared/object_index_slots.h"
#include "records/Rec_func_80094268_arg0.h"


typedef struct S_8009A3A4_1 {
    u8 pad_00[0x40];
    s32 unk_40;
} S_8009A3A4_1;   /* call_arg0 in townRunPlayerIndexedHandler */

typedef struct S_8009A3A4_2 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8009A3A4_2;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_44 in townRunPlayerIndexedHandler */


extern s32 townCallTheHandlerSelectsNonzeroEntry();
extern s32 townInitializeRecordWithHandlerTable();

/* Run the object's indexed handler, clear its table flag, and reset its state. */
void townRunPlayerIndexedHandler(Rec_func_80094268_arg0 *object, s32 position, s32 context) {
    townCallTheHandlerSelectsNonzeroEntry(((S_8009A3A4_2 *)(object->unk_44))->unk_14, object, context);
    *(((u8 *)D_80082660) + (((S_8009A3A4_1 *)object)->unk_40 * 8)) = 0;
    townInitializeRecordWithHandlerTable(object, position, context);
}
