# Huffman-Code

Lossless text compression app using the Huffman code algorithm for text compression. 

I heard about Huffman Code from an Information theory course in university. Even back than I thought that it is going to be an interesting project to create a text compression app. It turned out even better than expected. 

## Structures implemented
* **Efficient bit stack**. You can operate with it on a bit level, but internally it stores data on byte level, which makes it more memory efficient (you don't need 1 byte to represent 1 bit like boolean variables).
* **Huffman tree**. It is used to create the encodings for each characters. When decoding a compressed file we use it like a finite state automata, which makes decoding linear in time. The tree is created in a deterministic way (same files create same trees).
* **Bitwise I/O**. In order to be efficient with memory I had to create my own protocol for saving and reconstructing data in binary files. I worked on bit level once again and padding is used only on the very last byte of the compressed file.

## Results
* 4.9MB of English words -> 2.7MB in compressed format.
* 4.9MB of random characters [a-z] and numbers [0-9] -> 3.6MB in compressed format.
* 5.1MB od random ASCII -> 4.5MB in compressed format.

As expected compressing natural text is more efficient as there are symbols and letters which come up, much more often than others. On the other hand compressing random characters and numbers works better than random ASCII as the range of values in the second case is bigger. 