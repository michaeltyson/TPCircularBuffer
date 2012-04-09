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

/*!
 * Copy the audio buffer list onto the buffer
 *
 * @param buffer Circular buffer
 * @param bufferList Buffer list containing audio to copy to buffer
 * @return YES if buffer list was successfully copied; NO if there was insufficient space
 */
BOOL TPCircularBufferProduceAudioBufferList(TPCircularBuffer *buffer, const AudioBufferList *bufferList);

/*!
 * Get a pointer to the next stored buffer list
 *
 * @param buffer Circular buffer
 * @return Pointer to the next buffer list in the buffer
 */
static __inline__ __attribute__((always_inline)) AudioBufferList *TPCircularBufferNextBufferList(TPCircularBuffer *buffer) {
    int32_t dontcare; // Length of segment is contained within buffer list, so we can ignore this
    return TPCircularBufferTail(buffer, &dontcare);
}

/*!
 * Consume the next buffer list
 *
 * @param buffer Circular buffer
 * @param bufferList The buffer list to consume (must be the most recent value from TPCircularBufferNextBufferList)
 */
static __inline__ __attribute__((always_inline)) void TPCircularBufferConsumeBufferList(TPCircularBuffer *buffer, AudioBufferList *bufferList) {
    long size = ((char*)bufferList->mBuffers[bufferList->mNumberBuffers-1].mData + bufferList->mBuffers[bufferList->mNumberBuffers-1].mDataByteSize) - (char*)bufferList;
    TPCircularBufferConsume(buffer, size);
}

#ifdef __cplusplus
}
#endif

#endif
