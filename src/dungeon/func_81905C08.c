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
extern void func_80025524() __attribute__((noreturn));
extern void func_8002576C() __attribute__((noreturn));
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
    register u16 sentinel ASM_REG("$23");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    s16 value;
    s32 index;
    register s32 one ASM_REG("$21");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 width ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    u16 *cursor;
    register Point *center_ptr ASM_REG("$20");   /* MATCH pin: keeps a constant in a register as retail does */
    void *effect;
    u8 *buffer;
    u8 *copy_page;
    register Box *source ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */

    effect = arg2;
    source = (Box *)(void *)&D_80024004;
    rect0 = *source;
#ifdef NON_MATCHING
    source = (Box *)(void *)&D_8002400C;
#else
    copy_page = (u8 *)0x80020000;
    ASM_KEEP_NV(copy_page);   /* MATCH pin: retail delay-slot fill depends on it */
    source = (Box *)(copy_page + 0x400C);
    ASM_KEEP_NV(source);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
#endif
    rect1 = *source;
    ASM_USE2_NV(source, copy_page);   /* MATCH pin: load-bearing for the whole function shape */
    state = *(s16 *)arg0;
    D_800267B8 = 1;
    if (state != 0) {
        if (state != 1) {
            return func_8002576C();
        }
        goto block_16;
    }

    outer = 0;
    buffer = (u8 *)0x80020000;
    ASM_KEEP_NV(buffer);   /* MATCH pin: retail register colouring depends on it */
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
        return func_80025524(index);
    }
    *cursor = 0;
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
                register Point *call_center ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */

                call_rect = &rect1;
                center_ptr = &center;
                call_center = center_ptr;
                row = 0x340;
                buffer = (u8 *)0x100;
                ASM_KEEP_NV(call_rect);   /* MATCH pin: keeps a statement from moving across a call/branch */
                ASM_KEEP_NV(call_center);   /* MATCH pin: retail schedule: same instructions, different order without it */
                ASM_KEEP_NV(row);   /* MATCH pin: keeps a constant in a register as retail does */
                ASM_KEEP_NV(buffer);   /* MATCH pin: retail register colouring depends on it */
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
                register Point *call_center ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */

                call_rect = &rect0;
                call_center = center_ptr;
                ASM_KEEP_NV(call_rect);   /* MATCH pin: keeps a statement from moving across a call/branch */
                ASM_KEEP_NV(call_center);   /* MATCH pin: retail schedule: same instructions, different order without it */
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
