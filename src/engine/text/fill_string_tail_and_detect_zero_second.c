#include "common.h"
#include "engine/text.h"
#include "sdk/libc.h"
#include "slus/text_pattern_data.h"

/* Fills a field, appends two pattern bytes, and returns the appended position. */
char *pad_double_byte_field_and_append_marker(u8 *dst, s32 field_width) {
    u8 *field_end = dst;
    s32 width = field_width;

    fill_string_tail_and_detect_zero(dst, field_width);
    field_end = field_end + (width << 1);
    strncpy((char *)field_end, (char *)&string_tail_fill_pattern, 2);
    return (char *)field_end;
}
