#ifndef FRONTEND_CARD_DEV_CARD_DIRECTORY_DATA_H
#define FRONTEND_CARD_DEV_CARD_DIRECTORY_DATA_H

#include "common.h"

/* Devkit card-server directory records at 0x80409290. The search routines
 * advance by 0x28 bytes; the remaining-block reader uses the size at 0x18. */
typedef struct DevCardDirectoryEntry {
    u8 name[0x18];
    s32 file_size;
    u8 reserved[0xC];
} DevCardDirectoryEntry;

extern DevCardDirectoryEntry dev_card_directory[];

#endif
