#include "common.h"

extern void func_8001A1A0(void *, void *);
extern void func_8001A200(void *, void *);
extern s32 func_8001E670(s32);

typedef struct {
    u8 pad0[4];
    s16 field4;
    u8 pad6[2];
    s32 field8;
} Record12;

extern Record12 D_8001791C[];
extern u8 D_80017ADC;
extern u8 D_80017AE8;
extern u8 D_80017AF4;
extern u8 D_80017B00;
extern u8 D_80017B0C;
extern u8 D_80017B18;
extern u8 D_80017D50;

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

u8 *func_8001A86C(s32 arg0) {
    s32 i;
    register s32 flag ASM_REG("$21");
    register s32 setting ASM_REG("$20");
    u8 *base;
    register Record12 *record_base ASM_REG("$2");
    Record12 *record;
    void *out;

    flag = 0;
    base = &D_80017D50;
    if (arg0 != 0) {
        i = 1;
        setting = 0x400;
        out = base + 0x14;
        record_base = D_8001791C;
        record = &record_base[1];
loop:
        if (func_8001E670(record->field4) != 0) {
            if (record->field8 != 0) {
                FIELD(out, s16, 2) = setting;
                if (i == 1) {
                    flag = 1;
                }
                goto next;
            }
            if (arg0 == i) {
                FIELD(out, s16, 2) = setting;
            }
        }
next:
        out += 0x14;
        i++;
        record++;
        if (i < 8) {
            goto loop;
        }
    }

    func_8001A200(base, &D_80017ADC);
    func_8001A1A0(base, &D_80017AE8);
    if (flag != 0) {
        *(s16 *)(base + 0xA2) = 0x400;
        func_8001A1A0(base + 0xA0, &D_80017B00);
    } else {
        *(s16 *)(base + 0xB6) = 0x400;
        func_8001A1A0(base + 0xB4, &D_80017B0C);
    }
    func_8001A1A0(base + 0xDC, &D_80017AF4);
    func_8001A1A0(base + 0xC8, &D_80017B18);
    return base;
}
