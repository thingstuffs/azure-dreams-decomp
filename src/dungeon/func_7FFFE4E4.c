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

/* Updates motion, handles ground contact, and checks the tile height limit. */
void func_7FFFE4E4(void *owner, void *actor, void *motion, s32 callback_arg) {
    s16 ground_height;
    s32 ground_height_s32;

    townAddHex20000SSignedOffsetHex14(motion);
    if (*(s32 *)((u8 *)motion + 0x14) > 0x200000) {
        *(s32 *)((u8 *)motion + 0x14) = 0x200000;
    }
    townAddMotionDeltasToPosition(motion);
    ground_height = townGetSmallerQueryResultCappedHex80WritesAssociatedOutput(motion, ((u8 *)&D_800FE488));
    townCallTheSameContextBothProcessingRoutines(actor, motion);
    townHandleResolveBoundingBoxOverlapsLinkedCollidersAlongLeastPenetratingAxis(actor, motion);
    ground_height_s32 = ground_height;
    if (*(s16 *)((u8 *)motion + 0xA) >= ground_height_s32) {
        townSetTheStateFlagInitializeSFixedPointClearPairedField(actor, motion, ground_height_s32);
        ((Callback *)(*(void **)((u8 *)owner + 0x58)))[1](owner, actor, motion, callback_arg);
    } else if (*(u8 *)((u8 *)actor + 0x3B) != 0) {
        *(s32 *)((u8 *)motion + 0xC) = 0;
        *(s32 *)((u8 *)motion + 0x10) = 0;
        *(s32 *)((u8 *)motion + 0x14) = 0;
        ((Callback *)(*(void **)((u8 *)owner + 0x58)))[1](owner, actor, motion, callback_arg);
    }
    if ((*(u16 *)((u8 *)owner - 2) & 0x8000) == 0 &&
        *(void **)((u8 *)owner + 0x50) == D_8009B454) {
        s32 tile_type;

        tile_type = townCheckMaskedValueInCurrentRange((u16)townReadMapCellAtWorldPosition(
            *(s16 *)((u8 *)motion + 2), *(s16 *)((u8 *)motion + 6)));
        if (tile_type != 0) {
            s16 height = *(s16 *)((u8 *)motion + 0xA);
            s16 height_limit = D_800D45AA[tile_type];

            if (height > height_limit) {
                SD_Call(0x517);
            }
        }
    }
}
