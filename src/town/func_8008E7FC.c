#include "common.h"

extern void release_town_map_record(void **);

/* Decrease the record value by 0x100, clamp at -0x400, and handle the lower limit. */
void decrease_town_record_value(void **record_ref) {
    void *record;
    void *first_record;
    u16 value;

    first_record = *record_ref;
    value = *(u16 *)((u8 *)first_record + 0xA);
    value -= 0x100;
    *(u16 *)((u8 *)first_record + 0xA) = value;
    record = *record_ref;
    if (*(s16 *)((u8 *)record + 0xA) < -0x400) {
        *(s16 *)((u8 *)record + 0xA) = -0x400;
        release_town_map_record(record_ref);
    }
}
