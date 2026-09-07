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

    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    group = group_index;
    ASM_KEEP_NV(group);   /* MATCH pin: retail schedule: same instructions, different order without it */
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
    ASM_KEEP_NV(lookup_flag);   /* MATCH pin: load-bearing for the whole function shape */

    {
        u8 *engine_page;
        u8 *data_page;
        Engine *engine;
        register u8 *dispatch_ptr ASM_REG("$2");   /* MATCH pin: retail callee-saved set / frame layout depends on it */

        engine_page = (u8 *)0x80010000;
        ASM_KEEP(engine_page);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        engine = *(Engine **)(engine_page + 0x6000);
        dispatch_ptr = engine->items;
        ASM_KEEP_NV(dispatch_ptr);   /* MATCH pin: retail schedule: same instructions, different order without it */
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        dispatch_ptr += group;
        current_index = dispatch_ptr[0x3700];
        ASM_KEEP_NV(current_index);   /* MATCH pin: retail schedule: same instructions, different order without it */
        entries = lookup->entries;
        ASM_KEEP_NV(entries);   /* MATCH pin: retail schedule: same instructions, different order without it */
        dispatch_ptr = (u8 *)engine->callbacks;
        ASM_KEEP_NV(dispatch_ptr);   /* MATCH pin: retail schedule: same instructions, different order without it */
        dispatch_ptr = (u8 *)((CallbackBlock *)dispatch_ptr)->callback;
        ASM_KEEP_NV(dispatch_ptr);   /* MATCH pin: retail schedule: same instructions, different order without it */
        data_page = (u8 *)0x80020000;
        ASM_KEEP(data_page);   /* MATCH pin: keeps a statement from moving across a call/branch */
        ((Callback)dispatch_ptr)(data_page - 0x6E94, D_80019178, entry_index, group);
        ASM_KEEP(data_page);   /* MATCH pin: keeps a statement from moving across a call/branch */

        dispatch_ptr = *(u8 **)(engine_page + 0x6000);
        dispatch_ptr = (u8 *)((Engine *)dispatch_ptr)->callbacks;
        ASM_KEEP_NV(dispatch_ptr);   /* MATCH pin: retail schedule: same instructions, different order without it */
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        dispatch_ptr = (u8 *)((CallbackBlock *)dispatch_ptr)->callback;
        ASM_KEEP_NV(dispatch_ptr);   /* MATCH pin: retail schedule: same instructions, different order without it */
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
        register u8 *dispatch_ptr ASM_REG("$2");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        u8 *callback_context;
        u8 *format_page;
        s32 entry_value;

        engine_page = (u8 *)0x80010000;
        ASM_KEEP(engine_page);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        dispatch_ptr = *(u8 **)(engine_page + 0x6000);
        dispatch_ptr = (u8 *)((Engine *)dispatch_ptr)->callbacks;
        ASM_KEEP_NV(dispatch_ptr);   /* MATCH pin: retail schedule: same instructions, different order without it */
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        dispatch_ptr = (u8 *)((CallbackBlock *)dispatch_ptr)->callback;
        ASM_KEEP_NV(dispatch_ptr);   /* MATCH pin: retail schedule: same instructions, different order without it */
        data_page = (u8 *)0x80020000;
        ASM_KEEP(data_page);   /* MATCH pin: keeps a statement from moving across a call/branch */
        ((Callback)dispatch_ptr)(data_page - 0x6E94, D_80019178, entry_index);
        ASM_KEEP(data_page);   /* MATCH pin: keeps a statement from moving across a call/branch */

        dispatch_ptr = *(u8 **)(engine_page + 0x6000);
        ASM_KEEP_NV(dispatch_ptr);   /* MATCH pin: retail schedule: same instructions, different order without it */
        dispatch_ptr = (u8 *)((Engine *)dispatch_ptr)->callbacks;
        ASM_KEEP_NV(dispatch_ptr);   /* MATCH pin: retail schedule: same instructions, different order without it */
        entry = (Entry *)(entry_index << 3);
        entry = (Entry *)((s32)entry + (s32)entries);
        ASM_KEEP(entry);   /* MATCH pin: load-bearing for the whole function shape */
        dispatch_ptr = (u8 *)((CallbackBlock *)dispatch_ptr)->callback;
        ASM_KEEP_NV(dispatch_ptr);   /* MATCH pin: retail schedule: same instructions, different order without it */
        callback_context = data_page - 0x6E94;
        ASM_KEEP_NV(callback_context);   /* MATCH pin: load-bearing for the whole function shape */
        format_page = (u8 *)0x80020000;
        ASM_KEEP_NV(format_page);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        entry_value = entry->first;
        ((Callback)dispatch_ptr)(callback_context, format_page - 0x6E7C, entry_value);

        dispatch_ptr = *(u8 **)(engine_page + 0x6000);
        dispatch_ptr = (u8 *)((Engine *)dispatch_ptr)->callbacks;
        ASM_KEEP_NV(dispatch_ptr);   /* MATCH pin: retail schedule: same instructions, different order without it */
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        dispatch_ptr = (u8 *)((CallbackBlock *)dispatch_ptr)->callback;
        ASM_KEEP_NV(dispatch_ptr);   /* MATCH pin: retail schedule: same instructions, different order without it */
        callback_context = data_page - 0x6E94;
        ASM_KEEP_NV(callback_context);   /* MATCH pin: load-bearing for the whole function shape */
        format_page = (u8 *)0x80020000;
        ASM_KEEP_NV(format_page);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        entry_value = entry->second;
        ((Callback)dispatch_ptr)(callback_context, format_page - 0x6E70, entry_value);
        return entry;
    }
}
