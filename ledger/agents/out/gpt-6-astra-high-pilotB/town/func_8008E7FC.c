#include "common.h"

extern void func_8008BF0C(void **);

/* Decrease the record's 0xA field, clamping and invoking its handler below -0x400. */
void func_8008BF5C(void **record_ptr) {
    void *record;
    void *first_record;
    u16 value;

    first_record = *record_ptr;
    value = *(u16 *)((u8 *)first_record + 0xA);
    value -= 0x100;
    *(u16 *)((u8 *)first_record + 0xA) = value;
    record = *record_ptr;
    if (*(s16 *)((u8 *)record + 0xA) < -0x400) {
        *(s16 *)((u8 *)record + 0xA) = -0x400;
        func_8008BF0C(record_ptr);
    }
}
