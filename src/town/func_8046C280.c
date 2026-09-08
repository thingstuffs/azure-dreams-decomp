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

/* Select a lookup entry relative to the current index and report its values through the engine callback. */
void *func_8001D280(s32 group_index, s32 requested_index, s32 lookup_variant) {
    s32 entry_index;
    s32 lookup_flag;
    s32 current_index;
    void *entries;
    s32 group;
    Lookup *lookup;
    s32 delta;

    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    group = group_index;
    ASM_KEEP_NV(group);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    if (group >= 10) {
        return 0;
    }
    entry_index = requested_index;

    {
        Lookup *lookup_base;
        s32 lookup_offset;

        lookup_base = D_8001902C;
        lookup_offset = (group * 3 + lookup_variant) * 8;
        lookup_offset = lookup_offset + (s32)lookup_base;
        lookup = (Lookup *)lookup_offset;
    }
    lookup_flag = lookup->flag;
    ASM_KEEP_NV(lookup_flag);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    {
        u8 *engine_page;
        u8 *data_page;
        Engine *engine;
        register u8 *dispatch_ptr ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

        engine_page = (u8 *)0x80010000;
        ASM_KEEP(engine_page);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        engine = *(Engine **)(engine_page + 0x6000);
        dispatch_ptr = engine->items;
        ASM_KEEP_NV(dispatch_ptr);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        dispatch_ptr += group;
        current_index = dispatch_ptr[0x3700];
        ASM_KEEP_NV(current_index);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        entries = lookup->entries;
        ASM_KEEP_NV(entries);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        dispatch_ptr = (u8 *)engine->callbacks;
        ASM_KEEP_NV(dispatch_ptr);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        dispatch_ptr = (u8 *)((CallbackBlock *)dispatch_ptr)->callback;
        ASM_KEEP_NV(dispatch_ptr);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        data_page = (u8 *)0x80020000;
        ASM_KEEP(data_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ((Callback)dispatch_ptr)(data_page - 0x6E94, D_80019178, entry_index, group);
        ASM_KEEP(data_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

        dispatch_ptr = *(u8 **)(engine_page + 0x6000);
        dispatch_ptr = (u8 *)((Engine *)dispatch_ptr)->callbacks;
        ASM_KEEP_NV(dispatch_ptr);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        dispatch_ptr = (u8 *)((CallbackBlock *)dispatch_ptr)->callback;
        ASM_KEEP_NV(dispatch_ptr);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ((Callback)dispatch_ptr)(data_page - 0x6E94, &D_8001917C, current_index);
    }

    delta = entry_index - current_index;
    if (lookup_flag == 0) {
        goto common;
    }
    if (delta < 0) {
        goto negative;
    }
    delta += 1;
    entry_index = lookup_flag - delta;
    goto common;
negative:
    entry_index = current_index - entry_index;
    entry_index -= 1;
common:

    {
        u8 *engine_page;
        u8 *data_page;
        Entry *entry;
        register u8 *dispatch_ptr ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        u8 *callback_context;
        u8 *format_page;
        s32 entry_value;

        engine_page = (u8 *)0x80010000;
        ASM_KEEP(engine_page);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        dispatch_ptr = *(u8 **)(engine_page + 0x6000);
        dispatch_ptr = (u8 *)((Engine *)dispatch_ptr)->callbacks;
        ASM_KEEP_NV(dispatch_ptr);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        dispatch_ptr = (u8 *)((CallbackBlock *)dispatch_ptr)->callback;
        ASM_KEEP_NV(dispatch_ptr);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        data_page = (u8 *)0x80020000;
        ASM_KEEP(data_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ((Callback)dispatch_ptr)(data_page - 0x6E94, D_80019178, entry_index);
        ASM_KEEP(data_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

        dispatch_ptr = *(u8 **)(engine_page + 0x6000);
        ASM_KEEP_NV(dispatch_ptr);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        dispatch_ptr = (u8 *)((Engine *)dispatch_ptr)->callbacks;
        ASM_KEEP_NV(dispatch_ptr);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        entry = (Entry *)(entry_index << 3);
        entry = (Entry *)((s32)entry + (s32)entries);
        ASM_KEEP(entry);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        dispatch_ptr = (u8 *)((CallbackBlock *)dispatch_ptr)->callback;
        ASM_KEEP_NV(dispatch_ptr);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        callback_context = data_page - 0x6E94;
        ASM_KEEP_NV(callback_context);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        format_page = (u8 *)0x80020000;
        ASM_KEEP_NV(format_page);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        entry_value = entry->first;
        ((Callback)dispatch_ptr)(callback_context, format_page - 0x6E7C, entry_value);

        dispatch_ptr = *(u8 **)(engine_page + 0x6000);
        dispatch_ptr = (u8 *)((Engine *)dispatch_ptr)->callbacks;
        ASM_KEEP_NV(dispatch_ptr);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        dispatch_ptr = (u8 *)((CallbackBlock *)dispatch_ptr)->callback;
        ASM_KEEP_NV(dispatch_ptr);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        callback_context = data_page - 0x6E94;
        ASM_KEEP_NV(callback_context);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        format_page = (u8 *)0x80020000;
        ASM_KEEP_NV(format_page);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        entry_value = entry->second;
        ((Callback)dispatch_ptr)(callback_context, format_page - 0x6E70, entry_value);
        return entry;
    }
}
