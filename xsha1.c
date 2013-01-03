/*
MBNCSUtil -- Managed Battle.net Authentication Library
Copyright (C) 2005-2008 by Robert Paveza
X-SHA-1 ported to C by wjlafrance, January 3rd 2013.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1.) Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.
2.) Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.
3.) The name of the author may not be used to endorse or promote products derived
from this software without specific prior written permission.

See LICENSE.TXT that should have accompanied this software for full terms and
conditions.
*/

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define ROTATE e = d; d = c; c = ROL(b, 30); b = a; a = g;

uint32_t ROL(uint32_t val, uint32_t shift) {
    shift &= 0x1f;
    val = (val >> (0x20 - shift)) | (val << shift);
    return val;
}

void xsha1_calcHashBuf(const char* input, size_t length, uint32_t* result) {
    void *dataptr = malloc(1024);
    uint32_t *data = (uint32_t *) dataptr;
    memcpy(data, input, length);

    for (int i = 0; i < 64; i++) {
        data[i + 16] = ROL(1, (int) (data[i] ^ data[i + 8] ^ data[i + 2] ^ data[i + 13]) % 32);
    }

    uint32_t a = 0x67452301;
    uint32_t b = 0xefcdab89;
    uint32_t c = 0x98badcfe;
    uint32_t d = 0x10325476;
    uint32_t e = 0xc3d2e1f0;
    uint32_t g = 0;

    for (int i = 0; i < 20; i++) {
        g = *data++ + ROL(a, 5) + e + ((b & c) | (~b & d)) + 0x5A827999; ROTATE;
    }

    for (int i = 0; i < 20; i++) {
        g = (d ^ c ^ b) + e + ROL(g, 5) + *data++ + 0x6ed9eba1; ROTATE;
    }

    for (int i = 0; i < 20; i++) {
        g = *data++ + ROL(g, 5) + e + ((c & b) | (d & c) | (d & b)) - 0x70E44324; ROTATE;
    }

    for (int i = 0; i < 20; i++) {
        g = (d ^ c ^ b) + e + ROL(g, 5) + *data++ - 0x359d3e2a; ROTATE;
    }

    *result++ = 0x67452301 + a;
    *result++ = 0xefcdab89 + b;
    *result++ = 0x98badcfe + c;
    *result++ = 0x10325476 + d;
    *result   = 0xc3d2e1f0 + e;

    free(dataptr);
}
