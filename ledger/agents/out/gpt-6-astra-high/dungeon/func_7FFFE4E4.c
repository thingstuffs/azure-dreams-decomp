#include "common.h"

typedef void (*Callback)(void *, void *, void *, s32);

extern void func_80095388(void *);
extern void func_8009539C(void *);
extern s16 func_8008F170(void *, void *);
extern void func_8008F27C(void *, void *, s16);
extern void func_8008F294(void *, void *);
extern void func_8008F664(void *, void *);
extern s32 func_8008C180(s16, s16);
extern s32 func_800C1D44(u16);
extern void func_80053DA8(s32);

extern u8 D_8009B454[];
extern s16 D_800D45AA[];
extern u8 D_800FE488[];

/* Updates motion, handles ground contact, and checks the tile height limit. */
void func_7FFFE4E4(void *owner, void *actor, void *motion, s32 callback_arg) {
    s16 ground_height;
    s32 ground_height_s32;

    func_80095388(motion);
    if (*(s32 *)((u8 *)motion + 0x14) > 0x200000) {
        *(s32 *)((u8 *)motion + 0x14) = 0x200000;
    }
    func_8009539C(motion);
    ground_height = func_8008F170(motion, D_800FE488);
    func_8008F294(actor, motion);
    func_8008F664(actor, motion);
    ground_height_s32 = ground_height;
    if (*(s16 *)((u8 *)motion + 0xA) >= ground_height_s32) {
        func_8008F27C(actor, motion, ground_height_s32);
        ((Callback *)(*(void **)((u8 *)owner + 0x58)))[1](owner, actor, motion, callback_arg);
    } else if (*(u8 *)((u8 *)actor + 0x3B) != 0) {
        *(s32 *)((u8 *)motion + 0xC) = 0;
        *(s32 *)((u8 *)motion + 0x10) = 0;
        *(s32 *)((u8 *)motion + 0x14) = 0;
        ((Callback *)(*(void **)((u8 *)owner + 0x58)))[1](owner, actor, motion, callback_arg);
    }
    if ((*(u16 *)((u8 *)owner - 2) & 0x8000) == 0 &&
        *(void **)((u8 *)owner + 0x50) == D_8009B454) {
        s32 tile_type;

        tile_type = func_800C1D44((u16)func_8008C180(
            *(s16 *)((u8 *)motion + 2), *(s16 *)((u8 *)motion + 6)));
        if (tile_type != 0) {
            s16 height = *(s16 *)((u8 *)motion + 0xA);
            s16 height_limit = D_800D45AA[tile_type];

            if (height > height_limit) {
                func_80053DA8(0x517);
            }
        }
    }
}
