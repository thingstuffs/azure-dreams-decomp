#include "common.h"

extern void func_800478B8(void *arg0);
extern s32 D_800814A0;

/* Sets target and global flags based on source flags, then processes the source. */
void func_800D79B0(u16 *target_data, void *unused, u16 *source_data) {
    if (*(u16 *)((u8 *)source_data + 0x14) & 0x6000) {
        u16 *target_flags = (u16 *)((u8 *)target_data - 2);
        *target_flags = (u16)(*target_flags | 0x8000);
        D_800814A0 = D_800814A0 | 0x8000;
    }
    func_800478B8(source_data);
}
