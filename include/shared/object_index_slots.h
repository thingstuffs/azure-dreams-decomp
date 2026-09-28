#ifndef SHARED_OBJECT_INDEX_SLOTS_H
#define SHARED_OBJECT_INDEX_SLOTS_H

/* D_80082660 (SLUS .bss): a table of 8-byte slots indexed by an object's slot number (town objects keep it at +0x60 or
 * +0x40; the Konami runtime's event-script commands take it as a byte operand: slus/konami_runtime_w_8003931C,
 * w_80039470; slot 1 is special-cased by ms_mot_accpt_ow = konami_runtime_w_800392A4).  Rows reach +0..+4 from the
 * base of D_80082660 by index (census/c2660.jsonl, r78 phase 8: 71 rows, 68 index it); D_80082668/69/74/7C/80/88/B8
 * are fields of slots 1..11 spelled as their own addresses.  Length unproven (element 11 is the highest constant).
 *   object (+0x04): every row that stores it registers an object as `(u8 *)object - 0x20` (its 0x20-byte node
 *   header); ms_mot_accpt_ow returns object + 0x20 after checking the header's type word at +0x10.
 *   unk_00 (+0x00): store-only (sb 36: cleared to 0 when an object is dropped).  unk_01 (+0x01): lb/sb.
 *   unk_02 (+0x02): lbu 3, lb 2, sb 2 (unsigned by majority; the lb sites keep a cast). */
typedef struct ObjectIndexSlot {
    /* 0x00 */ signed char unk_00;
    /* 0x01 */ signed char unk_01;
    /* 0x02 */ unsigned char unk_02;
    /* 0x03 */ unsigned char pad_03;
    /* 0x04 */ void *object;
} ObjectIndexSlot;

extern ObjectIndexSlot D_80082660[];

#endif
