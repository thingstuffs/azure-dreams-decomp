#include "shared/dungeon_actor_callbacks.h"
#include "common.h"
#include "shared/dungeon_status.h"

extern void func_80099F04(s32);
extern void func_80099F70(s32);
extern u8 D_8008EAC8[];

/* Updates global flags and stores the pointer selected by the source flags. */
void *func_8008EA40(void *state, void *unused_1, void *unused_2, void *source) {
    void *next_ptr;

    func_80099F70(*(s32 *)((u8 *)source + 0x5C));
    func_80099F04(*(s32 *)((u8 *)source + 0x5C));
    dungeonStatus.flags |= 0x812;
    if (*(s32 *)((u8 *)source + 0x1C) & 0x100000) {
        next_ptr = D_8008EAC8;
    } else {
        next_ptr = func_8008ACDC;
    }
    *(void **)((u8 *)state + 0x8C) = next_ptr;
    return next_ptr;
}
