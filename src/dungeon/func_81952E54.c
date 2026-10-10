#include "modules/dungeon_ovl_1972800.h"
#include "common.h"
#include "shared/dir_step.h"

typedef struct SpawnPosition {
    u16 pad_00, x, pad_04, y, pad_08;
    union { u16 bits; s16 signed_value; } z;
} SpawnPosition;

typedef struct SpawnSprite {
    u8 pad_00[8];
    void *frames;
    u8 pad_0C[4];
    s16 size;
    u8 pad_12[2];
    u16 flags;
} SpawnSprite;

typedef struct SpiralState {
    u8 pad_00[0x0C];
    void *target;
    u16 x, y, z;
    u8 pad_16[0x10];
    u16 angle, reverse_angle;
    u8 pad_2A[2];
    s16 lifetime;
    u8 pad_2E[4];
    s16 mirrored;
} SpiralState;

/* The 0x20-byte object-list header that precedes an effect's record. */
typedef struct SpawnHeader {
    u8 pad_00[8];
    SpawnPosition *position;
    SpawnSprite *sprite;
    void (*callback)(void *, void *, void *);
    u8 pad_14[0xC];
} SpawnHeader;

typedef struct SpawnNode {
    SpawnHeader header;
    SpiralState state;
} SpawnNode;

typedef struct GridOrigin {
    u8 pad_00[0x24];
    u8 x, y;
} GridOrigin;

typedef struct OriginHeight {
    u8 pad_00[0x88];
    u16 height;
} OriginHeight;


/* Spawn the spiraling effect unless the shared bank stop flag is set.
 * The third ABI argument is unused in retail. The final argument mirrors
 * the direction and is retained in the spawned state.
 */
void func_80024654(void *anchor, s16 angle, s16 unused, void *target, s32 mirrored)
{
    SpawnNode *node;
    SpiralState *state;
    SpawnPosition *position;
    SpawnPosition *target_position;
    SpawnSprite *sprite;
    s32 height;
    s32 coordinate;
    s32 coordinate_y;
    TileObject *origin;
    s32 offset;

    if (D_800249A4 != 0) return;
    node = (SpawnNode *)func_8003FD64(0x212, (ObjectNodeHeader **)anchor);
    if (node == 0) return;
    node->header.callback = func_8002434C;
    func_8004491C(node, (s32)D_800CEEFC);
    position = node->header.position;
    sprite = node->header.sprite;
    sprite->frames = D_80024998;
    sprite->size = 0x20;
    sprite->flags |= 0xC;
    state = &node->state;
    state->angle = angle;
    if (mirrored != 0) state->angle = angle + 0x800;
    state->reverse_angle = 0x1000 - state->angle;
    if (target == 0) {
        origin = &D_80082E80;
        offset = ((u32)angle >> 9) & 7;
        coordinate = ((origin->tileX + dirStepX[offset]) << 6) + 0x20;
        position->x = coordinate;
        state->x = coordinate;
        coordinate_y = ((origin->tileY + dirStepY[offset]) << 6) + 0x20;
        position->y = coordinate_y;
        state->y = coordinate_y;
        state->z = position->z.bits = (u16)D_800814A8->unk_88;
    } else {
        target_position = ((SpawnHeader *)target - 1)->position;
        state->x = position->x = target_position->x;
        state->y = position->y = target_position->y;
        state->z = target_position->z.bits;
        height = func_800BCB04(position->x, position->y, target_position->z.signed_value);
        if ((s16)height > 0x200) height = target_position->z.bits;
        position->z.bits = height;
    }
    state->target = target;
    state->lifetime = 0x40;
    state->mirrored = mirrored;
}
