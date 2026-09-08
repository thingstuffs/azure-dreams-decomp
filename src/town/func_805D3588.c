#include "common.h"
#include "records/Rec_D_80016000.h"





typedef struct S_805D3588_1 {
    u8 pad_00[0x20];
    void * unk_20;
} S_805D3588_1;   /* ((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_pv.v in func_805D3588 */

typedef struct S_805D3588_2 {
    u8 pad_00[0x84];
    M2C_UNK (*unk_84)(M2C_UNK);
    u8 pad_88[0x190];
    M2C_UNK (*unk_218)(M2C_UNK *);
} S_805D3588_2;   /* ((S_805D3588_1 *)(((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_pv.v))->unk_20 in func_805D3588 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_800193E0();
extern M2C_UNK func_80019458();
extern M2C_UNK D_80016000;
extern M2C_UNK D_80019890;


/* Dispatches IDs 0x3EB and 0x631, then invokes object callbacks with 0 and &D_80019890. */
void func_805D3588(void) {
    func_800193E0(0x3EB);
    func_80019458(0x631);
    ((S_805D3588_2 *)(((S_805D3588_1 *)(((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_pv.v))->unk_20))->unk_84(0);
    ((S_805D3588_2 *)(((S_805D3588_1 *)(((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_pv.v))->unk_20))->unk_218(&D_80019890);
}
