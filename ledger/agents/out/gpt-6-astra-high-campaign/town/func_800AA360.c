#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A7AC0_0 {
    M2C_UNK * unk_00;
} S_800A7AC0_0;   /* arg0 in func_800A7AC0; pointer addresses record offset 0x10 */


M2C_UNK func_80033CD8();           /* extern */
M2C_UNK func_800C2CB0(); /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800A7B14;
extern M2C_UNK D_800F838C;

/* Initialize the object with its state, resource data, and callback. */
void func_800A7AC0(void *object, M2C_UNK unused, M2C_UNK context) {
    ((S_800A7AC0_0 *)((u8 *)object - 0x10))->unk_00 = &D_800A7B14;
    func_800C2CB0(object, context, &D_800F838C, 0);
    func_80033CD8(object, &D_80045340);
}
