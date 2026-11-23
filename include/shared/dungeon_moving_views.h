#ifndef SHARED_DUNGEON_MOVING_VIEWS_H
#define SHARED_DUNGEON_MOVING_VIEWS_H
#include "common.h"
/* Partial moving-effect views. */
typedef struct SignedWordView {
    u16 unk_00;
} SignedWordView;   /* D_80026470 in func_80024050 */

typedef struct SignedHalfView {
    u16 unk_00;
} SignedHalfView;   /* D_80026474 in func_80024050 */

typedef struct UnsignedWordView {
    u16 unk_00;
} UnsignedWordView;   /* D_80026476 in func_80024050 */

typedef struct UnsignedHalfView {
    u32 unk_00;
} UnsignedHalfView;   /* D_800265C0 in func_80024050 */

typedef struct UnsignedByteView {
    u32 unk_00;
} UnsignedByteView;   /* D_800265C4 in func_80024050 */

typedef struct MovingParameter {
    u8 pad_00[0x8];
    u32 unk_08;
} MovingParameter;   /* addr in func_80024050 */

/* Unsigned integer-half view of an object position, sharing storage supplied by allocate_list_node.
 * Effect constructors copy these components from the owner position. */
typedef struct MovingPosition {
    u8 pad_00[0x2];
    u16 x; /* integer X component of the position, in world units */
    u8 pad_04[0x2];
    u16 y; /* integer Y component on the ground plane, in world units */
    u8 pad_08[0x2];
    u16 z; /* integer height component, in world units */
} MovingPosition;   /* record in func_80024050 */

typedef struct OriginOffsetView {
    u8 pad_00[0x4];
    u16 unk_04;
} OriginOffsetView;   /* scratch in func_80024050 */

/* Map-tile view of the sprite record reached through an actor header.
 * Sprite constructors initialize these coordinates; item effects read them. */
typedef struct MovingTile {
    u8 pad_00[0x24];
    u8 tile_x; /* map column; world tile center is (column << 6) + 32 */
    u8 tile_y; /* map row; world tile center is (row << 6) + 32 */
} MovingTile;   /* target_record in func_80024050 */

typedef struct MovingHeight {
    u16 unk_00;
} MovingHeight;   /* D_800269C8 in func_80024050 */



#endif
