#include "common.h"
#include "shared/record_ptrs.h"

extern s32 func_800422A8(void *, void *, s32, s32);
extern s32 func_80098FB0(void);
extern s32 func_80098FF8(void);
extern void *func_800990FC(void);
extern s32 func_80099194(u8 *src, u8 *dst);
extern void func_80099290(s8 *byte_ptr);
extern s32 func_8009929C(s8 value, s8 *dest);
extern s32 func_80099368(void *, s32);
extern s32 func_8009955C(void *, s32);
extern void func_8009A3D0(u8, u8, s32);
extern void func_800A56E0(s32);
extern void func_800A5720(s8 *text);

extern u8 D_80081470[];
extern void *D_80081484;
extern u8 D_800E07EF[];
extern u8 D_800E3548[];
extern u8 D_800E36C8[];

void *func_80097F84(void *arg0, void *arg1, void *arg2, s16 arg3)
{
    s16 held_arg3 = arg3;
    s32 first;
    s32 second;
    s32 index;
    void *object;
    s32 found;
    s32 narrowed;
    u32 flags;
    u8 *entry;
    u8 *entry_base;
    s32 entry_base_s;
    void *global_object;

    if (arg0 == (void *)&D_80081484 ||
        arg0 == (void *)D_80081470 ||
        arg0 == *(void **)((u8 *)D_800814A8 + 0xF0)) {
    first = func_80098FB0();
    second = func_80098FF8();
    index = (s16)first;

    if (index < 0 || (s16)second < 0) {
        object = func_800990FC();
        func_80099290(func_80099194(arg2,
            func_8009955C(arg0,
                func_80099194(arg1, func_8009929C(8, object)))));
        func_800A5720(object);
        return 0;
    }

    object = func_800990FC();
    func_80099290(func_80099194(D_800E07EF,
        func_80099368(arg0, object)));
    if (held_arg3 != 0) {
        func_800A5720(object);
    }
    func_800A56E0(0x508);

    if (arg0 == (void *)&D_80081484) {
        do {
            ((void **)0x80010248)[index] = D_80081484;
        } while (0);
        global_object = D_800814A8;
        flags = *(u32 *)((u8 *)global_object + 0x1C);
        D_80081484 = 0;
        *(s32 *)((u8 *)global_object + 0x124) = 0;
        *(u32 *)((u8 *)global_object + 0x1C) = flags & 0xFFEFFFFF;
    } else {

        found = (s16)func_800422A8(*(void **)(((u8 *)D_800E3D7C) + 0xF0),
                                 D_800E3548, 4, 0x40);
        if (found >= 0) {
            entry_base_s = (s32)D_800E36C8;
            entry = (u8 *)(found * 12);
            entry += entry_base_s;
            func_8009A3D0(entry[0], entry[1], 0x800);
            ((void **)0x80010248)[index] = *(void **)D_80081470;
        } else {
            ((void **)0x80010248)[index] = *(void **)D_80081470;
        }
        *(s32 *)*(void **)((u8 *)D_800814A8 + 0xF0) = 0;
    }
    entry_base = (u8 *)0x80010248;
    narrowed = first << 16;
    narrowed >>= 14;
    narrowed += (s32)entry_base;
    ASM_KEEP(narrowed);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    *(s32 *)arg0 = 0;
    arg0 = (void *)narrowed;
    entry_base = (u8 *)0x80010000;
    narrowed = second << 16;
    narrowed >>= 14;
    narrowed += (s32)entry_base;
    *(void **)(narrowed + 0x29c) = arg0;
    }
    return arg0;
}
