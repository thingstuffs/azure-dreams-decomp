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
    u32 value;
    s32 pair_test;
    s16 count;
    u32 marker_page;
    u8 format_buf[64];
    s32 pair_count;
    s32 pair_index;

    *(Text5 *)output = D_800892DC;
    strcat(output, func_8004E634(1, format_buf));
    value = func_80043868(object);
    count = value;
    pair_test = (s16)value / 2;
    pair_index = 0;
    if (pair_test > 0) {
        marker_page = 0x80090000;
        pair_count = pair_test;
        do {
            strcat(output, (void *)(marker_page - 0x6D1C));
            pair_index++;
        } while (pair_index < pair_count);
    }
    value = count & 1;
    if (value) {
        strcat(output, D_800892E8);
    }
    strcat(output, D_800892EC);
    strcat(output, func_8004E634(0, format_buf));
    return output;
}

