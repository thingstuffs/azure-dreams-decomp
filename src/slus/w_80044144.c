#include "shared/object_node.h"
#include "common.h"

#include "common.h"

typedef struct TaskPayload {
    s32 field_0;
    s32 field_4;
    s16 field_8;
    s16 field_A;
    s16 field_C;
} TaskPayload;

typedef struct Task {
    u8 pad_00[0x10];
    void (*callback)(void);
    u8 pad_14[0x0C];
    TaskPayload payload;
} Task;

extern s16 reserveRuntimeSlot(s16 slot_id, s16 slot_value);
extern void clearFlagsOnResourceList(void);
extern void updateDeferredResourceTransitionTask(void);
extern u8 D_80080A84[3];

/* Creates a task with a mode-dependent lookup result and the supplied payload values. */
Task *createDeferredResourceTransitionTask(s16 mode, s16 lookup_id, s32 payload_word_0, s32 payload_word_4)
{
    TaskPayload *payload;
    Task *task;

    task = (Task *)func_8003FC64(0);
    if (task != 0) {
        task->callback = updateDeferredResourceTransitionTask;
        payload = &task->payload;
        if (mode == 1) {
            payload->field_8 = reserveRuntimeSlot(6, lookup_id);
        } else if (mode == 0) {
            payload->field_8 = reserveRuntimeSlot(5, lookup_id);
            clearFlagsOnResourceList();
            D_80080A84[2] = 0;
        }
        payload->field_4 = payload_word_4;
        payload->field_A = mode;
        payload->field_C = lookup_id;
        payload->field_0 = payload_word_0;
    }
    return task;
}
