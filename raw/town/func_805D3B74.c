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

extern PackedWord D_80016020;

TextEntry *func_805D3B74(TextEntry *entries)
{
    PackedWord text;
    s32 i;

    text = D_80016020;
    i = 0;
    while (((u8 *)&text)[i] != 0) {
        entries[i].character = ((u8 *)&text)[i];
        entries[i].field1 = 0x19;
        entries[i].field3 = 0;
        entries[i].field2 = 0;
        i++;
    }
    entries[i].field1 = 0;
    entries[i].character = 0;
    return entries;
}
