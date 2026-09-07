#include "common.h"

extern void func_800AB538(void);

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

void func_80173C40(void *arg0) {
    s32 field_A4;

    func_800AB538();
    field_A4 = FIELD(arg0, s32, 0xA4);
    FIELD(arg0, s16, 0xA6) = 0;
    FIELD(arg0, s32, 0xAC) = 0;
    FIELD(arg0, s32, 0xB0) = 0;
    FIELD(arg0, s32, 0xA8) = field_A4;
}
