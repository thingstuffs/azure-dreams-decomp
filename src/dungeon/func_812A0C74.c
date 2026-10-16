/* Relink of matched dungeon/func_81252C74 at file 0x1272C74; imports and data use paired retail relocations. */
#define dungeonStatus D_80085990
#include "common.h"
#include "shared/dungeon_status.h"


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_800A3784();
s32 func_800A9E78();
void func_800AC24C();
s32 func_800AC66C();
extern s32 D_8014C514;

typedef struct S_80172474_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
} S_80172474_0;   /* entity in func_8014D474 */

/* Runs actor callbacks, updates entity state on success, and applies the global flag adjustment. */
void func_8014D474(void *entity_ptr, s32 unused, s32 check_arg, s32 actor_arg)
{
    S_80172474_0 *entity = entity_ptr;
    s32 check_value = check_arg;
    s32 actor = actor_arg;

    if (func_800A9E78() != 0) {
        func_800AC24C(actor, 0);
        func_800A3784(actor);
        if ((func_800AC66C(check_value, actor) << 0x10) <= 0) {
            return;
        }
        do {
            entity->unk_8C = &D_8014C514;
        } while (0);
    }
    if (dungeonStatus.flags & 0x80) {
        entity->unk_92 = -0x20;
    }
}
