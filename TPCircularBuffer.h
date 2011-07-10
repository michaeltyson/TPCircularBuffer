//
//  TPCircularBuffer.h
//  Circular buffer implementation
//
//  Created by Michael Tyson on 19/03/2011.
//  Copyright 2011 A Tasty Pixel. All rights reserved.
//

typedef struct { 
    int head;
    int tail;
    int fillCount;
    int length;
} TPCircularBufferRecord;

// Initialise record structure
void TPCircularBufferInit(TPCircularBufferRecord *record, int length);

// Obtain fill count
int  TPCircularBufferFillCount(TPCircularBufferRecord *record);

// Obtain fill count for a contiguous area
int  TPCircularBufferFillCountContiguous(TPCircularBufferRecord *record);

// Obtain count of available space
int  TPCircularBufferSpace(TPCircularBufferRecord *record);

// Obtain count of available space for contiguous area
int  TPCircularBufferSpaceContiguous(TPCircularBufferRecord *record);

// Index of the head counter into the corresponding buffer
int  TPCircularBufferHead(TPCircularBufferRecord *record);

// Index of the tail counter into the corresponding buffer
int  TPCircularBufferTail(TPCircularBufferRecord *record);

// Produce data (by increasing the fill count and moving the head counter forwards)
void TPCircularBufferProduce(TPCircularBufferRecord *record, int amount);

// Consume data (by decreasing the fill count and moving the tail counter forwards)
void TPCircularBufferConsume(TPCircularBufferRecord *record, int amount);

// Clear the whole buffer, resetting fill count to zero and pointing the tail counter to the head
void TPCircularBufferClear(TPCircularBufferRecord *record);

// Produce by copying the data ('count' units of 'len' length) in the buffer at 'src' into the circular buffer 'dst'
int  TPCircularBufferCopy(TPCircularBufferRecord *record, void* dst, const void* src, int count, int len);