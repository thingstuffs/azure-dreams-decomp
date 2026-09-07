typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;

typedef struct Copy20 {
    s32 word[5];
} Copy20;

typedef struct Object136 {
    u8 pad0[8];
    void *data;
    void *entity;
    void *callback;
    u8 pad14[12];
    Copy20 init;
} Object136;

extern void *func_8003FC64();
extern void func_8004491C();
extern u8 D_8002614C[];
extern u8 D_80045340[];
extern u8 D_800F7944[];

void func_800253BC(Copy20 *arg0, s32 arg1)
{
    Object136 *obj;
    u8 *data;
    u8 *entity;

    obj = func_8003FC64(0x136);
    if (obj != 0) {
        obj->init = *arg0;
        obj->callback = D_8002614C;
        func_8004491C(obj, D_80045340);

        data = obj->data;
        entity = obj->entity;
        *(s32 *)(data + 0) = 0x05380000;
        *(s32 *)(data + 8) = 0xFFE00000;
        *(s32 *)(data + 4) = arg1;
        *(s16 *)(entity + 0x1E) = 0x1000;
        *(s16 *)(entity + 0x1C) = 0x1000;
        *(s32 *)(entity + 8) = (s32)D_800F7944;
        *(s8 *)(entity + 4) = 0;
        *(s8 *)(entity + 5) = 0;
        *(s32 *)(entity + 0xC) = 0x00808080;
        *(u16 *)(entity + 0x14) |= 0x80;
    }
}
