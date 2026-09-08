#include "common.h"

typedef struct {
    u32 words[2];
} __attribute__((packed)) Copy8;

extern u8 D_80089490[9];
extern void func_800673A0(void *arg0, s32 arg1, s32 arg2);

/* Passes a local copy of the global eight-byte data with fixed arguments. */
void func_800DBE98(void) {
    Copy8 copy;

    do { copy = *(Copy8 *)D_80089490; } while (0);
    func_800673A0(&copy, 0x1C2, 0x19C);
}
