#ifndef DUNGEON_OVL_1894800_H
#define DUNGEON_OVL_1894800_H
#include "common.h"
#include "modules/dungeon_native_abi.h"
typedef struct LinkedRenderNode {
    u8 pad0[8];
    void *context;
    void *data;
} LinkedRenderNode;
void project_textured_quad_or_callback(void *, void *, void *, s16);
void func_80024758(void *, void *, void *, u16);
s32 project_linked_quad_record(void *, void *, void *);
s32 draw_chained_object_records(void *, void *, void *);
s32 project_colored_point(u8 *, u8 *);
void func_80025278(void *, s16 *);
void update_effect_quad_and_completion(void *, void *, void *);
void spawn_randomized_spark_burst(u8 *, void *, u8 *);
void func_80024098(void *, s32, void *);
/* Signed two-byte view of the first counter; indexed reads use its address. */
extern s16 D_80026664;
#endif
