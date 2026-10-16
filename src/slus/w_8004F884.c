#include "common.h"

typedef struct S_8004F884_arg {
    u8 pad00[4];
    void *arr[8];  /* array of pointers starting at offset 0x04; only entries 0..count-1 used */
    s32 count;     /* 0x24 */
} S_8004F884_arg;

extern void interpolateSelectionMenuEntryCoordinates(S_8004F884_arg *a0);
extern void interpolateSelectionMenuEntryShade(S_8004F884_arg *a0);
extern void func_8004AFC8(void *base, s32 count, s32 size, int (*compar)(void *, void *));
extern int compareSelectionMenuEntryOrder(void *a0, void *a1);
extern void linkTypedListNode(void *a0, void *a1);

/* Sorts and relinks the list entries, then runs the list update hooks. */
void reorderAndInterpolateSelectionMenuEntries(S_8004F884_arg *list) {
    void *sorted[4];
    s32 index;
    void **dest;
    u8 *source;
    void **pair;

    index = 0;
    if (list->count > 0) {
        dest = sorted;
        source = (u8 *)list;
        do {
            void *entry = *(void **)(source + 4);
            source += 4;
            index++;
            *dest = entry;
            dest++;
        } while (index < list->count);
    }

    func_8004AFC8(sorted, list->count, 4, compareSelectionMenuEntryOrder);

    index = 0;
    if (list->count - 1 > 0) {
        pair = sorted;
        do {
            void *current = pair[0];
            void *next = pair[1];
            pair++;
            linkTypedListNode(current, next);
            index++;
        } while (index < list->count - 1);
    }

    interpolateSelectionMenuEntryCoordinates(list);
    interpolateSelectionMenuEntryShade(list);
}
