#include "shared/game_work.h"
/* gcc 2.8.1 -O2 — own TU (copy_view_halfword_triplet: callback fwd-decl conflict) */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* Inner struct pointed to by arg->unk20; only offsets 0x2/0x6/0xA are read (u16 fields). */
typedef struct {
    u8 pad0[2];
    u16 unk2;
    u8 pad4[2];
    u16 unk6;
    u8 pad8[2];
    u16 unkA;
} SrcStruct;

/* Outer struct passed in; only the pointer at offset 0x20 is used. */
typedef struct {
    u8 pad0[0x20];
    SrcStruct *unk20;
} InStruct;

/*
 * Copies three nested 16-bit fields into the global state.
 *
 * Destination global struct; only offsets 0xBC/0xBE/0xC0 are written. Size forces hi/lo access.
 */
void copy_view_halfword_triplet(InStruct *object)
{
    SrcStruct *source = object->unk20;

    g_game_work.view.camera_position.parts.camera_position_x = source->unk2;
    g_game_work.view.camera_position.parts.camera_position_y = source->unk6;
    g_game_work.view.camera_position.parts.camera_position_z = source->unkA;
}
