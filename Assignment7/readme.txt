ASSIGNMENT 7 - HOMEWORK README

I downloaded the file for the SRT implementation provided on the assignment
website. I then proceed to confirm that the current implementation is working.

make clean check
As expected, it fails when there is multithreading since multithreading is not
supported in this implementation and that implementing it is the homework!

We were given the hint that the multithreading would only require changes to
main.c and the Makefile. I identified for loops in the code where multithreading
could be an advantage and speed up the process significantly. Given the values
of threads that were passed in as nthreads, I split up the input data
accordingly.

We can see there in the main method, there is a series of 4 nested for loops
that clearly could be broken up. I allow my method called forloop to handle
this.

I decided to take out an if statement where we do single threading if the value
of nthreads is 1. We are able to handle this when I process splitting up the
input into "1" group, essentially the same thing. With the data then split up,
I created a method to process the inputs with the code previously in the main
method.

I had to change the makefile, as specified in the specs to include -lpthread.
I also had to change the “check” for it to work properly.

After completing this, I ran the same command as I did earlier:
make clean check > ../make-log.txt
less ../make-log.txt

---TIME COMPARISON---
nthreads = 1
  real	0m41.922s
  user	0m41.917s
  sys	0m0.001s
nthreads = 2
  real	0m32.041s
  user	1m3.795s
  sys	0m0.002s
nthreads = 4
  real	0m12.423s
  user	0m47.297s
  sys	0m0.001s
nthreads = 8
  real	0m5.758s
  user	0m44.614s
  sys	0m0.002s

We can see that as the number of threads increase, the time taken will go down.
However, the ratio of time decrease to threads is not proportional due to
buffer required with threading and system calls. 
