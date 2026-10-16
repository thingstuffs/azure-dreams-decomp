/* Relink of matched dungeon/func_80E12AA4; every changed retail word is a paired relocation. */
#define D_800E1F65 D_800E1FEA
#define D_800E1FB9 D_800E1FD2
#include "common.h"

extern s32 func_800990FC(void);
extern s32 func_80099194(u8 *src, u8 *dst);
extern void func_80099290(s8 *byte_ptr);
extern s32 func_80099734(void *record, u8 *out);
extern void func_800A5720(s8 *text);

extern u8 D_800E1FEA[9];
extern u8 D_800E1FD2[9];

/* Format an entity message or dispatch its alternate message. */
void func_801643CC(s32 alternate_message, s32 entity)
{
    s32 text_ctx;

    text_ctx = func_800990FC();
    if (alternate_message << 16) {
        func_80099290(func_80099194(D_800E1FD2,
                                    func_80099734(entity, text_ctx)));
        func_800A5720(text_ctx);
        return;
    }
    func_80099290(func_80099194(D_800E1FEA,
                                func_80099734(entity, text_ctx)));
    func_800A5720(text_ctx);
}
