#include "common.h"

#include "common.h"

typedef struct S_80036900_Sub {
    u8 pad00[0xA];
    u16 value;
} S_80036900_Sub;

typedef struct S_80036900 {
    S_80036900_Sub *sub;
    u8 pad04[0x40];
    u8 *base;
    u8 pad48[2];
    s16 index;
    u8 pad4C[0x1C];
    void (*handler)(void);
} S_80036900;

extern void func_80036980(void);
extern void func_80044A50(void *arg0);

/* Advances the sub-value, then unlinks the task, switches handlers, and sets its indexed flag past the threshold. */
void func_80036900(S_80036900 *state)
{
    state->sub->value += 0x100;
    if ((s16)state->sub->value >= 0x401) {
        func_80044A50((u8 *)state - 0x20);
        state->handler = func_80036980;
        {
            u8 *base;
            u8 *flag;

            base = state->base;
            flag = base + state->index + 0x50;
            *flag = 1;
        }
    }
}
