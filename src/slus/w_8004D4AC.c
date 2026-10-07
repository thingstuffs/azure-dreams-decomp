#include "common.h"
#include "shared/game_work.h"

#include "common.h"

#include "common.h"

typedef struct
{
    s16 m[3][3];
    s32 t[3];
}
MATRIX;

typedef struct
{
    s16 vx;
    s16 vy;
    s16 vz;
    s16 pad;
}
SVECTOR;

typedef struct
{
    s32 vx;
    s32 vy;
    s32 vz;
}
VECTOR;



extern void RotMatrix(SVECTOR *r, MATRIX *m);
extern void SetRotMatrix(MATRIX *m);
extern void SetTransMatrix(MATRIX *m);
extern void TransMatrix(MATRIX *m, VECTOR *v);
extern void RotTrans(SVECTOR *v0, VECTOR *v1, s32 *flg);
extern void CompMatrix(MATRIX *m0, MATRIX *m1, MATRIX *m2);
extern void func_80041900(MATRIX *m);

/* Build and install the combined rotation and translation from global transform state. */
void func_8004D4AC(void)
{
    GameView *transform = (GameView *)(&gameWork.view);
    VECTOR rotated_pos;
    MATRIX base_mat;
    MATRIX combined_mat;
    MATRIX offset_mat;
    MATRIX *offset_mat_ptr;
    SVECTOR neg_offset;
    s32 gte_flags;
    offset_mat.t[2] = 0;
    offset_mat.t[1] = 0;
    offset_mat.t[0] = 0;
    base_mat.t[2] = 0;
    offset_mat_ptr = &offset_mat;
    base_mat.t[1] = 0;
    base_mat.t[0] = 0;
    RotMatrix((SVECTOR *)&transform->unk_0AC, &offset_mat);
    SetRotMatrix(offset_mat_ptr);
    SetTransMatrix(&offset_mat);
    neg_offset.vx = -transform->unk_0A4;
    neg_offset.vy = -transform->unk_0A6;
    neg_offset.vz = -transform->unk_0A8;
    RotTrans(&neg_offset, &rotated_pos, &gte_flags);
    TransMatrix(&offset_mat, &rotated_pos);
    RotMatrix((SVECTOR *)&transform->unk_09C, &base_mat);
    SetRotMatrix(&base_mat);
    SetTransMatrix(&base_mat);
    RotTrans((SVECTOR *)&transform->unk_094, &rotated_pos, &gte_flags);
    TransMatrix(&base_mat, &rotated_pos);
    func_80041900(&base_mat);
    CompMatrix(&base_mat, &offset_mat, &combined_mat);
    SetTransMatrix(&combined_mat);
    SetRotMatrix(&combined_mat);
}
