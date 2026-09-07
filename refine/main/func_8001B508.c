#include "common.h"

/* Locate a space-delimited word in two-byte text and report its length and preceding character count. */
void func_8001B508(u8 *text, s32 limit, s32 *start_out,
                   s32 *length_out, s32 *total_out)
{
    s32 byte_offset;
    s32 word_length;
    s32 word_index;
    s32 space;
    u8 lead_byte;

    byte_offset = 0;
    word_length = 0;
    word_index = 0;
    *total_out = 0;
    if (limit >= 0) {
        do {
            *total_out += word_length;
            if (*text == ' ') {
                word_length = ' ';
                do {
                    text++;
                    byte_offset++;
                } while (*text == word_length);
            }
            *start_out = byte_offset;
            word_length = 0;
            if (*text != ' ') {
                space = ' ';
                lead_byte = *text;
scan_word:
                if (lead_byte != 0) {
                    text += 2;
                    lead_byte = *text;
                    word_length++;
                    if (lead_byte != space) {
                        goto scan_word;
                    }
                }
            }
            byte_offset += word_length * 2;
            word_index++;
            *length_out = word_length;
        } while (word_index <= limit);
    }
}
