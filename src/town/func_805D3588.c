#include "common.h"



typedef s32 M2C_UNK;

typedef struct S_805D3588_0 {
    void * unk_00;
} S_805D3588_0;   /* &D_80016000 in func_805D3588 */

typedef struct S_805D3588_1 {
    u8 pad_00[0x20];
    void * unk_20;
} S_805D3588_1;   /* ((S_805D3588_0 *)(&D_80016000))->unk_00 in func_805D3588 */

typedef struct S_805D3588_2 {
    u8 pad_00[0x84];
    M2C_UNK (*unk_84)(M2C_UNK);
    u8 pad_88[0x190];
    M2C_UNK (*unk_218)(M2C_UNK *);
} S_805D3588_2;   /* ((S_805D3588_1 *)(((S_805D3588_0 *)(&D_80016000))->unk_00))->unk_20 in func_805D3588 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_800193E0();
extern M2C_UNK func_80019458();
extern M2C_UNK D_80016000;
extern M2C_UNK D_80019890;


void func_805D3588(void) {
    func_800193E0(0x3EB);
    func_80019458(0x631);
    ((S_805D3588_2 *)(((S_805D3588_1 *)(((S_805D3588_0 *)(&D_80016000))->unk_00))->unk_20))->unk_84(0);
    ((S_805D3588_2 *)(((S_805D3588_1 *)(((S_805D3588_0 *)(&D_80016000))->unk_00))->unk_20))->unk_218(&D_80019890);
}
