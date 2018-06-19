Zhengfu Ding 104928991

Assignment 6. Multithreaded performance

In the original srt main.c file, the implementation was originally that of a single thread. Multi-threading was not option that was implemented into the original solution. 

In order to add multi-threading, I created an input number of pthreads and divided the columns of the pixels to trace between them. I created a 3D array scaled_color to hold the pixels values after the threads were joined. The image was traced so that each thread was designated unique pixels. This was done by starting each thread on its thread number and iterating by the number of threads. I also made number of threads nthreads and scene global variables because each thread needed to read this data. I also created local array that tracked the pthreads and their thread numbers. These arrays were used to join the threads after tracing and assign each thread its associated pixel. After joining all threads, I printed the pixels using the scaled_color array.

Due to my multi-threaded implementation, the performance of the program increased. Using parallism, the real time of the srt program decreased as the number of threads increased.
