# Fancy_Ft_Malloc

This project is a **malloc** implementation written using the [42Paris' subject](https://github.com/AugustinLopez/Fancy_Ft_Malloc/blob/main/resources/en_subject_malloc.pdf) as reference. It is *Fancy* because even if I already had a working one, I decided to remake it entirely. At least it looks good to me.


## The *42 Ways* of doing things
Most basic function are reimplemented from scratch instead of relying on the standard library. Dependencies are limited to a few syscalls such as **write** or **mmap**.

My files also follows the current *42 Norms*, which is starting to become debilitating and will probably become unecessary in the near future.

## Features
Homemade implementation of standard functions:
- **malloc**, **free** and **realloc**

Memory display of my structure:
- **show_alloc_mem** / **show_alloc_mem_ex**

Several personal environnment variables: 
- **FtMallocZone**: using every power of 2 between 16 and 4096 for allocation instead of the TINY, SMALL things that the subject ask us to do;
- **FtMallocLog**: log the state of the malloc datastructure in a .txt file; *Access permissions are not set when created by the program: created file might not have R/W rights*
- **FtMallocScribble**: fill the freed zone with 0xAA; *Causes crash (sometimes ?) when used with ./run.sh*
- **FtMallocPreScribble**: fill a newly allocated zone with 0xAA;
- **FtMallocGuard**: protect malloc metadata with PROT_NONE pages.
```sh
$ export FtMallocZone=1
```
## Datastructure

I wanted my model to handle allocation size between 1 and 2048 bytes with as little metadata as possible, using hypothesis that are largely shared among computer (but not portable according to the C Standard). 

To do so, my model will allocate a zone of memory for every power of 2 between 16 and 2048*, which guarantee that at least 50% of a given memory block is actually used. My zone's metadata fit in 256 bytes, and I can fit 15 of them in a single page (the 256 bytes left are the metadata's ... metadata). I don't have alignment problem, and since my metadata is isolated from the memory allocation, I can protect it against accidental overwrite. I use between 1.025 and 2.025 bytes of metadata by address, largely because I need to keep track of the size of the allocation.

This model is far from perfect (especially with large allocation), but I am content with what I could achieve in a 2 weeks time window. Check the image for the general idea.

\* *4096 actually, because it fit in my datastructure without further development*

![My malloc datastructure](https://github.com/AugustinLopez/Fancy_Ft_Malloc/blob/main/resources/malloc_graph.png)

## What about fragmentation ?

If I want to keep my metadata segregated from my actual allocation while keeping memory alignment, I don't think fragmentation is a good solution until an allocation of more than half a page (2049 bytes on system I care about). This is beyond the scope of what I need/want to do.
