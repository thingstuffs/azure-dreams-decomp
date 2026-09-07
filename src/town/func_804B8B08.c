#include "common.h"
#include "records/Rec_D_80016000.h"

typedef struct S_80017308_1 {
    u8 pad_00[0x2];
    s8 unk_02;
} S_80017308_1;   /* ((D_80016000->unk_08.at00_s32.v * 8) + D_80016000->unk_40.as_s32) in func_80017308 */




#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_80018854();
extern Rec_D_80016000 *D_80016000;

void func_80017308(void) {
    func_80018854(0x514);
    ((S_80017308_1 *)(((D_80016000->unk_08.at00_s32.v * 8) + D_80016000->unk_40.as_s32)))->unk_02 = 2;
}
