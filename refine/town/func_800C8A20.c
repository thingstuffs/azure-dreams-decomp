#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94(); /* extern */
M2C_UNK func_8008F01C();  /* extern */
M2C_UNK func_8009B218(); /* extern */
extern M2C_UNK D_800D0678;
extern M2C_UNK D_800D0690;
extern M2C_UNK D_800ED15C;

typedef struct S_800C6180_0 {
    u8 pad_00[0x4C];
    s8 unk_4C;
    s8 unk_4D;
} S_800C6180_0;   /* arg0 in func_800C6180 */

/* Initialize the object's sprite and behavior, then set its state bytes. */
void func_800C6180(S_800C6180_0 *object, M2C_UNK context, M2C_UNK sprite) {
    func_8003DB94(sprite, &D_800ED15C, 0);
    func_8008F01C(object, context, &D_800D0678);
    func_8009B218(object, context, sprite, &D_800D0690);
    object->unk_4D = 0xD;
    object->unk_4C = 7;
}
