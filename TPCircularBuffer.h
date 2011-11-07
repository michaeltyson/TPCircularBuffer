//
//  TPCircularBuffer.h
//  Circular buffer implementation
//
//  Created by Michael Tyson on 19/03/2011.
//  Copyright 2011 A Tasty Pixel. All rights reserved.
//

#include <libkern/OSAtomic.h>

typedef struct { 
    int32_t head;
    int32_t tail;
    volatile int32_t fillCount;
    int32_t length;
} TPCircularBufferRecord;

void TPCircularBufferInit(TPCircularBufferRecord *record, int length);
void TPCircularBufferClear(TPCircularBufferRecord *record);

int  TPCircularBufferFillCount(TPCircularBufferRecord *record);
int  TPCircularBufferFillCountContiguous(TPCircularBufferRecord *record);
int  TPCircularBufferSpace(TPCircularBufferRecord *record);
int  TPCircularBufferSpaceContiguous(TPCircularBufferRecord *record);

// Reading (consuming)
int  TPCircularBufferTail(TPCircularBufferRecord *record);
void TPCircularBufferConsume(TPCircularBufferRecord *record, int amount);
void TPCircularBufferConsumeSingleThread(TPCircularBufferRecord *record, int amount);

// Writing (producing)
int  TPCircularBufferHead(TPCircularBufferRecord *record);
void TPCircularBufferProduce(TPCircularBufferRecord *record, int amount);
void TPCircularBufferProduceSingleThread(TPCircularBufferRecord *record, int amount);
int  TPCircularBufferProduceBytes(TPCircularBufferRecord *record, void* dst, const void* src, int count, int len);
