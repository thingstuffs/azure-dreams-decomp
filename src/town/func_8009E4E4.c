#include "shared/position_query.h"
#include "common.h"

typedef void (*Callback)(void *, void *, void *, s32);

extern void townAddHex20000SSignedOffsetHex14(void *);
extern void townAddMotionDeltasToPosition(void *);
extern s16 townGetSmallerQueryResultCappedHex80WritesAssociatedOutput(void *, void *);
extern void townSetTheStateFlagInitializeSFixedPointClearPairedField(void *, void *, s16);
extern void townCallTheSameContextBothProcessingRoutines(void *, void *);
extern void townHandleResolveBoundingBoxOverlapsLinkedCollidersAlongLeastPenetratingAxis(void *, void *);
extern s32 townReadMapCellAtWorldPosition(s16, s16);
extern s32 townCheckMaskedValueInCurrentRange(u16);
extern void SD_Call(s32);

extern u8 D_8009B454[];
extern s16 D_800D45AA[];

/* Update motion, handle contact callbacks, and play the terrain height sound. */
void townUpdateMotionAndHandleTerrainContactAlt(void *entity, void *collision, void *motion, s32 callback_arg) {
    s16 contact_height;
    s32 contact_height_s32;

    townAddHex20000SSignedOffsetHex14(motion);
    if (*(s32 *)((u8 *)motion + 0x14) > 0x200000) {
        *(s32 *)((u8 *)motion + 0x14) = 0x200000;
    }
    townAddMotionDeltasToPosition(motion);
    contact_height = townGetSmallerQueryResultCappedHex80WritesAssociatedOutput(motion, ((u8 *)&D_800FE488));
    townCallTheSameContextBothProcessingRoutines(collision, motion);
    townHandleResolveBoundingBoxOverlapsLinkedCollidersAlongLeastPenetratingAxis(collision, motion);
    contact_height_s32 = contact_height;
    if (*(s16 *)((u8 *)motion + 0xA) >= contact_height_s32) {
        townSetTheStateFlagInitializeSFixedPointClearPairedField(collision, motion, contact_height_s32);
        ((Callback *)(*(void **)((u8 *)entity + 0x58)))[1](entity, collision, motion, callback_arg);
    } else if (*(u8 *)((u8 *)collision + 0x3B) != 0) {
        *(s32 *)((u8 *)motion + 0xC) = 0;
        *(s32 *)((u8 *)motion + 0x10) = 0;
        *(s32 *)((u8 *)motion + 0x14) = 0;
        ((Callback *)(*(void **)((u8 *)entity + 0x58)))[1](entity, collision, motion, callback_arg);
    }
    if ((*(u16 *)((u8 *)entity - 2) & 0x8000) == 0 &&
        *(void **)((u8 *)entity + 0x50) == D_8009B454) {
        s32 terrain_index;

        terrain_index = townCheckMaskedValueInCurrentRange((u16)townReadMapCellAtWorldPosition(
            *(s16 *)((u8 *)motion + 2), *(s16 *)((u8 *)motion + 6)));
        if (terrain_index != 0) {
            s16 height = *(s16 *)((u8 *)motion + 0xA);
            s16 terrain_height = D_800D45AA[terrain_index];

            if (height > terrain_height) {
                SD_Call(0x517);
            }
        }
    }
}
