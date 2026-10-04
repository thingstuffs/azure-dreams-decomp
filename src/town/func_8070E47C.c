#include "common.h"

extern char D_8001B14C[];
extern s32 D_8001B16C[];
extern char D_8001B9E0[];
extern char D_8001C6D0[];
extern char D_80020E44[];

extern s32 func_80016CE4(long long);
extern s32 func_80016D18(void);
extern char *func_80016E48(s32);

/* Select event data, using fallback data when an event handler returns null. */
char *func_8001747C(long long forwarded_arg, s32 event_id)
{
    s32 result_addr;

    switch (event_id - 12) {
    case 7:
        result_addr = func_80016CE4(forwarded_arg);
        D_8001B16C[0] = result_addr;
        if (result_addr == 0) {
            return D_8001B9E0;
        }
        return (char *)result_addr;
    case 6:
        result_addr = func_80016D18();
        D_8001B16C[0] = result_addr;
        if (result_addr != 0) {
            return (char *)result_addr;
        }
        return D_80020E44;
    case 40:
    case 41:
    case 42:
        return func_80016E48(event_id);
    case 0:
        return D_8001C6D0;
    default:
        return D_8001B14C;
    }
}
