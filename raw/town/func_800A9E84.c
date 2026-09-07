#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef struct {
    s32 unk0;
    void *value;
} EntryRecord;

extern void func_80033CD8();
extern void *func_8009C390();
extern s32 D_80045340;
extern EntryRecord D_80082660[];
extern u8 D_800A76F0;
extern s32 D_800D0E24[];
extern s32 D_800D0E3C[];

void func_800A75E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    register s32 saved_arg1 ASM_REG("$18");
    register s32 saved_arg2 ASM_REG("$19");
    register s32 saved_arg3 ASM_REG("$20");
    register void *call_arg0 ASM_REG("$4");
    register void *call_arg1 ASM_REG("$5");
    register void *call_arg2 ASM_REG("$6");
    register void *entry ASM_REG("$2");
    void *object;
    register u8 *body ASM_REG("$16");
    register void *part ASM_REG("$17");
    register s32 *value_slot ASM_REG("$3");
    void *part_data;

    saved_arg1 = arg1;
    saved_arg2 = arg2;
    saved_arg3 = arg3;
    call_arg0 = NULL;
    call_arg1 = call_arg0;
    if (arg0 != 0) {
        entry = D_80082660[arg0].value;
        if (entry != NULL) {
            call_arg0 = entry;
            call_arg1 = FIELD(entry, void *, 8);
            ASM_KEEP(entry);
        }
    }
    call_arg2 = &D_800A76F0;

    ASM_KEEP(call_arg0);
    ASM_KEEP(call_arg1);
    ASM_KEEP(call_arg2);
    object = func_8009C390(call_arg0, call_arg1, call_arg2, 0);
    body = (u8 *)object + 0x20;
    if (object != NULL) {
        call_arg0 = body;
        ASM_KEEP(call_arg0);
        entry = D_800D0E24;
        ASM_KEEP(entry);
        value_slot = (s32 *)(((u32)saved_arg1 << 2) + (u32)entry);
        ASM_KEEP(value_slot);
        part = FIELD(object, void *, 8);
        part_data = FIELD(object, void *, 0xC);
        FIELD(part_data, s32, 8) = *value_slot;
        func_80033CD8(call_arg0, &D_80045340, part_data);
        FIELD(part, u16, 0xA) = FIELD(part, u16, 0xA) - 0x62;
        FIELD(body, s16, 0x90) = 0xA;
        FIELD(body, s16, 0x6C) = saved_arg3;
        FIELD(body, s8, 0x95) = saved_arg1;
        FIELD(body, s8, 0x96) = saved_arg2;
        FIELD(body, s32, 0x50) = D_800D0E3C[saved_arg2];
    }
    ASM_KEEP(saved_arg1);
    ASM_KEEP(saved_arg2);
    ASM_KEEP(saved_arg3);
    ASM_KEEP(body);
    ASM_KEEP(part);
}

/* MECHANISM: Pinned argument/call registers reproduce the retail 0x28 frame and saved-register roles.
   An 8-byte entry record preserves the table's base-plus-field addressing; split pinned base/index
   liveness orders the two later global addresses, and the clean merge supplies the branch-delay lui. */
