#include "common.h"
#include "m2c_compat.h"

typedef struct S_80028320_1 {
    u8 pad_00[0x80];
    void * unk_80;
} S_80028320_1;   /* temp_s0 in func_80028320 */

typedef struct S_80028320_2 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_80028320_2;   /* ((S_80028320_1 *)temp_s0)->unk_80 in func_80028320 */


typedef struct S_80028320_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x14];
    s32 unk_18;
    u8 pad_1C[0x8];
    s32 unk_24;
    u8 pad_28[0x10];
    s32 unk_38;
    u8 pad_3C[0xC];
    s32 unk_48;
    u8 pad_4C[0x10];
    s32 unk_5C;
    u8 pad_60[0x34];
    s32 unk_94;
    s32 unk_98;
} S_80028320_0;   /* temp_s0 in func_80028320; pointer addresses record offset 0x10 */


M2C_UNK func_80027454();      /* extern */
s32 func_80027FA4();                             /* extern */
M2C_UNK func_80027FF4();                    /* extern */
M2C_UNK func_80028534();                         /* extern */
M2C_UNK func_80028648();                         /* extern */
extern M2C_UNK D_80027D7C;

/* Reset object state, store the initial value, and install its handler. */
void func_80028320(s32 object_addr, s32 initial_value) {
    void *state;

    state = object_addr + 0x20;
    ((S_80028320_0 *)((u8 *)state - 0x10))->unk_24 = 0;
    ((S_80028320_2 *)(((S_80028320_1 *)state)->unk_80))->unk_02 = 0;
    ((S_80028320_0 *)((u8 *)state - 0x10))->unk_48 = initial_value;
    ((S_80028320_0 *)((u8 *)state - 0x10))->unk_18 = 0;
    func_80027454(object_addr + 0x58, ((S_80028320_0 *)((u8 *)state - 0x10))->unk_24, 0, ((S_80028320_0 *)((u8 *)state - 0x10))->unk_38);
    func_80027FF4(((S_80028320_0 *)((u8 *)state - 0x10))->unk_5C, ((S_80028320_0 *)((u8 *)state - 0x10))->unk_24);
    ((S_80028320_0 *)((u8 *)state - 0x10))->unk_94 = func_80027FA4(((S_80028320_0 *)((u8 *)state - 0x10))->unk_98);
    func_80028534(((S_80028320_0 *)((u8 *)state - 0x10))->unk_98);
    func_80028648(object_addr);
    ((S_80028320_0 *)((u8 *)state - 0x10))->unk_00 = &D_80027D7C;
}
