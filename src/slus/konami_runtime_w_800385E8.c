#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_800385E8_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0x70];
    s8 unk_84;
} S_800385E8_0;   /* arg0 in func_800385E8 */


M2C_UNK SD_Call();                     /* extern */
extern M2C_UNK func_80038A10;

/* When the object's flag is set, call SD_Call and update its handler. */
void func_800385E8(S_800385E8_0 *object) {
    if (object->unk_84 != 0) {
        SD_Call(0xB4);
        object->unk_10 = &func_80038A10;
    }
}
