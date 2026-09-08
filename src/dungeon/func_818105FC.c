#include "common.h"

typedef struct {
    u8 text[17];
    u8 value;
    u8 type;
} Record818105FC;

extern char *func_80027110(s32 arg0, s32 arg1);
extern s32 strncmp(const char *lhs, const char *rhs, s32 count);
extern char *strncpy(char *dst, const char *src, s32 count);

void func_800255FC(char *text, s32 type, s32 value) {
    Record818105FC *record;
    u8 *record_type;
    u8 *dest;
    u8 *page;
    s32 i;
    s32 index;

    if (type == 19) {
        for (i = 0; i < 5; i++) {
            if (strncmp(text, func_80027110(value, i), 18) == 0) {
                return;
            }
        }
    }

    i = 0;
    record = (Record818105FC *)0x800157C0;
    record_type = (u8 *)0x80010000;
loop_records:
    if ((record_type[0x57D2] == type) &&
        (strncmp(text, (char *)record, 18) == 0)) {
        return;
    }
    record++;
    i++;
    record_type += 19;
    if (i < 64) {
        goto loop_records;
    }

    index = *(s32 *)0x80015C80;
    *(s32 *)0x80015C80 = index + 1;
    page = (u8 *)0x80010000;
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    if (*(s32 *)(page + 0x5C80) == 64) {
        *(s32 *)(page + 0x5C80) = 0;
    }

    dest = (u8 *)0x800157C0;
    i = index * 19;
    strncpy((char *)(dest + i), text, 18);
    if (type == 19) {
        page[i + 0x57D1] = value;
    }
    page[i + 0x57D2] = type;
}
