//
//  TPCircularBuffer+AudioBufferList.c
//  Circular/Ring buffer implementation
//
//  Created by Michael Tyson on 20/03/2012.
//  Copyright 2012 A Tasty Pixel. All rights reserved.
//

#include "TPCircularBuffer+AudioBufferList.h"

int TPCircularBufferProduceAudioBufferList(TPCircularBuffer *buffer, const AudioBufferList *bufferList) {
    int32_t availableBytes;
    AudioBufferList *list = (AudioBufferList*)TPCircularBufferHead(buffer, &availableBytes);
    
    int bufferListSize = sizeof(AudioBufferList) + ((bufferList->mNumberBuffers-1) * sizeof(AudioBuffer));
    
    if ( availableBytes < bufferListSize ) return NO;
    memcpy(list, bufferList, bufferListSize);
    
    char *dataPtr = (char*)list + bufferListSize;
    for ( int i=0; i<bufferList->mNumberBuffers; i++ ) {
        // Find the next 16-byte aligned memory area
        if ( (long)dataPtr & 0xF ) {
            dataPtr += 0x10 - ((long)dataPtr & 0xF);
        }
        
        if ( (dataPtr + bufferList->mBuffers[i].mDataByteSize) - (char*)list > availableBytes ) {
            return NO;
        }
        
        list->mBuffers[i].mData = dataPtr;
        memcpy(dataPtr, bufferList->mBuffers[i].mData, bufferList->mBuffers[i].mDataByteSize);
        dataPtr += bufferList->mBuffers[i].mDataByteSize;
    }
    
    TPCircularBufferProduce(buffer, dataPtr-(char*)list);
    
    return YES;
}

