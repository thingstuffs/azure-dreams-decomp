#include "common.h"

typedef struct Entry Entry;

struct Entry {
    Entry *next;
    s16 value;
    s16 state;
};

extern s32 Krom2RawAdd(s32);
extern void func_80067014(s32);
extern s16 *func_80121C90(s32, s16 *);

extern s16 D_80128A20[];
extern Entry *D_80129720;
extern s16 D_80129724;

s16 *func_80122FA8(s16 arg0)
{
    u16 id;
    Entry *scan;
    Entry *cur;
    Entry *prev;
    Entry *loop_head;
    Entry *next;
    s16 *result;

    id = arg0;
    if (Krom2RawAdd(id) == -1) {
        goto fail;
    }

    if (D_80129724 >= 30) {
        func_80067014(0);
        D_80129724 = 0;
    }

    cur = D_80129720;
    prev = cur;
    scan = cur;
    if (scan != 0) {
        do {
            if ((u16)scan->state == id) {
                result = &D_80128A20[(u16)scan->value];
                loop_head = D_80129720;
                if (scan == loop_head) {
                    goto found_head;
                }
                next = scan->next;
                D_80129720 = scan;
                cur->next = next;
                scan->next = loop_head;
                D_80129724++;
                return result;
            }
            prev = cur;
            cur = scan;
            scan = cur->next;
        } while (scan != 0);
    }

    result = func_80121C90((u16)arg0,
                           &D_80128A20[(u16)cur->value]);
    if (result != &D_80128A20[(u16)cur->value]) {
        goto fail;
    }
    {
        Entry *old_head;

        cur->state = arg0;
        prev->next = 0;
        old_head = D_80129720;
        D_80129720 = cur;
        cur->next = old_head;
        D_80129724++;
        return result;
    }

found_head:
    D_80129724++;
    return result;

fail:
    return 0;
}
