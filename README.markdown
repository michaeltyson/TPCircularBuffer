A simple, fast circular buffer implementation for audio processing
==================================================================

A simple C implementation for a circular (ring) buffer. Thread-safe with a single producer and a single consumer, using the fast OSAtomic.h primitives.

Usage
-----

Producing: Use TPCircularBufferProduce to put data into the buffer (starting at the offset indicated by TPCircularBufferHead, with TPCircularBufferSpace units of space available).  TPCircularBufferProduceBytes is a convenience routine for putting in data that’s coming straight from a buffer.

Consuming: Use TPCircularBufferConsume to pull data out the other end (starting from the offset indicated by TPCircularBufferTail, and of length indicated by TPCircularBufferFillCount).

Thread safety
-------------

As long as you restrict multithreaded access to just one producer, and just one consumer, this utility should be thread safe.

The routines under the heading "Reading" (in TPCircularBuffer.h) should only ever be used by one thread at a time; the same applies to those marked "Writing".

Other routines, except for TPCircularBufferInit and TPCircularBufferClear, can be accessed concurrently without issue.

-----------------------------------------------------

See more info at [atastypixel.com](http://atastypixel.com/blog/a-simple-fast-circular-buffer-implementation-for-audio-processing/)

Michael Tyson  
A Tasty Pixel