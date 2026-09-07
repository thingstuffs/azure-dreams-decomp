#include "common.h"
#include "m2c_compat.h"

typedef struct S_80027F34_1 {
    u8 pad_00[0x80];
    void * unk_80;
} S_80027F34_1;   /* arg0 in func_80027F34 */

typedef struct S_80027F34_2 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_80027F34_2;   /* ((S_80027F34_1 *)arg0)->unk_80 in func_80027F34 */


typedef struct S_80027F34_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
    s32 unk_10;
    s32 unk_14;
} S_80027F34_0;   /* arg0 in func_80027F34; pointer addresses record offset 0x10 */


M2C_UNK func_80027A20();              /* extern */
extern M2C_UNK D_80027A68;

void func_80027F34(void *arg0) {
    s32 temp_v0;

    ((S_80027F34_2 *)(((S_80027F34_1 *)arg0)->unk_80))->unk_02 = (s16) (0x400 - ((s32) (((S_80027F34_0 *)((u8 *)arg0 - 0x10))->unk_10 << 0xA) / (s32) ((S_80027F34_0 *)((u8 *)arg0 - 0x10))->unk_14));
    temp_v0 = ((S_80027F34_0 *)((u8 *)arg0 - 0x10))->unk_10 + 1;
    ((S_80027F34_0 *)((u8 *)arg0 - 0x10))->unk_10 = temp_v0;
    if (((S_80027F34_0 *)((u8 *)arg0 - 0x10))->unk_14 < temp_v0) {
        ((S_80027F34_0 *)((u8 *)arg0 - 0x10))->unk_10 = 0;
        ((S_80027F34_0 *)((u8 *)arg0 - 0x10))->unk_00 = &D_80027A68;
    }
    func_80027A20(arg0, arg0);
}
