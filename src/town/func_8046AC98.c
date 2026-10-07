#include "shared/town_event_state.h"
#include "common.h"

extern s32 D_8001E954[];

s32 func_8001A2F0(void);
u8 func_8001A3E8(void);
s32 func_8001BC60(s32);

void func_8001BC98(s32 unused, s32 unused_second, s32 unused_third)
{
    D_8001E950->unk_02 = 0xFF;
    if (func_8001A2F0() != 0) {
        D_8001E950->unk_04 = func_8001A3E8();
        D_8001E950->unk_05 = 2;
        D_8001E954[0] = func_8001BC60(D_8001E950->unk_04);
    } else {
        D_8001E950->unk_05 = 1;
    }
}
