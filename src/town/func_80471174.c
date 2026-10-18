#include "common.h"
#include "m2c_compat.h"

typedef struct S_80018174_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    s32 unk_24;
} S_80018174_0;   /* D_8001B318 in cache_value_at_offset_0x24 */


extern S_80018174_0 *D_8001B318;
extern s32 D_8001B31C;

/* Cache the value at offset 0x24 and return the value at offset 0x20. */
s32 cache_value_at_offset_0x24(void) {
    D_8001B31C = D_8001B318->unk_24;
    return D_8001B318->unk_20;
}
