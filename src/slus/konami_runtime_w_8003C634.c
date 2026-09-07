#include "common.h"

#include "common.h"

extern s32 D_80080A6C;
extern s32 D_8006B200[];

s32 func_8003C634(s32 key)
{
    s32 i;
    s32 result;

    i = 0;
    if (D_80080A6C > 0) {
        s32 count;
        s32 *entry;

        count = D_80080A6C;
        entry = D_8006B200;
        do {
            if (key == *entry) {
                result = i;
                goto done;
            }
            i++;
            entry += 2;
        } while (i < count);
    }

    result = -1;
done:
    return result;
}
