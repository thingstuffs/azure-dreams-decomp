#include "common.h"

typedef struct S_80017308_1 {
    u8 pad_00[0x2];
    s8 unk_02;
} S_80017308_1;   /* ((D_80016000->unk_08 * 8) + D_80016000->unk_40) in func_80017308 */


typedef struct S_80017308_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x34];
    s32 unk_40;
} S_80017308_0;   /* D_80016000 in func_80017308 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_80018854();
extern S_80017308_0 *D_80016000;

void func_80017308(void) {
    func_80018854(0x514);
    ((S_80017308_1 *)(((D_80016000->unk_08 * 8) + D_80016000->unk_40)))->unk_02 = 2;
}
