#include "common.h"

#include "common.h"

extern s32 D_80080A6C;
extern s32 D_8006B200[];

/* Return the index of a matching table key, or -1 if absent. */
s32 func_8003C634(s32 key)
{
    s32 entry_index;
    s32 result;

    entry_index = 0;
    if (D_80080A6C > 0) {
        s32 entry_count;
        s32 *entry_key;

        entry_count = D_80080A6C;
        entry_key = D_8006B200;
        do {
            if (key == *entry_key) {
                result = entry_index;
                goto done;
            }
            entry_index++;
            entry_key += 2;
        } while (entry_index < entry_count);
    }

    result = -1;
done:
    return result;
}
