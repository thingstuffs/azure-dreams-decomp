#include "common.h"
#include "engine/text.h"
#include "sdk/libc.h"

/* D_80080B70: a small pattern buffer; only bytes 0..2 are ever read (by
 * sibling fill_string_tail_and_detect_zero as a 3-byte fill pattern). Declared >8B so its
 * address is materialised via %hi/%lo instead of $gp-relative. */
typedef struct S_80080B70 {
    /* 0x0 */ s8 b0;
    /* 0x1 */ s8 b1;
    /* 0x2 */ s8 b2;
    /* 0x3 */ s8 pad[13];
} S_80080B70; /* size 0x10 */

extern S_80080B70 string_tail_fill_pattern;

/* Fills a field, appends two pattern bytes, and returns the appended position. */
char *pad_double_byte_field_and_append_marker(u8 *dst, s32 field_width) {
    u8 *field_end = dst;
    s32 width = field_width;

    fill_string_tail_and_detect_zero(dst, field_width);
    field_end = field_end + (width << 1);
    strncpy((char *)field_end, (char *)&string_tail_fill_pattern, 2);
    return (char *)field_end;
}
