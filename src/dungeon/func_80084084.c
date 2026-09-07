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
extern void func_80089A74();

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
        register Callback *firstCallback ASM_REG("$16");   /* MATCH pin: retail register colouring depends on it */
        register Callback *firstBase;
        register Callback *firstSpecial;
        u8 *firstPage;
        Callback *firstScan;
        register Callback fn ASM_REG("$7");   /* MATCH pin: retail delay-slot contents depend on it */
        register Entry **firstEntryp;
        register Entry *entry ASM_REG("$17");   /* MATCH pin: retail callee-saved set / frame layout depends on it */

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
                    register Callback *p ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */

                    firstPage = (u8 *)0x800E0000;
                    ASM_KEEP(firstPage);   /* MATCH pin: keeps a statement from moving across a call/branch */
                    firstScan = (Callback *)(firstPage - 0x3080);
                    p = firstSpecial;
                    ASM_KEEP(firstScan);   /* MATCH pin: retail keeps a computation the compiler would drop */
                    ASM_KEEP(p);   /* MATCH pin: load-bearing for the whole function shape */
                    if (*p == fn) {
                        ASM_KEEP(fn);   /* MATCH pin: retail register colouring depends on it */
                        fn(entry->data, entry->arg1, entry->arg2);
                        ASM_KEEP(firstSpecial);   /* MATCH pin: retail register colouring depends on it */
                        ASM_KEEP(firstBase);   /* MATCH pin: retail register colouring depends on it */
                        ASM_KEEP(firstEntryp);   /* MATCH pin: retail register colouring depends on it */
                        firstCallback++;
                        ASM_TAILSLOT_PIN(firstCallback);   /* MATCH pin: retail delay-slot contents depend on it */
                        func_800898BC();
                        return;
                    }
                    if (*firstScan != 0) {
                        firstScan++;
                        ASM_KEEP(firstScan);   /* MATCH pin: retail keeps a computation the compiler would drop */
                        p++;
                        ASM_TAILSLOT_PIN(p);   /* MATCH pin: retail delay-slot contents depend on it */
                        func_80089874();
                        return;
                    }
                }
            } else {
                ASM_CLOBBER("$17");   /* MATCH pin: retail register colouring depends on it */
                *firstCallback = 0;
            }
        }
        firstCallback++;
        firstEntryp++;
        if ((s32)firstCallback < (s32)(firstBase + 0x20)) {
            goto loop_first;
        }
        func_80089A74();
        return;
    }

    if (*(s32 *)((u8 *)D_800814A8 + 0x1C) & 0x10) {
        register Callback *secondCallback ASM_REG("$18");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        register Callback *secondBase;
        register Callback *secondSpecial ASM_REG("$22");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        register u8 *secondPage ASM_REG("$21");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        Callback *secondScan;
        register Callback fn ASM_REG("$7");   /* MATCH pin: retail delay-slot contents depend on it */
        register Callback specialFn ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        register Entry **secondEntryp;
        register Entry *entry;
        void *specialArg0;
        s32 specialArg1;
        s32 specialArg2;
        s32 saved;

        secondPage = (u8 *)0x800E0000;
        ASM_KEEP(secondPage);   /* MATCH pin: retail basic-block layout depends on it */
        secondSpecial = (Callback *)(secondPage - 0x3080);
           /* MATCH pin: retail schedule: same instructions, different order without it */
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
                        ASM_KEEP(saved);   /* MATCH pin: retail schedule: same instructions, different order without it */
                        entry->saved = 0;
                        fn(specialArg0, specialArg1, specialArg2);
                        ASM_KEEP(secondBase);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
                        ASM_KEEP(secondEntryp);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
                        entry->saved = saved;
                        func_800899C0();
                        return;
                    }
                    goto second_next;
second_scan_equal:
                    ASM_KEEP(fn);   /* MATCH pin: retail register colouring depends on it */
                    fn(entry->data, entry->arg1, entry->arg2);
                    secondCallback++;
                    ASM_TAILSLOT_PIN(secondCallback);   /* MATCH pin: retail delay-slot contents depend on it */
                    func_800899C4();
                    return;
second_scan_check:
                    ASM_KEEP(secondScan);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                    if (*secondScan == fn) {
                        goto second_scan_equal;
                    }
                    if (*secondScan == 0) {
                        goto second_next;
                    }
                    secondScan++;
                    ASM_KEEP(secondScan);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
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
        func_80089A74();
        return;
    }

    {
        Callback *thirdCallback;
        register Callback fn ASM_REG("$7");   /* MATCH pin: retail delay-slot contents depend on it */
        register Entry **thirdEntryp ASM_REG("$18");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        register Entry *entry ASM_REG("$17");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        register s32 i ASM_REG("$19");   /* MATCH pin: retail register colouring depends on it */
        register u8 *thirdPage ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        s32 result;

    i = 0;
    thirdPage = (u8 *)0x80080000;
    ASM_KEEP(thirdPage);   /* MATCH pin: load-bearing for the whole function shape */
    thirdCallback = (Callback *)(thirdPage + 0x3360);
    thirdPage = (u8 *)0x80080000;
    ASM_KEEP(thirdPage);   /* MATCH pin: load-bearing for the whole function shape */
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
                ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                thirdCallback++;
                if (result == 0) {
                    i++;
                    ASM_TAILSLOT_PIN(i);   /* MATCH pin: retail delay-slot contents depend on it */
                    func_80089A68();
                    return;
                }
                goto third_done;
            }
        } else {
            ASM_CLOBBER("$17");   /* MATCH pin: retail register colouring depends on it */
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
    ASM_USE(thirdCallback);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    }
}
