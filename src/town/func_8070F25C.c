#include "common.h"

extern char D_8001B14C[];
extern char D_8001C018[];
extern char D_8001D6B5[];
extern char D_8001D7A5[];
extern char D_800227FB[];

extern char *func_80016E48(s32);
extern s32 func_8001A64C(u32);

/* Selects a string, with a state-dependent choice for selector 12. */
char *func_8001825C(s32 unused_0, s32 unused_1, s32 text_id)
{
    s32 selector = text_id;

    switch (selector - 12) {
    case 7:
        return D_8001C018;
    case 6:
        return D_800227FB;
    case 0:
        if (func_8001A64C(0x94A) != 0) {
            return D_8001D6B5;
        }
        return D_8001D7A5;
    case 40:
    case 41:
    case 42:
        return func_80016E48(selector);
    default:
        return D_8001B14C;
    }
}
