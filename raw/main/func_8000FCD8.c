#include "common.h"

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

extern void func_80022774(void *arg0, void *arg1);
extern void func_80022934(void *arg0);
extern void func_80022488(void *arg0);
extern u8 D_80022524[];
extern u8 D_800226A8[];
extern u8 D_800280B4[];

void func_80022CD8(void *arg0)
{
    void *callback;
    s32 index;

    func_80022774((u8 *)arg0 + 0x24, arg0);
    func_80022934(arg0);
    index = FIELD(arg0, s32 *, 8);
    FIELD(arg0, s32 *, 0) = D_800280B4[index * 0x18 + 0x15];
    func_80022488(arg0);
    if (FIELD(arg0, s32 *, 0xC) == 2) {
        callback = D_800226A8;
    } else {
        callback = D_80022524;
    }
    FIELD(arg0, void **, -0x10) = callback;
}
