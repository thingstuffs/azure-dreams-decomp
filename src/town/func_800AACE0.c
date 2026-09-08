#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_800A8440_1 {
    u16 unk_00;
    u8 pad_02[0x2];
    u16 unk_04;
} S_800A8440_1;   /* arg0 in func_800A8440; pointer addresses record offset 0x2 */


M2C_UNK func_800478B8();                      /* extern */
extern s32 D_800814A0[];

/* Fades the primitive and sets completion flags when the countdown expires. */
void func_800A8440(void *record_fields, void *unused, Rec_D_80082E80 *primitive) {
    u16 ticks_left;
    u8 brightness;
    u8 unused_byte;

    func_800478B8(primitive);
    brightness = primitive->unk_0C.at00_u8.v;
    if (brightness != 0) {
        primitive->unk_0C.at00_u8.v = (brightness - 0x10);
        primitive->unk_0C.at02_u8.v = (brightness - 0x10);
        primitive->unk_0C.at01_u8.v = (brightness - 0x10);
    }
    ticks_left = ((S_800A8440_1 *)((u8 *)record_fields - 0x2))->unk_04 - 1;
    ((S_800A8440_1 *)((u8 *)record_fields - 0x2))->unk_04 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        ((S_800A8440_1 *)((u8 *)record_fields - 0x2))->unk_00 = (u16) (((S_800A8440_1 *)((u8 *)record_fields - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
