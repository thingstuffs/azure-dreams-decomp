#include "common.h"

extern s8 D_80016000[];
extern s32 D_8001C9F4;
extern s32 func_80018BD0(s32);
extern s32 func_80018C50(s32);

typedef void (*TownCallback)(s32, s32);

typedef struct S_func_80016BE8_0 {
    void *unk_00;
} S_func_80016BE8_0;

typedef struct S_func_80016BE8_1 {
    u8 pad_00[0x1C];
    void *unk_1C;
    void *unk_20;
} S_func_80016BE8_1;

typedef struct S_func_80016BE8_2 {
    u8 pad_00[0x40];
    void *unk_40;
} S_func_80016BE8_2;

typedef struct S_func_80016BE8_3 {
    u8 pad_00[0x2F8];
    TownCallback unk_2F8;
} S_func_80016BE8_3;

/* Conditionally updates the town state pointer and invokes the town callback. */
s32 func_80016BE8(void) {
    func_80018BD0(0xFB7);
    func_80018BD0(0xFB8);
    if (func_80018C50(0xFE8) == 0) {
        ((S_func_80016BE8_2 *)
            ((S_func_80016BE8_1 *)
                ((S_func_80016BE8_0 *)D_80016000)->unk_00)->unk_1C)->unk_40 = &D_8001C9F4;
    }
    ((S_func_80016BE8_3 *)
        ((S_func_80016BE8_1 *)
            ((S_func_80016BE8_0 *)D_80016000)->unk_00)->unk_20)->unk_2F8(0x10, 0x200);
    return 0;
}
