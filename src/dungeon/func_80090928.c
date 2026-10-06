#include "shared/dungeon_actor_callbacks.h"
#include "common.h"

extern s32 func_80042900(void *entry, s32 effect_id);
extern u8 D_8008EAC8[];
extern u8 D_80096384[];

/* Selects the target dispatch pointer from the source type and flags. */
void func_80096088(void *target, void *source) {

    {
        s32 type_match;
        type_match = func_80042900(source, 10) << 16;
        if (type_match != 0) {
            *(void **)((u8 *)target + 0x8C) = D_80096384;
        } else {

            {
                s32 source_flags;
                source_flags = *(s32 *)((u8 *)source + 0x1C);
                source_flags &= 0x100000;
                if (source_flags != 0) {
                    *(void **)((u8 *)target + 0x8C) = D_8008EAC8;
                } else {

                    {
                        u8 *default_dispatch;
                        default_dispatch = (u8 *)func_8008ACDC;
                        *(void **)((u8 *)target + 0x8C) = default_dispatch;
                    }
                }
            }
        }
    }
}
