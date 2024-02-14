//
//  TPCircularBuffer.c
//  Circular/Ring buffer implementation
//
//  https://github.com/michaeltyson/TPCircularBuffer
//
//  Created by Michael Tyson on 10/12/2011.
//
//  Copyright (C) 2012-2013 A Tasty Pixel
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the authors be held liable for any damages
//  arising from the use of this software.
//
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//     claim that you wrote the original software. If you use this software
//     in a product, an acknowledgment in the product documentation would be
//     appreciated but is not required.
//
//  2. Altered source versions must be plainly marked as such, and must not be
//     misrepresented as being the original software.
//
//  3. This notice may not be removed or altered from any source distribution.
//

#include "TPCircularBuffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

bool _TPCircularBufferInit(TPCircularBuffer *buffer, uint32_t length, size_t structSize) {
    
    assert(length > 0);
    
    if (structSize != sizeof(TPCircularBuffer)) {
        fprintf(stderr, "TPCircularBuffer: Header version mismatch. Check for old versions of TPCircularBuffer in your project\n");
        abort();
    }
    
    // Round length up to the nearest page size
    long pageSize = sysconf(_SC_PAGESIZE);
    uint32_t roundedLength = (length + pageSize - 1) & ~(pageSize - 1);

    buffer->length = roundedLength;

    // Allocate memory using mmap. MAP_ANONYMOUS means the mapping is not backed by any file; its content is initialized to zero.
    buffer->buffer = mmap(NULL, buffer->length, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (buffer->buffer == MAP_FAILED) {
        perror("Buffer allocation");
        return false;
    }

    buffer->fillCount = 0;
    buffer->head = buffer->tail = 0;
    buffer->atomic = true;

    return true;
}

void TPCircularBufferCleanup(TPCircularBuffer *buffer) {
    if (buffer->buffer) {
        munmap(buffer->buffer, buffer->length);
    }
    memset(buffer, 0, sizeof(TPCircularBuffer));
}

void TPCircularBufferClear(TPCircularBuffer *buffer) {
    uint32_t fillCount;
    if (TPCircularBufferTail(buffer, &fillCount)) {
        TPCircularBufferConsume(buffer, fillCount);
    }
}

void TPCircularBufferSetAtomic(TPCircularBuffer *buffer, bool atomic) {
    buffer->atomic = atomic;
}
