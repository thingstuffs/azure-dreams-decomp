#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80035068_2 {
    u8 pad_00[0x10];
    void * unk_10;
} S_80035068_2;   /* arg0 in func_80035068 */

typedef struct S_80035068_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80035068_3;   /* ((S_80035068_2 *)arg0)->unk_10 in func_80035068 */


typedef struct S_80035068_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    void * unk_08;
} S_80035068_0;   /* arg1 in func_80035068 */

typedef struct S_80035068_1 {
    u8 pad_00[0x10];
    void * unk_10;
} S_80035068_1;   /* arg0 in func_80035068 */


void func_80035068(void *arg0, S_80035068_0 *arg1) {
    arg1->unk_04 = (s32) (arg0 + 8);
    arg1->unk_08 = (void *) ((S_80035068_1 *)arg0)->unk_10;
    ((S_80035068_3 *)(((S_80035068_2 *)arg0)->unk_10))->unk_04 = arg1;
    ((S_80035068_1 *)arg0)->unk_10 = arg1;
}
