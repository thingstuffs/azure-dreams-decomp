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

void *func_8001D280(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_s3;
    s32 flag;
    s32 item;
    void *entries;
    s32 work_arg0;
    Lookup *lookup;
    s32 delta;

    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    work_arg0 = arg0;
    ASM_KEEP_NV(work_arg0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    if (work_arg0 >= 10) {
        return 0;
    }
    var_s3 = arg1;

    {
        Lookup *lookup_base;
        s32 lookup_offset;

        lookup_base = D_8001902C;
        lookup_offset = (work_arg0 * 3 + arg2) * 8;
        lookup_offset = lookup_offset + (s32)lookup_base;
        lookup = (Lookup *)lookup_offset;
    }
    flag = lookup->flag;
    ASM_KEEP_NV(flag);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    {
        u8 *engine_page;
        u8 *data_page;
        Engine *engine_a0;
        register u8 *temp_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

        engine_page = (u8 *)0x80010000;
        ASM_KEEP(engine_page);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        engine_a0 = *(Engine **)(engine_page + 0x6000);
        temp_v0 = engine_a0->items;
        ASM_KEEP_NV(temp_v0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        temp_v0 += work_arg0;
        item = temp_v0[0x3700];
        ASM_KEEP_NV(item);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        entries = lookup->entries;
        ASM_KEEP_NV(entries);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        temp_v0 = (u8 *)engine_a0->callbacks;
        ASM_KEEP_NV(temp_v0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        temp_v0 = (u8 *)((CallbackBlock *)temp_v0)->callback;
        ASM_KEEP_NV(temp_v0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        data_page = (u8 *)0x80020000;
        ASM_KEEP(data_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ((Callback)temp_v0)(data_page - 0x6E94, D_80019178, var_s3, work_arg0);
        ASM_KEEP(data_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

        temp_v0 = *(u8 **)(engine_page + 0x6000);
        temp_v0 = (u8 *)((Engine *)temp_v0)->callbacks;
        ASM_KEEP_NV(temp_v0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        temp_v0 = (u8 *)((CallbackBlock *)temp_v0)->callback;
        ASM_KEEP_NV(temp_v0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ((Callback)temp_v0)(data_page - 0x6E94, &D_8001917C, item);
    }

    delta = var_s3 - item;
    if (flag == 0) {
        goto common;
    }
    if (delta < 0) {
        goto negative;
    }
    delta += 1;
    var_s3 = flag - delta;
    goto common;
negative:
    var_s3 = item - var_s3;
    var_s3 -= 1;
common:

    {
        u8 *engine_page;
        u8 *data_page;
        Entry *entry;
        register u8 *temp_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        u8 *call_a0;
        u8 *call_a1;
        s32 call_a2;

        engine_page = (u8 *)0x80010000;
        ASM_KEEP(engine_page);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        temp_v0 = *(u8 **)(engine_page + 0x6000);
        temp_v0 = (u8 *)((Engine *)temp_v0)->callbacks;
        ASM_KEEP_NV(temp_v0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        temp_v0 = (u8 *)((CallbackBlock *)temp_v0)->callback;
        ASM_KEEP_NV(temp_v0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        data_page = (u8 *)0x80020000;
        ASM_KEEP(data_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ((Callback)temp_v0)(data_page - 0x6E94, D_80019178, var_s3);
        ASM_KEEP(data_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

        temp_v0 = *(u8 **)(engine_page + 0x6000);
        ASM_KEEP_NV(temp_v0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        temp_v0 = (u8 *)((Engine *)temp_v0)->callbacks;
        ASM_KEEP_NV(temp_v0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        entry = (Entry *)(var_s3 << 3);
        entry = (Entry *)((s32)entry + (s32)entries);
        ASM_KEEP(entry);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        temp_v0 = (u8 *)((CallbackBlock *)temp_v0)->callback;
        ASM_KEEP_NV(temp_v0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        call_a0 = data_page - 0x6E94;
        ASM_KEEP_NV(call_a0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        call_a1 = (u8 *)0x80020000;
        ASM_KEEP_NV(call_a1);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        call_a2 = entry->first;
        ((Callback)temp_v0)(call_a0, call_a1 - 0x6E7C, call_a2);

        temp_v0 = *(u8 **)(engine_page + 0x6000);
        temp_v0 = (u8 *)((Engine *)temp_v0)->callbacks;
        ASM_KEEP_NV(temp_v0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        temp_v0 = (u8 *)((CallbackBlock *)temp_v0)->callback;
        ASM_KEEP_NV(temp_v0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        call_a0 = data_page - 0x6E94;
        ASM_KEEP_NV(call_a0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        call_a1 = (u8 *)0x80020000;
        ASM_KEEP_NV(call_a1);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        call_a2 = entry->second;
        ((Callback)temp_v0)(call_a0, call_a1 - 0x6E70, call_a2);
        return entry;
    }
}
