#ifndef SLUS_ENTRY_WORDS_H
#define SLUS_ENTRY_WORDS_H

/* Present C interface; historical filename and TU boundary remain inferred. */
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

extern s32 primitive_pair_primary_color;
extern s32 primitive_pair_secondary_color;

/* Fills two entries from a template with distinct handler words and returns the next entry. */

void *fill_primitive_pair(S_800508F0 *entry, u8 *template);
void *func_800508F0(S_800508F0 *entry, u8 *template);

#endif
