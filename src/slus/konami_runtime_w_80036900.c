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

void func_80036900(S_80036900 *arg0)
{
    arg0->sub->value += 0x100;
    if ((s16)arg0->sub->value >= 0x401) {
        func_80044A50((u8 *)arg0 - 0x20);
        arg0->handler = func_80036980;
        {
            u8 *base;
            u8 *dest;

            base = arg0->base;
            dest = base + arg0->index + 0x50;
            *dest = 1;
        }
    }
}
