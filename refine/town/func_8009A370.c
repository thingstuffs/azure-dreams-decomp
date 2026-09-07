#include "common.h"

typedef struct S_80097AD0_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80097AD0_0;   /* arg0 in func_80097AD0 */

typedef struct S_80097AD0_1 {
    union { u16 u16; s32 s32; } unk_00;   /* accessed as both */
    union { u16 u16; s32 s32; } unk_04;   /* accessed as both */
    union { u16 u16; s32 s32; } unk_08;   /* accessed as both */
} S_80097AD0_1;   /* arg1 in func_80097AD0 */

typedef struct S_80097AD0_2 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80097AD0_2;   /* object in func_80097AD0 */

typedef struct S_80097AD0_3 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_80097AD0_3;   /* ((S_80097AD0_2 *)object)->unk_08 in func_80097AD0 */



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

/* Spawn objects at randomized positions around an origin with evenly spaced angles. */
void func_80097AD0(S_80097AD0_0 *origin, S_80097AD0_1 *spread, s32 count) {
    StackRecord record;
    s32 angle;
    s32 angle_step;
    s32 magnitude;
    s32 object_index;
    s32 angle_component;
    s32 y;
    u16 initial_y;
    S_80097AD0_2 *object;

    if (count != 0) {
        angle_step = 0x1000 / count;
        do { object_index = 0; } while (0);
        do { angle = rand(); } while (0);
        initial_y = origin->unk_0A;
        record.field16 = -4;
        record.y = initial_y;
        if (count > 0) {
            do {
                record.x = (origin->unk_02 +
                            func_800374F4(spread->unk_00.u16)) -
                           (spread->unk_00.s32 / 2);
                record.z = (origin->unk_06 +
                            func_800374F4(spread->unk_04.u16)) -
                           (spread->unk_04.s32 / 2);
                y = (origin->unk_0A -
                     func_800374F4(spread->unk_08.u16)) -
                    (spread->unk_08.s32 / 2);
                record.y = y;
                record.fieldC = func_80064584(angle, y) << 5;
                angle_component = func_800644B8(angle);
                {
                    void *record_ptr = &record;
                    ASM_KEEP(record_ptr);   /* MATCH pin: retail schedule: same instructions, different order without it */
                    angle_component <<= 5;
                    record.field10 = angle_component;
                    object = func_8009792C(record_ptr, angle);
                }
                if (object != 0) {
                    angle_component = func_800644B8(angle) << 5;
                    if (angle_component < 0) {
                        angle_component = -angle_component;
                    }
                    ((S_80097AD0_3 *)(object->unk_08))->unk_14 = -angle_component;
                }
                object_index++;
                angle += angle_step;
            } while (object_index < count);
        }
    }
}

/* MECHANISM:
 * The escaping 0x18-byte record fixes the 0x48 frame and stack fields at 0x10..0x26.
 * A guarded short-lived $a0 record pointer orders addiu &record before the return shift.
 * ASM_KEEP(value) fences that sll before the s16 angle cast; both anchors emit zero words.
 */
