#include "common.h"


extern void func_800672D8();

extern u8 D_80024640[];
extern u8 D_80024660[];
extern u8 D_80024680[];
extern u8 D_800246C0[];
extern s32 D_800814A0[];


typedef struct S_80023BCC_0_pre {
    u16 unk_00;
} S_80023BCC_0_pre;   /* the 0x2 bytes before arg0 in func_80023BCC, addressed as arg0[-1] */

typedef struct S_80023BCC_0 {
    u8 pad_00[0x5C];
    union { s16 s; u16 u; } unk_5C;   /* accessed as both */
    u16 unk_5E;
} S_80023BCC_0;   /* arg0 in func_80023BCC */

/* Updates image-strip animation and sets completion flags when its timer expires. */
void func_80023BCC(void *anim)
{
    s16 rect[4];
    s16 phase;
    u8 *image;
    u16 timer;

    rect[2] = 0x10;
    rect[3] = 1;

    switch (((S_80023BCC_0 *)anim)->unk_5C.s) {
    case 0:
        ((S_80023BCC_0 *)anim)->unk_5E = 0x78;
        ((S_80023BCC_0 *)anim)->unk_5C.u++;
        break;
    case 1:
        break;
    default:
        return;
    }

    rect[1] = 0x1D0;
    if ((((S_80023BCC_0 *)anim)->unk_5E >> 1) & 1) {
        image = D_80024660;
        rect[0] = 0x40;
        func_800672D8(rect, image);
        rect[0] = 0x50;
        func_800672D8(rect, image - 0x20);
    } else {
        image = D_80024640;
        rect[0] = 0x40;
        func_800672D8(rect, image);
        rect[0] = 0x50;
        func_800672D8(rect, image + 0x20);
    }

    rect[1] = 0x1F8;
    phase = (s16)((S_80023BCC_0 *)anim)->unk_5E % 3;
    switch (phase) {
    case 0:
        image = D_800246C0;
        rect[0] = 0xC0;
        func_800672D8(rect, image);
        rect[0] = 0xD0;
        rect[2] = 0x20;
        func_800672D8(rect, image - 0x40);
        break;
    case 1:
        image = (u8 *)0x80020000;
        ASM_KEEP(image);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        image += 0x4680;
        rect[0] = 0xE0;
        func_800672D8(rect, image);
        rect[0] = 0xC0;
        rect[2] = 0x20;
        func_800672D8(rect, image + 0x20);
        break;
    case 2:
        rect[0] = 0xC0;
        rect[2] = 0x30;
        func_800672D8(rect, D_80024680);
        break;
    default:
        break;
    }

    timer = ((S_80023BCC_0 *)anim)->unk_5E - 1;
    ((S_80023BCC_0 *)anim)->unk_5E = timer;
    if ((s16)timer <= 0) {
        u8 *page = (u8 *)0x80080000;
        ((S_80023BCC_0_pre *)anim)[-1].unk_00 |= 0x8000;
        ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        (*(s32 *)(page + 0x14A0)) |= 0x8000;
    }
}
