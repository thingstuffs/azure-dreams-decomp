#include "common.h"
#include "records/Rec_func_80094268_arg0.h"





typedef struct S_8009A344_1 {
    u8 pad_00[0x24];
    s32 unk_24;
} S_8009A344_1;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_44 in func_8009A344 */


extern void func_80094984(M2C_UNK arg0, void *arg1, M2C_UNK arg2);
extern void func_8009A1E8(void *arg0, M2C_UNK arg1, M2C_UNK arg2);

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))


void func_8009A344(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_80094984(((S_8009A344_1 *)(((Rec_func_80094268_arg0 *)arg0)->unk_44))->unk_24, arg0, arg2);
    func_8009A1E8(arg0, arg1, arg2);
}
