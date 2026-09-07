#include "common.h"
#include "m2c_compat.h"

typedef struct S_800ABB20_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800ABB20_0;   /* arg1 in func_800ABB20 */

typedef struct S_800ABB20_1 {
    u16 unk_00;
    u8 pad_02[0x2];
    u16 unk_04;
    s16 unk_06;
} S_800ABB20_1;   /* arg0 in func_800ABB20; pointer addresses record offset 0x2 */

typedef struct S_800ABB20_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_800ABB20_2;   /* arg2 in func_800ABB20 */


extern void func_800478B8(void *arg0);
extern s32 D_800814A0[3];

/* Update effect motion, fade its brightness, and mark it expired when its timer ends. */
void func_800ABB20(void *effect_record, S_800ABB20_0 *motion, S_800ABB20_2 *primitive) {
    u16 ticks_left;
    u8 brightness;

    motion->unk_14 = (s32) (motion->unk_14 + (((S_800ABB20_1 *)((u8 *)effect_record - 0x2))->unk_06 << 0xB));
    ((S_800ABB20_1 *)((u8 *)effect_record - 0x2))->unk_06 = (s16) ((u16) ((S_800ABB20_1 *)((u8 *)effect_record - 0x2))->unk_06 + 1);
    motion->unk_00 = (s32) (motion->unk_00 + motion->unk_0C);
    motion->unk_04 = (s32) (motion->unk_04 + motion->unk_10);
    motion->unk_08 = (s32) (motion->unk_08 + motion->unk_14);
    func_800478B8(primitive);
    brightness = primitive->unk_0C;
    if (brightness != 0) {
        brightness = brightness - 0x10;
        primitive->unk_0C = brightness;
        primitive->unk_0E = brightness;
        primitive->unk_0D = brightness;
    }
    ticks_left = ((S_800ABB20_1 *)((u8 *)effect_record - 0x2))->unk_04 - 1;
    ((S_800ABB20_1 *)((u8 *)effect_record - 0x2))->unk_04 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        ((S_800ABB20_1 *)((u8 *)effect_record - 0x2))->unk_00 = (u16) (((S_800ABB20_1 *)((u8 *)effect_record - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] |= 0x8000;
    }
}
