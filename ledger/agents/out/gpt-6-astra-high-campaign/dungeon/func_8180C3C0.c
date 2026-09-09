#include "common.h"
#include "records/Rec_D_80083160.h"

typedef struct S_800253C0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { volatile s16 v; s16 n; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    union { u8 n; volatile u8 v; } unk_9B;   /* accessed as both */
    u8 pad_9C[0x10];
    void * unk_AC;
    void * unk_B0;
} S_800253C0_0;   /* arg0 in func_800253C0 */

typedef struct S_800253C0_1 {
    u8 pad_00[0x2A];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0x24];
    s16 unk_88;
} S_800253C0_1;   /* arg3 in func_800253C0 */

typedef struct S_800253C0_2 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_800253C0_2;   /* page1 in func_800253C0 */

typedef struct S_800253C0_3 {
    u8 pad_00[0x2C];
    void * unk_2C;
} S_800253C0_3;   /* fa0 in func_800253C0 */

typedef struct S_800253C0_4 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_800253C0_4;   /* record in func_800253C0 */

typedef struct S_800253C0_5_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_800253C0_5_pre;   /* the 0x18 bytes before object in func_800253C0, addressed as object[-1] */

typedef struct S_800253C0_5 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x12];
    union { u16 n; s16 n2; volatile u16 v; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x5C];
    union { s16 s; u16 u; } unk_88;   /* accessed as both */
    u16 unk_8A;
} S_800253C0_5;   /* object in func_800253C0 */

typedef struct S_800253C0_6 {
    u8 pad_00[0xA8];
    u8 unk_A8;
} S_800253C0_6;   /* page in func_800253C0 */

typedef struct S_800253C0_7 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_800253C0_7;   /* page_loop in func_800253C0 */

typedef struct S_800253C0_8 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800253C0_8;   /* arg2 in func_800253C0 */

typedef struct S_800253C0_9 {
    u8 pad_00[0x2];
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
} S_800253C0_9;   /* prim in func_800253C0 */

typedef struct S_800253C0_10 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
} S_800253C0_10;   /* arg1 in func_800253C0 */

typedef struct S_800253C0_11 {
    u32 unk_00;
} S_800253C0_11;   /* amounts in func_800253C0 */

typedef struct S_800253C0_12 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_800253C0_12;   /* record2 in func_800253C0 */

typedef struct S_800253C0_13 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_800253C0_13;   /* page3b in func_800253C0 */

typedef struct S_800253C0_14_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_800253C0_14_pre;   /* the 0x18 bytes before other in func_800253C0, addressed as other[-1] */

typedef struct S_800253C0_15 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x8];
    u32 unk_0C;
    u8 pad_10[0xB8];
    s16 unk_C8;
} S_800253C0_15;   /* tb in func_800253C0 */

typedef struct S_800253C0_16_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800253C0_16_pre;   /* the 0x14 bytes before object2 in func_800253C0, addressed as object2[-1] */

