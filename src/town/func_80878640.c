#include "common.h"
#include "m2c_compat.h"

typedef struct S_80702640_0 {
    u8 pad_00[0x60];
    M2C_UNK (*unk_60)(M2C_UNK);
} S_80702640_0;   /* *(void **)0x807030B8 in func_80702640 */


void func_80702640(void) {
    ((S_80702640_0 *)(*(void **)0x807030B8))->unk_60(0);
}
