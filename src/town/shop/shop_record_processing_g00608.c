/* Shop record processing (G00608). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B3110. */
#include "town/shop/shop_record_processing_g00608.h"
#include "town/shop.h"

/* Initializes two consecutive records with source bytes and fixed control values. */
void initialize_shop_display_records(void *destination, S_800B0870_1 *source) {
    u8 sourceByte4;
    u8 sourceByte6;

    ((S_800B0870_0 *)destination)->unk_01.s = 0x2A;
    sourceByte4 = source->unk_04;
    ((S_800B0870_0 *)destination)->unk_0A = sourceByte4;
    sourceByte6 = source->unk_06;
    ((S_800B0870_0 *)destination)->unk_04.at00.v = 0x401010;
    ((S_800B0870_0 *)destination)->unk_0B = sourceByte6;
    ((S_800B0870_0 *)destination)->unk_02 = (u8) source->unk_00;
    ((S_800B0870_0 *)destination)->unk_03 = (u8) source->unk_02;
    destination += 0xC;
    ((S_800B0870_0 *)destination)->unk_01.u = 0x81;
    ((S_800B0870_0 *)destination)->unk_04.at00u.v = 0;
    ((S_800B0870_0 *)destination)->unk_04.at02.v = 1;
    ((S_800B0870_0 *)destination)->unk_00 = (u8) (((S_800B0870_0 *)destination)->unk_00 | 0x80);
}

/* Process the record and its subrecord at offset 0x48 using the shared data. */
void process_shop_record_and_subrecord(u8 *record_address) {
    texture_build_a_hex_48_byte_two_color_swapped_pattern_blocks_returns_base(record_address, &D_800D15C4);
    initialize_shop_display_records((void *)(record_address + 0x48), (S_800B0870_1 *)&D_800D15C4);
}
