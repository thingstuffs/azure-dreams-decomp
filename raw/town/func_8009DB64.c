#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct {
    u8 pad_00[0x10];
    void *field_10;
    u8 pad_14[4];
    s32 index;
    void *owner;
    u8 pad_20[0x1A];
    u8 state;
    u8 state_3B;
} TownControl;

typedef struct {
    void (*func0)(void);
    void *pad_04[5];
    void (*func18)(void);
} TownVtable;

typedef struct {
    u8 pad_00[0x58];
    TownVtable *vtable;
} TownObject;

extern void func_8009B444(void);
extern void func_8009C120(void);
extern void func_8009C148(void);

extern s32 D_800834B8;
extern u8 D_80091F64[];
extern u8 D_8009204C[];
extern u8 D_800920F4[];
extern u8 D_800924EC[];
extern u8 D_80092698[];
extern u8 D_800927EC[];
extern TownControl D_800CFCB4;
extern s32 D_800CFCCC;
extern s32 D_800CFDD8[];

s32 func_8009B2C4(TownObject *arg0, void *arg1) {
    register TownControl *control ASM_REG("$9");
    register TownControl *initial_page ASM_REG("$2");
    TownControl *var_v0;
    TownControl *base;
    register u8 *entry ASM_REG("$2");
    s32 *page;
    s32 temp_v1;

    initial_page = (TownControl *)0x800D0000;
    ASM_KEEP_NV(initial_page);
    control = (TownControl *)((u8 *)initial_page - 0x34C);

    if (control->field_10 == arg1) {
        register s32 index ASM_REG("$8") = control->index;
        if (FIELD((u8 *)arg1 + D_800CFDD8[index], u8, 0x3A) != 0) {
            entry = (u8 *)(index + (s32)control);
            if (FIELD(entry, u8, 0x3A) == 1) {
                if (D_800834B8 == (s32)&D_800924EC) {
                    arg0->vtable->func0();
                    func_8009B444();
                    ASM_SCHED_BARRIER();
                    return 1;
                }
                goto block_7;
            }
block_7:
            if (D_800834B8 == (s32)&D_80092698) {
                func_8009C120();
                func_8009B444();
                ASM_SCHED_BARRIER();
                return 1;
            }
            var_v0 = (TownControl *)0x800D0000;
            if (D_800834B8 == (s32)&D_800927EC) {
                var_v0 = (TownControl *)0x800D0000;
                if (D_800CFCCC == 0) {
                    func_8009C148();
                    func_8009B444();
                    ASM_SCHED_BARRIER();
                    return 1;
                }
            }
            goto block_15;
        }
        goto block_15;
    }
block_15:
    var_v0 = (TownControl *)0x800D0000;
    ASM_KEEP(var_v0);
    base = (TownControl *)((u8 *)var_v0 - 0x34C);
    if ((base->state == 0) || (base->owner != arg1)) {
        if ((FIELD(arg1, u8, 0x3B) != 0) && (FIELD(arg1, void *, 0x20) == base)) {
            goto block_20;
        }
    } else {
block_20:
        page = (s32 *)0x80080000;
        temp_v1 = D_800834B8;
        if ((temp_v1 == (s32)&D_80091F64) ||
            (temp_v1 == (s32)&D_800920F4) ||
            (temp_v1 == (s32)&D_8009204C)) {
            arg0->vtable->func18();
        }
    }
    return 0;
}
