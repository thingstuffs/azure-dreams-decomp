#include "common.h"
#include "shared/dungeon_effect_source.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_7FFE7BE8_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0x1C];
    s32 unk_2C;
    u8 pad_30[0x14];
    void * unk_44;
} S_7FFE7BE8_0;   /* arg0 in initialize_source_position_object */

typedef struct S_7FFE7BE8_1 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_7FFE7BE8_1;



   /* arg2 in initialize_source_position_object */

typedef struct S_7FFE7BE8_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x2];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_7FFE7BE8_4;

typedef struct S_7FFE7BE8_5 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_7FFE7BE8_5;   /* arg1 in initialize_source_position_object */


extern void func_70040A18(void *, void *);
extern void func_7003A7C4(void *, void *, s32);
extern s32 D_8004136C;

/* Initialize the object from its source and position, then configure its display state. */
void initialize_source_position_object(S_7FFE7BE8_0 *object, S_7FFE7BE8_5 *source, MovingPosition *position)
{
    S_7FFE7BE8_1 *display_flags;
    S_7FFE7BE8_4 *display_state;
    MovingPosition *object_position;
    s32 source_value;

    object->unk_44 = source;
    func_70040A18(object, &D_8004136C);
    display_flags = object->unk_0C;
    display_flags->unk_10 = 0x20;
    display_flags->unk_14 = display_flags->unk_14 | 0xC;
    object_position = object->unk_08;
    object_position->x = position->x;
    object_position->y = position->y;
    object_position->z = position->z;
    display_state = object->unk_0C;
    display_state->unk_1E = 0x800;
    display_state->unk_1C = 0x800;
    object->unk_2C = source->unk_0C;
    source_value = source->unk_0C;
    display_state->unk_12 = 0x7DCF;
    display_state->unk_0C = source_value;
    display_state->unk_14 |= 0x100;
    func_7003A7C4(display_state, positioned_effect_source, 0);
}
