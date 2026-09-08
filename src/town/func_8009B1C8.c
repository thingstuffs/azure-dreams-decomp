#include "common.h"

extern void func_80099754(s32 arg0);
extern void func_80094984(void *arg0, void *arg1, s32 arg2);
extern u8 D_800D0078[];
extern void *D_80097DE8[];
extern s8 D_80082669[16];

typedef struct {
    s32 unk0;
    void **unk4;
} Struct8009B1C8;

/* Initialize the record, assign its handler table, and clear the first flag. */
void func_80098928(Struct8009B1C8 *record, s32 setup_value, s32 init_value) {
    func_80099754(setup_value);
    func_80094984(D_800D0078, record, init_value);
    record->unk4 = D_80097DE8;
    D_80082669[0] = 0;
}
