#include "common.h"
#include "shared/game_work.h"
#include "town/map.h"

typedef struct S_800A51CC_0 {
    union {
        struct { s32 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x2]; u16 v; } at02;
    } unk_00;   /* overlapping accesses */
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    u8 pad_06[0xA];
    union {
        struct { s32 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x2]; u16 v; } at02;
    } unk_10;   /* overlapping accesses */
    union { s16 s; u16 u; } unk_14;   /* accessed as both */
    u8 pad_16[0x2];
    s32 unk_18;
    u8 pad_1C[0x4];
    void * unk_20;
} S_800A51CC_0;   /* arg0 in update_current_and_saved_coordinates */

extern u8 D_800A526C[16];

/* Update current and saved coordinates from the reference, or set state 9 if they differ. */
void update_current_and_saved_coordinates(S_800A51CC_0 *object)
{
    GameWork *reference;
    s32 position_pair;
    u16 coord;

    reference = &g_game_work;
    position_pair = object->unk_00.at00.v;
    if ((position_pair != *(s32 *)&reference->view.view_offset.words[0]) ||
        (object->unk_04.s != reference->view.view_offset.parts.view_offset_z)) {
        if ((position_pair != object->unk_10.at00.v) ||
            (object->unk_04.s != object->unk_14.s)) {
            object->unk_18 = 9;
            object->unk_20 = D_800A526C;
            return;
        }

        coord = *(u16 *)&reference->view.view_offset.parts.view_offset_x;
        object->unk_00.at00u.v = coord;
        object->unk_10.at00u.v = coord;
        coord = *(u16 *)&reference->view.view_offset.parts.view_offset_y;
        object->unk_00.at02.v = coord;
        object->unk_10.at02.v = coord;
        coord = *(u16 *)&reference->view.view_offset.parts.view_offset_z;
        object->unk_04.u = coord;
        object->unk_14.u = coord;
    }
}
