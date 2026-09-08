#include "common.h"

typedef struct {
    s16 first;
    s16 second;
    s16 third;
    s16 fourth;
} DrawRecord;

extern void func_8004E57C(s32 value, u16 width, char *buf);
extern void func_800673A0(void *record, s32 y, s32 x);
extern u8 D_800808ED[];

/* Draws the first formatted number with mode-dependent padding glyphs. */
void func_800DBC20(s32 first_number, s32 second_number, u16 width, s16 y, u16 x, s16 mode)
{
    DrawRecord record;
    char first_buf[16];
    char second_buf[16];
    u8 *cursor;
    s16 padding_mode;

    cursor = (u8 *)first_buf;
    func_8004E57C(first_number, width, first_buf);
    func_8004E57C(second_number, width, second_buf);
    if (first_buf[0] != 0) {
        padding_mode = mode;
        do {
            s32 glyph_u;

            if (padding_mode != 0) {
                u8 char_code;

                char_code = *cursor;
                if ((*((u8 *)((u32)char_code + (u32)D_800808ED)) & 4) == 0) {
                    glyph_u = 0x1C0;
                } else {
                    glyph_u = (char_code << 2) + 0x100;
                }
            } else {
                u8 char_code;

                char_code = *cursor;
                if ((*((u8 *)((u32)char_code + (u32)D_800808ED)) & 4) != 0) {
                    glyph_u = (char_code << 2) + 0x100;
                } else {
                    glyph_u = 0x1E8;
                }
            }
            record.first = glyph_u;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            record.second = 0x1C0;
            record.third = 4;
            record.fourth = 8;
            func_800673A0(&record, y, (s16)x);
            cursor++;
            y -= 4;
        } while (*cursor != 0);
    }
}

/* MECHANISM: Sibling 16-byte buffers plus an 8-byte halfword record yield the 0x58 frame.
   The s16 sixth arg stays in s4 across both calls, then narrows into reused s1; one joined
   glyph_u yields one sh. Direct integer-ordered global indexing and a post-sh fence close ordering. */
