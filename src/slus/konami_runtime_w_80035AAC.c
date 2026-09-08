#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80035AAC_0 {
    u8 pad_00[0x68];
    M2C_UNK * unk_68;
} S_80035AAC_0;   /* arg0 in func_80035AAC */


extern M2C_UNK func_80035AF8;

/* Set the object's function pointer to func_80035AF8. */
void func_80035AAC(S_80035AAC_0 *object) {
    object->unk_68 = &func_80035AF8;
}
