#include "common.h"

extern void func_8008BF0C(void **);

/* Decrease the record's field at 0xA by 0x100, clamping to -0x400 and calling its handler on underflow. */
void func_8008BF5C(void **record_ptr) {
    void *record;
    void *first_record;
    u16 field_value;

    first_record = *record_ptr;
    field_value = *(u16 *)((u8 *)first_record + 0xA);
    field_value -= 0x100;
    *(u16 *)((u8 *)first_record + 0xA) = field_value;
    record = *record_ptr;
    if (*(s16 *)((u8 *)record + 0xA) < -0x400) {
        *(s16 *)((u8 *)record + 0xA) = -0x400;
        func_8008BF0C(record_ptr);
    }
}
