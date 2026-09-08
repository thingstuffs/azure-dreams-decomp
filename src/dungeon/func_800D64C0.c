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

void func_800DBC20(s32 arg0, s32 arg1, u16 width, s16 y, u16 x, s16 mode)
{
    DrawRecord record;
    char first_buf[16];
    char second_buf[16];
    u8 *cursor;
    s16 signed_mode;

    cursor = (u8 *)first_buf;
    func_8004E57C(arg0, width, first_buf);
    func_8004E57C(arg1, width, second_buf);
    if (first_buf[0] != 0) {
        signed_mode = mode;
        do {
            s32 first_value;

            if (signed_mode != 0) {
                u8 value;

                value = *cursor;
                if ((*((u8 *)((u32)value + (u32)D_800808ED)) & 4) == 0) {
                    first_value = 0x1C0;
                } else {
                    first_value = (value << 2) + 0x100;
                }
            } else {
                u8 value;

                value = *cursor;
                if ((*((u8 *)((u32)value + (u32)D_800808ED)) & 4) != 0) {
                    first_value = (value << 2) + 0x100;
                } else {
                    first_value = 0x1E8;
                }
            }
            record.first = first_value;
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
   first_value yields one sh. Direct integer-ordered global indexing and a post-sh fence close ordering. */
