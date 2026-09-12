#include "common.h"

typedef struct {
    u8 text[17];
    u8 value;
    u8 type;
} Record818105FC;

extern char *func_80027110(s32 arg0, s32 arg1);
extern s32 strncmp(const char *lhs, const char *rhs, s32 count);
extern char *strncpy(char *dst, const char *src, s32 count);

/* Stores a text record in the circular table unless it matches an existing entry. */
void func_800255FC(char *text, s32 type, s32 value) {
    Record818105FC *record;
    u8 *type_base;
    u8 *records_base;
    u8 *data_base;
    s32 cursor;
    s32 write_slot;

    if (type == 19) {
        for (cursor = 0; cursor < 5; cursor++) {
            if (strncmp(text, func_80027110(value, cursor), 18) == 0) {
                return;
            }
        }
    }

    cursor = 0;
    record = (Record818105FC *)0x800157C0;
    type_base = (u8 *)0x80010000;
loop_records:
    if ((type_base[0x57D2] == type) &&
        (strncmp(text, (char *)record, 18) == 0)) {
        return;
    }
    record++;
    cursor++;
    type_base += 19;
    if (cursor < 64) {
        goto loop_records;
    }

    write_slot = *(s32 *)0x80015C80;
    *(s32 *)0x80015C80 = write_slot + 1;
    data_base = (u8 *)0x80010000;
    if (*(s32 *)(data_base + 0x5C80) == 64) {
        *(s32 *)(data_base + 0x5C80) = 0;
    }

    records_base = (u8 *)0x800157C0;
    cursor = write_slot * 19;
    strncpy((char *)(records_base + cursor), text, 18);
    if (type == 19) {
        data_base[cursor + 0x57D1] = value;
    }
    data_base[cursor + 0x57D2] = type;
}
