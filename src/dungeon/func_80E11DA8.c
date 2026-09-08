#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    u8 pad00[0x2A];
    s16 field2A;
    u8 pad2C[0x84];
    u16 fieldB0;
} FuncArg0;

typedef struct {
    s32 field00;
    s32 field04;
    s32 field08;
    s32 field0C;
    s32 field10;
    s32 field14;
} FuncArg1;

typedef struct {
    u8 pad00[0x28];
    s32 field28;
} FuncArg2;

typedef struct {
    u8 pad00[6];
    s16 field06;
    u8 pad08[4];
    s32 field0C;
    u16 field10;
    s16 field12;
    u16 field14;
    u8 pad16[6];
    s16 field1C;
    s16 field1E;
    u8 pad20[8];
    s32 field28;
} FuncInner;

typedef struct {
    u8 pad00[4];
    s16 field04;
    u16 field06;
} FuncTail;

typedef struct {
    u8 pad00[8];
    FuncArg1 *buffer;
    FuncInner *inner;
    void *field10;
    u8 pad14[0xC];
    FuncTail tail;
} FuncTemp;

extern u8 D_80045340[];
extern u32 D_80175480;
extern FuncTemp *func_8003FC64(u32);
extern void func_8004491C(FuncTemp *, u8 *);
extern void func_80047784(FuncInner *, s16, s16);

/* Creates a directional effect and applies the supplied position offsets. */
s32 func_801755A8(FuncArg0 *source, FuncArg1 *position, FuncArg2 *render_context) {
    FuncTemp *effect;
    FuncTail *direction_state;
    FuncInner *sprite;
    FuncArg1 *effect_position;
    s16 angle;
    s32 biased_angle;

    effect = func_8003FC64(0x312);
    if (effect != NULL) {
        effect->field10 = &D_80175480;
        func_8004491C(effect, D_80045340);
        angle = source->field2A;
        direction_state = &effect->tail;
        biased_angle = angle;
        if (angle < 0) {
            biased_angle = angle + 0xFFF;
        }
        direction_state->field04 = (s16) (((angle - ((biased_angle >> 0xC) << 0xC)) << 0x10) >> 0x19);
        direction_state->field06 = source->fieldB0;
        sprite = effect->inner;
        sprite->field28 = render_context->field28;
        sprite->field14 |= 0x100;
        sprite->field12 = direction_state->field06 + ((direction_state->field04 + 6) % 8);
        sprite->field0C = 0x808080;
        sprite->field1E = 0x1000;
        sprite->field1C = 0x1000;
        sprite->field06 = 1;
        sprite->field14 |= 0xC;
        sprite->field10 |= 0x20;
        func_80047784(sprite, 0x31, 0);
        effect_position = effect->buffer;
        *effect_position = *position;
        effect_position->field00 += effect_position->field0C;
        effect_position->field04 += effect_position->field10;
        return (s32) effect;
    }
    return 0;
}
