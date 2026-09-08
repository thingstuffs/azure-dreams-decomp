#include "common.h"

typedef struct __attribute__((packed)) {
    u8 bytes[0x30];
} Packed48;

typedef struct __attribute__((packed)) {
    u8 bytes[0xC];
} Packed12;

typedef struct __attribute__((packed)) {
    u32 value;
} PackedWord;

typedef struct __attribute__((packed)) {
    u8 bytes[0x10];
} Packed16;

typedef struct {
    u32 words[4];
} Aligned16;

typedef struct {
    Packed48 first;
    Packed12 second;
} CopyTarget;

extern u8 D_800D16D8[0xC];
extern u8 D_800D16FC[0x30];

void func_800B4188(CopyTarget *arg0)
{
    CopyTarget *base;
    register u8 *src;
    register u8 *dst ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *end;
    register u32 page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register u32 tail0 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u32 tail1 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u32 tail2 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    base = arg0;
    ASM_KEEP(base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    src = D_800D16FC;
    dst = (u8 *)base;
    if (((u32)src | (u32)base) & 3) {
        end = src + 0x30;
        do {
            *(Packed16 *)dst = *(Packed16 *)src;
            src += 0x10;
            dst += 0x10;
        } while (src != end);
        page = 0x800D0000;
        goto tail;
    } else {
        end = src + 0x30;
        do {
            u32 word0;
            u32 word1;
            u32 word2;
            u32 word3;

            word0 = *(u32 *)(src + 0x0);
            word1 = *(u32 *)(src + 0x4);
            word2 = *(u32 *)(src + 0x8);
            word3 = *(u32 *)(src + 0xC);
            *(u32 *)(dst + 0x0) = word0;
            *(u32 *)(dst + 0x4) = word1;
            *(u32 *)(dst + 0x8) = word2;
            *(u32 *)(dst + 0xC) = word3;
            ASM_KEEP(src);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            dst += 0x10;
            src += 0x10;
        } while (src != end);
        page = 0x800D0000;
    }

tail:
    src = (u8 *)page + 0x16D8;
    tail0 = (*(PackedWord *)(src + 0x0)).value;
    tail1 = (*(PackedWord *)(src + 0x4)).value;
    tail2 = (*(PackedWord *)(src + 0x8)).value;
    (*(PackedWord *)((u8 *)base + 0x30)).value = tail0;
    (*(PackedWord *)((u8 *)base + 0x34)).value = tail1;
    (*(PackedWord *)((u8 *)base + 0x38)).value = tail2;
}
