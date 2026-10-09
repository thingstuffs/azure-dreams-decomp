#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"

extern u16 D_80027452[];

/* Position block (three 4-byte slots, only the second halfword of each is used). */
typedef struct EffectPosition {
    u16 pad_00;
    u16 x;
    u16 pad_04;
    u16 y;
    u16 pad_08;
    u16 z;
} EffectPosition;

/* Render data (the header's unk_0C); only the colour word is used here. */
typedef struct RenderData {
    u8 pad_00[0xC];
    s32 color;
} RenderData;

/* The follower's record (the object header precedes it): it tracks the object stored at +8. */
typedef struct FollowerRecord {
    u8 pad_00[8];
    ObjectNodeHeader *owner;
} FollowerRecord;

/* Copy the owner's position and colour; flag completion once the owner is finished. */
void func_80024E60(FollowerRecord *record, EffectPosition *position, RenderData *render)
{
    ObjectNodeHeader *owner;
    EffectPosition *owner_pos;
    s32 owner_done;

    owner = record->owner;
    owner_done = owner->flags & 0x8000;
    D_80027452[0]++;
    if (owner_done != 0) {
        ((ObjectNodeHeader *)record - 1)->flags |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
        return;
    }
    render->color = ((RenderData *)owner->unk_0C)->color;
    owner_pos = record->owner->unk_08;
    position->x = owner_pos->x;
    position->y = owner_pos->y;
    position->z = owner_pos->z;
}
