#ifndef SHARED_TOWN_SCENE_IMAGE_H
#define SHARED_TOWN_SCENE_IMAGE_H

#include "common.h"

/* A TOWN scene image is one packed CD read to 0x80016000.  The scene loader reads it whole:
 * set_next_scene (0x8003BAF8) copies a scene descriptor's record pointer (+8) into the pending scene,
 * load_cur_scene (0x80053C6C) passes it to Control_CD(6), and the CD worker decodes the record as
 * word 0 = sector count << 23 | destination, word 1 = disc LBA (r115_opus_town scene_loader_receipt.json).
 * Word 0 of every image is the root pointer D_80016000, patched at run time; two entry records follow. */
typedef struct TownSceneEntry {
    /* 0x00 */ u32 magic; /* 0x4C070707 in every TOWN scene image */
    /* 0x04 */ void (*entry)(void);
    /* 0x08 */ u32 value;
} TownSceneEntry;

/* One word of a scene image's initialized data whose words are either plain values or link-time addresses
 * inside the same image (the image's own tables are not typed yet). */
typedef union TownStoredWord {
    u32 value;
    const void *address;
} TownStoredWord;

#endif
