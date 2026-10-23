#ifndef FRAGMENT_FRAGMENT_B7C20_H
#define FRAGMENT_FRAGMENT_B7C20_H
#include "common.h"
/* One packed eight-byte transfer value; the consumers only copy it. */
typedef struct { u32 word[2]; } __attribute__((packed)) TransitionWords;
typedef struct MapTile { u16 type; u16 height; u16 unk_04; } MapTile;
extern TransitionWords tile_height_upload_rect;
extern u8 packed_tile_heights[];
extern MapTile generation_cells[];
extern void LoadImage(void *transfer_value, u8 *pixels);
#endif
