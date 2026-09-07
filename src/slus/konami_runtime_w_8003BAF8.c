#include "common.h"

#include "common.h"

typedef struct InputRecord {
    s16 field_00;
    s16 field_02;
    u16 field_04;
    u16 field_06;
    void *field_08;
    void *field_0C;
    u16 field_10;
    u16 field_12;
} InputRecord;

typedef struct RuntimeState {
    u8 pad_00[4];
    void *field_04;
    u8 pad_08[4];
    u16 field_0C;
    u16 field_0E;
    void *field_10;
    u16 field_14;
    u16 field_16;
    s16 field_18;
    s16 field_1A;
    u8 pad_1C[8];
    void *field_24;
    u16 field_28;
    u16 field_2A;
} RuntimeState;

typedef struct TableEntry {
    u16 field_00;
    u16 field_02;
    u16 field_04;
    u16 field_06;
    u8 pad_08[0x18];
} TableEntry;

typedef struct PairRecord {
    u8 pad_00[4];
    s16 field_04;
    s16 field_06;
} PairRecord;

typedef void (*RuntimeCallback)(RuntimeState *, void *);

extern void func_800A0560(void);
extern PairRecord *func_800C1034(s16, s16);
extern void func_80041094(u16, s16, s16, s32, s32);
extern s32 func_80034FE4(void *);

extern RuntimeState D_8006ADBC;
extern RuntimeState D_8006ADEC;
extern RuntimeState D_8006ADEC_read __asm__("D_8006ADEC");
extern s16 D_8006ADE8[5];
extern s16 D_8006ADE8_else[5] __asm__("D_8006ADE8");
extern RuntimeCallback D_8006AE10[3];
extern volatile s16 D_8006AE18[5];
extern volatile u8 D_80080A88;
extern u8 D_800812F8;
extern u8 D_80082A38[9];
extern u16 D_80082E76[5];
extern TableEntry D_800D2650[];
extern TableEntry D_800D2FC0[];
extern volatile u8 D_800D381A;
extern s16 D_800D426C;
extern s16 D_800D426E;
extern u16 D_800D5070[];
extern u16 D_80013714[5];

__asm__(".set D_80080A88, 0x80080A88");
__asm__(".set D_800D426C, 0x800D426C");
__asm__(".set D_800D426E, 0x800D426E");
__asm__(".set D_800812F8, 0x800812F8");
__asm__(".set D_800D381A, 0x800D381A");

void func_8003BAF8(InputRecord *arg0)
{
    TableEntry *entry;
    PairRecord *pair;
    RuntimeState *state;
    void *value;
    void *state_word;
    u16 temp;

    func_800A0560();
    D_8006ADBC.field_28 = D_8006ADBC.field_18;
    D_8006ADEC.field_28 = D_8006ADBC.field_18;
    D_8006ADBC.field_2A = D_8006ADBC.field_1A;
    D_8006ADEC.field_2A = D_8006ADBC.field_1A;
    D_8006ADEC.field_18 = arg0->field_00;
    temp = arg0->field_02;
    D_8006ADEC.field_1A = temp;
    D_800D381A = temp;
    do { } while (0);

    if (arg0->field_00 == 11) {
        entry = (TableEntry *)((u8 *)D_800D2650 +
                               (arg0->field_02 << 5));
    } else {
        entry = (TableEntry *)((u8 *)D_800D2FC0 +
                               (arg0->field_02 << 5));
    }

    pair = func_800C1034(D_8006ADEC_read.field_18,
                         D_8006ADEC_read.field_1A);
    do { } while (0);
    if (pair->field_04 == D_800D426C &&
        pair->field_06 == D_800D426E) {
        D_80080A88 = 1;
    }

    state = &D_8006ADEC;
    state_word = arg0->field_0C;
    state->field_10 = entry;
    state->field_24 = state_word;
    state->field_14 = arg0->field_04;
    state->field_16 = arg0->field_06;
    state->field_0C = D_800D5070[arg0->field_10 & 3];
    state->field_0E = arg0->field_12;
    value = arg0->field_08;
    if (value != 0) {
        if (state->field_18 != 12) {
            state->field_04 = &D_800812F8;
        } else {
            state->field_04 = value;
        }
    }

    if (D_8006AE10[0] != 0) {
        D_8006AE10[0](state, value);
    }

    func_80041094(arg0->field_00,
                  (s16)(entry->field_04 +
                        (arg0->field_04 + entry->field_00)),
                  (s16)(entry->field_06 +
                        (arg0->field_06 + entry->field_02)),
                  0, D_80082E76[0] ^ 1);

    D_80013714[0] &= 0xFFFD;
    {
        s32 ret = func_80034FE4(D_80082A38);
        if (ret != 0) {
            s16 one = 1;
            do { } while (0);
            D_8006ADE8[0] = one;
            D_8006AE18[0] = 0;
        } else {
            ASM_KEEP(ret);   /* MATCH pin: slus-diff */
            D_8006ADE8_else[0] = 0;
            D_8006AE18[0] = 0;
        }
    }
}
