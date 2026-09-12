#include "common.h"

typedef void (*Callback)();

typedef struct {
    u8 pad_00[0x168];
    Callback callback;
} CallbackBlock;

typedef struct {
    u8 pad_00[0x20];
    CallbackBlock *callbacks;
    u8 pad_24[0x14];
    u8 *items;
} Engine;

typedef struct {
    s16 flag;
    s16 unused;
    void *entries;
} Lookup;

typedef struct {
    s16 first;
    s16 second;
    s32 unused;
} Entry;

extern s8 D_80016000[];
extern Lookup D_8001902C[];
extern s32 D_8001916C[];
extern s32 D_80019178[];
extern s32 *D_8001917C;
extern s32 D_80019184[];
extern s32 D_80019190[];

/* Select a vertex relative to the list head, print its coordinates, and return its address. */
void *func_8001D280(s32 group_index, s32 requested_index, s32 lookup_variant) {
    s32 n;
    s32 lookup_flag;
    s32 head;
    void *ptr;
    s32 group;
    Lookup *lookup;
    s32 delta;

    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    group = group_index;
    ASM_KEEP_NV(group);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    if (group >= 10) {
        return 0;
    }
    n = requested_index;

    {
        Lookup *lookup_base;
        s32 lookup_offset;

        lookup_base = D_8001902C;
        lookup_offset = (group * 3 + lookup_variant) * 8;
        lookup_offset = lookup_offset + (s32)lookup_base;
        lookup = (Lookup *)lookup_offset;
    }
    do {
        lookup_flag = lookup->flag;
    } while (0);

    {
        u8 *data_page;
        Engine *engine;
        register u8 *dispatch_ptr ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

        engine = *(Engine **)((u8 *)D_80016000);
        dispatch_ptr = engine->items;
        dispatch_ptr += group;
        head = dispatch_ptr[0x3700];
        do {
            ptr = lookup->entries;
        } while (0);
        dispatch_ptr = (u8 *)engine->callbacks;
        do {
            dispatch_ptr = (u8 *)((CallbackBlock *)dispatch_ptr)->callback;
        } while (0);
        data_page = (u8 *)0x80020000;
        ASM_KEEP(data_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ((Callback)dispatch_ptr)(data_page - 0x6E94, D_80019178, n, group);
        ASM_KEEP(data_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

        dispatch_ptr = *(u8 **)((u8 *)D_80016000);
        dispatch_ptr = (u8 *)((Engine *)dispatch_ptr)->callbacks;
           /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
           /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        dispatch_ptr = (u8 *)((CallbackBlock *)dispatch_ptr)->callback;
        do {
            ((Callback)dispatch_ptr)(data_page - 0x6E94, &D_8001917C, head);
        } while (0);
    }

    delta = n - head;
    if (lookup_flag == 0) {
        goto common;
    }
    if (delta < 0) {
        goto negative;
    }
    delta += 1;
    n = lookup_flag - delta;
    goto common;
negative:
    n = head - n;
    n -= 1;
common:

    {
        u8 *data_page;
        Entry *vertex;
        u8 *dispatch_ptr;
        u8 *callback_context;
        u8 *format_page;
        s32 coordinate;

        dispatch_ptr = *(u8 **)((u8 *)D_80016000);
        dispatch_ptr = (u8 *)((Engine *)dispatch_ptr)->callbacks;
        do {
            dispatch_ptr = (u8 *)((CallbackBlock *)dispatch_ptr)->callback;
        } while (0);
        data_page = (u8 *)0x80020000;
        ASM_KEEP(data_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ((Callback)dispatch_ptr)(data_page - 0x6E94, D_80019178, n);
        ASM_KEEP(data_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

        dispatch_ptr = *(u8 **)((u8 *)D_80016000);
        ASM_KEEP_NV(dispatch_ptr);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        dispatch_ptr = (u8 *)((Engine *)dispatch_ptr)->callbacks;
        ASM_KEEP_NV(dispatch_ptr);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        vertex = (Entry *)(n << 3);
        vertex = (Entry *)((s32)vertex + (s32)ptr);
        ASM_KEEP(vertex);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        do {
            dispatch_ptr = (u8 *)((CallbackBlock *)dispatch_ptr)->callback;
        } while (0);
        callback_context = data_page - 0x6E94;
        ASM_KEEP_NV(callback_context);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        format_page = (u8 *)0x80020000;
        ASM_KEEP_NV(format_page);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        coordinate = vertex->first;
        ((Callback)dispatch_ptr)(callback_context, format_page - 0x6E7C, coordinate);

        dispatch_ptr = *(u8 **)((u8 *)D_80016000);
        dispatch_ptr = (u8 *)((Engine *)dispatch_ptr)->callbacks;
           /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
           /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        do {
            dispatch_ptr = (u8 *)((CallbackBlock *)dispatch_ptr)->callback;
        } while (0);
        callback_context = data_page - 0x6E94;
        ASM_KEEP_NV(callback_context);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        format_page = (u8 *)0x80020000;
        ASM_KEEP_NV(format_page);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        coordinate = vertex->second;
        ((Callback)dispatch_ptr)(callback_context, format_page - 0x6E70, coordinate);
        return vertex;
    }
}
