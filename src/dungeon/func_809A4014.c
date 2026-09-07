#include "common.h"
#include "m2c_compat.h"

typedef struct S_80175814_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
    u8 pad_24[0x6];
    u16 unk_2A;
} S_80175814_0;   /* temp_v0 in func_80175814 */

typedef struct S_80175814_1 {
    s32 unk_00;
    u8 pad_04[0x3E];
    u16 unk_42;
} S_80175814_1;   /* arg0 in func_80175814; pointer addresses record offset 0x18 */


/* cfail-repair: tf7-phase1-cache-v3 */
void *func_8003FD64();                  /* extern */
s32 func_800A56E0();                     /* extern */
extern M2C_UNK D_801756D4;

void func_80175814(void *arg0) {
    S_80175814_0 *temp_v0;

    temp_v0 = func_8003FD64(0x202, arg0 - 0x20);
    if (temp_v0 != NULL) {
        temp_v0->unk_10 = &D_801756D4;
        temp_v0->unk_20 = arg0;
        temp_v0->unk_08 = (s32) ((S_80175814_1 *)((u8 *)arg0 - 0x18))->unk_00;
        temp_v0->unk_2A = (u16) ((S_80175814_1 *)((u8 *)arg0 - 0x18))->unk_42;
        func_800A56E0(0x703);
    }
}
