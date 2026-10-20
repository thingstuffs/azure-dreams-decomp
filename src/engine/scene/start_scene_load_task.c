#include "common.h"

/* task struct returned by create_deferred_resource_transition_task; only field 0x10 (a function
   pointer callback) is touched here */
typedef struct S_80051164_task {
    u8 pad[0x10];
    void (*unk10)(void);
} S_80051164_task;

/* struct passed as a0 to start_scene_load_task; unk4 points to the task struct
   allocated elsewhere (e.g. stored by a previous create_deferred_resource_transition_task call) */
typedef struct S_80051164 {
    s32 unk0;
    S_80051164_task *unk4;
} S_80051164;

extern void *create_deferred_resource_transition_task(s16 a0, s16 a1, void *callback, void *arg);
extern void load_scene_record(void *a0);
extern void propagate_scene_flag(void);

/* Creates a task and, on success, updates the owner's existing task callback. */
void start_scene_load_task(S_80051164 *owner)
{
    void *new_task = create_deferred_resource_transition_task(1, 0x1E, (void *)load_scene_record, owner);

    if (new_task != 0) {
        owner->unk4->unk10 = propagate_scene_flag;
    }
}
