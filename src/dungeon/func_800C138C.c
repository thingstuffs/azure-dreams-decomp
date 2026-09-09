#include "common.h"

typedef struct Func800C138CData {
    u8 pad0[8];
    void *arg1;
    void *arg2;
} Func800C138CData;

extern void func_800C6B40(void *arg0, void *arg1, void *arg2, s32 arg3);

s32 func_800C6AEC(void *arg0, void *arg1, void *arg2) {
    void *next = arg0;
    void *data;

    for (;;) {
        func_800C6B40(next, arg1, arg2, 0);
        data = *((void **)next - 2);
        if (data == 0) {
            return 0;
        }
        next = (u8 *)data + 0x20;
        arg1 = ((Func800C138CData *)data)->arg1;
        arg2 = ((Func800C138CData *)data)->arg2;
    }
}
