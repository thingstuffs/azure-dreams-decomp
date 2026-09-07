#include "common.h"

typedef struct Struct_7FFEE2A0 {
    char pad0[0x64];
    s16 unk64;
    void (*unk68)(void);
    void (*unk6C)(void);
} Struct_7FFEE2A0;

void func_8008BA00(Struct_7FFEE2A0 *arg0) {
    arg0->unk64--;
    if (arg0->unk64 < 0) {
        void (*func)(void) = arg0->unk6C;
        arg0->unk68 = func;
        func();
    }
}
