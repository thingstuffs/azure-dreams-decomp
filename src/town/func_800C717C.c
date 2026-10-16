#include "common.h"
#include "shared/object_index_slots.h"

typedef struct {
    s8 val;
    u8 pad[7];
} Rec8;

extern void townInitializeObjectEntries(void *state, s32 output, void *entries);
extern s16 townClampTransformCoordinateDeltas(s16 x, s16 y, s32 origin);
extern void func_800C3C5C(void);

/* Initialize the object's animation, clear its record flag, and update its facing. */
void townInitializeObjectAnimationAndFacing(void *object, s32 position, s32 animation_state) {
    townInitializeObjectEntries(object, animation_state, *(void **)((u8 *)*(void **)((u8 *)object + 0x80) + 0x14));
    D_80082660[*(s32 *)((u8 *)object + 0x60)].unk_00 = 0;
    *(void **)((u8 *)object + 0x54) = (void *)func_800C3C5C;
    *(s16 *)((u8 *)object + 0x72) = townClampTransformCoordinateDeltas(
        *(s16 *)((u8 *)object + 0x88),
        *(s16 *)((u8 *)object + 0x8A),
        position);
}
