#include "common.h"

#include "common.h"

/* Sub-object embedded at offset 0x20 of the entity (same family as
 * func_800520B4 / func_80051E94): owner backpointer, four zeroed shorts,
 * a table pointer, then a walked slot array of s32 (16 entries, +4/step). */
typedef struct S_80053374_Sub {
    /* 0x00 */ void *owner;
    /* 0x04 */ s16 f04;
    /* 0x06 */ s16 f06;
    /* 0x08 */ s16 f08;
    /* 0x0A */ s16 f0A;
    /* 0x0C */ void *tbl;
    /* 0x10 */ /* s32 slots[16] walked via s32* p = (s32 *)sub; p[4].. */
} S_80053374_Sub;

typedef struct S_80053374_obj {
    /* 0x00 */ u8 pad00[0x10];
    /* 0x10 */ void (*unk10)(void *);
    /* 0x14 */ u8 pad14[0x20 - 0x14];
    /* 0x20 */ S_80053374_Sub sub;
} S_80053374_obj;

extern s32 D_80071A84[4];

extern void func_8005313C(void *a0);
extern void *func_8003FD64(s32 a0, void *a1);
extern void func_80052FE8(void *a0, s16 a1);
extern void func_80052A20(void);

/* Installs state-fn func_8005313C, inits the embedded sub-object (owner=a1,
 * four zeroed shorts, tbl=&D_80071A84), then tries 16 times to attach a slot
 * via func_8003FD64(0x212, entity); on success configures it with
 * func_80052FE8(slot, i) and stashes it in the sub-object's slot array
 * (starting at +0x10, walked by a running s32* incremented per lap).
 * Finishes with func_80052A20 (global table init).
 *
 * Match requires 2.7.2-cdk: plain 2.7.2 folds the sub-base materialization
 * into direct a0+const stores and collapses addiu-into-s1 (1 word short of
 * retail's addiu-v0 + move-s1 preheader). Sibling func_800520B4 uses the
 * same a0->sub.owner + (s16*)((u8*)a0+0x20) split and also matches only at
 * cdk. */
void func_80053374(S_80053374_obj *a0, void *a1)
{
    s16 *sub;
    s32 i;
    s32 *p;
    void *v0;

    i = 0;
    sub = (s16 *)((u8 *)a0 + 0x20);
    a0->unk10 = func_8005313C;
    a0->sub.owner = a1;
    sub[2] = 0;
    sub[3] = 0;
    sub[4] = 0;
    sub[5] = 0;
    *(void **)(sub + 6) = &D_80071A84;
    p = (s32 *)sub;

    do {
        v0 = func_8003FD64(0x212, a0);
        if (v0 != 0) {
            func_80052FE8(v0, (s16)i);
            p[4] = (s32)v0;
        }
        i++;
        p++;
    } while (i < 0x10);

    func_80052A20();
}
