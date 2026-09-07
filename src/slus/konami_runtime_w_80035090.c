#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80035090_1 {
    u8 pad_00[0x4];
    void * unk_04;
    void * unk_08;
} S_80035090_1;   /* arg0 in func_80035090 */

typedef struct S_80035090_2 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80035090_2;   /* ((S_80035090_1 *)arg0)->unk_04 in func_80035090 */

typedef struct S_80035090_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80035090_3;   /* ((S_80035090_1 *)arg0)->unk_08 in func_80035090 */


typedef struct S_80035090_0 {
    u8 pad_00[0x4];
    void * unk_04;
    void * unk_08;
} S_80035090_0;   /* arg0 in func_80035090 */


void func_80035090(S_80035090_0 *arg0) {
    ((S_80035090_2 *)(((S_80035090_1 *)arg0)->unk_04))->unk_08 = (void *) arg0->unk_08;
    ((S_80035090_3 *)(((S_80035090_1 *)arg0)->unk_08))->unk_04 = (void *) arg0->unk_04;
}
