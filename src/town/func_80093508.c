#include "common.h"
#include "shared/game_work.h"
#include "records/Rec_func_80090C68_arg0.h"


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void townDispatchActorInteractionActions(void *, s32, s32);
extern void townInitializeSharedSceneData();
extern s32 func_80093DD8();
extern s32 townRunTheActionSequenceContextUnlessFlagHexA5Set();
extern void townRunTheThreeUpdateRoutinesContext();
extern void townClearEntityRecordFields();
/* Updates the record, then handles a flagged action or countdown if its state is unchanged. */
void townUpdateEntityAndHandleFlaggedAction(void *record, s32 context, s32 update_arg) {
    s32 previous_state;
    GameWork *global_state;
    u16 ticks_left;

    global_state = &gameWork;
    previous_state = ((Rec_func_80090C68_arg0 *)record)->unk_00;
    townDispatchActorInteractionActions(record, context, update_arg);
    if (previous_state == ((Rec_func_80090C68_arg0 *)record)->unk_00) {
        if (global_state->buttons & 0x80) {
            townClearEntityRecordFields(context);
            townRunTheThreeUpdateRoutinesContext(context);
            if (townRunTheActionSequenceContextUnlessFlagHexA5Set(record - 0x20) != 0) {
                townInitializeSharedSceneData(record, context, update_arg);
                return;
            }
        } else {
            ticks_left = ((Rec_func_80090C68_arg0 *)record)->unk_0A - 1;
            ((Rec_func_80090C68_arg0 *)record)->unk_0A = ticks_left;
            if ((ticks_left << 0x10) <= 0) {
                func_80093DD8(record, context, update_arg);
            }
        }
    }
}

