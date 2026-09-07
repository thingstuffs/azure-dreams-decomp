#include "common.h"

/* Copies arg0->count pointer entries from arg0's inline array (offset 0x04) into a 4-slot
 * stack buffer, sorts them via the qsort-style func_8004AFC8 helper (comparator func_8004F85C),
 * then re-links each adjacent sorted pair back into their list via func_80044AAC (insert-after).
 * Finishes with two more per-object hooks, func_8004F684(arg0) and func_8004F780(arg0). */
#include "common.h"

typedef struct S_8004F884_arg {
    u8 pad00[4];
    void *arr[8];  /* array of pointers starting at offset 0x04; only entries 0..count-1 used */
    s32 count;     /* 0x24 */
} S_8004F884_arg;

extern void func_8004F684(S_8004F884_arg *a0);
extern void func_8004F780(S_8004F884_arg *a0);
extern void func_8004AFC8(void *base, s32 count, s32 size, int (*compar)(void *, void *));
extern int func_8004F85C(void *a0, void *a1);
extern void func_80044AAC(void *a0, void *a1);

void func_8004F884(S_8004F884_arg *arg0) {
    void *buf[4];
    s32 i;
    void **p;
    u8 *q;
    void **s;

    i = 0;
    if (arg0->count > 0) {
        p = buf;
        q = (u8 *)arg0;
        do {
            void *v = *(void **)(q + 4);
            q += 4;
            i++;
            *p = v;
            p++;
        } while (i < arg0->count);
    }

    func_8004AFC8(buf, arg0->count, 4, func_8004F85C);

    i = 0;
    if (arg0->count - 1 > 0) {
        s = buf;
        do {
            void *a = s[0];
            void *b = s[1];
            s++;
            func_80044AAC(a, b);
            i++;
        } while (i < arg0->count - 1);
    }

    func_8004F684(arg0);
    func_8004F780(arg0);
}
