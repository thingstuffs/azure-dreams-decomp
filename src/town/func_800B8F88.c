#include "common.h"

extern void update_mode_display_spacing(s32 base, s16 display_mode);
extern void process_object_data_by_mode(void *object);
extern s32 D_800B6578[];

/* Advance the object's five-step sequence, then reset it and set its next handler. */
void advance_monster_status_opening(void *object) {
    s16 step;

    step = *(s16 *)((u8 *)object + 0xE);
    if (step < 5) {
        update_mode_display_spacing(*(s32 *)((u8 *)object + 0x98), step);
        *(u16 *)((u8 *)object + 0xE) = *(u16 *)((u8 *)object + 0xE) + 1;
        return;
    }
    process_object_data_by_mode(object);
    *(void **)object = &D_800B6578[0];
}
