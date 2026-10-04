#include "common.h"
#include "shared/dungeon_status.h"


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_800A4ACC();
s32 func_800AB1C0();
void func_800AD594();
s32 func_800AD9B4();
extern s32 D_80171514;

typedef struct S_80172474_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
} S_80172474_0;   /* entity in func_80172474 */

/* Runs actor callbacks, updates entity state on success, and applies the global flag adjustment. */
void func_80172474(void *entity_ptr, s32 unused, s32 check_arg, s32 actor_arg)
{
    S_80172474_0 *entity = entity_ptr;
    s32 check_value = check_arg;
    s32 actor = actor_arg;

    if (func_800AB1C0() != 0) {
        func_800AD594(actor, 0);
        func_800A4ACC(actor);
        if ((func_800AD9B4(check_value, actor) << 0x10) <= 0) {
            return;
        }
        do {
            entity->unk_8C = &D_80171514;
        } while (0);
    }
    if (dungeonStatus.flags & 0x80) {
        entity->unk_92 = -0x20;
    }
}
