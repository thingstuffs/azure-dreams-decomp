#include "common.h"
#include "town/scene/dialogue.h"

typedef struct {
    u32 value;
} __attribute__((packed)) PackedWord;



extern PackedWord D_80016020;

/* Copies packed text into initialized entries and appends a terminator. */
DialogueTextCell *copy_packed_text_to_entries(DialogueTextCell *entries)
{
    PackedWord packed_text;
    s32 char_index;

    packed_text = D_80016020;
    char_index = 0;
    while (((u8 *)&packed_text)[char_index] != 0) {
        entries[char_index].character = ((u8 *)&packed_text)[char_index];
        entries[char_index].field1 = 0x19;
        entries[char_index].field3 = 0;
        entries[char_index].field2 = 0;
        char_index++;
    }
    entries[char_index].field1 = 0;
    entries[char_index].character = 0;
    return entries;
}
