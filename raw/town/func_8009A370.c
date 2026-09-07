#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_800374F4(u16 value);
extern s32 func_800644B8(s32 value);
extern s32 func_80064584(s32 value, s32 other);
extern s32 rand(void);
extern void *func_8009792C(void *arg0, s16 arg1);

typedef struct {
    s16 unk0;
    s16 x;
    s16 unk4;
    s16 z;
    s16 unk8;
    u16 y;
    s32 fieldC;
    s32 field10;
    s16 unk14;
    s16 field16;
} StackRecord;

void func_80097AD0(void *arg0, void *arg1, s32 count) {
    StackRecord record;
    s32 angle;
    s32 step;
    s32 magnitude;
    s32 i;
    s32 value;
    s32 y;
    u16 initial_y;
    void *object;

    if (count != 0) {
        step = 0x1000 / count;
        do { i = 0; } while (0);
        do { angle = rand(); } while (0);
        initial_y = FIELD(arg0, u16, 0xA);
        record.field16 = -4;
        record.y = initial_y;
        if (count > 0) {
            do {
                record.x = (FIELD(arg0, u16, 2) +
                            func_800374F4(FIELD(arg1, u16, 0))) -
                           (FIELD(arg1, s32, 0) / 2);
                record.z = (FIELD(arg0, u16, 6) +
                            func_800374F4(FIELD(arg1, u16, 4))) -
                           (FIELD(arg1, s32, 4) / 2);
                y = (FIELD(arg0, u16, 0xA) -
                     func_800374F4(FIELD(arg1, u16, 8))) -
                    (FIELD(arg1, s32, 8) / 2);
                record.y = y;
                record.fieldC = func_80064584(angle, y) << 5;
                value = func_800644B8(angle);
                {
                    register void *record_ptr ASM_REG("$4") = &record;
                    ASM_KEEP(record_ptr);
                    value <<= 5;
                    ASM_KEEP(value);
                    record.field10 = value;
                    object = func_8009792C(record_ptr, angle);
                }
                if (object != 0) {
                    value = func_800644B8(angle) << 5;
                    if (value < 0) {
                        value = -value;
                    }
                    FIELD(FIELD(object, void *, 8), s32, 0x14) = -value;
                }
                i++;
                angle += step;
            } while (i < count);
        }
    }
}

/* MECHANISM:
 * The escaping 0x18-byte record fixes the 0x48 frame and stack fields at 0x10..0x26.
 * A guarded short-lived $a0 record pointer orders addiu &record before the return shift.
 * ASM_KEEP(value) fences that sll before the s16 angle cast; both anchors emit zero words.
 */
