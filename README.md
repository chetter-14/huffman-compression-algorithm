# Huffman compression algorithm 

## About project

It is a project for compressing and decompressing files with Huffman algorithm. To get a brief insight on what Huffman algorithm is 
you can watch this [video](https://www.youtube.com/watch?v=JsTptu56GM8). 

## Details on implementation

There are 5 main steps in the execution algorithm of this program:
1. Read the file we want to compress, count frequencies of all the characters in there and build a frequency map.
2. Using a frequency map we insert those values into a priority queue and from the priority queue form an encoding (huffman) tree.
3. We make an encoding map from the encoding tree (by traversing the tree). So we get characters and their appropriate huffman codes.
4. Here we read the characters from the initial file and via the encoding map we write these bits representations of characters into 
the result (compressed) file. 	
	- Important note, at first we write a frequency table into the compressed file in order to be able to read
	the file content the next time (maybe we just want to decompress a file and in such a situation we don't have any encoding maps, 
	trees, etc. So here we use the frequency table in a file header).
5. (Optional one) Reading the compressed file: 
	- Read a frequency table from the file header.
	- Build an encoding map from the frequency table (steps 2-3).
	- Using the encoding map read data from the compressed file and write corresponding characters to the result file (decompressed one).

## Resources, links

The project is mostly built on information and details described 
[here](https://web.stanford.edu/class/archive/cs/cs106b/cs106b.1176//assn/huffman.html). 
