#include "common.h"

#include "common.h"

typedef struct S_8004A330_Sub20 {
    u16 field0;
    u16 pad2;
    s16 x;
    s16 y;
    void *field8;
} S_8004A330_Sub20;

typedef struct S_8004A330_Entity {
    u8 pad0[0xC];
    void *field_c;
    void (*update_fn)(void *);
    u8 pad1[0x1E - 0x14];
    u16 flags;
    S_8004A330_Sub20 sub20;
    u8 pad2[0x50 - 0x2C];
    u8 sub50[4];
} S_8004A330_Entity;

extern S_8004A330_Entity *func_8003FC64(s32 a0);
extern s32 func_8004B404(s32 a0);
extern void func_8004A24C(S_8004A330_Sub20 *a0, s32 a1, s32 a2,
                          s16 a3, s16 a4, s16 a5);
extern void func_8004491C(void *a0, void *a1);
extern void func_8004CAA0(void);
extern void func_80049F2C(void *a0);
extern s32 D_800814A0;
#ifndef NON_MATCHING
extern s32 D_800814A0_load[3];
__asm__(".set D_800814A0_load, 0x800814A0");
#endif

S_8004A330_Entity *func_8004A330(s32 p0, s32 p1, s32 p2, s32 p3,
                                  s32 p4, s32 p5, s32 p6, s32 p7) {
    S_8004A330_Entity *entity;
    register S_8004A330_Sub20 *sub20 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 resptr;
    s32 saved_p0 = p0;
    register s32 saved_p1 ASM_REG("$22") = p1;   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    register s32 saved_p2 ASM_REG("$20") = p2;   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    register s32 saved_p3 ASM_REG("$18") = p3;   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    register s32 saved_p4 ASM_REG("$19") = p4;   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    register s32 saved_p5 ASM_REG("$21") = p5;   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    u16 entity_flags;
    s32 global_flags;
#ifndef NON_MATCHING
    s32 *global_page;
#endif

    entity = func_8003FC64(0);
    if (entity != 0) {
        resptr = func_8004B404(0);
        sub20 = &entity->sub20;
        sub20->field8 = (void *)resptr;
        if (resptr != 0) {
            sub20->field0 = (u16)p6;
            sub20->x = (s16)(saved_p3 - 0xA0);
            sub20->y = (s16)(saved_p4 - 0x80);
            func_8004A24C(sub20, saved_p0, p7, (s16)saved_p1,
                          (s16)saved_p2,
                          (s16)saved_p5);
            ASM_KEEP(saved_p1);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            ASM_KEEP(saved_p2);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            ASM_KEEP(saved_p3);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            ASM_KEEP(saved_p4);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            ASM_KEEP(saved_p5);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            entity->field_c = &entity->sub50;
            func_8004491C(entity, func_8004CAA0);
            entity->update_fn = func_80049F2C;
        } else {
            entity_flags = entity->flags;
            entity->flags = entity_flags | 0x8000;
#ifndef NON_MATCHING
            global_flags = D_800814A0_load[0];
#else
            global_flags = D_800814A0;
#endif
            entity = 0;
            global_flags |= 0x8000;
#ifndef NON_MATCHING
            global_page = (s32 *)0x80080000;
            global_page[0x528] = global_flags;
#else
            D_800814A0 = global_flags;
#endif
        }
    }
    return entity;
}
