#include "common.h"
#include "m2c_compat.h"

typedef struct {
    s32 value;
} Timer;

extern void initialize_object_entries();
extern M2C_UNK D_800C78A8;
extern s32 D_800D5FE8;
extern Timer D_80113220;

/* Initialize the object callback and set the shared timer to 16. */
void initialize_mother_event_with_timer_16(void *object, s32 unused, s32 init_data) {
    Timer *timer;

    initialize_object_entries(object, init_data, &D_800D5FE8);
    *(s32 **)((u8 *)object + 0x50) = &D_800C78A8;
    timer = &D_80113220;
    timer->value = 0x10;
}
