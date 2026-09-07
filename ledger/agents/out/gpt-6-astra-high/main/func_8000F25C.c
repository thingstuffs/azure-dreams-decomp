#include "common.h"

/* Finds a word's byte offset and character count, and counts preceding characters. */
void func_8002225C(
    u8 *text, s32 word_index, s32 *offset_out, s32 *length_out, s32 *prior_chars_out
)
{
    s32 byte_offset;
    s32 word_length;
    s32 word_count;
    s32 space;
    u8 lead_byte;

    byte_offset = 0;
    word_length = byte_offset;
    word_count = word_length;
    *prior_chars_out = 0;
    if (word_index >= 0) {
        space = 0x20;
        do {
            *prior_chars_out += word_length;
            if (*text == space) {
                s32 skip_space;
                if (byte_offset != 0) {
                    skip_space = 0x20;
                } else {
                    skip_space = 0x20;
                }
                do {
                    text++;
                    byte_offset++;
                } while (*text == skip_space);
            }
            *offset_out = byte_offset;
            lead_byte = *text;
            word_length = 0;
            if (lead_byte != space) {
                s32 scan_space;
                if (lead_byte != 0) {
                    scan_space = 0x20;
                } else {
                    scan_space = 0x20;
                }
scan:
                if (lead_byte != 0) {
                    text += 2;
                    lead_byte = *text;
                    word_length++;
                    if (lead_byte == scan_space) {
                        goto post_scan;
                    }
                    goto scan;
                }
            }
post_scan:
            byte_offset += word_length * 2;
            word_count++;
            *length_out = word_length;
        } while (word_count <= word_index);
    }
}
