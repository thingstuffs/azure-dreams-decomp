#include "common.h"

extern void func_800239B0(void *arg0);
extern s32 D_800814A0[];

/* Processes a nonzero record and sets its flag and the global flag to include bit 15. */
void func_80023A00(s32 record) {
    void *record_data;

    if (record != 0) {
        record_data = (void *) (record + 0x20);
        func_800239B0(record_data);
        *(u16 *) ((s8 *) record_data - 2) = *(u16 *) ((s8 *) record_data - 2) | 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
