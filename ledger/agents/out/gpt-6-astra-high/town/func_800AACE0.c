#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A8440_0 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_800A8440_0;   /* arg2 in func_800A8440 */

typedef struct S_800A8440_1 {
    u16 unk_00;
    u8 pad_02[0x2];
    u16 unk_04;
} S_800A8440_1;   /* arg0 in func_800A8440; pointer addresses record offset 0x2 */


M2C_UNK func_800478B8();                      /* extern */
extern s32 D_800814A0[];

/* Fades the primitive and sets completion flags when the countdown expires. */
void func_800A8440(void *record_fields, void *unused, S_800A8440_0 *primitive) {
    u16 ticks_left;
    u8 brightness;
    u8 unused_byte;

    func_800478B8(primitive);
    brightness = primitive->unk_0C;
    if (brightness != 0) {
        primitive->unk_0C = (brightness - 0x10);
        primitive->unk_0E = (brightness - 0x10);
        primitive->unk_0D = (brightness - 0x10);
    }
    ticks_left = ((S_800A8440_1 *)((u8 *)record_fields - 0x2))->unk_04 - 1;
    ((S_800A8440_1 *)((u8 *)record_fields - 0x2))->unk_04 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        ((S_800A8440_1 *)((u8 *)record_fields - 0x2))->unk_00 = (u16) (((S_800A8440_1 *)((u8 *)record_fields - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
