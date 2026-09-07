typedef signed int s32;
typedef signed short s16;

typedef struct {
    char pad0[8];
    s16 x;
    s16 y;
} ObjectData;

typedef struct {
    char pad0[4];
    ObjectData *data;
} Object;

typedef struct {
    char pad0[0x68];
    Object *objects[10];
} Context;

void func_800AF2F8(Context *arg0)
{
    s32 i;

    for (i = 26; i < 36; i++) {
        arg0->objects[i - 26]->data->x = ((i - 26) / 5) * 128 + 88;
        arg0->objects[i - 26]->data->y = ((i - 26) % 5) * 16 + 136;
    }
}
