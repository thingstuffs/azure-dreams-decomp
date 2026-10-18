#ifndef SHARED_TYPES3C_TYPES_H
#define SHARED_TYPES3C_TYPES_H
#include "common.h"

/* Catalog object data pointer at +0x08; extent 0x0C. */
typedef struct CatalogObjectPayloadView {
    u8 pad_00[0x8];
    void * unk_08;
} CatalogObjectPayloadView;

/* Three default record words copied into the catalog secondary record. */
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} CatalogRecordDefaults;

/* Effect object payload pointer at +0x08; extent 0x0C. */
typedef struct EffectObjectPayloadView {
    u8 pad_00[0x8];
    void * unk_08;
} EffectObjectPayloadView;

/* Signed position integer halves; extent 0x0C, alignment 2. */
typedef struct SignedPositionView {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} SignedPositionView;

/* Unsigned sprite flags at +0x14; extent 0x16. */
typedef struct SpriteFlagsView {
    u8 pad_00[0x14];
    u16 unk_14;
} SpriteFlagsView;

#endif
