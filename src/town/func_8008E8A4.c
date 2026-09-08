#include "common.h"

extern void func_8008BF0C(void **);

void func_8008C004(void **arg0) {
    void *record;
    void *first_record;
    u16 value;

    first_record = *arg0;
    value = *(u16 *)((u8 *)first_record + 8);
    value -= 0x200;
    *(u16 *)((u8 *)first_record + 8) = value;
    record = *arg0;
    if (*(s16 *)((u8 *)record + 8) < -0x800) {
        *(s16 *)((u8 *)record + 8) = -0x800;
        func_8008BF0C(arg0);
    }
}
