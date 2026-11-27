#include "shared/game_work.h"
/* gcc 2.8.1 -O2 — own TU (copy_camera_position_from_object: callback fwd-decl conflict) */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* Inner struct pointed to by arg->unk20; only offsets 0x2/0x6/0xA are read (u16 fields). */
typedef struct {
    u8 pad0[2];
    u16 x_int;
    u8 pad4[2];
    u16 y_int;
    u8 pad8[2];
    u16 z_int;
} SrcStruct;

/* Outer struct passed in; only the pointer at offset 0x20 is used. */
typedef struct {
    u8 pad0[0x20];
    SrcStruct *position_source;
} InStruct;

/*
 * Copies three nested 16-bit fields into the global state.
 *
 * Destination global struct; only offsets 0xBC/0xBE/0xC0 are written. Size forces hi/lo access.
 */
void copy_camera_position_from_object(InStruct *object)
{
    SrcStruct *source = object->position_source;

    g_game_work.view.camera_position.parts.camera_position_x = source->x_int;
    g_game_work.view.camera_position.parts.camera_position_y = source->y_int;
    g_game_work.view.camera_position.parts.camera_position_z = source->z_int;
}
