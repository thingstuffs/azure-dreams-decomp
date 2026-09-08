#include "common.h"

typedef s32 (*Callback)(void *, s32, s32);

typedef struct Entry {
    u8 pad0[8];
    s32 arg1;
    s32 arg2;
    s32 unk10;
    s32 active;
    s32 saved;
    u16 unk1C;
    u16 flags;
    u8 data[1];
} Entry;

extern s32 func_80045310(s32);
extern void func_80089874();
extern void func_800898BC();
extern void func_8008999C();
extern void func_800899C0();
extern void func_800899C4();
extern void func_80089A68();

extern void *D_800814A8;
extern void *D_80083160[];
extern Callback D_80083360[0x20];
extern Entry *D_800833E0[0x20];
extern Entry D_80083498;
extern Callback D_800DCF80[];
extern Callback D_800DCFA4;
extern s32 D_800E296C;

void func_800897E4(void)
{
    if (D_800E296C & 0x02000000) {
        register Callback *firstCallback ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register Callback *firstBase;
        register Callback *firstSpecial;
        u8 *firstPage;
        Callback *firstScan;
        register Callback fn ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        register Entry **firstEntryp;
        register Entry *entry ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

        firstSpecial = D_800DCF80 + 9;
        firstBase = D_80083360;
        firstCallback = firstBase;
        firstEntryp = D_800833E0;
loop_first:
        fn = *firstCallback;
        if (fn != 0) {
            entry = *firstEntryp;
            if (entry != 0) {
                if (!(entry->flags & 0x800)) {
                    register Callback *p ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

                    firstPage = (u8 *)0x800E0000;
                    ASM_KEEP(firstPage);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                    firstScan = (Callback *)(firstPage - 0x3080);
                    p = firstSpecial;
                    ASM_KEEP(firstScan);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                    ASM_KEEP(p);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    if (*p == fn) {
                        ASM_KEEP(fn);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                        fn(entry->data, entry->arg1, entry->arg2);
                        ASM_KEEP(firstSpecial);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                        ASM_KEEP(firstBase);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                        ASM_KEEP(firstEntryp);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                        firstCallback++;
                        ASM_TAILSLOT_PIN(firstCallback);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
                        func_800898BC();
                        return;
                    }
                    if (*firstScan != 0) {
                        firstScan++;
                        ASM_KEEP(firstScan);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                        p++;
                        ASM_TAILSLOT_PIN(p);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
                        func_80089874();
                        return;
                    }
                }
            } else {
                ASM_CLOBBER("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                *firstCallback = 0;
            }
        }
        firstCallback++;
        firstEntryp++;
        if ((s32)firstCallback < (s32)(firstBase + 0x20)) {
            goto loop_first;
        }
        return;
    }

    if (*(s32 *)((u8 *)D_800814A8 + 0x1C) & 0x10) {
        register Callback *secondCallback ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        register Callback *secondBase;
        register Callback *secondSpecial ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        register u8 *secondPage ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        Callback *secondScan;
        register Callback fn ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        register Callback specialFn ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register Entry **secondEntryp;
        register Entry *entry;
        void *specialArg0;
        s32 specialArg1;
        s32 specialArg2;
        s32 saved;

        secondPage = (u8 *)0x800E0000;
        ASM_KEEP(secondPage);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        secondSpecial = (Callback *)(secondPage - 0x3080);
           /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        secondBase = D_80083360;
        secondCallback = secondBase;
        secondEntryp = D_800833E0;
loop_second:
        fn = *secondCallback;
        if (fn != 0) {
            entry = *secondEntryp;
            if (entry != 0) {
                if (!(entry->flags & 0x800)) {
                    specialFn = *(Callback *)(secondPage - 0x3080);
                    secondScan = secondSpecial + 1;
                    if (specialFn != fn) {
                        goto second_scan_check;
                    }
                    entry = &D_80083498;
                    if (entry->active != 0) {
                        specialArg0 = entry->data;
                        specialArg1 = entry->arg1;
                        specialArg2 = entry->arg2;
                        saved = entry->saved;
                        ASM_KEEP(saved);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                        entry->saved = 0;
                        fn(specialArg0, specialArg1, specialArg2);
                        ASM_KEEP(secondBase);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
                        ASM_KEEP(secondEntryp);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
                        entry->saved = saved;
                        func_800899C0();
                        return;
                    }
                    goto second_next;
second_scan_equal:
                    ASM_KEEP(fn);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    fn(entry->data, entry->arg1, entry->arg2);
                    secondCallback++;
                    ASM_TAILSLOT_PIN(secondCallback);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
                    func_800899C4();
                    return;
second_scan_check:
                    ASM_KEEP(secondScan);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                    if (*secondScan == fn) {
                        goto second_scan_equal;
                    }
                    if (*secondScan == 0) {
                        goto second_next;
                    }
                    secondScan++;
                    ASM_KEEP(secondScan);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                    func_8008999C();
                    return;
                }
            } else {
                *secondCallback = 0;
            }
        }
second_next:
        secondCallback++;
        secondEntryp++;
        if ((s32)secondCallback < (s32)(secondBase + 0x20)) {
            goto loop_second;
        }
        return;
    }

    {
        Callback *thirdCallback;
        register Callback fn ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        register Entry **thirdEntryp ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        register Entry *entry ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        register s32 i ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register u8 *thirdPage ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s32 result;

    i = 0;
    thirdPage = (u8 *)0x80080000;
    ASM_KEEP(thirdPage);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    thirdCallback = (Callback *)(thirdPage + 0x3360);
    thirdPage = (u8 *)0x80080000;
    ASM_KEEP(thirdPage);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    thirdEntryp = (Entry **)(thirdPage + 0x33E0);
loop_third:
    fn = *thirdCallback;
    if (fn != 0) {
        entry = *thirdEntryp;
        if (entry != 0) {
            if (!(entry->flags & 0x800)) {
                fn(entry->data, entry->arg1, entry->arg2);
                result = func_80045310(
                    *(s32 *)((u8 *)D_80083160[0] + 0x8D0));
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                thirdCallback++;
                if (result == 0) {
                    i++;
                    ASM_TAILSLOT_PIN(i);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
                    func_80089A68();
                    return;
                }
                goto third_done;
            }
        } else {
            ASM_CLOBBER("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            *thirdCallback = 0;
        }
    }
    thirdCallback++;
    i++;
    thirdEntryp++;
    if (i < 0x20) {
        goto loop_third;
    }
third_done:
    ASM_USE(thirdCallback);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    }
}
