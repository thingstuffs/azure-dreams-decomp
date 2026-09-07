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

extern s16 func_8003F794(s32, s32);
extern Task *func_8003FC64(s32);
extern void func_80040454(void);
extern void func_80043FD0(void);
extern u8 D_80080A84[16];

Task *func_80044144(s16 arg0, s16 arg1, s32 arg2, s32 arg3)
{
    TaskPayload *payload;
    Task *task;

    task = func_8003FC64(0);
    if (task != 0) {
        task->callback = func_80043FD0;
        payload = &task->payload;
        if (arg0 == 1) {
            payload->field_8 = func_8003F794(6, arg1);
        } else if (arg0 == 0) {
            payload->field_8 = func_8003F794(5, arg1);
            func_80040454();
            D_80080A84[2] = 0;
        }
        payload->field_4 = arg3;
        payload->field_A = arg0;
        payload->field_C = arg1;
        payload->field_0 = arg2;
    }
    return task;
}
