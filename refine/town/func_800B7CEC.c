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
    register u32 prefix_page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register Text5 *prefix ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 copy_word ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    register s32 copy_tail ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 raw_count;
    s32 pair_test;
    register s32 count ASM_REG("$20");   /* MATCH pin: load-bearing for the whole function shape */
    u32 marker_page;
    register s32 has_remainder ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    u8 format_buf[64];
    s32 pair_count;
    s32 pair_index;

    prefix_page = 0x80090000;
    ASM_KEEP_NV(prefix_page);   /* MATCH pin: keeps a statement from moving across a call/branch */
    prefix = (Text5 *)(prefix_page - 0x6D24);
    copy_word = prefix->word;
    ASM_KEEP_NV(copy_word);   /* MATCH pin: retail schedule: same instructions, different order without it */
    copy_tail = prefix->tail;
    ASM_KEEP_NV(copy_tail);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ((Text5 *)output)->word = copy_word;
    ((Text5 *)output)->tail = copy_tail;
    strcat(output, func_8004E634(1, format_buf));
    raw_count = func_80043868(object);
    count = raw_count;
    ASM_KEEP(count);   /* MATCH pin: retail register colouring depends on it */
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
    has_remainder = count & 1;
    if (has_remainder) {
        strcat(output, D_800892E8);
    }
    strcat(output, D_800892EC);
    strcat(output, func_8004E634(0, format_buf));
    return output;
}

