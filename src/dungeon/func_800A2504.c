#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_800A7CC4;

typedef struct S_800A7C64_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    s32 unk_10;
} S_800A7C64_0;   /* temp_v0 in func_800A7C64 */

typedef struct S_800A7C64_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_800A7C64_1;   /* temp_s0 in func_800A7C64 */

void func_800A7C64(void) {
    S_800A7C64_1 *temp_s0;
    S_800A7C64_0 *temp_v0;

    temp_v0 = func_8003FC64(2);
    if (temp_v0 != NULL) {
        temp_s0 = temp_v0->unk_0C;
        temp_v0->unk_10 = 0;
        func_8004491C(temp_v0, &D_800A7CC4);
        temp_s0->unk_0E = 0x80;
        temp_s0->unk_0D = 0x80;
        temp_s0->unk_0C = 0x80;
        temp_s0->unk_1E = 0x1000;
        temp_s0->unk_1C = 0x1000;
    }
}
