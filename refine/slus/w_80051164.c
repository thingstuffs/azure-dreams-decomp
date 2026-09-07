#include "common.h"

/* task struct returned by func_80044144; only field 0x10 (a function
   pointer callback) is touched here */
typedef struct S_80051164_task {
    u8 pad[0x10];
    void (*unk10)(void);
} S_80051164_task;

/* struct passed as a0 to func_80051164; unk4 points to the task struct
   allocated elsewhere (e.g. stored by a previous func_80044144 call) */
typedef struct S_80051164 {
    s32 unk0;
    S_80051164_task *unk4;
} S_80051164;

extern void *func_80044144(s16 a0, s16 a1, void *callback, void *arg);
extern void func_800510A0(void *a0);
extern void func_800510DC(void);

/* Creates a task and, on success, updates the owner's existing task callback. */
void func_80051164(S_80051164 *owner)
{
    void *new_task = func_80044144(1, 0x1E, (void *)func_800510A0, owner);

    if (new_task != 0) {
        owner->unk4->unk10 = func_800510DC;
    }
}
