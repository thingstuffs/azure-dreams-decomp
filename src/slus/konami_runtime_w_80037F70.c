#include "common.h"

#include "common.h"

typedef struct Func80037F70Inner {
    u8 pad_00[0x85];
    u8 field_85;
    u8 field_86;
} Func80037F70Inner;

typedef struct Func80037F70Outer {
    Func80037F70Inner *field_00;
} Func80037F70Outer;

extern const char D_8002D000[0x10];
extern const char D_8002D010[0x10];
extern const char D_8002D020[0x10];
extern u8 D_80082A38[0xB0];

extern s32 func_80043FB8(const char *arg0, ...);
extern void func_8003800C(Func80037F70Inner *arg0);

void func_80037F70(Func80037F70Outer *arg0)
{
    u8 *state = D_80082A38;

    func_80043FB8(D_8002D000, state);
    func_80043FB8(D_8002D010, state + 0xA8);
    func_80043FB8(D_8002D020, state + 0x9C);
    func_8003800C(arg0->field_00);
    arg0->field_00->field_86 = arg0->field_00->field_85;
    arg0->field_00->field_85 = 0;
}
