#include "common.h"

typedef struct S_8001B960_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8001B960_0;   /* arg0 in func_8001B960 */

typedef struct S_8001B960_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8001B960_1;   /* (arg1 * 0x10) + ((S_8001B960_0 *)arg0)->unk_10 in func_8001B960 */



extern u8 *D_8001E950;
extern s32 func_8001A73C(void);

s32 func_8001B960(S_8001B960_0 *arg0, s32 arg1) {
    if (D_8001E950[5] == 0) {
        ((S_8001B960_1 *)((arg1 * 0x10) + arg0->unk_10))->unk_08 =
            func_8001A73C();
        return 0;
    }
    return 1;
}
