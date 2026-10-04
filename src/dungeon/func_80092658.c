#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad0[0x1c];
    s32 flags;
    u8 pad20[0x3c];
    s32 value;
} Resource;

typedef struct {
    u8 pad0[0x8c];
    u8 *callback;
    u8 pad90[6];
    u16 counter;
    u8 pad98[3];
    u8 state;
    u8 pad9c[6];
    u16 flags;
} Object;

extern u8 D_80096384[];
extern u8 D_80097C78;
extern s32 func_80042900(void *, s32);
extern void func_80099F04(s32);
extern void func_80099F70(s32);
extern s32 func_800A5C70(void);

void func_80097DB8(Object *object, s32 unused1, s32 unused2, Resource *resource) {
    s32 state;
        /* MATCH: Keep the guard result in v0 across argument setup. */
    s32 guard;
    GameWork *work;
        /* MATCH: Keep the shared flag table in its retail saved register. */
    DungeonGlobalStatus *status;
        /* MATCH: Keep the incoming resource in a3 for the pass-through call. */
        /* MATCH: Set a0 in both guard delay slots without a redundant call-slot move. */
    Resource *callResource;

    state = object->state;
    work = &gameWork;
    switch (state) {
    case 0:
        object->callback = &D_80097C78;
        object->state += 1;
        break;
    case 1:
                /* MATCH: Prevent propagation of the a3 copy into the a0 argument setup. */
        if ((dungeonStatus.flags & 4) == 0 && (object->flags & 0x10) != 0) {
            guard = work->buttons & 0x20;
            callResource = resource;
            if (guard != 0) {
                guard = func_800A5C70();
                callResource = resource;
                if (guard != 0) {
                    status = &dungeonStatus;
                    status->flags |= 0x80;
                }
            }
            if ((func_80042900(callResource, 1) << 16) == 0) {
                object->callback = 0;
                dungeonStatus.unk_0A += 1;
                object->state += 1;
            } else {
                func_80099F70(resource->value);
                func_80099F04(resource->value);
                dungeonStatus.flags |= 0x812;
            }
        }
        break;
    case 2:
        resource->flags &= ~0x200;
        func_80099F70(resource->value);
        func_80099F04(resource->value);
        dungeonStatus.flags |= 0x812;
        object->callback = D_80096384;
        dungeonStatus.unk_0A -= 1;
        break;
    }
    object->counter += 1;
}
