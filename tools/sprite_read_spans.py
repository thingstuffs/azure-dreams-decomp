"""Check Dungeon sprite read pairs against the disc and their readers."""

import hashlib
import json
import os
from pathlib import Path
import struct

from tools.gate.disc_slice import Disc
from tools.scene_read_spans import TOWN_ENGINE_DELTA, TOWN_RESOURCE_CATALOG


CLASS = "sprite_resource_read"
TOWN_CLASS = "town_sprite_request_read"
MANIFEST = "docs/evidence/dungeon_sprite_resource_reads.json"
VOLUME = "DUNGEON/DUNGEON.BIN"
TOWN_VOLUME = "TOWN/TOWN.BIN"
SECTOR = 2048
METADATA_SECTORS = 26
IMAGE_SECTORS = 17
NORMAL_SPECIES = range(1, 56)
THREE_SLOT_SPECIES = 56
THREE_SLOT_METADATA_SECTORS = 3 * METADATA_SECTORS
TOWN_READERS = {
    "reserve_tw_mon_load": (0x8008B550, 12),
    "process_pending_resource_load": (0x8008B55C, 124),
    "update_player_minigame_motion": (0x800C035C, 1900),
}
READERS = {
    "pack_tagged_resource_descriptor": (0x8003F6D4, 32),
    "build_sprite_metadata_read_descriptor": (0x80043704, 160),
    "build_sprite_image_read_descriptor": (0x800437A4, 152),
    "relocate_sprite_metadata_pointers": (0x80046F88, 204),
    "queue_entity_resource_descriptor_pair": (0x800479D4, 112),
    "queue_sprite_resource_slot_reads": (0x80047A68, 60),
    "upload_image_tiles": (0x80047AB0, 208),
    "queue_sprite_resource_in_free_slot": (0x80047C8C, 76),
    "prepare_uncached_sprite_resource": (0x80047CD8, 108),
    "load_cd_resource": (0x80047E78, 116),
    "register_sprite_resource": (0x80047EEC, 164),
    "load_and_upload_sprite_resource": (0x80048088, 144),
}


def reader_hashes(executable):
    if len(executable) < 0x800 or not executable.startswith(b"PS-X EXE"):
        raise ValueError("invalid executable for sprite resource readers")
    base, length = struct.unpack_from("<II", executable, 0x18)
    if not 0 < length <= len(executable) - 0x800:
        raise ValueError("invalid executable load extent for sprite resource readers")
    result = {}
    for name, (address, size) in READERS.items():
        offset = address - base
        if not 0 <= offset < offset + size <= length:
            raise ValueError("sprite resource reader lies outside the executable")
        result[name] = hashlib.sha256(executable[0x800 + offset:0x800 + offset + size]).hexdigest()
    return result


def transfer(resource_id, first_lba, volume_size):
    if type(resource_id) is not int or not (resource_id in NORMAL_SPECIES or resource_id == THREE_SLOT_SPECIES):
        raise ValueError("sprite read is outside the checked Dungeon species domain")
    # The packer stores the supplied LBA in the descriptor's second word.
    if resource_id == THREE_SLOT_SPECIES:
        metadata_lba, image_lba = 0x421F, 0x426D
    else:
        metadata_lba = 0x56D6 + (resource_id - 1) * (METADATA_SECTORS + IMAGE_SECTORS)
        image_lba = metadata_lba + METADATA_SECTORS
    offset = (metadata_lba - first_lba) * SECTOR
    size = (image_lba - metadata_lba + IMAGE_SECTORS) * SECTOR
    if not 0 <= offset < offset + size <= volume_size:
        raise ValueError("sprite read lies outside the Dungeon container")
    return offset, size


def check_payload(data, metadata_sectors=METADATA_SECTORS):
    """Follow the two pointer arrays consumed by the metadata relocator."""
    metadata_size = metadata_sectors * SECTOR
    if len(data) != metadata_size + IMAGE_SECTORS * SECTOR:
        raise ValueError("sprite transfer size differs from the two descriptors")
    start, count, end = struct.unpack_from("<III", data)
    anchor, = struct.unpack_from("<I", data, 0x24)
    start = (start - anchor) & 0xFFFFFFFF
    end = (end - anchor) & 0xFFFFFFFF
    split = start + count * 4
    if start != 0x28 or not count or not start < split <= end <= metadata_size or (end - split) % 8:
        raise ValueError("sprite metadata arrays have invalid bounds")
    for offsets in (range(start, split, 4), range(split + 4, end, 8)):
        for at in offsets:
            pointer, = struct.unpack_from("<I", data, at)
            if ((pointer - anchor) & 0xFFFFFFFF) >= metadata_size:
                raise ValueError("sprite metadata pointer falls outside the read")
    # The uploader uses four tile blocks followed by its palette.
    image = data[metadata_size:]
    if not any(image[:0x8000]) or not any(image[0x8000:]):
        raise ValueError("sprite upload has no tile or palette payload")


