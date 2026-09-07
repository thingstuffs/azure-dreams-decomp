#include "common.h"

typedef struct DungeonState {
    u8 pad[0x1C];
    u32 flags;
} DungeonState;

extern DungeonState *D_800E3D7C[];
extern void * volatile D_800DD724[];

extern s32 func_8004AC3C(s32, s32 *);
extern s32 strlen(s32);
extern void memcpy(s32, s32, s32);
extern void func_80099330(void) __attribute__((noreturn));

s32 func_800992E8(s32 arg0, s32 arg1) {
    s32 sp10;
    s32 first;
    s32 second;

    if (D_800E3D7C[0]->flags & 0x10) {
        first = (s32)D_800DD724[0];
        func_80099330();
    }

    first = func_8004AC3C(arg0, &sp10);
    second = strlen(first);
    memcpy(arg1, first, second);
    return arg1 + second;
}
