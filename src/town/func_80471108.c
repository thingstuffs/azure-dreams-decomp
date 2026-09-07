#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"

typedef struct S_80018108_1 {
    u8 pad_00[0x68];
    s32 (*unk_68)(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *);
} S_80018108_1;   /* D_80016000->unk_20 in func_80018108 */




M2C_UNK func_80018824();          /* extern */
M2C_UNK func_80018914();                   /* extern */
extern Rec_D_80016000 *D_80016000;
extern M2C_UNK D_8001B218;
extern s32 D_8001B318;

void func_80018108(void) {
    func_80018824(&D_8001B218, 0x100);
    func_80018914(&D_8001B218);
    D_8001B318 = ((S_80018108_1 *)(D_80016000->unk_20))->unk_68(0, 1, 1, &D_8001B218);
}
