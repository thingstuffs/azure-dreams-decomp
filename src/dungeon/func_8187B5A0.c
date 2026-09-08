#include "common.h"

#define FIELD_U8(base, off)  (*(u8 *)((u8 *)(base) + (off)))
#define FIELD_S16(base, off) (*(s16 *)((u8 *)(base) + (off)))
#define FIELD_U16(base, off) (*(u16 *)((u8 *)(base) + (off)))
#define FIELD_U32(base, off) (*(u32 *)((u8 *)(base) + (off)))
#define FIELD_PTR(base, off) (*(u8 **)((u8 *)(base) + (off)))
#define VOL_U32(base, off) (*(volatile u32 *)((u8 *)(base) + (off)))
#define VOL_PTR(base, off) (*(u8 * volatile *)((u8 *)(base) + (off)))

extern u8 D_80080000[];
extern void func_80024DF8() __attribute__((noreturn));
extern u32 func_80065420();
extern s32 func_80066460();
extern s32 func_80067F20();

s32 func_8187B5A0(u8 *arg0, u8 *arg1)
{
    u8 **context_slot;
    u8 *scratch;
    u8 *context;
    u8 *packet;
    u8 *packet2;
    u8 *next;
    u8 *input = arg1;
    u16 first_coord;
    u8 blue;
    u32 index;
    register u32 high_mask ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u32 low_mask;
    u32 *entry2;
    register u8 *tail_arg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */

    context = FIELD_PTR(D_80080000, 0x3160);
    context_slot = (u8 **)(D_80080000 + 0x3160);
    ASM_KEEP_NV(context_slot);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    low_mask = 0x00FFFFFF;
    high_mask = 0xFF000000;
    scratch = (u8 *)0x1F800000;
    ASM_KEEP(high_mask);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    FIELD_PTR(scratch, 0x18) = FIELD_PTR(context, 0x8D0);
    FIELD_PTR(scratch, 0x20) = context + 0xB0;
    ASM_KEEP(scratch);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    packet = VOL_PTR(scratch, 0x18);
    first_coord = FIELD_U16(input, 2);
    FIELD_U16(scratch, 0) = first_coord;
    FIELD_U16(scratch, 2) = FIELD_U16(input, 6);
    FIELD_U16(scratch, 4) = FIELD_U16(input, 0xA);
    FIELD_PTR(scratch, 0x18) = packet + 0xC;

    index = func_80065420(scratch, packet + 8, scratch + 0x90, scratch + 0x94);
    FIELD_U32(scratch, 0xC0) = index;
    if (index < 0x1E0U) {
        FIELD_U32(packet, 4) = FIELD_U32(arg0, 0);
        FIELD_U8(packet, 4) = (u8)((FIELD_U8(packet, 4) * FIELD_S16(arg0, 0x10)) /
                                  FIELD_S16(arg0, 0x12));
        FIELD_U8(packet, 5) = (u8)((FIELD_U8(packet, 5) * FIELD_S16(arg0, 0x10)) /
                                  FIELD_S16(arg0, 0x12));
        blue = (u8)((FIELD_U8(packet, 6) * FIELD_S16(arg0, 0x10)) /
                    FIELD_S16(arg0, 0x12));
        FIELD_U8(packet, 3) = 2;
        FIELD_U8(packet, 7) = 0x6A;
        FIELD_U8(packet, 6) = blue;

        FIELD_U32(packet, 0) = (FIELD_U32(packet, 0) & high_mask) |
            (*(u32 *)((VOL_U32(scratch, 0xC0) * 4) + (u32)VOL_PTR(scratch, 0x20)) & low_mask);
        {
            u32 *tag_ptr;
            register u32 tag_word ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            tag_ptr = (u32 *)((VOL_U32(scratch, 0xC0) * 4) +
                              (u32)VOL_PTR(scratch, 0x20));
            tag_word = *tag_ptr;
            *tag_ptr = (tag_word & high_mask) |
                       ((u32)packet & low_mask);
        }

        packet2 = FIELD_PTR(scratch, 0x18);
        FIELD_PTR(scratch, 0x18) = packet2 + 0xC;
        func_80067F20(packet2, 0, 0, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);

        FIELD_U32(packet2, 0) = (FIELD_U32(packet2, 0) & high_mask) |
            (*(u32 *)((VOL_U32(scratch, 0xC0) * 4) + (u32)VOL_PTR(scratch, 0x20)) & low_mask);
        entry2 = (u32 *)((VOL_U32(scratch, 0xC0) * 4) + (u32)VOL_PTR(scratch, 0x20));
        *entry2 = (*entry2 & high_mask) | ((u32)packet2 & low_mask);
    }

    next = FIELD_PTR(arg0, -8);
    arg0 = next + 0x20;
    if (next != 0) {
        input = FIELD_PTR(next, 8);
        ASM_KEEP(arg0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(input);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        tail_arg = scratch;
        ASM_TAILSLOT_PIN_TIED(tail_arg);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_80024DF8();
    }
    FIELD_PTR(*context_slot, 0x8D0) = FIELD_PTR(scratch, 0x18);
    return 0;
}
