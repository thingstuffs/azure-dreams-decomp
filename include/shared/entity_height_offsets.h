#ifndef SHARED_ENTITY_HEIGHT_OFFSETS_H
#define SHARED_ENTITY_HEIGHT_OFFSETS_H
/* Unsigned height offsets indexed by the entity byte at +0x13. Consumers add
 * or subtract the value (or its half) from z, including 16.16 coordinates.
 * Neither the index's game meaning nor the table extent is established. */
typedef unsigned char EntityHeightOffset;
extern EntityHeightOffset D_800DDC40[];

/* Exact access views shared across registered binary consumers. */
/* Three signed alternatives selected from the actor height-band value record. */
typedef struct HeightBandValues {
    int unk_00;
    int unk_04;
    int unk_08;
} HeightBandValues;

#endif
