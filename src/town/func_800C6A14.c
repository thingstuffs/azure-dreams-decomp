#include "common.h"
#include "records/Rec_func_80094268_arg0.h"





typedef struct S_800C4174_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800C4174_1;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_80 in func_800C4174 */


extern void func_800C2E84(void *arg0, M2C_UNK arg1, M2C_UNK arg2);
extern void func_800C41D4(void *arg0, M2C_UNK arg1, M2C_UNK arg2);

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))


/* Apply setup from the object descriptor and then run the object update. */
void func_800C4174(void *object, M2C_UNK update_context, M2C_UNK setup_context) {
    func_800C2E84(object, setup_context, ((S_800C4174_1 *)(((Rec_func_80094268_arg0 *)object)->unk_80))->unk_04);
    func_800C41D4(object, update_context, setup_context);
}
