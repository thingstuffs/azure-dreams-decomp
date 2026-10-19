#ifndef SHARED_OBJECT_PAYLOAD_H
#define SHARED_OBJECT_PAYLOAD_H
#include "common.h"


/* Exact access views shared across registered binary consumers. */
/* Object constructor result projection exposing its +8 payload pointer. */
typedef struct ObjectPayloadView {
    unsigned char pad_00[0x8];
    void * unk_08;
} ObjectPayloadView;

/* Catalog object data pointer at +0x08; extent 0x0C. */
typedef struct CatalogObjectPayloadView {
    unsigned char pad_00[0x8];
    void * unk_08;
} CatalogObjectPayloadView;

/* Three default record words copied into the catalog secondary record. */
typedef struct {
    int unk0;
    int unk4;
    int unk8;
} CatalogRecordDefaults;

#endif
