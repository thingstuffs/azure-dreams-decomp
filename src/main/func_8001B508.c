#include "common.h"

void func_8001B508(u8 *text, s32 limit, s32 *start_out,
                   s32 *length_out, s32 *total_out)
{
    s32 position;
    s32 length;
    s32 iteration;
    s32 delimiter;
    u8 value;

    position = 0;
    length = 0;
    iteration = 0;
    *total_out = 0;
    if (limit >= 0) {
        do {
            *total_out += length;
            if (*text == ' ') {
                length = ' ';
                do {
                    text++;
                    position++;
                } while (*text == length);
            }
            *start_out = position;
            length = 0;
            if (*text != ' ') {
                delimiter = ' ';
                value = *text;
loop:
                if (value != 0) {
                    text += 2;
                    value = *text;
                    length++;
                    if (value != delimiter) {
                        goto loop;
                    }
                }
            }
            position += length * 2;
            iteration++;
            *length_out = length;
        } while (iteration <= limit);
    }
}
