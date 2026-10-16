/* Relink of matched dungeon/func_80AC7330; every changed retail word is a paired relocation. */
#define D_80171728 D_8015F760
#include "common.h"

extern s32 func_800AB1C0(void);
extern void func_800AD594(s32, s32);
extern void func_800A4ACC(s32);
extern s32 func_800AD9B4(s32, s32);
extern s32 D_8015F760;

/* Updates the actor and resets the entity state when the checks succeed. */
void func_80160AF0(void *entity_arg, s32 unused, s32 check_arg, s32 actor_arg) {
    void *entity = entity_arg;
    s32 check_value = check_arg;
    s32 actor = actor_arg;

    if (func_800AB1C0() != 0) {
        func_800AD594(actor, 4);
        func_800A4ACC(actor);
        if ((func_800AD9B4(check_value, actor) << 16) > 0) {
            do {
                *(s32 **)((u8 *)entity + 0x8C) = &D_8015F760;
            } while (0);
            *(s32 *)((u8 *)entity + 0x90) = 0;
        }
    }
}
