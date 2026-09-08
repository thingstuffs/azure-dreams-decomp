#include "common.h"

extern void *func_80043704(s16 a0, s32 a1);
extern void *func_800437A4(s16 a0, s32 a1);
extern s32 func_8003E4FC(s32 a0, void *a1, void *a2);

/* Registers two callbacks for event kind 6 using a shared ID. */
void func_800479D4(s32 first_value, s32 second_value, s16 callback_id) {
    func_8003E4FC(6, func_80043704(callback_id, first_value), 0);
    func_8003E4FC(6, func_800437A4(callback_id, second_value), 0);
}
