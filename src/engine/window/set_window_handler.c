#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80035AAC_0 {
    u8 pad_00[0x68];
    s32 * unk_68;
} S_80035AAC_0;   /* arg0 in set_window_handler */


extern M2C_UNK func_80035AF8;

/* Set the object's function pointer to func_80035AF8. */
void set_window_handler(S_80035AAC_0 *object) {
    object->unk_68 = &func_80035AF8;
}
