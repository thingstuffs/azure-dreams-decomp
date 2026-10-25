"""Bounded implementation of the resident decompress_lz bit grammar.

Flags are consumed least significant bit first and interleaved with data.
A zero flag emits a literal; 10 is a long reference (or zero terminator),
11 plus two bits is a short reference. References may overlap output.
The encoder uses greedy longest matches, nearest ties, a 4095-byte history,
and a fresh dictionary for each stream. Retail identity is proved per stream.
"""

def decode(data, limit):
    if not isinstance(limit, int) or limit < 0:
        raise ValueError('invalid decoded limit')
    cursor = flags = bits = 0
    output = bytearray()

    def byte():
        nonlocal cursor
        if cursor >= len(data):
            raise ValueError('truncated compressed stream')
        value = data[cursor]
        cursor += 1
        return value

    def bit():
        nonlocal flags, bits
        if not bits:
            flags, bits = byte(), 8
        value = flags & 1
        flags >>= 1
        bits -= 1
        return value

    while True:
        if not bit():
            if len(output) >= limit:
                raise ValueError('decoded size exceeds limit')
            output.append(byte())
            continue
        if not bit():
            token = (byte() << 8) | byte()
            if not token:
                return bytes(output), cursor
            count = (token & 15) + 2 if token & 15 else byte() + 1
            distance = token >> 4
        else:
            count = (bit() << 1) + 2 + bit()
            distance = byte() or 256
        if not distance or distance > len(output):
            raise ValueError('invalid backward reference')
        if len(output) + count > limit:
            raise ValueError('decoded size exceeds limit')
        for _ in range(count):
            output.append(output[-distance])


def encode(data):
    from collections import defaultdict, deque
    output, index = bytearray(), defaultdict(deque)
    flag, bits, position = -1, 8, 0

    def bit(value):
        nonlocal flag, bits
        if bits == 8:
            flag, bits = len(output), 0
            output.append(0)
        output[flag] |= value << bits
        bits += 1

    while position < len(data):
        length, distance = 1, 0
        candidates = index[data[position:position+2]]
        while candidates and candidates[0] < position - 4095:
            candidates.popleft()
        maximum = min(256, len(data) - position)
        for previous in reversed(candidates):
            count, back = 0, position - previous
            while count < maximum and data[previous+count] == data[position+count]:
                count += 1
            if count > length and (count >= 3 or back <= 256):
                length, distance = count, back
                if length == maximum:
                    break
        if length == 1:
            bit(0)
            output.append(data[position])
        else:
            bit(1)
            if distance <= 256 and length <= 5:
                bit(1)
                bit((length - 2) >> 1)
                bit((length - 2) & 1)
                output.append(distance & 255)
            else:
                bit(0)
                token = (distance << 4) | (length - 2 if length <= 17 else 0)
                output.extend((token >> 8, token & 255))
                if length > 17:
                    output.append(length - 1)
        for cursor in range(position, position + length):
            index[data[cursor:cursor+2]].append(cursor)
        position += length
    bit(1)
    bit(0)
    output.extend((0, 0))
    return bytes(output)
