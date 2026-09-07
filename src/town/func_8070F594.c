#include "common.h"
#include "m2c_compat.h"

typedef struct S_8070F594_0 {
    u8 pad_00[0x1C];
    void * unk_1C;
    void * unk_20;
} S_8070F594_0;   /* D_80016000 in func_8070F594 */

typedef struct S_8070F594_1 {
    u8 pad_00[0x40];
    M2C_UNK * unk_40;
} S_8070F594_1;   /* ((S_8070F594_0 *)D_80016000)->unk_1C in func_8070F594 */

typedef struct S_8070F594_2 {
    u8 pad_00[0x2F8];
    M2C_UNK (*unk_2F8)(M2C_UNK, M2C_UNK);
} S_8070F594_2;   /* ((S_8070F594_0 *)D_80016000)->unk_20 in func_8070F594 */




M2C_UNK func_80016CC4();                            /* extern */
M2C_UNK func_8001A5CC();                     /* extern */
extern S_8070F594_0 *D_80016000;
extern M2C_UNK D_8001D9D4;


s32 func_8070F594(void) {
    func_80016CC4();
    func_8001A5CC(0x935);
    func_8001A5CC(0x936);
    ((S_8070F594_1 *)(D_80016000->unk_1C))->unk_40 = &D_8001D9D4;
    ((S_8070F594_2 *)(D_80016000->unk_20))->unk_2F8(0xE, 0x200);
    return 0;
}
