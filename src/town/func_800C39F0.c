#include "common.h"

typedef struct {
    u8 pad[0x18];
    s16 field18;
    s16 field1A;
} GlobalState;

extern GlobalState D_8006ADBC;
extern s16 D_800D4258[];
extern s16 D_800D4260[];

extern void func_8004425C(s32 arg0);
extern void func_8004450C(s32 arg0);
extern void SD_Call(s32 arg0);
extern void func_800542BC(void);
extern u16 *func_800C1034(s16 arg0, s16 arg1);

/* Loads a four-value record and applies the pending override to its first value. */
void func_800C1150(void) {
    u16 *record_values;
    u16 *current_values;

    SD_Call(0x72);
    func_800542BC();
    SD_Call(0x74);
    func_800542BC();
    func_8004425C(2);
    func_8004450C(0);

    record_values = func_800C1034(D_8006ADBC.field18, D_8006ADBC.field1A);
    D_800D4260[0] = record_values[0];
    current_values = D_800D4260;
    current_values[1] = record_values[1];
    current_values[2] = record_values[2];
    current_values[3] = record_values[3];

    if (D_800D4258[0] == -5) {
        D_800D4258[0] = -1;
        D_800D4260[0] = -1;
    }
    if (D_800D4258[0] != -1) {
        D_800D4260[0] = D_800D4258[0];
    }
    if ((s16) D_800D4260[0] != -1) {
        func_8004425C((s16) D_800D4260[0]);
    }
}
