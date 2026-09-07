#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C838C_0 {
    u8 pad_00[0x80];
    void * unk_80;
} S_800C838C_0;   /* arg0 in func_800C838C */

typedef struct S_800C838C_1 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_800C838C_1;   /* ((S_800C838C_0 *)arg0)->unk_80 in func_800C838C */




M2C_UNK func_800C3050(); /* extern */
extern M2C_UNK D_800D6244;
extern M2C_UNK D_800D62D8;
extern M2C_UNK D_800D62E0;
extern M2C_UNK D_800D6308;
extern M2C_UNK D_800D630C;


/* Initialize the object with configuration 0xA and set its associated data pointer. */
void func_800C838C(S_800C838C_0 *object) {
    func_800C3050(object, 0xA, &D_800D6308, &D_800D630C, &D_800D62D8, &D_800D62E0);
    ((S_800C838C_1 *)(object->unk_80))->unk_04 = &D_800D6244;
}
