#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 padC;
    s32 pad10;
} StackRecord;

typedef void (*EntityCallback)(void *, void *, void *, void *);

extern void func_8003DB94(void *, void *, s8);
extern void func_800478B8(void *);
extern s32 func_80096FF4(void *);
extern void func_800970AC(s32, void *);
extern void func_800A6758(void);
extern void func_800A6888(void);
extern void func_800A6A94(StackRecord *);
extern void func_800A6B70(StackRecord *);
extern s32 func_800C2E1C(s16, s16);
extern s32 func_800C2F14(s16, s16);

void func_800A6684(void *arg0, void *arg1, void *arg2)
{
    StackRecord rec;
    s32 index;
    s32 above;
    s32 value;
    register void *call_a0 ASM_REG("$4");
    register u32 tail_value ASM_REG("$2");

    FIELD(arg0, EntityCallback, 0x50)(arg0, arg0, arg1, arg2);
    if (!(FIELD(arg0, u16, -2) & 0x8000)) {
        func_800970AC(func_80096FF4(arg1), arg0);

        index = func_800C2E1C(FIELD(arg0, s16, 0x72), FIELD(arg0, s16, 0x64));
        if (FIELD(arg0, s16, 0x74) != index) {
            func_8003DB94(arg2, FIELD(arg0, void **, 0x78)[index], FIELD(arg2, s8, 4));
            FIELD(arg0, s16, 0x74) = index;
        }

        if ((func_800C2F14(FIELD(arg0, s16, 0x72), FIELD(arg0, s16, 0x64)) << 0x10) != 0) {
            tail_value = FIELD(arg2, u16, 0x14) | 1;
            ASM_TAILSLOT_PIN(tail_value);
            func_800A6758();
            return;
        }

        ASM_SCHED_BARRIER();
        FIELD(arg2, u16, 0x14) &= 0xFFFE;
        ASM_SCHED_BARRIER();
        call_a0 = arg2;
        func_800478B8(call_a0);

        above = FIELD(arg1, s32, 4) > 0x06500000;
        if (!above && FIELD(arg0, s32, 0xA0) > 0x06500000) {
            FIELD(arg2, u8, 0xC) = FIELD(arg2, u8, 0xD) = FIELD(arg2, u8, 0xE) = 0xFF;
            rec.unk0 = FIELD(arg1, s32, 0);
            rec.unk4 = 0x06400000;
            rec.unk8 = FIELD(arg1, s32, 8) - 0x00280000;
            func_800A6A94(&rec);
            func_800A6888();
            return;
        }

        if (above && FIELD(arg0, s32, 0xA0) <= 0x06500000 &&
            FIELD(arg0, s32, 0xA4) <= 0x06500000) {
            FIELD(arg2, u8, 0xC) = FIELD(arg2, u8, 0xD) = FIELD(arg2, u8, 0xE) = 0xFF;
            rec.unk0 = FIELD(arg1, s32, 0);
            rec.unk4 = 0x06600000;
            rec.unk8 = FIELD(arg1, s32, 8) - 0x00280000;
            func_800A6B70(&rec);
            func_800A6888();
            return;
        }

        value = FIELD(arg2, u8, 0xC) - 8;
        FIELD(arg2, u8, 0xC) = value;
        if ((u32)(value & 0xFF) < 0x80U) {
            FIELD(arg2, u8, 0xC) = 0x80;
        }
        value = FIELD(arg2, u8, 0xD) - 0x10;
        FIELD(arg2, u8, 0xD) = value;
        if ((u32)(value & 0xFF) < 0x80U) {
            FIELD(arg2, u8, 0xD) = 0x80;
        }
        FIELD(arg2, u8, 0xE) = FIELD(arg2, u8, 0xD);
        FIELD(arg0, s32, 0xA4) = FIELD(arg0, s32, 0xA0);
        FIELD(arg0, s32, 0xA0) = FIELD(arg1, s32, 4);
    }
}
