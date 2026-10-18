#include "modules/dungeon_ovl_1972800.h"
#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern void process_effect_modes_and_completion(void *state);

typedef struct S_80024908_0 {
    u8 pad_00[0x10];
    void (*unk_10)(void *);
} S_80024908_0;

typedef struct S_80024908_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x16];
    s16 unk_26;
    u8 pad_28[0x4];
    s16 unk_2C;
    u8 pad_2E[0x2];
    s16 unk_30;
} S_80024908_1;

/* Allocate an object and initialize its handler and state fields. */
void allocate_and_initialize_effect_object(s32 alloc_arg, s16 value_26, s16 value_30, s32 value_0c) {
    void *object;
    S_80024908_1 *state;

    object = func_8003FD64(0x200, (ObjectNodeHeader **)alloc_arg);
    if (object != 0) {
        ((S_80024908_0 *)object)->unk_10 = process_effect_modes_and_completion;
        state = object + 0x20;
        state->unk_26 = value_26;
        state->unk_0C = value_0c;
        state->unk_30 = value_30;
        state->unk_2C = 0x40;
    }
}
