//
//  TPCircularBuffer.h
//  Circular/Ring buffer implementation
//
//  Created by Michael Tyson on 10/12/2011.
//  Copyright 2011 A Tasty Pixel. All rights reserved.
//
//
//  This implementation makes use of a virtual memory mapping technique that inserts a virtual copy
//  of the buffer memory directly after the buffer's end, negating the need for any buffer wrap-around
//  logic. Clients can simply use the returned memory address as if it were contiguous space.
//  
//  The implementation is thread-safe in the case of a single producer and single consumer.
//
//  Virtual memory technique originally proposed by Philip Howard (http://vrb.slashusr.org/), and
//  adapted to Darwin by Kurt Revis (http://www.snoize.com,
//  http://www.snoize.com/Code/PlayBufferedSoundFile.tar.gz)
//
//  Redistribution and use in source and binary forms, with or without modification, are permitted
//  freely. Credit is appreciated, but not required.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS 
//  OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY 
//  AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR 
//  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
//  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF 
//  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
//  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
//  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <libkern/OSAtomic.h>

typedef struct {
    void             *buffer;
    int32_t           length;
    int32_t           tail;
    int32_t           head;
    volatile int32_t  fillCount;
} TPCircularBuffer;

bool  TPCircularBufferInit(TPCircularBuffer *buffer, int32_t length);
void  TPCircularBufferCleanup(TPCircularBuffer *buffer);
void  TPCircularBufferClear(TPCircularBuffer *buffer);

// Reading (consuming)
void* TPCircularBufferTail(TPCircularBuffer *buffer, int32_t* availableBytes);
void  TPCircularBufferConsume(TPCircularBuffer *buffer, int32_t amount);

// Writing (producing)
void* TPCircularBufferHead(TPCircularBuffer *buffer, int32_t* availableBytes);
void  TPCircularBufferProduce(TPCircularBuffer *buffer, int32_t amount);
int   TPCircularBufferProduceBytes(TPCircularBuffer *buffer, const void* src, int32_t len);
