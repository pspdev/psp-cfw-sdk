#!/usr/bin/env python3

import os, sys

if len(sys.argv) != 3:
    print("Usage:\n\t %s path_to_resources NAME.PKG"%sys.argv[0])
    exit()

RESOURCES_DIR = sys.argv[1]
RESOURCES = os.listdir(RESOURCES_DIR)

def int2bytes(number):
    hex = '%08X' %(number)

    A = int('0x' + hex[6:8], 16).to_bytes(1, 'little')
    B = int('0x' + hex[4:6], 16).to_bytes(1, 'little')
    C = int('0x' + hex[2:4], 16).to_bytes(1, 'little')
    D = int('0x' + hex[0:2], 16).to_bytes(1, 'little')

    return A + B + C + D

for resource in RESOURCES:
    print("Theme: {}".format(resource))

    CUR_DIR = os.path.join(RESOURCES_DIR, resource)
    RES_DIR = os.path.join(CUR_DIR, 'resources')
    dir = os.listdir(RES_DIR)
    dir.sort()

    DEST_FILE = os.path.join(CUR_DIR, sys.argv[2])

    track = []
    with open(DEST_FILE, 'wb+') as pkg:
        for item in dir:
            track.append(pkg.tell())
            pkg.write(int2bytes(0) + int2bytes(len(item)))
            pkg.write(bytes(item + '\0', "UTF8"))

        pkg.write(bytes.fromhex("FFFFFFFF"))

        track.reverse()

        for item in dir:
            cur = pkg.tell()
            pkg.seek(track.pop())
            pkg.write(int2bytes(cur))
            pkg.seek(cur)

            with open(os.path.join(RES_DIR, item), 'rb') as fd:
                pkg.write(fd.read())
