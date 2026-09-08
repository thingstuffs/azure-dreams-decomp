#include "common.h"

extern int func_8004D880(int a0);
extern void func_8004D98C(int a0, int a1, void *a2);
extern void func_8004E264(void *a0, int a1);
extern void func_8004D9E0(signed char *a0, int a1, int a2, int a3, int a4);

/* Decodes text into note entries and marks the final entry as the end of the sequence. */
void *func_8004DA74(void *entries, u8 *text, s32 initial_octave)
{
    s8 *entry = (s8 *)entries;
    u8 *cursor = text;
    s32 octave = initial_octave;
    s32 length = 0;
    s32 tie_count = length;
    s32 dot_count = length;
    s8 *first_entry = (s8 *)entries;
    u8 ch;

    if (cursor == 0) {
        return (void *)length;
    }

    ch = *cursor;
    if (ch != 0) {
        do {
            if (ch == ' ') {
                cursor++;
                length++;
            } else if (ch == 8) {
                cursor++;
                octave = *cursor++ - 0x30;
            } else if (ch == 0xA) {
                cursor++;
                length = 0;
                tie_count++;
            } else if (ch == 9) {
                cursor++;
                ch = *cursor;
                if (ch == 's') {
                    cursor++;
                    dot_count = *cursor - 0x30;
                } else {
                    s32 length_bias = length - 0x30;
                    length = length_bias + ch;
                }
                cursor++;
            } else {
                u8 note_hi = cursor[0];
                u8 note_lo = cursor[1];
                u8 note = (u8)func_8004D880(note_lo | (note_hi << 8));
                do { cursor += 2; } while (0);
                if (note != ' ') {
                    func_8004D98C(note, octave, entry);
                    func_8004E264(entry, octave);
                    func_8004D9E0(entry, length, tie_count, dot_count, 0);
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
