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

/* Builds a formatted marker string for the object's value, including an odd remainder. */
void *func_800B544C(void *output, void *object)
{
    register u32 prefix_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register Text5 *prefix ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 copy_word ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 copy_tail ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 raw_count;
    s32 pair_test;
    s16 count;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u32 marker_page;
    u8 format_buf[64];
    s32 pair_count;
    s32 pair_index;

    prefix_page = 0x80090000;
    ASM_KEEP_NV(prefix_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    prefix = (Text5 *)(prefix_page - 0x6D24);
    copy_word = prefix->word;
    ASM_KEEP_NV(copy_word);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    copy_tail = prefix->tail;
    ASM_KEEP_NV(copy_tail);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ((Text5 *)output)->word = copy_word;
    ((Text5 *)output)->tail = copy_tail;
    strcat(output, func_8004E634(1, format_buf));
    raw_count = func_80043868(object);
    count = raw_count;
    pair_test = (s16)raw_count / 2;
    if (pair_test > 0) {
        pair_index = 0;
        marker_page = 0x80090000;
        pair_count = pair_test;
        do {
            strcat(output, (void *)(marker_page - 0x6D1C));
            pair_index++;
        } while (pair_index < pair_count);
    }
    raw_count = count & 1;
    if (raw_count) {
        strcat(output, D_800892E8);
    }
    strcat(output, D_800892EC);
    strcat(output, func_8004E634(0, format_buf));
    return output;
}

