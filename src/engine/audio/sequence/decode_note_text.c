#include "common.h"
#include "engine/audio/sequence.h"
#include "engine/camera.h"
#include "engine/text.h"
#include "slus.h"

/* Decode fullwidth text into glyph entries and mark the final entry. */
void *decode_fullwidth_text(void *entries, u8 *text, s32 initial_style)
{
    s8 *entry = (s8 *)entries;
    u8 *cursor = text;
    s32 style = initial_style;
    s32 length = 0;
    s32 row = length;
    s32 spacing = length;
    s8 *first_entry = (s8 *)entries;
    u8 ch;

    if (cursor == 0) {
        return 0;
    }

    ch = *cursor;
    if (ch != 0) {
        do {
            if (ch == ' ') {
                cursor++;
                length++;
            } else if (ch == 8) {
                cursor++;
                style = *cursor++ - 0x30;
            } else if (ch == 0xA) {
                cursor++;
                length = 0;
                row++;
            } else if (ch == 9) {
                cursor++;
                ch = *cursor;
                if (ch == 's') {
                    cursor++;
                    spacing = *cursor - 0x30;
                } else {
                    s32 length_bias = length - 0x30;
                    length = length_bias + ch;
                }
                cursor++;
            } else {
                u8 glyph_hi = cursor[0];
                u8 glyph_lo = cursor[1];
                u8 glyph = (u8)map_fullwidth_character_to_glyph_byte(glyph_lo | (glyph_hi << 8));
                /* BYTES: sched1/sched2 region barrier or tie: unwrap reorders independent insns (no memory dependence) (ledger/onetrip_loadbearing.jsonl: slus/w_8004DA74). */
                do {
                    cursor += 2;
                } while (0);
                if (glyph != ' ') {
                    initialize_styled_glyph_rectangle(glyph, style, entry);
                    set_glyph_style_index(entry, style);
                    set_descriptor_grid_byte_coordinates(entry, length, row, spacing, 0);
                    entry += 0xC;
                }
                length += 2;
            }
            ch = *cursor;
        } while (ch != 0);
    }

    if (entry != first_entry) {
        entry[-0xC] = entry[-0xC] | 0x80;
    } else {
        first_entry = 0;
    }
    return first_entry;
}
