#include "common.h"
#include "shared/game_work.h"
#include "records/Rec_func_80090C68_arg0.h"


typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) \
(*(type_ptr)((u8 *)(expr) + (offset)))

extern void townDispatchActorInteractionActions(void *, void *, s32);
extern void townInitializeSharedSceneData(void *record, void *context, s32 update_arg);
extern s32 townRunTheActionSequenceContextUnlessFlagHexA5Set(void *context);
extern void townRunTheThreeUpdateRoutinesContext(void *context);
extern void townClearEntityRecordFields(void *record);


/* Run follow-up updates if the record value is unchanged and flag 0x80 is set. */
void townUpdateEntityCountdownTransition(void *record, void *context, s32 update_arg) {
    s32 saved_value;
    GameWork *state_words;

    state_words = &gameWork;
    saved_value = ((Rec_func_80090C68_arg0 *)record)->unk_00;
    townDispatchActorInteractionActions(record, context, update_arg);
    if ((saved_value == ((Rec_func_80090C68_arg0 *)record)->unk_00) &&
        (state_words->buttons & 0x80)) {
        townClearEntityRecordFields(context);
        townRunTheThreeUpdateRoutinesContext(context);
        if (townRunTheActionSequenceContextUnlessFlagHexA5Set((u8 *)record - 0x20) != 0) {
            townInitializeSharedSceneData(record, context, update_arg);
        }
    }
}
