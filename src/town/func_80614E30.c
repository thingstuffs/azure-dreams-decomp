#include "common.h"

typedef struct S_func_80614E30_0 {
    void *unk_00;
} S_func_80614E30_0;

typedef struct S_func_80614E30_1 {
    u8 pad_00[0x1C];
    void *unk_1C;
    void *unk_20;
} S_func_80614E30_1;

typedef struct S_func_80614E30_2 {
    u8 pad_00[0x40];
    void *unk_40;
} S_func_80614E30_2;

typedef struct S_func_80614E30_3 {
    u8 pad_00[0x2F8];
    s32 (*unk_2F8)(s32, s32);
} S_func_80614E30_3;

extern s32 func_80018BD0(s32);
extern s32 func_80018C50(s32);
extern s8 D_80016000[];
extern s32 D_8001A3B5;

// Processes IDs 0xFB7 and 0xFB8, conditionally sets a data pointer, and invokes the context callback.
s32 func_80016630(void) {
    func_80018BD0(0xFB7);
    func_80018BD0(0xFB8);
    if (func_80018C50(0xFC0) != 0) {
        ((S_func_80614E30_2 *)((S_func_80614E30_1 *)((S_func_80614E30_0 *)D_80016000)->unk_00)->unk_1C)->unk_40 = &D_8001A3B5;
    }
    ((S_func_80614E30_3 *)((S_func_80614E30_1 *)((S_func_80614E30_0 *)D_80016000)->unk_00)->unk_20)->unk_2F8(0x10, 0x200);
    return 0;
}
