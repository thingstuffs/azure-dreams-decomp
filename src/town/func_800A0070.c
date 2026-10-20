#include "town/menu/window.h"

/* Clear each record's first byte until the end marker is reached. */
void clear_record_20_status_bytes(s8 *records) {
    s8 *record;

    record = records;
    if ((((func_800A0070_S_8009D7D0_0 *)record)->unk_01 & 0xC0) != 0x80) {
        do {
            *record = 0;
            record += 0x14;
        } while ((((func_800A0070_S_8009D7D0_0 *)record)->unk_01 & 0xC0) != 0x80);
    }
}
