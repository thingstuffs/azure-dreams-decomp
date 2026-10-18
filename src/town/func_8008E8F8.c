/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"

extern void release_town_map_record(void **);

void advance_record_value_and_reset_when_capped(void **record_ref) {
    void *record;
    void *first_record;
    u16 value;

    first_record = *record_ref;
    value = *(u16 *)((u8 *)first_record + 8);
    value += 0x200;
    *(u16 *)((u8 *)first_record + 8) = value;
    record = *record_ref;
    if (*(s16 *)((u8 *)record + 8) > 0x800) {
        *(s16 *)((u8 *)record + 8) = 0x800;
        release_town_map_record(record_ref);
    }
}
