# SLUS jump-table ownership: r120_jtbl

Base commit: 97f105e7fd8bbfdeab9b87ad675d5345c744b939.
The two rows retain their registered 2.7.2-cdk recipe and replace computed gotos with retail-mapped switches.

| owner | canonical member | table VMA | asset offset | owned bytes | table words |
|---|---|---|---|---|---|
| jtbl_80041588 | src/slus/w_80041588.c | 0x8002D658 | 0x658 | 36 | 9 |
| jtbl_800595C0 | src/slus/w_800595C0.c | 0x8003310C | 0x610C | 232 | 58 |

Each owner is a wrapper TU including the canonical member. The existing manifest carve places its compiler-local .rodata at the retail address. The existing slus_rodata_trim.py hook cuts the first table from GNU-as's 40-byte section to the 36-byte owned span; the second is already 232 bytes. The following owner at 0x8002D67C and SPU strings at 0x800331F4 remain outside these spans.

The migration follows d9f94903e; see [the original migration](slus_rodata_migration.md) for the general proof rules. The lane's PROOF.md records the fresh full-image SHA-1 gate, direct genuine ownership proof and tests. Its delivery package binds before/after hashes to this base and requires --live for the canonical root.

## Validation

The scratch tree's fresh full SLUS build passed at retail SHA-1 `e6bfbb95ff6676899e077481221d73ddd4d3bf52` (861 TUs). Its generated recipe equals the repinned `ledger/splits/slus.build.ninja`, SHA-256 `e384f60a87942ddb6b35e1b603e94ebb7b3aff133f15df2301ad85e3df81af3c`.

[The ownership receipt](r120_jtbl_slus_ownership_receipt.json) proves both `.rodata` spans through the production `prove_slus_ownership.py` branch: 9 and 58 R_MIPS_32 table words, map placement, resolved text references, exact retail bytes, and removed absolute table symbols. Both members are direct genuine ASPSX 2.79 and retail exact, with zero masked words and no fired maspsx imitation passes. This is data ownership, without an L4/L5 placement certificate.

All 228 existing SLUS unit tests passed, including the ownership/trim negative controls. The archived scratch's ignored rebaseline-test fixture was reconstructed using the existing `verify.py --rebaseline-slus` command after the full-image gate; no tracked input changed for that fixture.

ASPSX 2.79 cannot open inputs under the lane's long filesystem path. The lane-only launcher uses a private user/mount namespace to present its ordinary lane-owned temporary directory at `/tmp`. It invokes the installed wibo and ASPSX with the original input stream and flags; it changes no production tool or proof check. Every guest write still lands inside the lane's temporary directory.
