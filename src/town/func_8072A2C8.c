#include "common.h"
#include "m2c_compat.h"

typedef struct S_8072A2C8_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8072A2C8_0;   /* D_80016000 in func_8072A2C8 */

typedef struct S_8072A2C8_1 {
    u8 pad_00[0x270];
    M2C_UNK (*unk_270)(M2C_UNK *);
} S_8072A2C8_1;   /* ((S_8072A2C8_0 *)D_80016000)->unk_20 in func_8072A2C8 */




M2C_UNK func_80017684();                     /* extern */
extern S_8072A2C8_0 *D_80016000;
extern M2C_UNK D_80017AD0;


void func_8072A2C8(void) {
    ((S_8072A2C8_1 *)(D_80016000->unk_20))->unk_270(&D_80017AD0);
    func_80017684(0xBDB);
}
