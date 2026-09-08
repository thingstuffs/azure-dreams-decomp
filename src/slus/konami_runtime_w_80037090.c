#include "common.h"

#include "common.h"

typedef struct {
    u8 unk00[0x44];
    u8 *base;
    u8 unk48[2];
    s16 index;
    u8 unk4c[0x18];
    volatile u16 counter;
    s16 table_index;
} Func37090Input;

typedef struct {
    u8 unk00[8];
    u32 table_value;
    u32 color;
} Func37090Output;

extern s32 func_80037534(Func37090Input *, void *, Func37090Output *);
extern void func_80036C7C(u8 *, u8 *, u8 *);

extern u32 D_8006A958[3];
extern u32 D_8006A964[3];
extern u32 D_8006A970[3];
extern u32 D_8006A97C[32];
extern u8 D_80082B50[16];
extern u8 D_80082B60[16];
extern u8 D_80082B70[16];

/* Updates lookup data and selects the current entry's table value and blinking color. */
void func_80037090(Func37090Input *state, void *context, Func37090Output *output) {
    u8 entry;

    if (func_80037534(state, context, output) != 0) {
        return;
    }

    func_80036C7C(state->base + 0xC, (u8 *)D_8006A958, D_80082B50);
    func_80036C7C(state->base + 0xC, (u8 *)D_8006A964, D_80082B60);
    func_80036C7C(state->base + 0xC, (u8 *)D_8006A970, D_80082B70);

    {
        u8 *entries = state->base + 0x4C;
        s16 entry_index = state->index;

        entry = entries[entry_index];
    }
    if (entry & 0x80) {
        state->counter++;
        if (state->counter & 1) {
            output->color = 0xC0C0C0;
        } else {
            output->color = 0;
        }
    } else {
        output->color = 0;
    }

    output->table_value = D_8006A97C[((entry & 0x7F) + state->table_index)];
}
