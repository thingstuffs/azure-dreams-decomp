#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 memset();
extern s32 func_800263C0();
extern s32 func_80026370();
extern volatile u8 D_800294F8[9];

void func_8002654C(s32 arg0)
{
    void *obj;

    obj = (void *)(arg0 + 0x20);
    memset(FIELD(obj, s32, 0x14), 0,
                  (D_800294F8[FIELD(obj, s32, 0x10)] * 2) | 1);
    func_800263C0(FIELD(obj, s32, 0x70), FIELD(obj, s32, 0x14));
    FIELD(obj, s32, 8) = 0;
    func_80026370(FIELD(obj, s32, 0x70), 0);
}
