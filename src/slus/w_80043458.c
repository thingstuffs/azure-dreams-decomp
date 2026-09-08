#include "common.h"

#include "common.h"

typedef struct {
    u8 pad[0x24B];
    u8 value;
} BytePage;

typedef struct {
    u8 pad[0x304];
    s32 flags;
} WordPage;

typedef struct {
    u8 pad[0xA94];
    s32 flags;
} SecondPage;

void func_80043458(void) {
    s32 i;
    s32 mask;
    volatile WordPage *word_ptr;
    volatile BytePage *byte_ptr;
    volatile u8 *base;
    s32 mask2;
    volatile SecondPage *second_ptr;

    i = 0;
    mask = ~0x4000;
    ASM_USE(mask);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    word_ptr = (WordPage *)0x80010000;
    byte_ptr = (BytePage *)word_ptr;
    ASM_KEEP(byte_ptr);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    base = (u8 *)byte_ptr;
    ASM_KEEP(base);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    *(volatile s32 *)(base + 0x208C) = 0;
    *(volatile s32 *)(base + 0x2090) = 0;
    base[0x2D52] = 0xFF;
    base[0x2D53] = 0xFF;
    base[0x21E0] = 0xFF;
    base[0x21E1] = 0xFF;
    do {
        i += 1;
        byte_ptr->value &= 0x5F;
        word_ptr->flags &= mask;
        byte_ptr = (BytePage *)((u8 *)byte_ptr + 4);
        word_ptr = (WordPage *)((u8 *)word_ptr + 0x54);
    } while (i < 0x14);

    i = 0;
    mask2 = ~0x4000;
    second_ptr = (SecondPage *)0x80010000;
    do {
        i += 1;
        second_ptr->flags &= mask2;
        second_ptr = (SecondPage *)((u8 *)second_ptr + 0x54);
    } while (i < 0x40);
}
