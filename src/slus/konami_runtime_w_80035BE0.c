#include "common.h"

#include "common.h"

typedef struct Func80035BE0State {
    u8 pad00[0x64];
    u16 counter;
    u8 pad66[2];
    void (*callback)(void *, void *);
    u8 pad6c[0x0c];
    u8 sound_id;
    s8 sound_arg;
} Func80035BE0State;

extern void func_8003C7D8(u8 sound_id, s8 sound_arg);
extern void func_8003C160(void);
extern void func_80035C44(void *, void *);

void func_80035BE0(Func80035BE0State *arg0) {
    u16 counter;

    counter = arg0->counter;
    counter--;
    arg0->counter = counter;
    if ((s16)counter < 0) {
        func_8003C7D8(arg0->sound_id, arg0->sound_arg);
        func_8003C160();
        arg0->callback = func_80035C44;
    }
}
