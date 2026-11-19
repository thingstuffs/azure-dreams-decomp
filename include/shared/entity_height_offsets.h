#ifndef SHARED_ENTITY_HEIGHT_OFFSETS_H
#define SHARED_ENTITY_HEIGHT_OFFSETS_H
/* Unsigned height offsets indexed by the entity byte at +0x13. Consumers add
 * or subtract the value (or its half) from z, including 16.16 coordinates.
 * Neither the index's game meaning nor the table extent is established. */
typedef unsigned char EntityHeightOffset;
extern EntityHeightOffset entity_height_offsets[];

/* Exact access views shared across registered binary consumers. */
/* The Town actor selects one of three resident sprite sources by height band. */
typedef struct HeightBandValues {
    void *sources[3];
} HeightBandValues;

#endif
