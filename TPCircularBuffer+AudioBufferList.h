//
//  TPCircularBuffer+AudioBufferList.h
//  Circular/Ring buffer implementation
//
//  Created by Michael Tyson on 20/03/2012.
//  Copyright 2012 A Tasty Pixel. All rights reserved.
//

#ifndef TPCircularBuffer_AudioBufferList_h
#define TPCircularBuffer_AudioBufferList_h

#ifdef __cplusplus
extern "C" {
#endif

#include "TPCircularBuffer.h"
#include <AudioToolbox/AudioToolbox.h>

int TPCircularBufferProduceAudioBufferList(TPCircularBuffer *buffer, const AudioBufferList *bufferList);

static __inline__ __attribute__((always_inline)) AudioBufferList *TPCircularBufferNextBufferList(TPCircularBuffer *buffer) {
    int32_t dontcare; // Length of segment is contained within buffer list, so we can ignore this
    return TPCircularBufferTail(buffer, &dontcare);
}

static __inline__ __attribute__((always_inline)) void TPCircularBufferConsumeBufferList(TPCircularBuffer *buffer, AudioBufferList *bufferList) {
    long size = ((char*)bufferList->mBuffers[bufferList->mNumberBuffers-1].mData + bufferList->mBuffers[bufferList->mNumberBuffers-1].mDataByteSize) - (char*)bufferList;
    TPCircularBufferConsume(buffer, size);
}

#ifdef __cplusplus
}
#endif

#endif
