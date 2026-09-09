#include "common.h"

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

typedef struct S_func_80016D74_0 {
    void *unk_00;
} S_func_80016D74_0;

typedef struct S_func_80016D74_1 {
    u8 pad_00[0x20];
    void *unk_20;
} S_func_80016D74_1;

typedef struct S_func_80016D74_2 {
    u8 pad_00[0x54];
    s32 (*unk_54)(s32);
    u8 pad_58[0x2A0];
    void (*unk_2F8)(s32, s32);
} S_func_80016D74_2;

extern s8 D_80016000[];
extern s32 D_80018FB4;
extern s32 func_80018BD0(s32);

/* Runs the global interface setup sequence and saves its initial result. */
s32 func_80016D74(void) {
    D_80018FB4 = ((S_func_80016D74_2 *)
        ((S_func_80016D74_1 *)
            ((S_func_80016D74_0 *)D_80016000)->unk_00)->unk_20)->unk_54(3);
    func_80018BD0(0xFB7);
    func_80018BD0(0xFB8);
    ((S_func_80016D74_2 *)
        ((S_func_80016D74_1 *)
            ((S_func_80016D74_0 *)D_80016000)->unk_00)->unk_20)->unk_2F8(0x10, 0x200);
    return 0;
}
