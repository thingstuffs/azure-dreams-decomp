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
    register u32 source_page ASM_REG("$2");
    register Text5 *source ASM_REG("$6");
    register s32 copy_word ASM_REG("$3");
    register s32 copy_tail ASM_REG("$4");
    register s32 raw_value ASM_REG("$2");
    register s32 half_test ASM_REG("$3");
    register s32 value ASM_REG("$20");
    register u32 loop_page ASM_REG("$19");
    register s32 odd ASM_REG("$2");
    u8 digits[64];
    s32 half;
    s32 i;

    source_page = 0x80090000;
    ASM_KEEP_NV(source_page);
    source = (Text5 *)(source_page - 0x6D24);
    ASM_KEEP_NV(source);
    copy_word = source->word;
    ASM_KEEP_NV(copy_word);
    copy_tail = source->tail;
    ASM_KEEP_NV(copy_tail);
    ((Text5 *)arg0)->word = copy_word;
    ((Text5 *)arg0)->tail = copy_tail;
    strcat(arg0, func_8004E634(1, digits));
    raw_value = func_80043868(arg1);
    value = raw_value;
    ASM_KEEP(value);
    half_test = (s16)raw_value / 2;
    ASM_KEEP_NV(half_test);
    if (half_test > 0) {
        i = 0;
        loop_page = 0x80090000;
        ASM_KEEP_NV(loop_page);
        half = half_test;
        do {
            strcat(arg0, (void *)(loop_page - 0x6D1C));
            i++;
        } while (i < half);
    }
    odd = value & 1;
    ASM_KEEP_NV(odd);
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
