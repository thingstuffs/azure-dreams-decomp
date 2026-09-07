#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80090A74();
extern M2C_UNK func_80090D20();
extern M2C_UNK func_80093D18();
extern M2C_UNK func_80093DD8();
extern s32 func_80094B0C();
extern M2C_UNK func_8009550C();
extern M2C_UNK func_80099754();
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 flags;
} D_80083160_t;

extern D_80083160_t D_80083160;


typedef struct S_80090C68_0 {
    s32 unk_00;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_80090C68_0;   /* arg0 in func_80090C68 */

void func_80090C68(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 temp_s0;
    D_80083160_t *temp_s3;
    u16 temp_v0;

    temp_s3 = &D_80083160;
    temp_s0 = ((S_80090C68_0 *)arg0)->unk_00;
    func_80090A74();
    if (temp_s0 == ((S_80090C68_0 *)arg0)->unk_00) {
        if (temp_s3->flags & 0x80) {
            func_80099754(arg1);
            func_8009550C(arg1);
            if (func_80094B0C(arg0 - 0x20) != 0) {
                func_80093D18(arg0, arg1, arg2);
                func_80090D20();
            }
        } else {
            temp_v0 = ((S_80090C68_0 *)arg0)->unk_0A - 1;
            ((S_80090C68_0 *)arg0)->unk_0A = temp_v0;
            if ((temp_v0 << 0x10) <= 0) {
                func_80093DD8(arg0, arg1, arg2);
            }
        }
    }
}

/* MECHANISM: Removing the inherited $s3 pin and ASM_KEEP lets cdk split &D_80083160
   as retail does: lui $v0 before the $s3 save, then addiu $s3,$v0 in the call slot.
   The natural held pointer still yields the exact 0x28 frame, save set, and CFG. */
