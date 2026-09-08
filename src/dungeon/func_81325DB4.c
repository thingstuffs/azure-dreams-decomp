#include "common.h"

typedef struct DungeonState {
    u8 pad0[10];
    s16 field_A;
    u8 pad_C[4];
    s32 field_10;
} DungeonState;

extern DungeonState D_80083460;
extern u8 D_8016B778[];
extern void func_8016AD00(void);

/* Advances the object's counter and switches its script when the dungeon is ready. */
void func_8016D5B4(void *object, s32 unused_1, s32 unused_2, s32 state_base)
{
    u8 previous_count;
    u8 count;

    previous_count = *(u8 *)((u8 *)object + 0x9B);
    count = previous_count + 1;
    *(u8 *)((u8 *)object + 0x9B) = count;

    if (count == 1) {
        s32 state_code = D_80083460.field_10;

        if (state_code == state_base - 0x20) {
            D_80083460.field_10 = state_code & 0x7FFFFFFF;
            return;
        }
    } else if (count >= 5) {
        DungeonState *dungeon = &D_80083460;

        *(u8 *)((u8 *)object + 0x9B) = previous_count;
        if (dungeon->field_A == 0) {
            func_8016AD00();
            *(s8 *)((u8 *)object + 0xB4) = 1;
            dungeon->field_A = (u16)dungeon->field_A + 1;
            *(u8 *)((u8 *)object + 0x9B) = 0;
            *(u8 **)((u8 *)object + 0x8C) = D_8016B778;
        }
    }
}
