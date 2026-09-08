#include "common.h"

typedef struct {
    u16 field_00;
    u16 field_02;
    u8 pad_04[8];
    s32 field_0C;
    s32 field_10;
    u16 field_14;
    u16 field_16;
} DungeonState;

extern DungeonState D_80083460;
extern s32 func_800A2B5C(void *);
extern s32 func_800ADAE4(void *, void *);

/* Attempts a pending action and updates dungeon state on success. */
s32 func_800AB464(void *action, s32 unused, void *source, void *target) {
    DungeonState *state;
    s32 result;

    if (*((u8 *)action + 0x9B) == 0) {
        *((u8 *)target + 0x71) &= 0x7F;
        state = &D_80083460;
        if (state->field_02 & 0x2000) {
            return 0;
        }
        if ((func_800A2B5C(target) << 16) != 0) {
            return 0;
        }

        result = func_800ADAE4(source, target);
        if ((result << 16) != 0) {
            state->field_0C = 0;
            state->field_14 -= 1;
            *((u8 *)action + 0x9B) = 1;
        }
    } else {
        result = 1;
    }
    return (s16)result;
}
