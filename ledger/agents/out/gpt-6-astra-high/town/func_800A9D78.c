#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94(); /* extern */
M2C_UNK func_8008F01C();     /* extern */
M2C_UNK func_8009B218(); /* extern */
extern M2C_UNK D_800D0690;
extern M2C_UNK D_800D0E04;
extern M2C_UNK D_800D6A58;

/* Initialize the object's sprite, scene data, and behavior. */
void func_800A74D8(s32 object, M2C_UNK scene, M2C_UNK sprite) {
    func_8003DB94(sprite, &D_800D0E04, 0);
    func_8008F01C(object, scene, &D_800D6A58);
    func_8009B218(object, scene, sprite, &D_800D0690);
}
