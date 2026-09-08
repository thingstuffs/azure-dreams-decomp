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

/* Initializes the entity state and sub-object, creates up to 16 slots, and initializes the global table. */
void func_80053374(S_80053374_obj *entity, void *owner)
{
    s16 *sub;
    s32 slot_index;
    s32 *slot_cursor;
    void *slot;

    slot_index = 0;
    sub = (s16 *)((u8 *)entity + 0x20);
    entity->unk10 = func_8005313C;
    entity->sub.owner = owner;
    sub[2] = 0;
    sub[3] = 0;
    sub[4] = 0;
    sub[5] = 0;
    *(void **)(sub + 6) = &D_80071A84;
    slot_cursor = (s32 *)sub;

    do {
        slot = func_8003FD64(0x212, entity);
        if (slot != 0) {
            func_80052FE8(slot, (s16)slot_index);
            slot_cursor[4] = (s32)slot;
        }
        slot_index++;
        slot_cursor++;
    } while (slot_index < 0x10);

    func_80052A20();
}
