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
    register s32 work_arg0 ASM_REG("$7");
    Lookup *lookup;
    s32 delta;

    ASM_SCHED_BARRIER();
    work_arg0 = arg0;
    ASM_KEEP_NV(work_arg0);
    if (work_arg0 >= 10) {
        return 0;
    }
    var_s3 = arg1;

    {
        register Lookup *lookup_base ASM_REG("$2");
        register s32 lookup_offset ASM_REG("$3");

        lookup_base = D_8001902C;
        ASM_KEEP_NV(lookup_base);
        lookup_offset = (work_arg0 * 3 + arg2) * 8;
        ASM_KEEP_NV(lookup_offset);
        lookup_offset = lookup_offset + (s32)lookup_base;
        ASM_KEEP_NV(lookup_offset);
        lookup = (Lookup *)lookup_offset;
    }
    flag = lookup->flag;
    ASM_KEEP_NV(flag);

    {
        register u8 *engine_page ASM_REG("$17");
        register u8 *data_page ASM_REG("$16");
        register Engine *engine_a0 ASM_REG("$4");
        register u8 *temp_v0 ASM_REG("$2");

        engine_page = (u8 *)0x80010000;
        ASM_KEEP(engine_page);
        engine_a0 = *(Engine **)(engine_page + 0x6000);
        ASM_KEEP_NV(engine_a0);
        ASM_SCHED_BARRIER();
        temp_v0 = engine_a0->items;
        ASM_KEEP_NV(temp_v0);
        ASM_SCHED_BARRIER();
        temp_v0 += work_arg0;
        ASM_KEEP_NV(temp_v0);
        item = temp_v0[0x3700];
        ASM_KEEP_NV(item);
        entries = lookup->entries;
        ASM_KEEP_NV(entries);
        temp_v0 = (u8 *)engine_a0->callbacks;
        ASM_KEEP_NV(temp_v0);
        ASM_SCHED_BARRIER();
        temp_v0 = (u8 *)((CallbackBlock *)temp_v0)->callback;
        ASM_KEEP_NV(temp_v0);
        data_page = (u8 *)0x80020000;
        ASM_KEEP(data_page);
        ((Callback)temp_v0)(data_page - 0x6E94, D_80019178, var_s3, work_arg0);
        ASM_KEEP(data_page);

        temp_v0 = *(u8 **)(engine_page + 0x6000);
        ASM_KEEP_NV(temp_v0);
        ASM_SCHED_BARRIER();
        temp_v0 = (u8 *)((Engine *)temp_v0)->callbacks;
        ASM_KEEP_NV(temp_v0);
        ASM_SCHED_BARRIER();
        temp_v0 = (u8 *)((CallbackBlock *)temp_v0)->callback;
        ASM_KEEP_NV(temp_v0);
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
        register u8 *engine_page ASM_REG("$18");
        register u8 *data_page ASM_REG("$17");
        register Entry *entry ASM_REG("$16");
        register u8 *temp_v0 ASM_REG("$2");
        register u8 *call_a0 ASM_REG("$4");
        register u8 *call_a1 ASM_REG("$5");
        register s32 call_a2 ASM_REG("$6");

        engine_page = (u8 *)0x80010000;
        ASM_KEEP(engine_page);
        temp_v0 = *(u8 **)(engine_page + 0x6000);
        ASM_KEEP_NV(temp_v0);
        ASM_SCHED_BARRIER();
        temp_v0 = (u8 *)((Engine *)temp_v0)->callbacks;
        ASM_KEEP_NV(temp_v0);
        ASM_SCHED_BARRIER();
        temp_v0 = (u8 *)((CallbackBlock *)temp_v0)->callback;
        ASM_KEEP_NV(temp_v0);
        data_page = (u8 *)0x80020000;
        ASM_KEEP(data_page);
        ((Callback)temp_v0)(data_page - 0x6E94, D_80019178, var_s3);
        ASM_KEEP(data_page);

        temp_v0 = *(u8 **)(engine_page + 0x6000);
        ASM_KEEP_NV(temp_v0);
        ASM_SCHED_BARRIER();
        temp_v0 = (u8 *)((Engine *)temp_v0)->callbacks;
        ASM_KEEP_NV(temp_v0);
        entry = (Entry *)(var_s3 << 3);
        ASM_KEEP_NV(entry);
        entry = (Entry *)((s32)entry + (s32)entries);
        ASM_KEEP(entry);
        temp_v0 = (u8 *)((CallbackBlock *)temp_v0)->callback;
        ASM_KEEP_NV(temp_v0);
        call_a0 = data_page - 0x6E94;
        ASM_KEEP_NV(call_a0);
        call_a1 = (u8 *)0x80020000;
        ASM_KEEP_NV(call_a1);
        call_a2 = entry->first;
        ((Callback)temp_v0)(call_a0, call_a1 - 0x6E7C, call_a2);
        ASM_KEEP(data_page);

        temp_v0 = *(u8 **)(engine_page + 0x6000);
        ASM_KEEP_NV(temp_v0);
        ASM_SCHED_BARRIER();
        temp_v0 = (u8 *)((Engine *)temp_v0)->callbacks;
        ASM_KEEP_NV(temp_v0);
        ASM_SCHED_BARRIER();
        temp_v0 = (u8 *)((CallbackBlock *)temp_v0)->callback;
        ASM_KEEP_NV(temp_v0);
        call_a0 = data_page - 0x6E94;
        ASM_KEEP_NV(call_a0);
        call_a1 = (u8 *)0x80020000;
        ASM_KEEP_NV(call_a1);
        call_a2 = entry->second;
        ((Callback)temp_v0)(call_a0, call_a1 - 0x6E70, call_a2);
        return entry;
    }
}
