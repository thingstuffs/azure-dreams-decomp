#include "common.h"
#include "m2c_compat.h"

typedef struct S_80814610_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_80814610_0;   /* arg1 in func_80814610 */

typedef struct S_80814610_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
} S_80814610_1;   /* arg2 in func_80814610 */

typedef struct S_80814610_2_pre {
    u16 unk_00;
} S_80814610_2_pre;   /* the 0x2 bytes before arg0 in func_80814610, addressed as arg0[-1] */


M2C_UNK func_8003EA54();                 /* extern */
extern s32 D_80084D5C;

/* Updates motion and brightness, processes the visual, and marks flagged objects. */
void func_80814610(void *object, void *motion, void *visual) {
    s32 velocity;
    u8 brightness;

    velocity = ((S_80814610_0 *)motion)->unk_14;
    if (velocity != 0) {
        ((S_80814610_0 *)motion)->unk_08 = (s32) (((S_80814610_0 *)motion)->unk_08 + velocity);
        ((S_80814610_0 *)motion)->unk_14 = (s32) (((S_80814610_0 *)motion)->unk_14 + 0x18000);
        brightness = ((S_80814610_1 *)visual)->unk_0E - 0x20;
        ((S_80814610_1 *)visual)->unk_0E = brightness;
        ((S_80814610_1 *)visual)->unk_0D = brightness;
        ((S_80814610_1 *)visual)->unk_0C = brightness;
    }
    func_8003EA54(visual);
    if (((S_80814610_1 *)visual)->unk_14 & 0x6000) {
        (*(u16 *)((u8 *)object + -2)) = (u16) (((S_80814610_2_pre *)object)[-1].unk_00 | 0x8000);
        D_80084D5C |= 0x8000;
    }
}