typedef struct S_800253C0_17 {
    u8 pad_00[0xC];
    union { struct { u8 v; } at00; struct { volatile u8 v; } at00u; struct { u32 v; } at00p; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    s16 unk_10;
    union { u16 u; s16 s; } unk_12;   /* accessed as both */
    union { s16 s; u16 u; } unk_14;   /* accessed as both */
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800253C0_17;   /* child in func_800253C0 */

typedef struct S_800253C0_18 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_800253C0_18;   /* (void *)((i << 2) + (s32)arg0) in func_800253C0 */

typedef struct S_800253C0_19 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_800253C0_19;   /* page8 in func_800253C0 */




extern u8 D_80083160[];
extern s8 D_8006CCD8[];
extern s8 D_8006CCE8[];
extern void *D_8006CD58[];
extern s16 D_8008346A[1];
extern u8 D_80083460[];
extern u8 D_800DD148[];
extern u8 D_800DD150[];
extern u8 D_8008ACDC[];
extern u8 D_80025000[];
extern u8 D_80025024[];
extern u8 D_80025028[];
extern u8 D_80025068[];
extern u8 D_800287F0[];

extern void func_8003F540(void *, void *, void *, s32);
extern s32 func_800445E0(void);
extern void Control_CD(s32, s32, s32);
extern void func_800ACB98(void *, void *, void *, void *);
extern void func_800A56E0(s32);
extern void func_80026C88(s16, s16, s16, void *);
extern void func_80026A84(void *, void *, void *, void *);
extern void func_800B835C(void *, void *, s32, s32);
extern void func_80025FF4(void *, void *);
extern s32 func_8003FA44(s32);
extern s32 func_800990FC(void);
extern s32 func_8009929C(s32, s32);
extern s32 func_80099734(void *, s32);
extern s32 func_80099194(void *, s32);
extern s32 func_80099290(s32);
extern s32 func_800999B0(s32);
extern void func_800A5720(s32);
extern void *func_800280F4(void *, void *, void *);
extern void func_800264D4(void *, void *, s32, s32);
extern void func_80027070(s16, s16, s16, s32, void *);
extern void *func_800277F4(void *, void *, s32);
extern s32 func_80028208(void *, s32);
extern void func_80027534(s16, s16, s16, s32);
extern void func_80048A44(void *, s32, s32, s32);


/* Advance the paired-object sequence, animating both objects and displaying the result. */
void func_800253C0(void *sequence_in, void *position_in, void *actor_in, void *owner_in)
{
    void *sequence = sequence_in;
    void *position = position_in;
    void *actor = actor_in;
    register void *owner = owner_in;
    u8 *scene = D_80083160;
    register void *anim_actor ASM_REG("$4");
    s32 anim_mode;
    register u8 *anim_entry ASM_REG("$2");
    u8 state;
    u32 result_flags;

    state = ((S_800253C0_0 *)sequence)->unk_9B.n;
    switch (state) {
    case 0:
        if (((S_800253C0_0 *)sequence)->unk_AC == 0) {
            goto missing_object;
        }
        if (((S_800253C0_0 *)sequence)->unk_B0 != 0) {
            goto start_sequence;
        }
missing_object:
        ((S_800253C0_0 *)sequence)->unk_9B.n = 13;
        goto done;
start_sequence:
        {
            void *sound_data = *(void *volatile *)&D_8006CD58[0];
            func_8003F540(0, sound_data, 0, 0x1000530);
        }
        {
            s32 cd_value = func_800445E0();
            Control_CD(21, cd_value, 0);
        }
        goto advance_state;

    case 1:
        {
            s32 index;
            u8 *turn_scene;
            u16 old_angle;

            turn_scene = D_80083160;
            old_angle = ((S_800253C0_1 *)owner)->unk_2A.u;
            index = ((((S_800253C0_2 *)turn_scene)->unk_C8 +
                ((S_800253C0_1 *)owner)->unk_2A.s + 0x100) >> 9) & 7;
            if (index == 2) {
                anim_actor = actor;
                ((S_800253C0_3 *)anim_actor)->unk_2C = D_800DD148;
                anim_mode = 0;
                anim_entry = D_800DD148 + ((((((S_800253C0_2 *)turn_scene)->unk_C8 +
                    ((S_800253C0_1 *)owner)->unk_2A.s) + 0x100) >> 9) & 7);
                goto set_animation;
            }
            ((S_800253C0_1 *)owner)->unk_2A.s = old_angle + 0x200;
            goto done;
        }

    case 2:
        {
            register s32 object_index ASM_REG("$17") = 0;
            u32 mask = 0x20000000;
            void *object_slot = sequence;

            do {
                register void *object ASM_REG("$16") = ((S_800253C0_4 *)object_slot)->unk_AC;
                if ((((S_800253C0_5 *)object)->unk_14 & mask) != 0) {
                    func_800ACB98(object, ((S_800253C0_5_pre *)object)[-1].unk_00,
                        ((S_800253C0_5_pre *)object)[-1].unk_04, object);
                }
                object_index++;
                object_slot = (u8 *)object_slot + 4;
            } while (object_index < 2);
        }
        goto advance_state;

    case 3:
        if (D_8008346A[0] != 0) {
            goto done;
        }
        {
            register s32 object_index ASM_REG("$17") = 0;
            u32 mask = 0x100000;
            void *object_slot = sequence;
            do {
                register void *object ASM_REG("$16") = ((S_800253C0_4 *)object_slot)->unk_AC;
                u16 angle;
                object_slot = (u8 *)object_slot + 4;
                object_index++;
                ((S_800253C0_5 *)object)->unk_14 |= mask;
                angle = ((S_800253C0_5 *)object)->unk_2A.n;
                ((S_800253C0_5 *)object)->unk_8A = angle;
            } while (object_index < 2);
        }
        {
            register s32 object_index ASM_REG("$17");
            void *object_slot;
            u8 brightness;
            s16 timer;
            s32 delta;
            u8 *scene_rgb;
            register s32 target_level ASM_REG("$3");
            u8 *move_scene;
            s16 *table_x;
            s16 *table_y;

            ((S_800253C0_0 *)sequence)->unk_9B.n++;
            ((S_800253C0_0 *)sequence)->unk_96.v = 32;
            ASM_SCHED_BARRIER();
            target_level = 32;
            brightness = ((S_800253C0_6 *)scene)->unk_A8;
            timer = ((S_800253C0_0 *)sequence)->unk_96.n;
            delta = (target_level - brightness) / timer;
            brightness = brightness + delta;
            scene_rgb = scene + 0xA8;
            object_index = 0;
            object_slot = sequence;
            move_scene = D_80083160;
            table_x = (s16 *)&D_8006CCD8;
            table_y = (s16 *)&D_8006CCE8;
            ASM_KEEP(scene_rgb);
            ((S_800253C0_6 *)scene)->unk_A8 = brightness;
            scene_rgb[1] = brightness;
            scene_rgb[2] = brightness;
            do {
                register void *object ASM_REG("$16");
                register void *prim ASM_REG("$8");
                register s32 table_index ASM_REG("$5");
                register s32 coord_delta ASM_REG("$3");
                s32 delta;
                register s32 old_coord ASM_REG("$2");
                s32 frames_left;

                table_index = object_index << 11;
                object = ((S_800253C0_4 *)object_slot)->unk_AC;
                old_coord = ((S_800253C0_7 *)move_scene)->unk_C8;
                table_index = table_index - old_coord;
                table_index = (table_index + 0x100) >> 8;
                table_index &= 0xE;
                coord_delta = (s32)((S_800253C0_8 *)actor)->unk_24;
                frames_left = ((S_800253C0_0 *)sequence)->unk_96.n;
                coord_delta = coord_delta + table_x[table_index >> 1];
                coord_delta = coord_delta << 6;
                prim = ((S_800253C0_5_pre *)object)[-1].unk_00;
                old_coord = ((S_800253C0_9 *)prim)->unk_02.s - 0x20;
                coord_delta = coord_delta - old_coord;
                ((S_800253C0_9 *)prim)->unk_02.u = ((S_800253C0_9 *)prim)->unk_02.u + coord_delta / frames_left;
                coord_delta = (s32)((S_800253C0_8 *)actor)->unk_25;
                {
                    register s32 y_offset ASM_REG("$2");
                    y_offset = table_y[table_index >> 1];
                    coord_delta = coord_delta + y_offset;
                }
                coord_delta = coord_delta << 6;
                old_coord = ((S_800253C0_9 *)prim)->unk_06.s - 0x20;
                coord_delta = coord_delta - old_coord;
                ((S_800253C0_9 *)prim)->unk_06.u = ((S_800253C0_9 *)prim)->unk_06.u +
                    coord_delta / ((S_800253C0_0 *)sequence)->unk_96.n;
                {
                    s32 old_z = ((S_800253C0_9 *)prim)->unk_0A.s;
                    s32 z_delta = ((S_800253C0_10 *)position)->unk_0A.s - old_z;
                    ((S_800253C0_9 *)prim)->unk_0A.u = ((S_800253C0_9 *)prim)->unk_0A.u +
                        z_delta / ((S_800253C0_0 *)sequence)->unk_96.n;
                }

                {
                    s32 angle = ((S_800253C0_7 *)move_scene)->unk_C8 + ((S_800253C0_5 *)object)->unk_2A.n2;
                    u16 old_angle = ((S_800253C0_5 *)object)->unk_2A.n;
                    if ((((angle + 0x100) >> 9) & 7) != 2) {
                        ((S_800253C0_5 *)object)->unk_2A.n = old_angle + 0x200;
                    }
                }
                object_index++;
                object_slot = (u8 *)object_slot + 4;
            } while (object_index < 2);
            timer = ((S_800253C0_0 *)sequence)->unk_96.n - 1;
            ((S_800253C0_0 *)sequence)->unk_96.n = timer;
            if (timer > 0) {
                goto done;
            }
            func_800A56E0(0x300);
            {
                register s32 object_index ASM_REG("$17");
                u8 *snap_scene;
                s16 *snap_x;
                s16 *snap_y;
                void *final_slot;
                ((S_800253C0_11 *)scene_rgb)->unk_00 = 0x2C202020;
                object_index = 0;
                snap_scene = D_80083160;
                snap_x = (s16 *)&D_8006CCD8;
                snap_y = (s16 *)&D_8006CCE8;
                final_slot = sequence;
                do {
                    register void *object ASM_REG("$16") = ((S_800253C0_12 *)final_slot)->unk_AC;
                    register void *prim ASM_REG("$8");
                    s32 table_index = ((object_index << 11) - ((S_800253C0_13 *)snap_scene)->unk_C8 + 0x100) >> 8;
                    s32 x;
                    s32 y;
                    ASM_KEEP_NV(table_index);
                    table_index &= 0xE;
                    x = (s32)((S_800253C0_8 *)actor)->unk_24 + snap_x[table_index >> 1];
                    prim = ((S_800253C0_5_pre *)object)[-1].unk_00;
                    ((S_800253C0_9 *)prim)->unk_02.s = (x << 6) + 0x20;
                    y = (s32)((S_800253C0_8 *)actor)->unk_25 + snap_y[table_index >> 1];
                    ((S_800253C0_9 *)prim)->unk_06.s = (y << 6) + 0x20;
                    ((S_800253C0_9 *)prim)->unk_0A.u = ((S_800253C0_10 *)position)->unk_0A.u;
                    final_slot = (u8 *)final_slot + 4;
                    object_index++;
                } while (object_index < 2);
                {
                    register s32 next_timer ASM_REG("$3");
                    next_timer = 16;
                    state = ((S_800253C0_0 *)sequence)->unk_9B.v;
                    ((S_800253C0_0 *)sequence)->unk_96.n = next_timer;
                }
            }
            goto store_next_state;
        }

    case 4:
        {
            s16 timer = ((S_800253C0_0 *)sequence)->unk_96.n - 1;
            ((S_800253C0_0 *)sequence)->unk_96.n = timer;
            if (timer > 0) {
                goto done;
            }
            func_80026C88(((S_800253C0_10 *)position)->unk_02, ((S_800253C0_10 *)position)->unk_06,
                ((S_800253C0_10 *)position)->unk_0A.s, actor);
            {
                register s32 next_timer ASM_REG("$3");
                next_timer = 32;
                state = ((S_800253C0_0 *)sequence)->unk_9B.v;
                ((S_800253C0_0 *)sequence)->unk_96.n = next_timer;
            }
            goto store_next_state;
        }

    case 5:
        {
            s16 timer = ((S_800253C0_0 *)sequence)->unk_96.n - 1;
            s32 object_index;
            register void *object_slot ASM_REG("$18");
            register void *object ASM_REG("$16");

            ((S_800253C0_0 *)sequence)->unk_96.n = timer;
            if (timer > 0) {
                goto done;
            }
            object_index = 0;
            object_slot = sequence;
            do {
                register void *call_position ASM_REG("$4") = position;
                register void *call_actor ASM_REG("$7") = actor;
                object = ((S_800253C0_4 *)object_slot)->unk_AC;
                object_slot = (u8 *)object_slot + 4;
                object_index++;
                func_80026A84(call_position, ((S_800253C0_5_pre *)object)[-1].unk_00, object, call_actor);
            } while (object_index < 2);
            {
                s16 texture_rect[4];
                ((S_800253C0_0 *)sequence)->unk_9B.n++;
                ((S_800253C0_0 *)sequence)->unk_96.n = 60;
                texture_rect[0] = 0x340;
                texture_rect[1] = 0x180;
                texture_rect[3] = 0x40;
                texture_rect[2] = 0x40;
                func_800B835C(D_800287F0, texture_rect, 1, 0);
            }
            goto done;
        }

    case 6:
        func_80025FF4(((S_800253C0_0 *)sequence)->unk_AC, ((S_800253C0_0 *)sequence)->unk_B0);
        {
            s16 timer = ((S_800253C0_0 *)sequence)->unk_96.n - 1;
            ((S_800253C0_0 *)sequence)->unk_96.n = timer;
            if (timer > 0) {
                goto done;
            }
            {
                register s32 next_timer ASM_REG("$3");
                next_timer = 8;
                state = ((S_800253C0_0 *)sequence)->unk_9B.v;
                ASM_SCHED_BARRIER();
                ((S_800253C0_0 *)sequence)->unk_96.n = next_timer;
            }
            goto store_next_state;
        }

    case 7:
        func_80025FF4(((S_800253C0_0 *)sequence)->unk_AC, ((S_800253C0_0 *)sequence)->unk_B0);
        {
            s16 timer = ((S_800253C0_0 *)sequence)->unk_96.n - 1;
            ((S_800253C0_0 *)sequence)->unk_96.n = timer;
            if (timer > 0) {
                goto done;
            }
        }
        if (func_8003FA44(13) == 0) {
            goto done;
        }
        {
            register s32 message_id ASM_REG("$22") = func_800990FC();
            s32 text = func_8009929C(8, message_id);
            s32 saved_text;
            register s32 next_state ASM_REG("$2");
            text = func_80099734(((S_800253C0_0 *)sequence)->unk_AC, text);
            text = func_80099194(D_80025000, text);
            text = func_80099734(((S_800253C0_0 *)sequence)->unk_B0, text);
            saved_text = func_80099194(D_80025024, text);
            {
                void *object =
                    func_800280F4(((S_800253C0_0 *)sequence)->unk_AC,
                    ((S_800253C0_0 *)sequence)->unk_B0,
                    &result_flags);
                ((S_800253C0_1 *)owner)->unk_60 = object;
                if (object != 0) {
                    s32 object_index = 0;
                    register void *object_slot ASM_REG("$20") = sequence;
animate_objects:
                    {
                        register s32 slot_index ASM_REG("$19");
                        register s32 index_bits ASM_REG("$2");
                        void *other;
                        index_bits = object_index << 16;
                        slot_index = index_bits >> 16;
                        other = ((S_800253C0_4 *)object_slot)->unk_AC;
                        func_800264D4(((S_800253C0_14_pre *)other)[-1].unk_00, other,
                            slot_index, object == other);
                        if (object == ((S_800253C0_4 *)object_slot)->unk_AC) {
                            register u8 *table_base ASM_REG("$12") = D_80083160;
                            s32 angle;
                            s32 index;
                            s32 x;
                            s32 y;
                            ASM_USE_NV(table_base);
                            angle = ((S_800253C0_15 *)table_base)->unk_C8;
                            angle = -angle;
                            index = ((angle + 0x500) >> 8) & 0xE;
                            table_base = (u8 *)&D_8006CCD8;
                            x = ((S_800253C0_8 *)actor)->unk_24 + *(s16 *)(table_base + index);
                            table_base = (u8 *)&D_8006CCE8;
                            y = ((S_800253C0_8 *)actor)->unk_25 + *(s16 *)(table_base + index);
                            func_80027070((s16)((x << 6) + 0x20),
                                (s16)((y << 6) + 0x20),
                                ((S_800253C0_1 *)owner)->unk_88, slot_index, object);
                        }
                        object_index++;
                        object_slot = (u8 *)object_slot + 4;
                    }
                    if (object_index < 2) {
                        goto animate_objects;
                    }
                    {
                        register s32 object_index ASM_REG("$17") = 0;
                        register s32 sprite_x = 32;
                        register s32 sprite_flags = 12;
                        void *final_slot = sequence;
                        do {
                            register void *source_object ASM_REG("$16") = ((S_800253C0_12 *)final_slot)->unk_AC;
                            register void *child ASM_REG("$5") = ((S_800253C0_16_pre *)source_object)[-1].unk_00;
                            u16 child_y = ((S_800253C0_17 *)child)->unk_12.u;
                            object_index++;
                            ((S_800253C0_17 *)child)->unk_10 = sprite_x;
                            ((S_800253C0_17 *)child)->unk_14.s = sprite_flags;
                            ASM_SCHED_BARRIER();
                            ((S_800253C0_17 *)child)->unk_12.s = child_y - 128;
                            final_slot = (u8 *)final_slot + 4;
                        } while (object_index < 2);
                    }
                    next_state = ((S_800253C0_0 *)sequence)->unk_9B.n;
                    ((S_800253C0_0 *)sequence)->unk_96.n = 38;
                    next_state = next_state + 1;
                    goto show_result;
                }
            }
            saved_text = func_8009929C(10, saved_text);
            saved_text = func_80099194(D_80025028, saved_text);
            ASM_KEEP(saved_text);
            next_state = ((S_800253C0_0 *)sequence)->unk_9B.n;
            ((S_800253C0_0 *)sequence)->unk_96.n = 32;
            next_state = next_state + 2;
show_result:
            ((S_800253C0_0 *)sequence)->unk_9B.n = next_state;
            func_80099290(saved_text);
            func_800A5720(message_id);
            goto done;
        }

    case 8:
        func_80025FF4(((S_800253C0_0 *)sequence)->unk_AC, ((S_800253C0_0 *)sequence)->unk_B0);
        {
            register s32 object_index ASM_REG("$17") = 0;
            void *object_slot = sequence;
            do {
                register void *object ASM_REG("$16") = ((S_800253C0_4 *)object_slot)->unk_AC;
                void *child = ((S_800253C0_5_pre *)object)[-1].unk_04;
                u32 red = ((S_800253C0_17 *)child)->unk_0C.at00.v;
                register u32 green ASM_REG("$3") = ((S_800253C0_17 *)child)->unk_0C.at01.v;
                u32 blue;
                red = red - (red >> 1);
                ((S_800253C0_17 *)child)->unk_0C.at00.v = red;
                ASM_KEEP(red);
                green = green - (green >> 1);
                blue = ((S_800253C0_17 *)child)->unk_0C.at02.v;
                red = ((S_800253C0_17 *)child)->unk_0C.at00u.v;
                ((S_800253C0_17 *)child)->unk_0C.at01.v = green;
                blue = blue - (blue >> 1);
                ((S_800253C0_17 *)child)->unk_0C.at02.v = blue;
                if (red < 5) {
                    ((S_800253C0_17 *)child)->unk_0C.at02.v = 0;
                    ((S_800253C0_17 *)child)->unk_0C.at01.v = 0;
                    ((S_800253C0_17 *)child)->unk_0C.at00.v = 0;
                }
                object_index++;
                object_slot = (u8 *)object_slot + 4;
            } while (object_index < 2);
            {
                s16 timer = ((S_800253C0_0 *)sequence)->unk_96.n - 1;
                ((S_800253C0_0 *)sequence)->unk_96.n = timer;
                if (timer > 0) {
                    goto done;
                }
            }
        }
        {
            void *object = ((S_800253C0_1 *)owner)->unk_60;
            if (object != 0) {
                void **first_slot;
                void **text_slot;
                void **removed_slot;
                void *new_object;
                register s32 message_id ASM_REG("$22");
                register s32 message_text ASM_REG("$18");
                s32 text_cursor;

                message_id = func_800990FC();
                first_slot = (void **)((u8 *)sequence + 0xAC);
                text_cursor = message_id;
                text_slot = first_slot;
                if (*first_slot != object) {
                    text_slot = (void **)((u8 *)sequence + 0xB0);
                }
                text_cursor = func_80099734(*text_slot, text_cursor);
                message_text = func_80099194(D_80025068, text_cursor);
                text_slot = first_slot;
                if (*first_slot == object) {
                    text_slot = (void **)((u8 *)sequence + 0xB0);
                }
                text_cursor = func_80099734(*text_slot, message_text);
                text_cursor = func_80099194(D_80025024, text_cursor);
                text_cursor = func_800999B0(text_cursor);
                text_cursor = func_80099290(text_cursor);
                text_cursor = func_8009929C(17, text_cursor);
                func_800A5720(message_id);
                new_object = func_800277F4(((S_800253C0_0 *)sequence)->unk_AC,
                    ((S_800253C0_0 *)sequence)->unk_B0, 0);
                ASM_KEEP_NV(new_object);
                removed_slot = first_slot;
                if (*first_slot == new_object) {
                    removed_slot = (void **)((u8 *)sequence + 0xB0);
                }
                *removed_slot = 0;
                message_id = func_800990FC();
                text_cursor = func_80028208(new_object, message_id);
                text_cursor = func_80099290(text_cursor);
                func_800A5720(message_id);
            }
        }
        {
            s32 object_index = 0;
            u8 *restore_scene = D_80083160;
            s16 *table_x = (s16 *)&D_8006CCD8;
            do {
                register void *object ASM_REG("$16") =
                    ((S_800253C0_18 *)((void *)((object_index << 2) + (s32)sequence)))->unk_AC;
                if (object != 0) {
                    register void *prim ASM_REG("$8") = ((S_800253C0_5_pre *)object)[-1].unk_00;
                    register void *child ASM_REG("$5") = ((S_800253C0_5_pre *)object)[-1].unk_04;
                    s32 index;
                    register u8 *y_table ASM_REG("$2");
                    s32 effect_size;
                    s32 x;
                    s32 y;
                    s32 z;
                    ((S_800253C0_17 *)child)->unk_0C.at00p.v = 0x808080;
                    ((S_800253C0_17 *)child)->unk_10 = 0;
                    ((S_800253C0_17 *)child)->unk_12.u &= 0x3F;
                    ((S_800253C0_17 *)child)->unk_14.u &= 0xFFF3;
                    index = (((-((S_800253C0_19 *)restore_scene)->unk_C8 + 0x500) >> 8) & 0xE);
                    x = ((S_800253C0_8 *)actor)->unk_24 + table_x[index >> 1];
                    ((S_800253C0_9 *)prim)->unk_02.s = (x << 6) + 0x20;
                    effect_size = 16;
                    ASM_KEEP(effect_size);
                    y_table = (u8 *)&D_8006CCE8;
                    index = index + (s32)y_table;
                    y = ((S_800253C0_8 *)actor)->unk_25 + *(s16 *)index;
                    ((S_800253C0_9 *)prim)->unk_06.s = (y << 6) + 0x20;
                    z = ((S_800253C0_10 *)position)->unk_0A.u;
                    ((S_800253C0_9 *)prim)->unk_0A.u = z;
                    func_80027534(((S_800253C0_9 *)prim)->unk_02.s, ((S_800253C0_9 *)prim)->unk_06.s,
                        (s16)(z - 0x20), effect_size);
                }
                object_index++;
            } while (object_index < 2);
            {
                register s32 next_timer ASM_REG("$3");
                next_timer = 64;
                state = ((S_800253C0_0 *)sequence)->unk_9B.v;
                ((S_800253C0_0 *)sequence)->unk_96.n = next_timer;
            }
            goto store_next_state;
        }

    case 9:
        {
            s16 timer = ((S_800253C0_0 *)sequence)->unk_96.n - 1;
            ((S_800253C0_0 *)sequence)->unk_96.n = timer;
            if (timer > 0) {
                goto done;
            }
            {
                register s32 next_timer ASM_REG("$3");
                next_timer = 32;
                ASM_SCHED_BARRIER();
                state = ((S_800253C0_0 *)sequence)->unk_9B.v;
                ((S_800253C0_0 *)sequence)->unk_96.n = next_timer;
            }
            goto store_next_state;
        }

    case 10:
        {
            register s32 object_index ASM_REG("$17");
            void *object_slot;
            register u8 *scene_rgb ASM_REG("$18");
            s32 target_level;
            register void *object ASM_REG("$16");
            register void *prim ASM_REG("$8");
            void *child;
            register void *final_slot;
            s16 timer;
            s32 step;
            s32 brightness;
            s32 old_coord;
            s32 delta;
            s32 x;
            s32 current_angle;
            u16 old_angle;
            u32 saved_angle;
            register u32 clear_flags;

            step = (128 - ((S_800253C0_6 *)scene)->unk_A8) / ((S_800253C0_0 *)sequence)->unk_96.n;
            scene_rgb = scene + 0xA8;
            object_index = 0;
            object_slot = sequence;
            brightness = ((S_800253C0_6 *)scene)->unk_A8 + step;
            ((S_800253C0_6 *)scene)->unk_A8 = brightness;
            scene_rgb[2] = brightness;
            scene_rgb[1] = brightness;
            do {
                object = ((S_800253C0_4 *)object_slot)->unk_AC;
                if (object != 0) {
                    register s32 coord_delta ASM_REG("$3");
                    register s32 old_coord ASM_REG("$2");
                    child = ((S_800253C0_5_pre *)object)[-1].unk_04;
                    prim = ((S_800253C0_5_pre *)object)[-1].unk_00;
                    coord_delta = (s32)((S_800253C0_17 *)child)->unk_24;
                    coord_delta = coord_delta << 6;
                    old_coord = ((S_800253C0_9 *)prim)->unk_02.s - 0x20;
                    coord_delta = coord_delta - old_coord;
                    ((S_800253C0_9 *)prim)->unk_02.u = ((S_800253C0_9 *)prim)->unk_02.u +
                        coord_delta / ((S_800253C0_0 *)sequence)->unk_96.n;
                    coord_delta = (s32)((S_800253C0_17 *)child)->unk_25;
                    ASM_SCHED_BARRIER();
                    coord_delta = coord_delta << 6;
                    old_coord = ((S_800253C0_9 *)prim)->unk_06.s - 0x20;
                    coord_delta = coord_delta - old_coord;
                    ((S_800253C0_9 *)prim)->unk_06.u = ((S_800253C0_9 *)prim)->unk_06.u +
                        coord_delta / ((S_800253C0_0 *)sequence)->unk_96.n;
                    {
                        s32 old_z = ((S_800253C0_9 *)prim)->unk_0A.s;
                        s32 z_delta = ((S_800253C0_5 *)object)->unk_88.s - old_z;
                        ((S_800253C0_9 *)prim)->unk_0A.u = ((S_800253C0_9 *)prim)->unk_0A.u +
                            z_delta / ((S_800253C0_0 *)sequence)->unk_96.n;
                    }
                    saved_angle = ((S_800253C0_5 *)object)->unk_8A;
                    ((S_800253C0_5 *)object)->unk_2A.v =
                        ((S_800253C0_5 *)object)->unk_2A.n & 0xFFF;
                    current_angle = ((S_800253C0_5 *)object)->unk_2A.n2;
                    old_angle = ((S_800253C0_5 *)object)->unk_2A.n;
                    saved_angle = saved_angle & 0xFFF;
                    ((S_800253C0_5 *)object)->unk_8A = saved_angle;
                    if (current_angle != (s16)saved_angle) {
                        ((S_800253C0_5 *)object)->unk_2A.n = old_angle + 0x200;
                    }
                }
                object_index++;
                object_slot = (u8 *)object_slot + 4;
            } while (object_index < 2);
            timer = ((S_800253C0_0 *)sequence)->unk_96.n - 1;
            ((S_800253C0_0 *)sequence)->unk_96.n = timer;
            if (timer > 0) {
                goto done;
            }
            ((S_800253C0_11 *)scene_rgb)->unk_00 = 0x2C808080;
            object_index = 0;
            clear_flags = 0xFFEFFFFF;
            final_slot = sequence;
            do {
                object = ((S_800253C0_12 *)final_slot)->unk_AC;
                if (object != 0) {
                    child = ((S_800253C0_5_pre *)object)[-1].unk_04;
                    x = ((S_800253C0_17 *)child)->unk_24;
                    prim = ((S_800253C0_5_pre *)object)[-1].unk_00;
                    ((S_800253C0_9 *)prim)->unk_02.s = (x << 6) + 0x20;
                    ((S_800253C0_9 *)prim)->unk_06.s = ((s32)((S_800253C0_17 *)child)->unk_25 << 6) + 0x20;
                    ((S_800253C0_9 *)prim)->unk_0A.u = ((S_800253C0_5 *)object)->unk_88.u;
                    ((S_800253C0_5 *)object)->unk_14 &= clear_flags;
                }
                object_index++;
                final_slot = (u8 *)final_slot + 4;
            } while (object_index < 2);
            goto advance_state;
        }

    case 11:
        anim_actor = actor;
        ((S_800253C0_3 *)anim_actor)->unk_2C = D_800DD150;
        anim_mode = 0;
        anim_entry = D_800DD150 + ((((((Rec_D_80083160 *)D_80083160)->unk_C8.as_s16 +
            ((S_800253C0_1 *)owner)->unk_2A.s) + 0x100) >> 9) & 7);
set_animation:
        func_80048A44(anim_actor, *anim_entry, anim_mode, 1);
advance_state:
        state = ((S_800253C0_0 *)sequence)->unk_9B.n;
store_next_state:
        ((S_800253C0_0 *)sequence)->unk_9B.n = state + 1;
        goto done;

    case 12:
        if ((((S_800253C0_8 *)actor)->unk_14 & 0xE000) == 0) {
            goto done;
        }
        {
            u8 *scene_flags;
            u16 value;
            scene_flags = D_80083460;
            value = ((S_800253C0_15 *)scene_flags)->unk_02;
            ((S_800253C0_15 *)scene_flags)->unk_0C = 0;
            ((S_800253C0_15 *)scene_flags)->unk_02 = value | 0x812;
        }
        ((S_800253C0_0 *)sequence)->unk_8C = D_8008ACDC;

    case 13:
        break;
    }
done:
    return;
}
