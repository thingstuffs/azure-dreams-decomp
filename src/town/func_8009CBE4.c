#include "common.h"



typedef s32 M2C_UNK;

typedef struct S_8009A344_0 {
    u8 pad_00[0x44];
    void * unk_44;
} S_8009A344_0;   /* arg0 in func_8009A344 */

typedef struct S_8009A344_1 {
    u8 pad_00[0x24];
    s32 unk_24;
} S_8009A344_1;   /* ((S_8009A344_0 *)arg0)->unk_44 in func_8009A344 */


extern void func_80094984(M2C_UNK arg0, void *arg1, M2C_UNK arg2);
extern void func_8009A1E8(void *arg0, M2C_UNK arg1, M2C_UNK arg2);

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))


void func_8009A344(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_80094984(((S_8009A344_1 *)(((S_8009A344_0 *)arg0)->unk_44))->unk_24, arg0, arg2);
    func_8009A1E8(arg0, arg1, arg2);
}
