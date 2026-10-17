# r121_sdk2 archived native objects (hash manifest)

The lane archived one production-gate object per row (878 `.o` files, 2,393,692 bytes) under
`docs/evidence/r121_sdk2_objects/dungeon/`. Standing rule (decision 60f): git holds no binaries, so the
objects are not in the repository. `objects.tsv` keeps what the objects proved:

- `archive_sha256`: sha256 of the archived object (the lane's copy).
- `production_sha256`: sha256 of the untouched production object it was copied from.
- `metadata_offset`, `metadata_length`, `metadata_before_sha256`: the only bytes the archive changed. They are
  the ELF STT_FILE filename string in the string table (byte range `[offset, offset+length)` of the object,
  100 bytes in every case); the archive holds a repository-relative path there instead of the build path.
  `metadata_before_sha256` is the sha256 of the production bytes of that range. All code bytes, relocation
  records and symbol indices are identical to the production object.

The per-row relocation audit stays in `docs/evidence/r121_sdk2.receipt.json` (`object_audit`); that receipt
still names the former archive paths, which no longer exist in the tree. To recreate an object, rebuild the
row's production window (`tools/overlay_local_gate.py --config <gate_config>`) and compare with `production_sha256`.
