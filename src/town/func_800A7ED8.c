#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_8009431C_arg0.h"

void townHandleResolveBoundingBoxOverlapsLinkedCollidersAlongLeastPenetratingAxis();           /* extern */
void townProcessSceneRecordUpdate();     /* extern */
void townAddMotionDeltasToPosition();                      /* extern */
void townApplyTheEnabledMovementOffsetsAddingZOffsetOnlyPositive();                      /* extern */
void func_80095460();                      /* extern */
void townUpdateTheSField10UsingCallee8008FE90();                   /* extern */
s32 townUpdateObjectAndClearStatusFields();                      /* extern */
void townTurnEntityTowardTarget();     /* extern */
extern s32 D_800903FC[];
extern M2C_UNK D_800CFCB4;
extern M2C_UNK D_800FE490;


typedef struct S_800A5638_0_pre {
    s32 unk_00;
    u8 pad_04[0xA];
    u16 unk_0E;
} S_800A5638_0_pre;   /* the 0x10 bytes before arg0 in townUpdateEffectRecordAndDispatch, addressed as arg0[-1] */


/* Updates the record, invokes its handler, clamps values, and dispatches follow-up processing. */
void townUpdateEffectRecordAndDispatch(void *handler, EntityRec *record, s32 context) {
    townApplyTheEnabledMovementOffsetsAddingZOffsetOnlyPositive(record);
    townUpdateTheSField10UsingCallee8008FE90(&D_800FE490);
    townAddMotionDeltasToPosition(record);
    townUpdateObjectAndClearStatusFields(record);
    func_80095460(record);
    townHandleResolveBoundingBoxOverlapsLinkedCollidersAlongLeastPenetratingAxis(&D_800CFCB4, record);
    ((Rec_func_8009431C_arg0 *)handler)->unk_00.as_x78b360(handler, record, context);
    if (!(((S_800A5638_0_pre *)handler)[-1].unk_0E & 0x8000)) {
        if (record->y.v <= 0x06500000) {
            record->y.v = 0x06500000;
            record->unk_10 = 0x180000;
            if (record->z.v > 0) {
                record->z.v = 0;
            }
        }
        if (((S_800A5638_0_pre *)handler)[-1].unk_00 == &D_800903FC) {
            townProcessSceneRecordUpdate(handler, record, context);
            return;
        }
        townTurnEntityTowardTarget(handler, record, context);
    }
}
