#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"

extern struct { s32 v; s32 pad[2]; } D_800814A0;

typedef struct UnkStruct807B11B8 {
    s32 unk0;
    s32 unk4;
    u8 pad8[4];
    s32 unkC;
    s32 unk10;
} UnkStruct807B11B8;

/* Advance motion and propagate update flags to the object and global state. */
void func_800F89B8(u16 *object_data, UnkStruct807B11B8 *motion, u16 *update_state) {
    motion->unk0 += motion->unkC;
    motion->unk4 += motion->unk10;
    func_800478B8(update_state);
    if (*(u16 *)((u8 *)update_state + 0x14) & 0x6000) {
        u16 *object_flags = (u16 *)((u8 *)object_data - 2);
        *object_flags = (u16)(*object_flags | 0x8000);
        D_800814A0.v = D_800814A0.v | 0x8000;
    }
}
