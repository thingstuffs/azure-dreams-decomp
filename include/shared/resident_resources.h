#ifndef SHARED_RESIDENT_RESOURCES_H
#define SHARED_RESIDENT_RESOURCES_H
#include "common.h"


/* Exact access views shared across registered binary consumers. */
/* Signed key and bitmap-bit value in the resident zero-terminated mapping table. */
typedef struct ResidentBitmapEntry {
    short key;
    short value;
} ResidentBitmapEntry;

/* Category/index pair in the twenty-entry table shared by resource slot operations. */
typedef struct ResourceCategoryPair {
    short a;
    short b;
} ResourceCategoryPair;

/* Signed cached object code and state selector in D_80083D78. */
typedef struct CachedObjectCodePair {
    short unk_00;
    short unk_02;
} CachedObjectCodePair;

/* Signed halfword at +A used to initialize a resource-slot state. */
typedef struct ResourceSlotStateView {
    unsigned char pad_00[0xA];
    short unk_0A;
} ResourceSlotStateView;

/* Twelve-byte resource-read state with one active word and two opaque signed words. */
typedef struct ResourceReadState {
    int field0;
    int pad4;
    int pad8;
} ResourceReadState;

#endif
