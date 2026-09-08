#include "common.h"

extern void func_80033C84(s32 arg0);
extern struct { s32 v; s32 pad[0x520]; } D_800814A0;

/* Process the referenced record, clear its preceding word, and set local and global flags. */
void func_8008BF0C(void *record_ref) {
    s32 global_flags;
    func_80033C84(*(s32 *)((u8 *) record_ref + 0));
    *(u16 *)((u8 *) record_ref - 2) = (u16) (*(u16 *)((u8 *) record_ref - 2) | 0x8000);
    global_flags = D_800814A0.v;
    *(s32 *)((u8 *) record_ref - 0x10) = 0;
    D_800814A0.v = (s32) (global_flags | 0x8000);
}
