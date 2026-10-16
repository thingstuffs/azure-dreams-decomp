/* Relink of matched dungeon/func_80976F6C; every changed retail word is a paired relocation. */
#define D_801714D4 D_8016B058
#include "common.h"
#include "shared/dungeon_status.h"

extern s32 func_800A4ACC();
extern s32 func_800AB1C0();
extern s32 func_800AD594();
extern s32 func_800AD9B4();

extern s32 D_8016B058[];

/* Selects the state table after a successful target check and applies the flagged offset. */
void func_8016C558(void *state, s32 unused, s32 source, s32 target) {
    if (func_800AB1C0() != 0) {
        func_800AD594(target, 4);
        func_800A4ACC(target);
        if ((func_800AD9B4(source, target) << 16) > 0) {
            *(s32 **)((u8 *)state + 0x8C) = D_8016B058;
            if (dungeonStatus.flags & 0x80) {
                *(s16 *)((u8 *)state + 0x92) = -0x20;
            }
        }
    } else if (dungeonStatus.flags & 0x80) {
        *(s16 *)((u8 *)state + 0x92) = -0x20;
    }
}
