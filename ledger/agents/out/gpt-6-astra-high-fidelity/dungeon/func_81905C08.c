#include "common.h"

typedef struct {
    u8 bytes[0x20];
} LocalPoints;

typedef struct {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
} Box __attribute__((packed));

typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
} PackedVector __attribute__((packed));

typedef struct {
    u16 x;
    u16 y;
} Point __attribute__((packed));

extern void func_80024B6C(void *, Box *, Point *, s32, s32);
extern s32 func_80067014(s32);
extern void func_800672D8(Box *, u8 *);
extern void func_8006733C(Box *, u8 *);
extern void func_800B8FC8(void *, Box *, Point *, s32, s32);
extern LocalPoints D_80024004;
extern PackedVector D_8002400C;
extern s16 D_800267B8;
extern u8 D_80026820[];
extern s32 D_800814A0;

void func_80025408(void *arg0, void *arg1, void *arg2) {
    Box rect0;
    Box rect1;
    Point center;
    s32 state;
    s32 outer;
    s32 middle;
    s32 row;
    s32 row_value;
    s32 column;
    register u16 sentinel ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s16 value;
    s32 index;
    register s32 one ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 width ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    u16 *cursor;
    register Point *center_ptr ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    void *effect;
    u8 *buffer;
    u8 *copy_page;
    register Box *source ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    effect = arg2;
    source = (Box *)(void *)&D_80024004;
    rect0 = *source;
#ifdef NON_MATCHING
    source = (Box *)(void *)&D_8002400C;
#else
    copy_page = (u8 *)0x80020000;
    ASM_KEEP_NV(copy_page);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    source = (Box *)(copy_page + 0x400C);
    ASM_KEEP_NV(source);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
#endif
    rect1 = *source;
    ASM_USE2_NV(source, copy_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    state = *(s16 *)arg0;
    D_800267B8 = 1;
    if (state != 0) {
        if (state == 1) {
            goto block_16;
        }
        goto block_217;
    }

    outer = 0;
    buffer = (u8 *)0x80020000;
    ASM_KEEP_NV(buffer);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    sentinel = -1;
    row = 0x340;
loop_5:
    middle = 0;
    row_value = row;
    column = 0x154;
loop_6:
    rect1.w = 0x18;
    rect1.x = row_value;
    rect1.y = column;
    rect1.h = 0x15;
    func_8006733C(&rect1, buffer + 0x6820);
    do {
    } while (func_80067014(1) != 0);
    cursor = (u16 *)(buffer + 0x6820);
    index = 0;
loop_9:
    if (*cursor == 0) {
        *cursor = sentinel;
    } else {
        *cursor = 0;
    }
    index += 1;
    cursor += 1;
    if (index >= 0x1f8) {
        func_800672D8(&rect1, buffer + 0x6820);
        middle += 1;
        column += 0x15;
        if (middle >= 4) {
            outer += 1;
            row += 0x18;
            if (outer >= 4) {
                *(s16 *)arg0 = (u16)*(s16 *)arg0 + 1;
                *(u16 *)((u8 *)effect + 0x14) &= 0xff7f;
block_16: {
                Box *call_rect;
                register Point *call_center ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

                call_rect = &rect1;
                center_ptr = &center;
                call_center = center_ptr;
                row = 0x340;
                buffer = (u8 *)0x100;
                ASM_KEEP_NV(call_rect);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                ASM_KEEP_NV(call_center);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                ASM_KEEP_NV(row);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
                ASM_KEEP_NV(buffer);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                width = 0x60;
                rect1.w = width;
                rect1.x = row;
                rect1.y = (s32)buffer;
                rect1.h = 0x54;
                center.x = 0x370;
                center.y = 0x148;
                one = 1;
                func_800B8FC8(*(void **)((u8 *)arg0 + 0x44), call_rect, call_center, 0, one);
}
{
                Box *call_rect;
                register Point *call_center ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

                call_rect = &rect0;
                call_center = center_ptr;
                ASM_KEEP_NV(call_rect);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                ASM_KEEP_NV(call_center);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                width = 0x60;
                rect0.w = width;
                rect0.x = row;
                rect0.y = (s32)buffer;
                rect0.h = 0x54;
                center.x = 0x370;
                center.y = 0x12a;
                func_80024B6C(*(void **)((u8 *)arg0 + 0x48), call_rect, call_center, one, one);
}
                value = *(s16 *)((u8 *)arg0 + 2);
                if (value < 0x15) {
                    *(s8 *)((u8 *)effect + 0xe) = (value << 7) / 20;
                    *(s8 *)((u8 *)effect + 0xd) = (*(s16 *)((u8 *)arg0 + 2) << 7) / 20;
                    *(s8 *)((u8 *)effect + 0xc) = (*(s16 *)((u8 *)arg0 + 2) << 7) / 20;
                }
                if (*(s16 *)((u8 *)arg0 + 2) >= 0x51) {
                    *(s8 *)((u8 *)effect + 0xe) = ((0x64 - *(s16 *)((u8 *)arg0 + 2)) << 7) / 20;
                    *(s8 *)((u8 *)effect + 0xd) = ((0x64 - *(s16 *)((u8 *)arg0 + 2)) << 7) / 20;
                    *(s8 *)((u8 *)effect + 0xc) = ((0x64 - *(s16 *)((u8 *)arg0 + 2)) << 7) / 20;
                }
                value = (u16)*(s16 *)((u8 *)arg0 + 2) + 1;
                *(s16 *)((u8 *)arg0 + 2) = value;
                if (value >= 0x65) {
                    *(s16 *)((u8 *)arg0 + 2) = 0;
                    *(s16 *)arg0 = (u16)*(s16 *)arg0 + 1;
                    *(s16 *)(*(u8 **)((u8 *)arg0 + 0x40) + 0x9c) = one;
                    *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
                    D_800814A0 |= 0x8000;
                }
block_217:
                if ((u32)(*(u8 *)(*(u8 **)((u8 *)arg0 + 0x3c) + 0x13) - 0x33) < 4U) {
                    *(u16 *)((u8 *)effect + 0x14) |= 0x80;
                }
                return;
            }
            goto loop_5;
        }
        goto loop_6;
    }
    goto loop_9;
}
