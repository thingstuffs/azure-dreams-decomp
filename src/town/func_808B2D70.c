#include "common.h"
#include "m2c_compat.h"

typedef struct S_808B2D70_0 {
    u8 pad_00[0xE];
    u8 unk_0E;
} S_808B2D70_0;   /* temp_v1 in func_808B2D70 */

s32 func_808B2D70(s32 arg0) {
    S_808B2D70_0 *temp_v1;

    temp_v1 = *(void **)0xA0700F40;
    temp_v1->unk_0E = (u8) temp_v1->unk_0E;
    return arg0;
}
