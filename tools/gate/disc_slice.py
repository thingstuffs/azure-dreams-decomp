"""Bounded ISO9660 file slices from a user's 2048-byte ISO or raw PlayStation BIN.

No retail offsets are hard-coded: directory records supply the container extents.
Multi-extent/interleaved files are refused rather than guessed.
"""
import struct


class Disc:
    def __init__(self, path):
        self.file = open(path, "rb")
        self.cache = {}
        for self.sector, self.payload in ((2048, 0), (2352, 24), (2352, 16)):
            self.file.seek(16*self.sector+self.payload)
            pvd = self.file.read(2048)
            if len(pvd) == 2048 and pvd[:7] == b"\x01CD001\x01":
                self.root = (struct.unpack_from("<I", pvd, 158)[0], struct.unpack_from("<I", pvd, 166)[0])
                return
        self.close()
        raise ValueError("not a supported ISO9660 disc (ISO/2048 or BIN/2352)")

    def close(self):
        self.file.close()

    def __enter__(self):
        return self

    def __exit__(self, *args):
        self.close()

    def logical(self, lba, offset, size):
        if min(lba, offset, size) < 0:
            raise ValueError("negative disc read")
        out = bytearray()
        while size:
            sector, inner = divmod(offset, 2048)
            count = min(size, 2048-inner)
            self.file.seek((lba+sector)*self.sector+self.payload+inner)
            b = self.file.read(count)
            if len(b) != count:
                raise ValueError("truncated disc sector")
            out.extend(b)
            offset += count
            size -= count
        return bytes(out)

    def directory(self, extent):
        if extent in self.cache:
            return self.cache[extent]
        lba, size = extent
        if size > 16*1024*1024:
            raise ValueError("unreasonable ISO directory size")
        data, out, i = self.logical(lba, 0, size), {}, 0
        while i < len(data):
            n = data[i]
            if n == 0:
                i = (i//2048+1)*2048
                continue
            if n < 34 or i+n > len(data) or i%2048+n > 2048 or 33+data[i+32] > n:
                raise ValueError("malformed ISO directory record")
            name = data[i+33:i+33+data[i+32]]
            if name not in (b"\x00", b"\x01"):
                if data[i+26] or data[i+27] or data[i+25] & 0x80 or data[i+1]:
                    raise ValueError("interleaved/multi-extent/extended ISO file unsupported")
                name = name.decode("ascii").split(";", 1)[0].upper()
                if name in out:
                    raise ValueError("ambiguous ISO file name: " + name)
                out[name] = (struct.unpack_from("<I", data, i+2)[0], struct.unpack_from("<I", data, i+10)[0], bool(data[i+25]&2))
            i += n
        self.cache[extent] = out
        return out

    def locate(self, path):
        parts = path.upper().split("/")
        extent = self.root
        for n, part in enumerate(parts):
            if part in ("", ".", ".."):
                raise ValueError("unsafe disc path")
            if part not in self.directory(extent):
                raise ValueError("disc file missing: " + path)
            lba, size, directory = self.directory(extent)[part]
            if directory != (n < len(parts)-1):
                raise ValueError("disc path type differs: " + path)
            extent = (lba, size)
        return extent

    def slice(self, path, offset, size):
        lba, length = self.locate(path)
        if offset < 0 or size < 0 or offset+size > length:
            raise ValueError("asset slice outside disc file: " + path)
        return self.logical(lba, offset, size)
