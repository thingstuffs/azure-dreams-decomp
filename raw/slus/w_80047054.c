#include "common.h"

#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

void func_80047054(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    register void *header ASM_REG("$4") = arg0;
    register s32 count ASM_REG("$2");
    register u32 cursor ASM_REG("$3");
    register u8 *entry ASM_REG("$10");
    register u8 *part ASM_REG("$9");
    register u8 *coords ASM_REG("$8");
    register s32 type ASM_REG("$11");
    u32 limit;
    u16 value;
    u8 flags;

    ASM_KEEP(header);
    count = FIELD(header, s32, 4);
    cursor = FIELD(header, s32, 0);
    count *= 4;
    ASM_KEEP(count);
    cursor += count;
    ASM_KEEP(cursor);
    if (cursor < FIELD(header, u32, 8)) {
        ASM_KEEP(cursor);
        type = 2;
        entry = (u8 *)cursor + 4;
        ASM_KEEP(type);
        ASM_KEEP(entry);
        do {
            if (FIELD(entry, s16, -2) == type) {
                part = FIELD(entry, u8 *, 0);
                ASM_KEEP(part);
                flags = *part;
                if (!(flags & 8)) {
                    *part = flags | 8;
                    coords = part + 6;
                    ASM_KEEP(coords);
                    do {
                        if (*part & 0x40) {
                            value = FIELD(coords, u16, -2) + arg1;
                        } else {
                            value = FIELD(coords, u16, -2) + arg3;
                        }
                        FIELD(coords, u16, -2) = value;
                        if (!(*part & 0x20)) {
                            FIELD(coords, u16, 0) = FIELD(coords, u16, 0) + arg2;
                        }
                        coords += 0xC;
                        value = *part & 0x80;
                        part += 0xC;
                    } while (!value);
                }
            }
            do {
                limit = FIELD(header, u32, 8);
            } while (0);
            cursor += 8;
            entry += 8;
        } while (cursor < limit);
    }
}
