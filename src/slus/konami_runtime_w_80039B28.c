#include "common.h"

#include "common.h"

typedef struct {
    u8 pad[0x1c];
    u8 *cursor;
} Func80039B28State;

extern s16 func_80053DA8(s32 a0);

void func_80039B28(Func80039B28State *arg0)
{
    u8 *cursor = arg0->cursor;
    u8 low = cursor[0];
    u8 high = cursor[1];

    arg0->cursor = cursor + 2;
    func_80053DA8(low | (high << 8));
}
