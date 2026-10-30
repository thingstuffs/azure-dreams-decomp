/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "frontend/card.h"


extern u8 D_8040C5C0[];
extern u16 D_8040C5DE_LOAD[5];
extern u16 D_8040C5DE_STORE[5];
extern u8 D_8040086C[];
extern u8 D_80400894[];
extern void *func_8003C714(s32 value, void *ptr, s32 value_2);
extern s32 func_80047FD8(void *object);
extern void func_8007BEF0(s32 value);
extern void func_8007BFE0(void *state, s32 value);
extern void func_8007C040(void *data, void *data_2, s32 value);
extern void set_record_values(void *state, s32 init_value_a, s32 init_value_b);
extern void memory_process_handles_and_mark_object(void *object);

/* Creates or resets the town object, initializes its state, and installs its callback. */
void *memory_init_work_object_and_callback(s32 init_value_a, s32 init_value_b) {
    void *object;
    u8 *state;

    object = D_8040C5C0;
    state = (u8 *)object + 0x20;
    if (func_80047FD8(object) != 0 || ((object = func_8003C714(0, D_8040C5C0, 0x19)) == 0 && (func_8007C040(D_8040086C, D_80400894, 0x173), func_8007BEF0(1), 1))) {
        memory_process_handles_and_mark_object(object);
        D_8040C5DE_STORE[0] = (u16) (D_8040C5DE_LOAD[0] & 0x7FFF);
        func_8007BFE0(state, 0x44);
    }
    set_record_values(state, init_value_a, init_value_b);
    *(void **)((u8 *)object + 0x10) = (void *)card_dev_create_slot_screen_objects;
    return object;
}
