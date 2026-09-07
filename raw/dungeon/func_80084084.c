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
        register Callback *firstCallback ASM_REG("$16");
        register Callback *firstBase;
        register Callback *firstSpecial;
        register u8 *firstPage ASM_REG("$2");
        register Callback *firstScan ASM_REG("$4");
        register Callback fn ASM_REG("$7");
        register Entry **firstEntryp;
        register Entry *entry ASM_REG("$17");

        firstSpecial = D_800DCF80 + 9;
        firstBase = D_80083360;
        firstCallback = firstBase;
        firstEntryp = D_800833E0;
        ASM_KEEP(firstBase);
        ASM_KEEP(firstCallback);
        ASM_KEEP(firstEntryp);
loop_first:
        fn = *firstCallback;
        ASM_KEEP(fn);
        if (fn != 0) {
            entry = *firstEntryp;
            if (entry != 0) {
                if (!(entry->flags & 0x800)) {
                    register Callback *p ASM_REG("$3");

                    firstPage = (u8 *)0x800E0000;
                    ASM_KEEP(firstPage);
                    firstScan = (Callback *)(firstPage - 0x3080);
                    p = firstSpecial;
                    ASM_KEEP(firstScan);
                    ASM_KEEP(p);
                    if (*p == fn) {
                        ASM_KEEP(fn);
                        ASM_KEEP(firstCallback);
                        fn(entry->data, entry->arg1, entry->arg2);
                        ASM_KEEP(firstSpecial);
                        ASM_KEEP(firstBase);
                        ASM_KEEP(firstEntryp);
                        firstCallback++;
                        ASM_TAILSLOT_PIN(firstCallback);
                        func_800898BC();
                        return;
                    }
                    if (*firstScan != 0) {
                        firstScan++;
                        ASM_KEEP(firstScan);
                        p++;
                        ASM_TAILSLOT_PIN(p);
                        func_80089874();
                        return;
                    }
                }
            } else {
                ASM_CLOBBER("$17");
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
        register Callback *secondCallback ASM_REG("$18");
        register Callback *secondBase;
        register Callback *secondSpecial ASM_REG("$22");
        register u8 *secondPage ASM_REG("$21");
        register Callback *secondScan ASM_REG("$3");
        register Callback fn ASM_REG("$7");
        register Callback specialFn ASM_REG("$2");
        register Entry **secondEntryp;
        register Entry *entry;
        register void *specialArg0 ASM_REG("$4");
        register s32 specialArg1 ASM_REG("$5");
        register s32 specialArg2 ASM_REG("$6");
        register s32 saved ASM_REG("$16");

        secondPage = (u8 *)0x800E0000;
        ASM_KEEP(secondPage);
        secondSpecial = (Callback *)(secondPage - 0x3080);
        ASM_KEEP(secondSpecial);
        secondBase = D_80083360;
        secondCallback = secondBase;
        secondEntryp = D_800833E0;
        ASM_KEEP(secondBase);
        ASM_KEEP(secondCallback);
        ASM_KEEP(secondEntryp);
loop_second:
        fn = *secondCallback;
        ASM_KEEP(fn);
        if (fn != 0) {
            entry = *secondEntryp;
            ASM_KEEP(entry);
            if (entry != 0) {
                if (!(entry->flags & 0x800)) {
                    specialFn = *(Callback *)(secondPage - 0x3080);
                    ASM_KEEP(specialFn);
                    secondScan = secondSpecial + 1;
                    if (specialFn != fn) {
                        goto second_scan_check;
                    }
                    entry = &D_80083498;
                    if (entry->active != 0) {
                        specialArg0 = entry->data;
                        ASM_KEEP(specialArg0);
                        specialArg1 = entry->arg1;
                        ASM_KEEP(specialArg1);
                        specialArg2 = entry->arg2;
                        ASM_KEEP(specialArg2);
                        saved = entry->saved;
                        ASM_KEEP(saved);
                        entry->saved = 0;
                        fn(specialArg0, specialArg1, specialArg2);
                        ASM_KEEP(secondBase);
                        ASM_KEEP(secondEntryp);
                        entry->saved = saved;
                        func_800899C0();
                        return;
                    }
                    goto second_next;
second_scan_equal:
                    ASM_KEEP(fn);
                    ASM_KEEP(secondCallback);
                    fn(entry->data, entry->arg1, entry->arg2);
                    ASM_KEEP(secondBase);
                    ASM_KEEP(secondEntryp);
                    secondCallback++;
                    ASM_TAILSLOT_PIN(secondCallback);
                    func_800899C4();
                    return;
second_scan_check:
                    ASM_KEEP(secondScan);
                    if (*secondScan == fn) {
                        goto second_scan_equal;
                    }
                    if (*secondScan == 0) {
                        goto second_next;
                    }
                    secondScan++;
                    ASM_KEEP(secondScan);
                    func_8008999C();
                    return;
                }
            } else {
                *secondCallback = 0;
            }
        }
second_next:
        ASM_KEEP(secondCallback);
        secondCallback++;
        secondEntryp++;
        if ((s32)secondCallback < (s32)(secondBase + 0x20)) {
            goto loop_second;
        }
        func_80089A74();
        return;
    }

    {
        register Callback *thirdCallback ASM_REG("$16");
        register Callback fn ASM_REG("$7");
        register Entry **thirdEntryp ASM_REG("$18");
        register Entry *entry ASM_REG("$17");
        register s32 i ASM_REG("$19");
        register u8 *thirdPage ASM_REG("$2");
        s32 result;

    i = 0;
    thirdPage = (u8 *)0x80080000;
    ASM_KEEP(thirdPage);
    thirdCallback = (Callback *)(thirdPage + 0x3360);
    ASM_CLOBBER("$2");
    thirdPage = (u8 *)0x80080000;
    ASM_KEEP(thirdPage);
    thirdEntryp = (Entry **)(thirdPage + 0x33E0);
    ASM_KEEP(i);
    ASM_KEEP(thirdCallback);
    ASM_KEEP(thirdEntryp);
loop_third:
    fn = *thirdCallback;
    ASM_KEEP(fn);
    if (fn != 0) {
        entry = *thirdEntryp;
        ASM_KEEP(entry);
        if (entry != 0) {
            if (!(entry->flags & 0x800)) {
                ASM_KEEP(thirdCallback);
                fn(entry->data, entry->arg1, entry->arg2);
                result = func_80045310(
                    *(s32 *)((u8 *)D_80083160[0] + 0x8D0));
                ASM_SCHED_BARRIER();
                thirdCallback++;
                if (result == 0) {
                    i++;
                    ASM_TAILSLOT_PIN(i);
                    func_80089A68();
                    return;
                }
                goto third_done;
            }
        } else {
            ASM_CLOBBER("$17");
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
    ASM_USE(thirdCallback);
    }
}
