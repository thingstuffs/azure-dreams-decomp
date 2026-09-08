#include "common.h"

typedef struct {
    s32 word;
    s8 tail;
} __attribute__((packed)) Text5;

extern s32 func_80043868(void *);
extern u8 *func_8004E634(s32, u8 *);
extern u8 *strcat(void *, const void *);

extern Text5 D_800892DC;
extern u8 D_800892E4[];
extern u8 D_800892E8[];
extern u8 D_800892EC[];

void *func_800B544C(void *arg0, void *arg1)
{
    register u32 source_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register Text5 *source ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 copy_word ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 copy_tail ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 raw_value;
    s32 half_test;
    register s32 value ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u32 loop_page;
    register s32 odd ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 digits[64];
    s32 half;
    s32 i;

    source_page = 0x80090000;
    ASM_KEEP_NV(source_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    source = (Text5 *)(source_page - 0x6D24);
    copy_word = source->word;
    ASM_KEEP_NV(copy_word);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    copy_tail = source->tail;
    ASM_KEEP_NV(copy_tail);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ((Text5 *)arg0)->word = copy_word;
    ((Text5 *)arg0)->tail = copy_tail;
    strcat(arg0, func_8004E634(1, digits));
    raw_value = func_80043868(arg1);
    value = raw_value;
    ASM_KEEP(value);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    half_test = (s16)raw_value / 2;
    if (half_test > 0) {
        i = 0;
        loop_page = 0x80090000;
        half = half_test;
        do {
            strcat(arg0, (void *)(loop_page - 0x6D1C));
            i++;
        } while (i < half);
    }
    odd = value & 1;
    if (odd) {
        strcat(arg0, D_800892E8);
    }
    strcat(arg0, D_800892EC);
    strcat(arg0, func_8004E634(0, digits));
    return arg0;
}

/* MECHANISM: A 64-byte escaping digit buffer establishes retail's 0x68 frame.
   Split page/source and packed word/tail roles preserve v0/a2/v1/a0 copy code.
   Short-lived v0/v1 temps and an s3 page hold reproduce the loop and odd test. */
