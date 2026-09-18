#include "common.h"

typedef void (*TownCallback)(s32, s32, s32, s32);

extern void *D_80016000[];
extern void *D_80016180[43];
extern void *D_8001B16C[4];
extern char D_8001B14C[];
extern char D_8001B9E0[];
extern char D_80020E44[];
extern char D_8001C6D0[];

extern char *func_80016CE4(long long);
extern char *func_80016D18(void);
extern char *func_80016E48(s32);
extern void func_8001A554(s32);
extern s32 func_8001A64C(s32);
extern s32 func_80019880(s32, s32);

/* Selects town text and runs the selected handler's fallback actions. */
char *func_800172DC(long long lookup, s32 text_selector)
{
    u32 index;
    static void *const keepalive[] = {
        &&L_first, &&L_second, &&L_third, &&L_fourth, &&L_default
    };

    (void)keepalive;

    index = text_selector - 12;
    if (index >= 43) {
        goto L_default;
    }
    goto *D_80016180[index];

L_first:
    {
        char *text = func_80016CE4(lookup);
        D_8001B16C[0] = text;
        if (text != 0) {
            return text;
        }
        return D_8001B9E0;
    }

L_second:
    {
        char *text = func_80016D18();
        D_8001B16C[0] = text;
        if (text != 0) {
            return text;
        }
        func_8001A554(0x943);
        if (func_8001A64C(0x941) != 0 && func_80019880(13, 6) == 0) {
            (*(TownCallback *)((u8 *)((void **)*(void **)D_80016000)[8] + 0x220))
                (6, 13, 0, 0);
        }
        return D_80020E44;
    }

L_third:
    return func_80016E48(text_selector);

L_fourth:
    return D_8001C6D0;

L_default:
    return D_8001B14C;
}
