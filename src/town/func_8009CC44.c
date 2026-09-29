#include "common.h"
#include "shared/object_index_slots.h"
#include "records/Rec_func_80094268_arg0.h"


typedef struct S_8009A3A4_1 {
    u8 pad_00[0x40];
    s32 unk_40;
} S_8009A3A4_1;   /* call_arg0 in func_8009A3A4 */

typedef struct S_8009A3A4_2 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8009A3A4_2;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_44 in func_8009A3A4 */


extern s32 func_80094984();
extern s32 func_80098928();

/* Run the object's indexed handler, clear its table flag, and reset its state. */
void func_8009A3A4(Rec_func_80094268_arg0 *object, s32 position, s32 context) {
    func_80094984(((S_8009A3A4_2 *)(object->unk_44))->unk_14, object, context);
    *(((u8 *)D_80082660) + (((S_8009A3A4_1 *)object)->unk_40 * 8)) = 0;
    func_80098928(object, position, context);
}
