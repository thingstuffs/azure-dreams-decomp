/* Relink of matched dungeon/func_80E12A58; every changed retail word is a paired relocation. */
#include "common.h"

extern s32 func_80042900(void *entry, s32 effect_id);
extern void func_80042B68(void *entry, s32 effect_id);

/* Checks object code 0x19, exits on failure, and applies it on success. */
s32 func_80170258(void *object) {
    if ((func_80042900(object, 0x19) << 0x10) != 0) {
        func_80042B68(object, 0x19);
        return 1;
    }
    return 0;
}
