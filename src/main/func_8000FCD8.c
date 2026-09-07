#include "common.h"

typedef struct S_80022CD8_0_pre {
    void ** unk_00;
    u8 pad_04[0xC];
} S_80022CD8_0_pre;   /* the 0x10 bytes before arg0 in func_80022CD8, addressed as arg0[-1] */

typedef struct S_80022CD8_0 {
    s32 * unk_00;
    u8 pad_04[0x4];
    s32 * unk_08;
    s32 * unk_0C;
} S_80022CD8_0;   /* arg0 in func_80022CD8 */



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
    index = ((S_80022CD8_0 *)arg0)->unk_08;
    ((S_80022CD8_0 *)arg0)->unk_00 = D_800280B4[index * 0x18 + 0x15];
    func_80022488(arg0);
    if (((S_80022CD8_0 *)arg0)->unk_0C == 2) {
        callback = D_800226A8;
    } else {
        callback = D_80022524;
    }
    ((S_80022CD8_0_pre *)arg0)[-1].unk_00 = callback;
}
