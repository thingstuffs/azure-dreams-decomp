#include "common.h"

extern u8 D_8008CA34;
extern void func_80400E34(void);
typedef struct { u8 pad[0x10]; void *callback; } Effect;
extern Effect *func_804083FC(void *, void *);
void func_8040855C(void *owner) {
    D_8008CA34 = 1;
    func_80400E34();
    func_804083FC(owner, (void *)1);
}
