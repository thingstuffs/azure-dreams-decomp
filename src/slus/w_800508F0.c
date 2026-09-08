#include "common.h"

/* 12-byte entry record; field4 is a raw word (opaque handler/id), fieldA/fieldB
 * mirror the source template's bytes at offsets 4 and 6. Offset 0 ("field0") is
 * intentionally left unwritten for the first entry -- retail asm shows no store
 * to it there. */
typedef struct S_800508F0 {
    /* 0x0 */ u8 field0;
    /* 0x1 */ u8 field1;
    /* 0x2 */ u8 field2;
    /* 0x3 */ u8 field3;
    /* 0x4 */ s32 field4;
    /* 0x8 */ u8 pad8[2];
    /* 0xA */ u8 fieldA;
    /* 0xB */ u8 fieldB;
} S_800508F0; /* size 0xC */

extern s32 D_80080B84;
extern s32 D_80080B80;

/* Fills two entries from a template with distinct handler words and returns the next entry. */
void *func_800508F0(S_800508F0 *entry, u8 *template)
{
    entry->field4 = D_80080B84;
    entry->field1 = 0x48;
    entry->field2 = template[0];
    entry->field3 = template[2];
    entry->fieldA = template[4];
    entry->fieldB = template[6];

    entry = entry + 1;
    entry->field4 = D_80080B80;
    entry->field1 = 0x48;
    entry->field2 = template[0];
    entry->field3 = template[2];
    entry->fieldA = template[4];
    entry->fieldB = template[6];
    entry->field0 = 3;

    return entry + 1;
}
