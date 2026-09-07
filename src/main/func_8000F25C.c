#include "common.h"

void func_8002225C(
    u8 *text, s32 limit, s32 *position_out, s32 *length_out, s32 *total_out
)
{
    s32 position;
    s32 length;
    s32 row;
    s32 outer_space;
    u8 value;

    position = 0;
    length = position;
    row = length;
    *total_out = 0;
    if (limit >= 0) {
        outer_space = 0x20;
        do {
            *total_out += length;
            if (*text == outer_space) {
                s32 skip_space;
                if (position != 0) {
                    skip_space = 0x20;
                } else {
                    skip_space = 0x20;
                }
                do {
                    text++;
                    position++;
                } while (*text == skip_space);
            }
            *position_out = position;
            value = *text;
            length = 0;
            if (value != outer_space) {
                s32 scan_space;
                if (value != 0) {
                    scan_space = 0x20;
                } else {
                    scan_space = 0x20;
                }
scan:
                if (value != 0) {
                    text += 2;
                    value = *text;
                    length++;
                    if (value == scan_space) {
                        goto post_scan;
                    }
                    goto scan;
                }
            }
post_scan:
            position += length * 2;
            row++;
            *length_out = length;
        } while (row <= limit);
    }
}
