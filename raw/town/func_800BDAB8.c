#include "common.h"

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

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
    FIELD(scratch, u8 *, 0x10) = global->ptr + 0xB0;
    low_mask = 0x00FFFFFF;
    high_mask = 0xFF000000;

draw_object:
    index = 0;
    do {
        arena = global->ptr;
        packet = FIELD(arena, u8 *, 0x8D0);
        FIELD(arena, u8 *, 0x8D0) = packet + 0xC;
        packet[3] = 2;
        packet[7] = 0x68;
        packet[4] = 0xFF;
        packet[5] = 0xFF;
        packet[6] = 0xFF;

        value = rand();
        angle = (s16)(value % 0x1000);

        scale = func_800644B8(angle) >> 4;
        {
            s32 height = FIELD(object, s8, 0x97);
            offset = (index / 8) % 12 + 0x48;
            FIELD(scratch, s16, 0x14) =
                FIELD(coords, u16, 2) + ((scale * (height + offset)) >> 8);
        }

        FIELD(scratch, s16, 0x16) =
            FIELD(coords, u16, 6) +
            (((func_80064584(angle) >> 4) *
              (FIELD(object, s8, 0x97) + offset)) >> 8);

        FIELD(scratch, s16, 0x18) =
            FIELD(coords, u16, 0xA) -
            (((func_800644B8((index % 16) << 6) >> 4) *
              (FIELD(object, s16, 0x66) + 0x10)) >> 8);

        FIELD(scratch, u32, 4) = func_80065420(
            scratch + 0x14, scratch, scratch + 8, scratch + 0xC);
        FIELD(packet, u16, 8) = FIELD(scratch, u16, 0);
        FIELD(packet, u16, 0xA) = FIELD(scratch, u16, 2);

        link = FIELD(scratch, u32, 4);
        if (link < 0x1E0) {
            link <<= 2;
            link += (unsigned long)FIELD(scratch, u8 *, 0x10);
            packet_tag = FIELD(packet, u32, 0);
            link = *(u32 *)link;
            link &= low_mask;
            merged = packet_tag & high_mask;
            merged |= link;
            FIELD(packet, u32, 0) = merged;
            *(u32 *)(FIELD(scratch, u8 *, 0x10) +
                     FIELD(scratch, u32, 4) * 4) =
                (*(u32 *)(FIELD(scratch, u8 *, 0x10) +
                          FIELD(scratch, u32, 4) * 4) & high_mask) |
                ((u32)packet & low_mask);
        }
    } while (++index < 0x180);

    next = FIELD(object, u8 *, -8);
    if (next != 0) {
        object = next + 0x20;
        coords = FIELD(next, u8 *, 8);
        goto draw_object;
    }
    return 0;
}
