#include "common.h"

typedef struct S_800A895C_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800A895C_0;   /* arg0 in func_800A895C */

typedef struct S_800A895C_1 {
    union { u16 u16; s32 s32; } unk_00;   /* accessed as both */
    union { u16 u16; s32 s32; } unk_04;   /* accessed as both */
    union { u16 u16; s32 s32; } unk_08;   /* accessed as both */
} S_800A895C_1;   /* arg1 in func_800A895C */

typedef struct S_800A895C_2 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800A895C_2;   /* object in func_800A895C */

typedef struct S_800A895C_3 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800A895C_3;   /* ((S_800A895C_2 *)object)->unk_08 in func_800A895C */



extern s32 func_800374F4(u16 value);
extern s32 func_800644B8(s32 value);
extern s32 func_80064584(s32 value, s32 other);
extern s32 rand(void);
extern void *func_800A878C(void *arg0, s16 arg1);

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

void func_800A895C(S_800A895C_0 *arg0, S_800A895C_1 *arg1, s32 count) {
    StackRecord record;
    s32 angle;
    s32 step;
    s32 magnitude;
    s32 i;
    s32 value;
    s32 y;
    u16 initial_y;
    S_800A895C_2 *object;

    if (count != 0) {
        step = 0x1000 / count;
        do { i = 0; } while (0);
        do { angle = rand(); } while (0);
        initial_y = arg0->unk_0A;
        record.field16 = -4;
        record.y = initial_y;
        if (count > 0) {
            do {
                record.x = (arg0->unk_02 +
                            func_800374F4(arg1->unk_00.u16)) -
                           (arg1->unk_00.s32 / 2);
                record.z = (arg0->unk_06 +
                            func_800374F4(arg1->unk_04.u16)) -
                           (arg1->unk_04.s32 / 2);
                y = (arg0->unk_0A +
                     func_800374F4(arg1->unk_08.u16)) -
                    (arg1->unk_08.s32 / 2);
                record.y = y;
                record.fieldC = func_80064584(angle, y) << 5;
                value = func_800644B8(angle);
                {
                    void *record_ptr = &record;
                    ASM_KEEP(record_ptr);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                    value <<= 5;
                    record.field10 = value;
                    object = func_800A878C(record_ptr, angle);
                }
                if (object != 0) {
                    value = func_800644B8(angle) << 5;
                    if (value < 0) {
                        value = -value;
                    }
                    ((S_800A895C_3 *)(object->unk_08))->unk_14 = -value;
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
 * The aligned-1 residue was semantic: adding the third func_800374F4 result emits retail's addu.
 */
