#include "common.h"
#include "records/Rec_func_80094268_arg0.h"





typedef struct S_8009A344_1 {
    u8 pad_00[0x24];
    s32 unk_24;
} S_8009A344_1;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_44 in func_8009A344 */


extern void func_80094984(M2C_UNK arg0, void *arg1, M2C_UNK arg2);
extern void func_8009A1E8(void *arg0, M2C_UNK arg1, M2C_UNK arg2);

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))


/* Initialize the record from linked data and apply its update parameters. */
void func_8009A344(void *record, M2C_UNK update_value, M2C_UNK init_context) {
    func_80094984(((S_8009A344_1 *)(((Rec_func_80094268_arg0 *)record)->unk_44))->unk_24, record, init_context);
    func_8009A1E8(record, update_value, init_context);
}
