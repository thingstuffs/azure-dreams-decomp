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

/* Updates a timed rectangle effect, fading its color in and out and marking completion. */
void func_80025360(void *effect_arg, void *unused, void *sprite_arg)
{
    Work work;
    s16 next_frame;
    s16 state;
    s16 frame;
    void *sprite;
    s32 one;
    s16 rect_x;
    u16 flags;
    Rect *rect_template;

    sprite = sprite_arg;
    rect_template = &D_80024048;
    work.rect = *rect_template;
    D_80026428 = 1;
    state = ((S_80025360_0 *)effect_arg)->unk_00;
    if (state != 0) {
        if (state != 1) {
            ASM_SCHED_BARRIER();
            return;
        }
        goto draw_effect;
    }
    ((S_80025360_0 *)effect_arg)->unk_00 = (s16)((u16)((S_80025360_0 *)effect_arg)->unk_00 + 1);
    flags = ((S_80025360_1 *)sprite)->unk_14;
    flags &= 0xFF7F;
    ((S_80025360_1 *)sprite)->unk_14 = flags;
draw_effect:
    rect_x = 0x340;
    work.rect.x = rect_x;
    work.rect.y = 0x100;
    work.rect.w = 0x60;
    work.rect.h = 0x40;
    work.x = 0x370;
    work.y = 0x120;
    one = 1;
    func_80024A5C(((S_80025360_0 *)effect_arg)->unk_48, &work.rect, &work.x, one, one);
    frame = ((S_80025360_0 *)effect_arg)->unk_02;
    if (frame < 0x15) {
        ((S_80025360_1 *)sprite)->unk_0E = (s8)((frame << 7) / 20);
        ((S_80025360_1 *)sprite)->unk_0D = (s8)((((S_80025360_0 *)effect_arg)->unk_02 << 7) / 20);
        ((S_80025360_1 *)sprite)->unk_0C = (s8)((((S_80025360_0 *)effect_arg)->unk_02 << 7) / 20);
    }
    if (((S_80025360_0 *)effect_arg)->unk_02 >= 0x51) {
        ((S_80025360_1 *)sprite)->unk_0E = (s8)(((0x64 - ((S_80025360_0 *)effect_arg)->unk_02) << 7) / 20);
        ((S_80025360_1 *)sprite)->unk_0D = (s8)(((0x64 - ((S_80025360_0 *)effect_arg)->unk_02) << 7) / 20);
        ((S_80025360_1 *)sprite)->unk_0C = (s8)(((0x64 - ((S_80025360_0 *)effect_arg)->unk_02) << 7) / 20);
    }
    next_frame = (u16)((S_80025360_0 *)effect_arg)->unk_02 + 1;
    ((S_80025360_0 *)effect_arg)->unk_02 = next_frame;
    if (next_frame >= 0x65) {
        ((S_80025360_0 *)effect_arg)->unk_02 = 0;
        ((S_80025360_0 *)effect_arg)->unk_00 = (s16)((u16)((S_80025360_0 *)effect_arg)->unk_00 + 1);
        ((S_80025360_2 *)(((S_80025360_0 *)effect_arg)->unk_40))->unk_9C = one;
        (*(u16 *)((u8 *)effect_arg + -2)) = (u16)(((S_80025360_0_pre *)effect_arg)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
