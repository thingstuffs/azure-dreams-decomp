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

/* summary: registers a new task (id 1, priority 0x1E) running
   func_800510A0 with a0 as its argument. On success, patches the
   callback field at offset 0x10 of the struct pointed to by a0->unk4
   to func_800510DC. */
void func_80051164(S_80051164 *a0)
{
    void *v0 = func_80044144(1, 0x1E, (void *)func_800510A0, a0);

    if (v0 != 0) {
        a0->unk4->unk10 = func_800510DC;
    }
}