def verify_records(manifest, executable, first_lba, volume_size, read):
    if manifest["schema"] != "azure-clean.dungeon-sprite-reads.v1" or manifest["readers"] != reader_hashes(executable):
        raise ValueError("sprite resource reader proof differs from the executable")
    spans = []
    for record in manifest["transfers"]:
        resource_id = record["resource_id"]
        offset, size = transfer(resource_id, first_lba, volume_size)
        if (record["foff"], record["size"]) != (offset, size):
            raise ValueError("sprite read coordinates differ from the two descriptors")
        data = read(offset, size)
        metadata_sectors = THREE_SLOT_METADATA_SECTORS if resource_id == THREE_SLOT_SPECIES else METADATA_SECTORS
        check_payload(data, metadata_sectors)
        spans.append((offset, offset + size))
    spans.sort()
    if not spans or any(end > start for (_, end), (start, _) in zip(spans, spans[1:])):
        raise ValueError("sprite reads are empty or overlap")
    return spans


def town_reader_hashes(retail):
    result = {}
    for name, (address, size) in TOWN_READERS.items():
        start = address - TOWN_ENGINE_DELTA
        # The reservation body is short. Include adjacent bytes so every
        # digest authenticates a window of at least sixteen bytes.
        end = start + max(size, 16)
        if not 0 <= start < end <= len(retail):
            raise ValueError("Town sprite request reader lies outside the container")
        result[name] = hashlib.sha256(retail[start:end]).hexdigest()
    return result


def town_transfers(retail, first_lba):
    result = []
    # The minigame reserves request 2. The pending reader follows it with
    # request 1, then clears the request. Both use catalog index 15 + request.
    catalog = TOWN_RESOURCE_CATALOG - TOWN_ENGINE_DELTA
    if len(retail) < catalog + 18 * 4:
        raise ValueError("Town sprite request catalog lies outside the container")
    for request in (1, 2):
        at = catalog + (15 + request) * 4
        resource_id, = struct.unpack_from("<I", retail, at)
        if resource_id < 58:
            raise ValueError("Town request does not select a Town sprite descriptor")
        lba = 0x1B8D + (resource_id - 58) * (METADATA_SECTORS + IMAGE_SECTORS)
        size = (METADATA_SECTORS + IMAGE_SECTORS) * SECTOR
        offset = (lba - first_lba) * SECTOR
        if not 0 <= offset < offset + size <= len(retail):
            raise ValueError("Town sprite request lies outside its container")
        result.append(dict(request=request, resource_id=resource_id, foff=offset, size=size))
    return result


def verify_town_records(records, retail, first_lba, read):
    if records["readers"] != town_reader_hashes(retail):
        raise ValueError("Town sprite request readers differ from the Town engine")
    expected = town_transfers(retail, first_lba)
    if records["transfers"] != expected:
        raise ValueError("Town sprite requests differ from the Town engine catalog")
    spans = []
    for record in expected:
        start, size = record["foff"], record["size"]
        check_payload(read(start, size))
        spans.append((start, start + size))
    spans.sort()
    if spans[0][1] > spans[1][0]:
        raise ValueError("Town sprite requests overlap")
    return spans


def checked_town_ranges(root, retail):
    manifest = root / MANIFEST
    if not manifest.is_file():
        return []
    records = json.loads(manifest.read_text()).get("town_requests")
    if records is None:
        return []
    disc_path = Path(os.environ.get("AZURE_CLEAN_DISC") or root / "bin/Azure Dreams.bin")
    with Disc(disc_path) as disc:
        first_lba, disk_size = disc.locate(TOWN_VOLUME)
        if disk_size != len(retail):
            raise ValueError("Town sprite volume differs from the registered container")

        def read(offset, size):
            data = retail[offset:offset + size]
            if disc.slice(TOWN_VOLUME, offset, size) != data:
                raise ValueError("Town sprite request differs from the extracted container")
            return data

        return verify_town_records(records, retail, first_lba, read)


def checked_ranges(root, disc_root, executable, volume_size):
    manifest = root / MANIFEST
    if not manifest.is_file():
        return []
    disc_path = Path(os.environ.get("AZURE_CLEAN_DISC") or root / "bin/Azure Dreams.bin")
    with Disc(disc_path) as disc, (disc_root / "work/disc/containers/DUNGEON_DUNGEON.BIN").open("rb") as extracted:
        first_lba, disk_size = disc.locate(VOLUME)
        if disk_size != volume_size:
            raise ValueError("sprite volume differs from the registered container")

        def read(offset, size):
            extracted.seek(offset)
            data = extracted.read(size)
            if disc.slice(VOLUME, offset, size) != data:
                raise ValueError("sprite read differs from the extracted container")
            return data

        return verify_records(json.loads(manifest.read_text()), executable, first_lba, disk_size, read)
