#ifndef SHARED_DUNGEON_IMAGE_BUFFER_H
#define SHARED_DUNGEON_IMAGE_BUFFER_H
#include "common.h"
/* Existing runtime image scratch area. Resident uploadImageTiles receives this
 * base from func_80047EEC. No fixed retail allocation, contents or size is owned
 * here; bank-specific offset tables select image records within that area. */
extern u8 D_8014A000[];
#endif
