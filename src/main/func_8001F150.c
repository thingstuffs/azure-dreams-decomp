#include "common.h"

typedef struct S_func_8001F150_0 {
    u8 pad_00[0x10];
    void (*unk_10)(void);
    u8 pad_14[0x34];
    s32 unk_48;
    s32 unk_4C;
    u8 pad_50[0x4];
    void (*unk_54)(void);
} S_func_8001F150_0;

typedef struct S_func_8001F150_1 {
    s32 unk_00;
    u8 pad_04[0x7C];
} S_func_8001F150_1;

extern void func_804032FC(void *arg0);
extern void func_80406368(void);
extern void func_80405A64(void);
extern void func_80405FC4(void);
extern s32 D_8009DDD8[];

/* Selects the object's next callback based on whether its indexed entry is active. */
void func_80406150(void *object_state)
{
    void (*next_callback)(void);
    S_func_8001F150_0 *object_base;
    s32 entry_index;
    s32 entry_active;

    entry_index = ((S_func_8001F150_0 *)((u8 *)object_state - 0x20))->unk_48;
    entry_active = ((S_func_8001F150_1 *)D_8009DDD8)[entry_index].unk_00;
    object_base = (S_func_8001F150_0 *)((u8 *)object_state - 0x20);
    if (entry_active != 0) {
        next_callback = func_80405FC4;
        ((S_func_8001F150_0 *)((u8 *)object_state - 0x20))->unk_4C = entry_index;
    } else {
        ((S_func_8001F150_0 *)((u8 *)object_state - 0x20))->unk_54 = func_80406368;
        func_804032FC(object_base);
        next_callback = func_80405A64;
    }
    ((S_func_8001F150_0 *)((u8 *)object_state - 0x20))->unk_10 = next_callback;
}
