#include "common.h"

typedef struct S_804803D8_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_804803D8_0;   /* D_80016000 in func_804803D8 */


typedef s32 M2C_UNK;

typedef struct S_804803D8_1 {
    u8 pad_00[0x68];
    s32 (*unk_68)(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *);
} S_804803D8_1;   /* D_80016000->unk_20 in func_804803D8 */

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80016A38();
M2C_UNK func_80016948();
extern S_804803D8_0 *D_80016000;
extern M2C_UNK D_80019440;
extern s32 D_80019540;

/* Prepare D_80019440 for the callback and store its result in D_80019540. */
void func_804803D8(void) {
    func_80016948(&D_80019440, 0x100);
    func_80016A38(&D_80019440);
    D_80019540 = ((S_804803D8_1 *)(D_80016000->unk_20))->unk_68(0, 1, 2, &D_80019440);
}
