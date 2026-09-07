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
    char pad0[0x40];
    Object *objects[10];
} Context;

void func_800AF600(Context *arg0)
{
    s32 i;

    for (i = 16; i < 26; i++) {
        arg0->objects[i - 16]->data->x = ((i - 16) / 5) * 128 + 96;
        arg0->objects[i - 16]->data->y = ((i - 16) % 5) * 16 + 136;
    }
}
