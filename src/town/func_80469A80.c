#include "common.h"

extern void func_8001A1A0(void *, void *);
extern void func_8001A200(void *, void *);
extern u8 D_8001791C[];
extern u8 D_80017AD0;
extern u8 D_80017B0C;
extern u8 D_80017B18;
extern u8 D_80017E54[];

/* Initialize the shared buffer using the selected table entry and return it. */
void *func_8001AA80(s32 entry_index) {
    u8 *buffer = D_80017E54;

    *(s32 *)(buffer + 0xC) = *(s32 *)(D_8001791C + (entry_index * 0xC));
    func_8001A200(buffer, &D_80017AD0);
    func_8001A1A0(buffer + 0x14, &D_80017B0C);
    func_8001A1A0(buffer + 0x28, &D_80017B18);
    return buffer;
}
