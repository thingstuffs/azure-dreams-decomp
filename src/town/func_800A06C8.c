#include "common.h"

extern s32 func_8009706C(s32 arg0);
extern void func_800970AC(s32 arg0, void *arg1);
extern void func_800478B8(void *arg0);

typedef struct {
    /* 0x00 */ u8 pad[0x4D];
    /* 0x4D */ u8 unk4D;
    /* 0x4E */ u8 pad2[0x2];
    /* 0x50 */ void (*unk50)(void *, void *, s32, s32);
} EntityLike;

/* Invoke the entity callback and perform follow-up processing unless its flags suppress it. */
void func_8009DE28(EntityLike *entity, s32 callback_id, s32 callback_data)
{
    u16 *flags = (u16 *)((u8 *)entity - 2);

    entity->unk50(entity, entity, callback_id, callback_data);
    if (!(*flags & 0x8000)) {
        func_800970AC(func_8009706C(callback_id), entity);
        if (entity->unk4D == 0x13) {
            func_800478B8((void *)callback_data);
        }
    }
}
