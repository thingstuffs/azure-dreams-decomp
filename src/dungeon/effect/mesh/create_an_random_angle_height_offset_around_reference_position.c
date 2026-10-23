#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef s32 M2C_UNK;

struct TargetVec;
extern struct TargetVec *D_80026208[];
void *allocate_list_node();
s32 register_node();
s32 rsin();
s32 rcos();
s32 rand();
extern void expand_fade(void *effect, void *position, void *sprite);
extern M2C_UNK D_80026180;
typedef struct TargetSub {
    u8 pad0[4];
    s16 field4;
    s16 field6;
    s16 field8;
    u16 fieldA;
} TargetSub;
typedef struct TargetVec {
    s32 field0;
    s32 field4;
    u8 pad8[2];
    u16 fieldA;
} TargetVec;
typedef struct TargetData {
    u8 pad0[0xC];
    u8 byteC;
    u8 byteD;
    u8 byteE;
    u8 padF;
    u16 field10;
    u8 pad12[2];
    u16 field14;
    u8 pad16[6];
    u16 field1C;
    u16 field1E;
} TargetData;
typedef struct TargetObj {
    u8 pad0[8];
    TargetVec *field8;
    TargetData *fieldC;
    void *field10;
    u8 pad14[0xC];
    TargetSub sub;
} TargetObj;
/* Creates an object at a random angle and height offset around the reference position. */
void create_an_random_angle_height_offset_around_reference_position(void)
{
    s32 axis_offset;
    s32 angle_random;
    s32 height_random;
    s32 axis_factor;
    s16 height_or_shade;
    s32 angle_quotient;
    s32 height_quotient;
    TargetSub *motion;
    TargetObj *obj;
    obj = allocate_list_node(0x212, ((u8 *)(&scene_object_list_anchor)));
    if (obj != 0) {
        motion = &obj->sub;
        obj->field10 = &expand_fade;
        motion->field4 = 0;
        motion->field6 = 0x20;
        angle_random = rand();
        angle_quotient = angle_random;
        angle_quotient = angle_random / 4096;
        motion->field8 = (s16) (angle_random % 4096);
        height_random = rand();
        height_quotient = height_random;
        height_quotient /= 32;
        height_or_shade = (height_quotient << 5) - height_random;
        {
            SpriteFrameState *render_data;
            void *render_config;
            render_config = &D_80026180;
            motion->fieldA = (u16) height_or_shade;
            render_data = obj->fieldC;
            render_data->color.c.b = (height_or_shade = 0x80);
            render_data->color.c.g = height_or_shade;
            render_data->color.c.r = height_or_shade;
            select_record_entry_and_value(render_data, render_config, 0);
            render_data->scale_y = 0x200;
            render_data->scale_x = 0x200;
            render_data->flags = (u16) (render_data->flags | 0xC);
            render_data->tpage_abr = (u16) (render_data->tpage_abr | 0x20);
        }
        {
            ObjectPosition *position;
            TargetVec *origin;
            s32 origin_y;
            position = obj->field8;
            axis_offset = (rsin(motion->field8) >> 4) * motion->field6;
            position->x.v = D_80026208[0]->field0 + (axis_offset << 8);
            axis_factor = rcos(motion->field8);
            axis_offset = (axis_factor >> 4) * motion->field6;
            origin = D_80026208[0];
            origin_y = origin->field4;
            position->y.v = origin_y + (axis_offset << 8);
            position->z.w.i = (s16) (origin->fieldA + motion->fieldA);
            register_node(obj, project_sprite_chain);
        }
    }
}

/* MECHANISM: Pure scheduler rotation. Retail materialises the `&D_80026180` lui/addiu pair BEFORE the
   `sh v0,0xA(s2)` remainder store; gcc-2.8.1 sinks the address pair past both the store and the `li
   v0,0x80`. */
