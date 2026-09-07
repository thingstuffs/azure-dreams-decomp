/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001CF9C_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8001CF9C_1;   /* ((arg1 * 0x10) + arg0->unk_10) in func_8001CF9C */




extern struct {
    u8 *ptr;
    u8 pad[8];
} D_8001E950;
extern M2C_UNK D_8001F0D8;
extern M2C_UNK D_8001F18C;

typedef struct S_8001CF9C_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8001CF9C_0;   /* arg0 in func_8001CF9C */

s32 func_8001CF9C(S_8001CF9C_0 *arg0, s32 arg1) {
    M2C_UNK *sp[2];

    do { sp[0] = &D_8001F0D8; } while (0);
    sp[1] = &D_8001F18C;
    ((S_8001CF9C_1 *)(((arg1 * 0x10) + arg0->unk_10)))->unk_08 = sp[D_8001E950.ptr[1]];
    return 0;
}
