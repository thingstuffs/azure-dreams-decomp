#include "common.h"

typedef struct S_80025360_0_pre {
    u16 unk_00;
} S_80025360_0_pre;   /* the 0x2 bytes before obj in func_80025360, addressed as obj[-1] */

typedef struct S_80025360_0 {
    s16 unk_00;
    s16 unk_02;
    u8 pad_04[0x3C];
    void * unk_40;
    u8 pad_44[0x4];
    s32 unk_48;
} S_80025360_0;   /* obj in func_80025360 */

typedef struct S_80025360_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
} S_80025360_1;   /* dest in func_80025360 */

typedef struct S_80025360_2 {
    u8 pad_00[0x9C];
    s16 unk_9C;
} S_80025360_2;   /* ((S_80025360_0 *)obj)->unk_40 in func_80025360 */



extern s32 func_80024A5C();
extern void func_80025598() __attribute__((noreturn));
typedef struct Rect {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect;

typedef struct Work {
    Rect rect;
    s16 x;
    s16 y;
} Work;

extern Rect D_80024048;
extern s16 D_80026428;
extern s32 D_800814A0;

void func_80025360(void *arg0, void *arg1, void *arg2)
{
    Work sp18;
    s16 temp_v0;
    s16 temp_v1;
    s16 temp_v1_2;
    void *obj;
    void *dest;
    s32 one;
    register s16 rect_x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register u16 mask ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    Rect *data;

    obj = arg0;
    dest = arg2;
    data = &D_80024048;
    sp18.rect = *data;
    ASM_KEEP(obj);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(dest);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    D_80026428 = 1;
    temp_v1 = ((S_80025360_0 *)obj)->unk_00;
    if (temp_v1 != 0) {
        if (temp_v1 != 1) {
            func_80025598();
            return;
        }
        rect_x = 0x340;
        goto block_5;
    }
    ((S_80025360_0 *)obj)->unk_00 = (s16)((u16)((S_80025360_0 *)obj)->unk_00 + 1);
    mask = ((S_80025360_1 *)dest)->unk_14;
    mask &= 0xFF7F;
    ((S_80025360_1 *)dest)->unk_14 = mask;
    rect_x = 0x340;
    ASM_KEEP(rect_x);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
block_5:
    sp18.rect.x = rect_x;
    sp18.rect.y = 0x100;
    sp18.rect.w = 0x60;
    sp18.rect.h = 0x40;
    sp18.x = 0x370;
    sp18.y = 0x120;
    one = 1;
    func_80024A5C(((S_80025360_0 *)obj)->unk_48, &sp18.rect, &sp18.x, one, one);
    temp_v1_2 = ((S_80025360_0 *)obj)->unk_02;
    if (temp_v1_2 < 0x15) {
        ((S_80025360_1 *)dest)->unk_0E = (s8)((temp_v1_2 << 7) / 20);
        ((S_80025360_1 *)dest)->unk_0D = (s8)((((S_80025360_0 *)obj)->unk_02 << 7) / 20);
        ((S_80025360_1 *)dest)->unk_0C = (s8)((((S_80025360_0 *)obj)->unk_02 << 7) / 20);
    }
    if (((S_80025360_0 *)obj)->unk_02 >= 0x51) {
        ((S_80025360_1 *)dest)->unk_0E = (s8)(((0x64 - ((S_80025360_0 *)obj)->unk_02) << 7) / 20);
        ((S_80025360_1 *)dest)->unk_0D = (s8)(((0x64 - ((S_80025360_0 *)obj)->unk_02) << 7) / 20);
        ((S_80025360_1 *)dest)->unk_0C = (s8)(((0x64 - ((S_80025360_0 *)obj)->unk_02) << 7) / 20);
    }
    temp_v0 = (u16)((S_80025360_0 *)obj)->unk_02 + 1;
    ((S_80025360_0 *)obj)->unk_02 = temp_v0;
    if (temp_v0 >= 0x65) {
        ((S_80025360_0 *)obj)->unk_02 = 0;
        ((S_80025360_0 *)obj)->unk_00 = (s16)((u16)((S_80025360_0 *)obj)->unk_00 + 1);
        ((S_80025360_2 *)(((S_80025360_0 *)obj)->unk_40))->unk_9C = one;
        (*(u16 *)((u8 *)obj + -2)) = (u16)(((S_80025360_0_pre *)obj)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: A 16-byte Work aggregate plus held s0/s1/s2 roles fixes the 0x38 frame and unaligned copy.
   Rerouting to 2.7.2-cdk-G0 colors that copy a2/v1/a0; the zero-arg noreturn call becomes the retail tail j.
   A fixed-v0 rect_x/mask with a state-0-only ASM_KEEP yields both 0x340 loads and the single joined store. */
