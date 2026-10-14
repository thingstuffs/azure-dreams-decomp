# ovmovie_libpress (OVMOVIE resident, libpress.c)

Sony LIBPRESS (MDEC/DCT movie decode support) as one original SDK object: 17 functions (ovmovie/func_80040ED8 ..
func_80041508; DecDCTin / DecDCTout / MDEC_in / MDEC_reset / MDEC_out_sync family), compiled as ONE stock
2.7.2-G0 TU (`src/ovmovie/modules/ovmovie_libpress_owned.c`), with its three storage/text allocations owned by the TU
(`ovmovie_libpress_storage.c`, model `separated-literal-allocations-v1`, tools/gate/overlay_native_allocations.py).
Volatile accesses are the MDEC/DMA hardware registers. Imports: func_8005FFFC, func_8006005C, printf (SLUS).

Evidence: r120_ovm REPORT.md / PROOF.md (work/native_lane/r120_ovm), docs/evidence/ovmovie_r120_*.json
(attribution, census, corpus, native text/owned, storage, g-axis genuine), membership
docs/evidence/ovmovie_libpress.membership.json (strong, coverage complete). Landed in 3b7485c58.

Reviewer: orchestrator-r120 (2026-10-14): membership (complete ledger group, selector receipt placement), types (member declarations reconciled into the module header) and ownership (imports bound to proven maps; owned allocations per separated-literal-allocations-v1) reviewed.
