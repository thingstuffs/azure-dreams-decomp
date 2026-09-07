#include "common.h"

typedef struct {
    u8 pad00[0x1E];
    s16 field1E;
    u8 pad20[0x0C];
    u8 *field2C;
} Obj;

typedef struct {
    u8 pad00[0x2A];
    s16 field2A;
} Other;

typedef struct {
    u8 pad00[0x9A];
    s8 field9A;
    s8 field9B;
    u8 pad9C[2];
    s16 field9E;
} First;

extern s16 D_80083228[];
extern u8 D_8017556C[];
extern void func_80047784(Obj *, u8, s32);

/* Initialize state and configure the object using the direction lookup table. */
void func_80172634(First *state, s32 unused, Obj *object, Other *angle_source)
{
    state->field9A = 0x10;
    state->field9B = 0;
    state->field9E = 2;
    object->field2C = D_8017556C;
    func_80047784(object,
                  D_8017556C[((D_80083228[0] + angle_source->field2A + 0x100) >> 9) & 7],
                  0);
    object->field1E = 0xC00;
}
