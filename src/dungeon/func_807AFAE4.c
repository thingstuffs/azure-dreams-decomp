#include "common.h"
#include "m2c_compat.h"

typedef struct S_807AFAE4_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
    u8 pad_24[0x6];
    u16 unk_2A;
} S_807AFAE4_0;   /* temp_v0 in func_807AFAE4 */

typedef struct S_807AFAE4_1 {
    s32 unk_00;
    u8 pad_04[0x3E];
    u16 unk_42;
} S_807AFAE4_1;   /* arg0 in func_807AFAE4; pointer addresses record offset 0x18 */


/* cfail-repair: tf7-phase1-cache-v3 */
void *func_8003FD64();                  /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern M2C_UNK D_800F71A4;

void func_807AFAE4(void *arg0) {
    S_807AFAE4_0 *temp_v0;

    temp_v0 = func_8003FD64(2, arg0 - 0x20);
    if (temp_v0 != NULL) {
        temp_v0->unk_10 = &D_800F71A4;
        temp_v0->unk_20 = arg0;
        temp_v0->unk_08 = (s32) ((S_807AFAE4_1 *)((u8 *)arg0 - 0x18))->unk_00;
        temp_v0->unk_2A = (u16) ((S_807AFAE4_1 *)((u8 *)arg0 - 0x18))->unk_42;
        func_800A56E0(0x703);
    }
}
