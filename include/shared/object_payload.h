#ifndef SHARED_OBJECT_PAYLOAD_H
#define SHARED_OBJECT_PAYLOAD_H
#include "common.h"


/* Exact access views shared across registered binary consumers. */
/* Object constructor result projection exposing its +8 payload pointer. */
/* Partial object header exposing the position/payload pointer at +8.
 * Constructors supply this pointer; callers retain their own view of the pointed-to record. */
typedef struct ObjectPayloadView {
    unsigned char pad_00[0x8];
    void * unk_08; /* object position/payload pointer at header +8 */
} ObjectPayloadView;

/* Catalog object data pointer at +0x08; extent 0x0C. */
typedef struct CatalogObjectPayloadView {
    unsigned char pad_00[0x8];
    void * aux;
} CatalogObjectPayloadView;

/* Three default record words copied into the catalog secondary record. */
/* Three default words copied into a catalog display record.
 * initialize_catalog_view_records copies the stored template into each secondary record. */
typedef struct {
    int unk0;
    int unk4;
    int unk8;
} CatalogRecordDefaults;

#endif
