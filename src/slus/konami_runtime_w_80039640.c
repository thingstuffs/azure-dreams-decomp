#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80039640_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x5C];
    void * unk_7C;
} S_80039640_0;   /* arg0 in func_80039640 */

typedef struct S_80039640_1 {
    s32 unk_00;
} S_80039640_1;   /* temp_v1 in func_80039640; pointer addresses record offset 0x4 */


void func_80039640(S_80039640_0 *arg0) {
    void *temp_v1;

    temp_v1 = arg0->unk_7C;
    arg0->unk_7C = (void *) (temp_v1 - 4);
    arg0->unk_1C = (s32) ((S_80039640_1 *)((u8 *)temp_v1 - 0x4))->unk_00;
}
