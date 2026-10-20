#include "common.h"

extern void clear_entity_record_fields(void *record);
extern s32 D_800D0608[];
extern s32 D_8009AAB8;

/* Move the object toward its target and advance the state when the timer expires. */
void move_player_toward_target(void *state, void *object) {
    u16 ticks_left;

    *(s32 *)((u8 *)object + 0x14) = (D_800D0608[2] - *(s32 *)((u8 *)object + 8)) / 2;
    ticks_left = *(u16 *)((u8 *)state + 0xA) - 1;
    *(u16 *)((u8 *)state + 0xA) = ticks_left;
    if ((s16) ticks_left < 0) {
        *(s32 *)((u8 *)object + 8) = D_800D0608[2];
        clear_entity_record_fields(object);
        *(u16 *)((u8 *)state + 0xA) = 0xA;
        *(s32 **)((u8 *)state + 4) = &D_8009AAB8;
    }
}
