#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"

typedef struct S_806D45CC_2 {
    u8 pad_00[0x4];
    s8 unk_04;
} S_806D45CC_2;   /* ((D_80016000->unk_08.at00_s32.v * 8) + D_80016000->unk_40.as_s32) in func_806D45CC */


typedef struct S_806D45CC_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_806D45CC_0;   /* arg0 in func_806D45CC */



M2C_UNK func_800176B8();             /* extern */
M2C_UNK func_80018594();                         /* extern */
extern Rec_D_80016000 *D_80016000;

/* Processes the object field, clears the current entry flag, and forwards the object and context. */
void func_806D45CC(S_806D45CC_0 *object, M2C_UNK context) {
    func_80018594(object->unk_18);
    ((S_806D45CC_2 *)(((D_80016000->unk_08.at00_s32.v * 8) + D_80016000->unk_40.as_s32)))->unk_04 = 0;
    func_800176B8(object, context);
}
