#include "common.h"

typedef void (*Callback)(void);

typedef struct {
    unsigned char pad[0x1c];
    u16 value;
} State;

extern void func_8003C4C0(void);

void func_8003C488(Callback *arg0, void *arg1, State *arg2) {
    arg2->value += 0x200;
    if (arg2->value < 0x1000) {
        return;
    }
    arg2->value = 0x1000;
    *arg0 = func_8003C4C0;
}
