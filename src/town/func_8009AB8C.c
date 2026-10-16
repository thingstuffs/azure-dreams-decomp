#include "shared/position_query.h"
#include "common.h"

extern u16 townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(void *position, void *out_value);
extern void townComputeAndClampsVectorBasedAdjustmentUpdatesTown(void *obj, s16 base_value, void *vec_ptr);
extern void townInitializeRecordWithHandlerTable(void *record, void *setup_value, s32 init_value);

extern u8 D_800CFCB4[];

/* Conditionally refreshes object data before passing it to townInitializeRecordWithHandlerTable. */
void townRefreshObjectPositionAndInitialize(void *context, void *object, s32 mode) {
    void *state;

    if (D_800CFCB4[0x3B] != 0) {
        state = *(void **)(*(void **)(D_800CFCB4 + 0x20) + 8);
        if ((*(s32 *)((u8 *)state + 0xC) != 0) ||
            (*(s32 *)((u8 *)state + 0x10) != 0) ||
            (*(s32 *)((u8 *)state + 0x14) != 0)) {
            townComputeAndClampsVectorBasedAdjustmentUpdatesTown(object, townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(object, ((u8 *)&D_800FE488)),
                          ((u8 *)&D_800FE488));
        }
    } else {
        townComputeAndClampsVectorBasedAdjustmentUpdatesTown(object, townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(object, ((u8 *)&D_800FE488)),
                      ((u8 *)&D_800FE488));
    }
    townInitializeRecordWithHandlerTable(context, object, mode);
}
