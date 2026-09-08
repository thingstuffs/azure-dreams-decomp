#include "common.h"

extern void func_8008BF0C(void **);

/* Decrease the record value by 0x200, clamp at -0x800, and handle the lower limit. */
void func_8008C004(void **record_ref) {
    void *record;
    void *first_record;
    u16 value;

    first_record = *record_ref;
    value = *(u16 *)((u8 *)first_record + 8);
    value -= 0x200;
    *(u16 *)((u8 *)first_record + 8) = value;
    record = *record_ref;
    if (*(s16 *)((u8 *)record + 8) < -0x800) {
        *(s16 *)((u8 *)record + 8) = -0x800;
        func_8008BF0C(record_ref);
    }
}
