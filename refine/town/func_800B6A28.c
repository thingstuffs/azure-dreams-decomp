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

/* Copies the 48-byte and 12-byte global blocks into the target. */
void func_800B4188(CopyTarget *target)
{
    CopyTarget *target_base;
    register u8 *src;
    register u8 *dst ASM_REG("$7");   /* MATCH pin: load-bearing for the whole function shape */
    u8 *src_end;
    register u32 data_page ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    register u32 tail_word0 ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    register u32 tail_word1 ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    register u32 tail_word2 ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */

    target_base = target;
    ASM_KEEP(target_base);   /* MATCH pin: retail schedule: same instructions, different order without it */
    src = D_800D16FC;
    dst = (u8 *)target_base;
    if (((u32)src | (u32)target_base) & 3) {
        src_end = src + 0x30;
        do {
            *(Packed16 *)dst = *(Packed16 *)src;
            src += 0x10;
            dst += 0x10;
        } while (src != src_end);
        data_page = 0x800D0000;
        goto tail;
    } else {
        src_end = src + 0x30;
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
            ASM_KEEP(src);   /* MATCH pin: retail schedule: same instructions, different order without it */
            dst += 0x10;
            src += 0x10;
        } while (src != src_end);
        data_page = 0x800D0000;
    }

tail:
    src = (u8 *)data_page + 0x16D8;
    tail_word0 = (*(PackedWord *)(src + 0x0)).value;
    tail_word1 = (*(PackedWord *)(src + 0x4)).value;
    tail_word2 = (*(PackedWord *)(src + 0x8)).value;
    (*(PackedWord *)((u8 *)target_base + 0x30)).value = tail_word0;
    (*(PackedWord *)((u8 *)target_base + 0x34)).value = tail_word1;
    (*(PackedWord *)((u8 *)target_base + 0x38)).value = tail_word2;
}
