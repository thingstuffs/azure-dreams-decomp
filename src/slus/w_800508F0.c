#include "common.h"

/* Fills two consecutive 12-byte entries at a0/a0+0xC from the 12-byte source
 * template a1 (only bytes 0,2,4,6 of the template are used), tagging the
 * entries with distinct opaque handler words (D_80080B84, D_80080B80).
 * Returns a pointer to the entry following the pair (a0+0x18). */
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

void *func_800508F0(S_800508F0 *a0, u8 *a1)
{
    a0->field4 = D_80080B84;
    a0->field1 = 0x48;
    a0->field2 = a1[0];
    a0->field3 = a1[2];
    a0->fieldA = a1[4];
    a0->fieldB = a1[6];

    a0 = a0 + 1;
    a0->field4 = D_80080B80;
    a0->field1 = 0x48;
    a0->field2 = a1[0];
    a0->field3 = a1[2];
    a0->fieldA = a1[4];
    a0->fieldB = a1[6];
    a0->field0 = 3;

    return a0 + 1;
}
