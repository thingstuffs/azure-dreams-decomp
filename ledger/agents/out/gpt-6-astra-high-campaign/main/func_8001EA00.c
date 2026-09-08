#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_804054E8();                      /* extern */
M2C_UNK func_80405900();                      /* extern */

typedef struct S_8001EA00_0 {
    u8 pad_00[0x9C];
    s32 unk_9C;
} S_8001EA00_0;   /* arg0 in func_8001EA00 */

/* Store the value and process embedded data when the object exists. */
void func_8001EA00(void *object, s32 value) {
    void *embedded_data;

    if (object != NULL) {
        ((S_8001EA00_0 *)object)->unk_9C = value;
        embedded_data = object + 0x20;
        func_80405900(embedded_data);
        func_804054E8(embedded_data);
    }
}
