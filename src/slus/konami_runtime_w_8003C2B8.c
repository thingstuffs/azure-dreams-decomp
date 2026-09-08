#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "records/Rec_D_80082D58.h"

typedef struct S_8003C2B8_0_pre {
    s32 unk_00;
    u8 pad_04[0x10];
} S_8003C2B8_0_pre;   /* the 0x14 bytes before &D_80082D58 in func_8003C2B8, addressed as &D_80082D58[-1] */



M2C_UNK func_80033D08();                   /* extern */
M2C_UNK func_8003C0C0();              /* extern */
extern M2C_UNK D_80082D58;

/* Clears D_80082D58 and processes it using the preceding block's value. */
void func_8003C2B8(void) {
    ((Rec_D_80082D58 *)(&D_80082D58))->unk_00 = 0;
    func_8003C0C0(&D_80082D58, ((S_8003C2B8_0_pre *)(&D_80082D58))[-1].unk_00);
    func_80033D08(&D_80082D58);
}
