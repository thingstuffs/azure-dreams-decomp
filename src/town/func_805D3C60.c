#include "common.h"

typedef struct {
    u32 value;
} __attribute__((packed)) PackedWord;

typedef struct {
    u8 character;
    u8 field1;
    u8 field2;
    u8 field3;
} TextEntry;

extern PackedWord D_80016024;

/* Copy the packed text into initialized entries and append a terminator. */
TextEntry *func_805D3C60(TextEntry *entries)
{
    PackedWord packed_text;
    s32 char_index;

    packed_text = D_80016024;
    char_index = 0;
    while (((u8 *)&packed_text)[char_index] != 0) {
        entries[char_index].character = ((u8 *)&packed_text)[char_index];
        entries[char_index].field1 = 0x19;
        entries[char_index].field3 = 8;
        entries[char_index].field2 = 0;
        char_index++;
    }
    entries[char_index].field1 = 0;
    entries[char_index].character = 0;
    return entries;
}
