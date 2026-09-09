#include "common.h"

extern s32 func_80042900(void *arg0, s32 arg1);
extern s32 D_8008ACDC;

#ifndef NON_MATCHING
#define KEEP_DISPATCH() \
    ASM_KEEP(dispatch_result)
#endif

/* Selects the target dispatch pointer from the source type and flags. */
void func_80096088(void *target, void *source) {
    u8 *dispatch_result;

#ifndef NON_MATCHING
    {
        s32 type_match;
        type_match = func_80042900(source, 10) << 16;
        if (type_match != 0) {
            dispatch_result = (u8 *)0x80090000;
            KEEP_DISPATCH();
            dispatch_result += 0x6384;
            *(void **)((u8 *)target + 0x8C) = dispatch_result;
        } else {
            dispatch_result = (u8 *)0x80090000;
            KEEP_DISPATCH();

            {
                s32 source_flags;
                source_flags = *(s32 *)((u8 *)source + 0x1C);
                source_flags &= 0x100000;
                if (source_flags != 0) {
                    dispatch_result = (u8 *)0x80090000;
                    KEEP_DISPATCH();
                    dispatch_result -= 5432;
                    *(void **)((u8 *)target + 0x8C) = dispatch_result;
                } else {
                    dispatch_result = (u8 *)0x80090000;
                    KEEP_DISPATCH();

                    {
                        u8 *default_dispatch;
                        default_dispatch = (u8 *)&D_8008ACDC;
                        *(void **)((u8 *)target + 0x8C) = default_dispatch;
                    }
                }
            }
        }
    }

#else
    if ((func_80042900(source, 10) << 16) != 0) {
        *(void **)((u8 *)target + 0x8C) = (u8 *)0x80096384;
    } else if ((*(s32 *)((u8 *)source + 0x1C) & 0x100000) != 0) {
        *(void **)((u8 *)target + 0x8C) = (u8 *)0x8008EAC8;
    } else {
        *(void **)((u8 *)target + 0x8C) = &D_8008ACDC;
    }
#endif
}
