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

/* Draw the first formatted number with mode-dependent filler glyphs. */
void func_800DBD5C(s32 first_number, s32 second_number, u16 width, s16 y, u16 x, s16 mode)
{
    DrawRecord record;
    char first_buf[16];
    char second_buf[16];
    u8 *char_ptr;
    s16 fill_mode;

    char_ptr = (u8 *)first_buf;
    func_8004E57C(first_number, width, first_buf);
    func_8004E57C(second_number, width, second_buf);
    if (first_buf[0] != 0) {
        fill_mode = mode;
        do {
            s32 glyph_coord;

            if (fill_mode != 0) {
                u8 character;

                character = *char_ptr;
                if ((*((u8 *)((u32)character + (u32)D_800808ED)) & 4) == 0) {
                    glyph_coord = 0x1C0;
                } else {
                    glyph_coord = (character << 2) + 0x100;
                }
            } else {
                u8 character;

                character = *char_ptr;
                if ((*((u8 *)((u32)character + (u32)D_800808ED)) & 4) != 0) {
                    glyph_coord = (character << 2) + 0x100;
                } else {
                    glyph_coord = 0x1EC;
                }
            }
            record.first = glyph_coord;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
            record.second = 0x1B0;
            record.third = 4;
            record.fourth = 16;
            func_800673A0(&record, y, (s16)x);
            char_ptr++;
            y -= 4;
        } while (*char_ptr != 0);
    }
}

/* MECHANISM: Sibling 16-byte buffers plus an 8-byte halfword record yield the 0x58 frame.
   The s16 sixth arg stays in s4 across both calls, then narrows into reused s1; one joined
   glyph_coord yields one sh. Direct integer-ordered global indexing and a post-sh fence close ordering. */
