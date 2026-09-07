#include "common.h"
typedef struct Vec3s { s16 x; s16 y; s16 z; s16 pad; } Vec3s;
typedef void (*ReportValue)(const char *, const char *, s32);
typedef struct TownDispatch { u8 pad_000[0x168]; ReportValue report_value; } TownDispatch;
typedef struct TownRoot { u8 pad_00[0x1C]; s32 *result_values; TownDispatch *dispatch; } TownRoot;
extern void func_8001A854(Vec3s *, s32);
extern s32 func_8001A8DC(Vec3s *, Vec3s *, s32, s32, Vec3s *);
extern TownRoot *D_80016000[];
extern char D_8001610C[8];
extern char D_80016118[8];
extern char D_80016120[8];
extern char D_80016128[8];
/* Blends two loaded vectors, reports their x values, and stores the result coordinates. */
void func_8001A9B8(s32 first_input, s32 second_input, s32 blend_weight, s32 remaining_weight)
{
    Vec3s first;
    Vec3s second;
    Vec3s result;
    TownRoot *root;
    const char *first_format;
    const char *second_format;
    const char *result_format;
    func_8001A854(&first, first_input);
    {
        ReportValue report;
        report = D_80016000[0]->dispatch->report_value;
        first_format = D_8001610C;
        report(first_format, D_80016118, first.x);
    }
    first_format = 0;
    func_8001A854(&second, second_input);
    {
        ReportValue report;
        report = D_80016000[0]->dispatch->report_value;
        second_format = D_8001610C;
        report(second_format, D_80016120, second.x);
    }
    second_format = 0;
    func_8001A8DC(&first, &second, blend_weight, remaining_weight, &result);
    {
        ReportValue report;
        report = D_80016000[0]->dispatch->report_value;
        result_format = D_8001610C;
        report(result_format, D_80016128, result.x);
    }
    root = D_80016000[0];
    root->result_values[1] = result.x;
    root->result_values[2] = result.y;
}
