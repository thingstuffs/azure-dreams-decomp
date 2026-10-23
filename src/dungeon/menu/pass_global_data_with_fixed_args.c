#include "common.h"
#include "dungeon/menu.h"

typedef struct {
    u32 words[2];
} __attribute__((packed)) Copy8;

extern u8 D_80089490[9];
extern void MoveImage(void *, s32, s32);

/* Passes a local copy of the global eight-byte data with fixed arguments. */
void pass_global_data_with_fixed_args(void) {
    Copy8 copy;

    copy = *(Copy8 *)D_80089490;
    MoveImage(&copy, 0x1C2, 0x19C);
}
