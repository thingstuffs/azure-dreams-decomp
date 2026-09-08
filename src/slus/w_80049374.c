#include "common.h"

#include "common.h"

typedef struct {
    u8 unk0;
    u8 unk1;
} Item;

typedef struct {
    char *unk0;
    char *unk4;
} StrPair;

/* Category entry is 0x14 bytes; kind@0 selects 12- vs 20-byte records; records@0xC */
typedef struct {
    u8 kind;
    u8 pad[0xB];
    void *records;
    u8 pad2[4];
} CatEnt;

extern s32 func_8004928C(Item *);
extern s32 func_800494FC(Item *);
extern s32 func_8004DD2C(char *);
extern char *rindex(char *, s32);
extern char *strcpy(char *, char *);

extern CatEnt itemCategoryTable[];
extern char D_80083D38[0x40];
extern char *D_800713F8[];

s32 func_80049374(Item *arg0, StrPair *arg1) {
    char *var_s1;
    s32 var_v1;
    CatEnt *temp_a0;
    CatEnt *base;
    s32 idx;
    s32 id;

    if ((arg0 == 0) || (arg0->unk1 == 0)) {
        var_s1 = arg1->unk4;
    } else if (func_800494FC(arg0) != 0) {
        var_s1 = arg1->unk0;
    } else {
        /* 3-statement base form: lui fills prior branch delay; idx then add */
        base = itemCategoryTable;
        idx = arg0->unk1;
        temp_a0 = base + idx;
        if (temp_a0->kind == 0) {
            id = arg0->unk0;
            var_v1 = id * 4;
        } else {
            id = arg0->unk0;
            var_v1 = id * 2;
        }
        var_v1 = var_v1 + id;
        /* Pin scale/addr to $v1 so final addu is addu v1,v1,v0 (not addu v0,v0,v1) */
        {
            register s32 addr ASM_REG("$3");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            addr = var_v1;
            addr = addr * 4;
            addr = addr + (s32)temp_a0->records;
            var_s1 = *(char **)(addr + 8);
        }
        if ((arg0->unk1 == 0x13) && (func_8004928C(arg0) != 0)) {
            strcpy(D_80083D38, var_s1);
            strcpy(rindex(D_80083D38, 0) - 0x12, D_800713F8[0]);
            var_s1 = D_80083D38;
        }
    }
    return func_8004DD2C(var_s1);
}
