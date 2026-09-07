#include "common.h"

typedef struct S_800BB218_0 {
    u16 unk_00;
    u16 unk_02;
    u32 unk_04;
    u8 pad_08[0x8];
    u8 * unk_10;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
} S_800BB218_0;   /* scratch in func_800BB218 */

typedef struct S_800BB218_1 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800BB218_1;   /* arena in func_800BB218 */

typedef struct S_800BB218_2_pre {
    u8 * unk_00;
    u8 pad_04[0x4];
} S_800BB218_2_pre;   /* the 0x8 bytes before object in func_800BB218, addressed as object[-1] */

typedef struct S_800BB218_2 {
    u8 pad_00[0x66];
    s16 unk_66;
    u8 pad_68[0x2F];
    s8 unk_97;
} S_800BB218_2;   /* object in func_800BB218 */

typedef struct S_800BB218_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800BB218_3;   /* coords in func_800BB218 */

typedef struct S_800BB218_4 {
    u32 unk_00;
    u8 pad_04[0x4];
    u16 unk_08;
    u16 unk_0A;
} S_800BB218_4;   /* packet in func_800BB218 */

typedef struct S_800BB218_5 {
    u8 pad_00[0x8];
    u8 * unk_08;
} S_800BB218_5;   /* next in func_800BB218 */



extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_80065420(void *, void *, void *, void *);
extern s32 rand(void);

typedef struct {
    void *ptr;
    u32 pad[2];
} Global83160;

extern Global83160 D_80083160;

s32 func_800BB218(void *arg0, void *arg1)
{
    s16 angle;
    s32 offset;
    u8 *packet;
    s32 index;
    u8 *scratch;
    u8 *object;
    u8 *coords;
    u32 low_mask;
    u32 high_mask;
    u8 *arena;
    u8 *next;
    s32 value;
    s32 scale;
    u32 packet_tag;
    u32 merged;
    unsigned long link;
    Global83160 *global;

    object = arg0;
    coords = arg1;
    global = &D_80083160;
    scratch = (u8 *)0x1F800000;
    ((S_800BB218_0 *)scratch)->unk_10 = global->ptr + 0xB0;
    low_mask = 0x00FFFFFF;
    high_mask = 0xFF000000;

draw_object:
    index = 0;
    do {
        arena = global->ptr;
        packet = ((S_800BB218_1 *)arena)->unk_8D0;
        ((S_800BB218_1 *)arena)->unk_8D0 = packet + 0xC;
        packet[3] = 2;
        packet[7] = 0x68;
        packet[4] = 0xFF;
        packet[5] = 0xFF;
        packet[6] = 0xFF;

        value = rand();
        angle = (s16)(value % 0x1000);

        scale = func_800644B8(angle) >> 4;
        {
            s32 height = ((S_800BB218_2 *)object)->unk_97;
            offset = (index / 8) % 12 + 0x48;
            ((S_800BB218_0 *)scratch)->unk_14 =
                ((S_800BB218_3 *)coords)->unk_02 + ((scale * (height + offset)) >> 8);
        }

        ((S_800BB218_0 *)scratch)->unk_16 =
            ((S_800BB218_3 *)coords)->unk_06 +
            (((func_80064584(angle) >> 4) *
              (((S_800BB218_2 *)object)->unk_97 + offset)) >> 8);

        ((S_800BB218_0 *)scratch)->unk_18 =
            ((S_800BB218_3 *)coords)->unk_0A -
            (((func_800644B8((index % 16) << 6) >> 4) *
              (((S_800BB218_2 *)object)->unk_66 + 0x10)) >> 8);

        ((S_800BB218_0 *)scratch)->unk_04 = func_80065420(
            scratch + 0x14, scratch, scratch + 8, scratch + 0xC);
        ((S_800BB218_4 *)packet)->unk_08 = ((S_800BB218_0 *)scratch)->unk_00;
        ((S_800BB218_4 *)packet)->unk_0A = ((S_800BB218_0 *)scratch)->unk_02;

        link = ((S_800BB218_0 *)scratch)->unk_04;
        if (link < 0x1E0) {
            link <<= 2;
            link += (unsigned long)((S_800BB218_0 *)scratch)->unk_10;
            packet_tag = ((S_800BB218_4 *)packet)->unk_00;
            link = *(u32 *)link;
            link &= low_mask;
            merged = packet_tag & high_mask;
            merged |= link;
            ((S_800BB218_4 *)packet)->unk_00 = merged;
            *(u32 *)(((S_800BB218_0 *)scratch)->unk_10 +
                     ((S_800BB218_0 *)scratch)->unk_04 * 4) =
                (*(u32 *)(((S_800BB218_0 *)scratch)->unk_10 +
                          ((S_800BB218_0 *)scratch)->unk_04 * 4) & high_mask) |
                ((u32)packet & low_mask);
        }
    } while (++index < 0x180);

    next = ((S_800BB218_2_pre *)object)[-1].unk_00;
    if (next != 0) {
        object = next + 0x20;
        coords = ((S_800BB218_5 *)next)->unk_08;
        goto draw_object;
    }
    return 0;
}
