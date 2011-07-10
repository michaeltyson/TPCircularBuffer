A simple, fast circular buffer implementation for audio processing
==================================================================

Circular buffers are pretty much what they sound like – arrays that wrap around. They’re fantastically useful as scratch space for audio processing, and generally passing audio around efficiently.

They work really well in a FIFO (first-in-first-out) context, like storing audio coming in the microphone for later playback or processing.

Consider a naive alternative: You copy the incoming audio into an NSData you allocate, and then pass that NSData off. This means you’re allocating memory each time, and deallocating the memory later once you’re done processing. That allocation incurs a penalty, which can be a show-stopper when part of an audio pipeline – The Core Audio documentation advises against any allocations when within a render callback, for example.

Alternatively, you can allocate space in advance, and write to that, but that has problems too: Either you have a synchronisation nightmare, or you spend lots of time moving bytes around so that the unprocessed audio is always at the beginning of the array.

A better solution is to use a circular buffer, where data goes in at the head, and is read from the tail. When you produce data at the head, the head moves up the array, and wraps around at the end. When you consume at the tail, the tail moves up too, so the tail chases the head around the circle.

This is a simple C implementation I recently put together.

Use TPCircularBufferProduce to put data into the buffer (starting at the offset indicated by TPCircularBufferHead, with TPCircularBufferSpace units of space available), and TPCircularBufferConsume to pull it out the other end (starting from the offset indicated by TPCircularBufferTail, and of length indicated by TPCircularBufferFillCount).

TPCircularBufferCopy is a convenience routine for putting in data that’s coming straight from a buffer.

See more info at [atastypixel.com](http://atastypixel.com/blog/a-simple-fast-circular-buffer-implementation-for-audio-processing/)

Michael Tyson  
A Tasty Pixel