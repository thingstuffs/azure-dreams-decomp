#include "modules/town_player_init.h"

/* Rebuild the town menu's node list for the current mode and hand it to the drawing pass. */
void townRebuildMenuNodeList(void *owner, EntityRec *node_in, s32 mode) {
    func_80092C9C_S_800903FC_3 *node;
    void *handler;
    u8 *base;
    u8 *object;
    u8 *work;
    s16 value;

    handler = (*(void * *)((u8 *)owner + (0)));
    if (handler != D_80097D2C || handler != func_80090A64) {
        townApplyTheEnabledMovementOffsetsAddingZOffsetOnlyPositive(node_in);
    }
    townAddMotionDeltasToPosition(node_in);

    handler = (*(void * *)((u8 *)owner + (0)));
    if (handler != D_80097D2C || handler != func_80090A64) {
        townUpdateObjectAndClearStatusFields(node_in);
    }

    if (node_in->z.v > 0 && D_8006ADD4[0] != 12 &&node_in->y.v > 0x03FFFFFF) {
        if (townCheckMaskedValueInCurrentRange((u16)townReadMapCellAtWorldPosition(node_in->x.w.i,
                                                  node_in->y.w.i)) == 0) {
            node_in->z.v = 0;
        }
    }

    func_80095460(node_in);

    work = (u8 *)&D_800FE490;
    ((func_80092C9C_S_800903FC_1 *)work)->unk_16 = (*(u16 *)((u8 *)owner + (0x10)));
    townUpdateTheSField10UsingCallee8008FE90(work);
    if (townGetWhetherHasAttachedStateTypeN1N3(work) != 0) {
        (*(s32 *)((u8 *)owner + (0x2C))) = 0;
        func_8008B158(((func_80092C9C_S_800903FC_1 *)work)->unk_10);

        object = D_80082BC0;
        (*(func_80092C9C_ObjectCallback *)((u8 *)object + (0x10)))(object + 0x20, 0, 0);

        if (func_800352FC() != 0) {
            base = (u8 *)&D_800CFCB4;
            if (((func_80092C9C_S_800903FC_2 *)base)->unk_3B == 0 ||
                (node = ((func_80092C9C_S_800903FC_4 *)(((func_80092C9C_S_800903FC_2 *)base)->unk_20))->unk_08)->unk_0C != 0 ||
                node->unk_10 != 0 || node->unk_14 != 0) {
                {
                    u8 *update_work;

                    update_work = ((u8 *)&D_800FE488);
                    value = townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(node_in, update_work);
                    townComputeAndClampsVectorBasedAdjustmentUpdatesTown(node_in, value, update_work);
                }
            }
            townRunTheThreeUpdateRoutinesContext(node_in);
            if ((*(void * *)((u8 *)owner + (0))) != D_80097D2C) {
                townInitializeRecordAndSelectActiveData(owner, node_in, mode);
            }
        }
    }

    townHandleResolveBoundingBoxOverlapsLinkedCollidersAlongLeastPenetratingAxis(&D_800CFCB4, node_in);
    (*(func_80092C9C_ActorCallback *)((u8 *)owner + (0)))(owner, node_in, mode);

    if ((*(void * *)((u8 *)owner + (-0x10))) == D_800A5638) {
        townTurnEntityTowardTarget(owner, node_in, mode);
        return;
    }
    townProcessSceneRecordUpdate(owner, node_in, mode);
}

/* MECHANISM: The 0x28 frame and s2/s1/s3 argument holds preserve the retail prologue.
   A block-local update_work separates D_800FE488 from the earlier work lifetime.
   GCC coalesces both to s0 and emits the two-edge lui/addiu held base. */
