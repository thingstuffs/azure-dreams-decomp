#include "common.h"
#include "records/Rec_func_801237A4_arg0.h"


typedef struct S_80125DDC_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80125DDC_1;   /* entry in func_80125DDC */

typedef struct S_80125DDC_2 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80125DDC_2;   /* inner in func_80125DDC */



extern void func_801235EC(void);
extern void func_801247F8(void *);
extern void *D_8011AD08[];
extern s8 D_80129728;

void func_80125DDC(Rec_func_801237A4_arg0 *arg0)
{
    static void *const sw_keep[20] = {
        &&case_0,
        &&done, &&done, &&done, &&done, &&done, &&done,
        &&case_789, &&case_789, &&case_789,
        &&case_10,
        &&case_111213, &&case_111213, &&case_111213,
        &&case_14,
        &&done, &&done, &&done, &&done, &&done
    };
    s32 swi;

    swi = (s16)(arg0->unk_04.as_u16 - 1);
    if ((u32)swi >= 20) {
        goto done;
    }
    (void)sw_keep;
    goto *D_8011AD08[swi];

case_0:
    func_801235EC();
    func_801247F8(arg0);
    goto done;

case_789:
    {
        s32 count;
        u8 *base;
        void **cursor;
        void *entry;
        void *inner;
        u16 value;

        count = 0x1C;
        base = (u8 *)&D_80129728;
        cursor = (void **)(base + 0x70);
        ASM_KEEP(count);   /* MATCH pin: retail register colouring depends on it */
        do {
            entry = *cursor;
            inner = ((S_80125DDC_1 *)entry)->unk_08;
            value = ((S_80125DDC_2 *)inner)->unk_02;
            ASM_KEEP(value);   /* MATCH pin: retail schedule: same instructions, different order without it */
            count++;
            value += 0x100;
            ((S_80125DDC_2 *)inner)->unk_02 = value;
            cursor = (void **)((u8 *)cursor + 4);
        } while (count < 0x62);
    }
    goto done;

case_10:
    {
        s32 count;
        u8 *base;
        s32 **cursor;
        s32 *entry;

        count = 0x1E;
        base = (u8 *)&D_80129728;
        cursor = (s32 **)(base + 0x78);
        do {
            entry = *cursor;
            ASM_KEEP(entry);   /* MATCH pin: keeps a statement from moving across a call/branch */
            count++;
            *entry = 0;
            cursor = (s32 **)((u8 *)cursor + 4);
        } while (count < 0x62);
    }

case_111213:
    {
        s32 count;
        u8 *base;
        void **cursor;
        void *entry;
        void *inner;
        u16 value;

        count = 0x1C;
        base = (u8 *)&D_80129728;
        cursor = (void **)(base + 0x70);
        ASM_KEEP(count);   /* MATCH pin: retail register colouring depends on it */
        do {
            entry = *cursor;
            inner = ((S_80125DDC_1 *)entry)->unk_08;
            value = ((S_80125DDC_2 *)inner)->unk_02;
            ASM_KEEP(value);   /* MATCH pin: retail schedule: same instructions, different order without it */
            count++;
            value += 0x100;
            ((S_80125DDC_2 *)inner)->unk_02 = value;
            cursor = (void **)((u8 *)cursor + 4);
        } while (count < 0x62);
    }
    goto done;

case_14:
    {
        s32 count;
        u8 *base;
        void **cursor;
        void *entry;
        void *inner;
        u16 value;

        count = 0x1C;
        base = (u8 *)&D_80129728;
        cursor = (void **)(base + 0x70);
        ASM_KEEP(count);   /* MATCH pin: retail register colouring depends on it */
        do {
            entry = *cursor;
            inner = ((S_80125DDC_1 *)entry)->unk_08;
            value = ((S_80125DDC_2 *)inner)->unk_02;
            ASM_KEEP(value);   /* MATCH pin: retail schedule: same instructions, different order without it */
            count++;
            value += 0x100;
            ((S_80125DDC_2 *)inner)->unk_02 = value;
            cursor = (void **)((u8 *)cursor + 4);
        } while (count < 0x62);
    }
    {
        s32 count;
        u8 *base;
        s32 **cursor;
        s32 *entry;

        count = 0x1C;
        base = (u8 *)&D_80129728;
        cursor = (s32 **)(base + 0x70);
        do {
            entry = *cursor;
            ASM_KEEP(entry);   /* MATCH pin: keeps a statement from moving across a call/branch */
            count++;
            *entry = 0;
            cursor = (s32 **)((u8 *)cursor + 4);
        } while (count < 0x1E);
    }

done:
    return;
}

/* MECHANISM: The true-space CFG uses the external 20-entry dispatch table and a local epilogue.
   Short-lived D_80129728 bases plus an a0 count pin reproduce each loop's address/register roles.
   ASM_KEEP on loaded values lets count++ fill every lhu/lw delay; the natural frame is 0x18 with s0/ra. */
