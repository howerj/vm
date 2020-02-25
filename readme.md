# Project Oberon-like (Jorgen)

| Project   | Jorgen: An system like Project Oberon      |
| --------- | ------------------------------------------ |
| Author    | Richard James Howe                         |
| Copyright | 2019 Richard James Howe                    |
| License   | MIT                                        |
| Email     | howe.r.j.89@gmail.com                      |
| Website   | <https://github.com/howerj/vm>             |

**This is a work in progress, it is liable to not be complete, not work, or not
make sense**


	       _                            
	      | |                           
	      | | ___  _ __ __ _  ___ _ __  
	  _   | |/ _ \| '__/ _` |/ _ \ '_ \ 
	 | |__| | (_) | | | (_| |  __/ | | |
	  \____/ \___/|_|  \__, |\___|_| |_|
			    __/ |           
			   |___/            


Project goals:
* Make an Oberon like language that compiles to a virtual machine that could,
  in principle, be ported to an FPGA.
  - The language should have *optional* garbage collection, manual
    allocation/deallocation, or none.
  - There may be a few extensions (attributes, reflection, multiple return
  values, more tools for proofs and assertions).
* Design a Unix like kernel
  - Similar to Plan 9
  - With a few more security related system calls:
    - unveil
    - restrict future system calls
* Port the system to an FPGA
  - My Forth CPU system <https://github.com/howerj/forth-cpu> could be used as
    basis for some of the peripherals

## To Do

* [ ] Add project documentation
* [ ] Implement a Virtual Machine
  * [ ] UART
  * [ ] Timer
  * [ ] Interrupts
  * [ ] Mass storage interface
* [ ] Make a simple compiler for it
  * [ ] Make test programs to exercise the virtual machine
  * [ ] Port trivial programs
* [ ] Improve Virtual Machine
  * [ ] Add Virtual Memory to the Virtual Machine
  * [ ] Graphics
  * [ ] Mouse
  * [ ] Sound
* [ ] Make a Kernel for the Virtual Machine

## Oberon Language

* Simplify certain things; no special character for private, use a capital
  first letter
* Add built in floating point numbers later, if at all, provide a library for Q
  numbers (Q32.32, or Q16.16).
* As many things as possible should be specified; the system integer width, the
  alignment of things in memory, how signed integers should wrap, etcetera. C
  is underspecified, and allows lots of undefined behaviour, this language
  would not.
* 64-bit only
* The language would have a much larger series of libraries, and language
features could be added as a library

## Major new language features:
* Multiple return values
* Function overloading
* Allow functions that are not nested to be returned from functions as a
  function pointer
* *optional* garbage collection; this could make it competitive with C
* A mechanism for specifying attributes; some the compiler may know about, for
  example to specify alignment, or to specify that a function is pure, some it 
  may not know about and would be user defined.
* Do not use shouty case for keywords
* UTF-8, enumerations (Maybe)

## References

* <http://www.projectoberon.com/>
* <https://en.wikipedia.org/wiki/Oberon_%28operating_system%29>
* <https://www.inf.ethz.ch/personal/wirth/ProjectOberon/index.html>
* <https://9p.io/plan9>
* <https://en.wikipedia.org/wiki/Plan_9_from_Bell_Labs>
* <https://en.wikipedia.org/wiki/PL/0>
* <https://github.com/mit-pdos/xv6-public>
* <https://en.wikipedia.org/wiki/Xv6>
* <https://pdos.csail.mit.edu/6.828/2018/xv6.html>
* <http://aiju.de/plan_9/plan9-syscalls>
* <https://en.wikipedia.org/wiki/MINIX>
* <https://www.minix3.org/>
* <https://wiki.osdev.org/Expanded_Main_Page>
* <https://github.com/vtereshkov/xdpw>

Additional system calls:

* unveil only parts of the file system: <https://man.openbsd.org/unveil>
* mmap <http://man7.org/linux/man-pages/man2/mmap.2.html>
* pledge <https://man.openbsd.org/pledge.2>
* tame <https://man.openbsd.org/OpenBSD-5.8/man2/tame.2>

## Extended Project Plan / Rant

The project has a few goals, but it is here mostly because the author wants to
learn more about (Unix) operating systems and languages than because the system
would be useful. It is a very ambitious project but it requires dedication more
than anything. The first goal is to specify a simple virtual machine, one that
could potentially be turned into something that could run on an FPGA, and write
a cross compiler for it in C for an [Oberon][] *like* language. This would then
be used to make a Plan 9/Unix like kernel for the system, which could then be
used to build up the user land. This is much easier said then done. I just want
to create a Unix that is better put together than current Unix systems. I aim
*not* to be POSIX compliant, and will make tools the way I thin they should
work (for example the '[dd][]' command is ridiculous, and the '[cut][]' command
works in a way that is much less useful than it could be).

The language itself used as the system programming language would be my own
take on [Oberon][], there are things I like and things I dislike about
[Pascal][] languages and [Oberon][] in particular. One thing I dislike about
[Oberon][] is that it uses garbage collection and it is mandatory, in the
variant I aim to create garbage collection would be optional. I believe the
easiest way to do this to simply allow an allocator to be passed into the
constructor for the object being created. The GC heap and the manually
allocated heap could coexist in the same space.

One of the reasons for using basing the system programming language on
[Oberon][] instead of on [C][] is that there are many deficiencies in [C][]
that no longer need to be present, and the language is just too unsafe. It has
a bad reputation at the moment and there is no need to make another Unix like
written in the same language, there are already other toy systems out there
that do the same.

The new language would be a 64-bit only system, the size of all integers,
pointers (which would not usually be accessed directly), floating point numbers
(if supported) would all be 64-bit. The only other type would be a byte, arrays
of which could be used for characters, like in C.

The language really does make the system. As I have mentioned, option garbage
collection is a mandatory feature. I would also like support coroutines, which
is a language feature that is missing from standard C, but it is very useful in
embedded contexts. It allows the creation of cooperative multithreading within
programs, or by making data pipes within a program, where one module yields to
the other when it has new data for it (like in Unix pipes).

Other handy features would be a fixed and standardized structure layout, which
makes (lazy) serialization and deserialization easier.

Some of the things I like about [Oberon][] are:

* It has nested function definitions
* The grammar is easy to parse (and therefore it is easy to write tooling for
  it, and quick to parse)
* Compilation of the language it quick and the compile is small <10,000 LoC.
* The language is well defined, compact, and small.
* Pascal strings are in ways better than NUL terminated strings, especially if
  the length specifier is a 64-bit value.

Some of the things that I think are missing from it:

* Function overloading (low priority).
* Optional/Default function arguments.
* Generics (low priority, difficult to implement correctly).
* Optional garbage collection and better control over allocation. 
This could be achieved by passing an allocator to the constructor. 
The C like allocator equivalent in this language could also be better than the
one provided by C, you should be able to query the size of the allocation that
backs a pointer, be able to create memory pools, query the pool to check if a
pointer belongs to it, and more.
* Enumerated types, which are not vital but are really handy.
* Coroutines.
* Standardized structure/record layout. This allows for easier (lazy)
  serialization of data structures.
* Multiple return values for functions, this would also allow for a grammatical 
  mechanism to extract the carry flag from an addition as well as making error
  handling easier.
* Non-nested functions can be passed around as function pointers and returned
  from functions.
* A bigger standard library, which will be described later.
* Nested namespaces/modules.
* A method for specifying arbitrary attributes, which could be used for
  optimization pragmas, alignment, placing functions in various sections,
  etcetera.
* An *optional* method for querying the types of objects at run time, allowing 
  run time reflect (low priority)
* Early returns would be allowed. 'assert' would be a keyword, as would
'implies'. It might be worth adding a 'finally' to functions, which could
also be used to specify post conditions easy, pre conditions are easy to
specify but with multiple returns post conditions are now.
 
Some of the things I would change

* Make the language more [C][] like in that fact it would use '{' and '}'
  instead of 'BEGIN' and 'END'. Some of the superficial aspects of the language
  could be made to be more C like.
* Shouty case should not be used for key words
* A private member could be indicated by the capitalization of the first letter
  and not by a '\*'. This, along with banning the underscore character from
  names, would mean that the naming convention for variables could be
  standardized.
* Again, Optional garbage collection, because it is so important for a system
  programming language to be taken seriously.

The library for the language would be split into three sections:

1. The bare minimum needed for any system, whether it is a hosted system or 
not. This would include things functions for traps, direct memory access,
system timers, coroutine functions, mutexs and semaphores, memory allocation 
and garbage collection routines as well as some other function like intrinsics.
2. The hosted standard library would include functionality that is not expected
to change in a long time and is pretty much an accepted standard, and is pretty
much common to all operating systems, or could be standardized for this
language. This would include a regex engine, a standard virtual machine, a
standard [sqlite][] like database, a constant database like [CDB][], string
manipulation functions, a library for data structures and general purposes
algorithms, Q-Format number library, a file access function set, the compiler
and linker itself, an EBNF parser generator, and perhaps networking
functionality. Non-blocking and blocking File based I/O would also go here.
3. The outer section of libraries would include more operating system specific
functionality, which changes depending on the system and over time, and modules
for dealing with other standards such as HTTP, MQTT, UTF-8, and the like. The
set of functionality here is a candidate for being managed by the languages or
systems package manager, and not part of any standardization effort of the
language itself.

In section 2 there is something that should be elaborated on more, the standard
virtual machine. I think it is important even for a language designed to be
compiled to a physical machine to have a standard virtual machine. Note also
that I believe the compiler for the language itself should be included in the
library. These two facts are important together.

The virtual machine itself should basically be the same machine as the physical
machine that I am designing, perhaps the hardware itself should include
virtualization features that enable 'VM code' to be run on the hardware. Each
language seems to define its own virtual machine, and any virtualization effort
imposes an overhead. It seems logical to define a virtual machine that is the
same as the underlying hardware of at least one architecture than to define a
virtual machine that is the same as the hardware of no-architectures. This
means that the VM runs slowly on 'N - 1' systems instead instead of on 'N' 
systems.

The compiler and linker in the standard library should have at minimum two
targets; the system that the language run time is running on and the standard
library virtual machine.

The reason for the standard library virtual machine is an obvious one, one way
of speeding up many things is to compile functionality into a virtual machine,
this goes for regular expressions, higher level languages like Lisp, AWK or 
TCL, EBNF code generators, and even database queries. By including a standard
virtual machine into the language library, all of these functions have a
standard machine they can target. The virtual machine, like the hardware itself
and like the hardware in Project Oberon, should be simple and easy to
implement.

The reason for including a standard SQLite like database into the library is
that such a library could have many uses; from use as a file system layer (or
at least as an impromptu one for embedded systems), as an Executable and
Linking format for object code (replacing ELF and PE), and as an archival
format (replacing 'tar' and 'ar'), as a file format for a Git/Fossil like
distributed version control, and of course as a general purpose file format for
storing structured data in it. The query language built on top of the
database layer could target the standard virtual machine as well.

If the executable format is the same as this DB format, then applications could
be distributed as a single file; the executable, configuration files, assets,
help files/manual pages, and saved data could all be stored in the same DB.
This would certainly ease installation of apps. The file permissions would
perhaps need to be stored separately. It may be worth creating a single user
for each application. This format would only be used for 'apps' and not for
system binaries like 'ls' or 'cmp'.

As for the Unix system, there are some designed decisions that I think are
important to get right, and that are done better in later versions of Unix. The
major pain points in Unix are; signals, inconsistent tool arguments because
different people made different tools, GUI programming, and networking
(specifically berkely sockets), arbitrary limitations, white space in file
names, lack of a system level database, the odd standard system shell.

Lessons learned from Plan-9 from Bell Labs, and Oberon, could be incorporated
into the project. A minimal set of system calls need to be implemented, with
some useful extensions, they would be:

* mmap, which is a very useful system call, this could be used as a faster
interface to certain peripherals if needed, like graphics cards and memory.
* Some security system calls such as tame, unveil, pledge.
* A system call for notifying a process that a file, or any of the files and
  folders under a directory has changed.

As the hardware would also be designed from scratch, some of the file formats
could be designed from scratch. The video peripheral would presumably layout a
frame of video in a certain way, this could be used as the raw standard image
format. Likewise for audio. This would allow a simple memory copy to be used to
create new images. If the peripheral contained meta-data that could be copied
directly (like image size, colors, ...) then all the better.

Another change would be the banning of many special and white space characters
from file names. Or at least if they are present, which they would need to be
when mounting foreign file systems, it would be required to use escape
characters to refer to those banned characters. The reason for this is because
it would make utilities that deal with files in bulk less brittle.




* Redesigning HTTPS, MQTT, IRC, Email, around the 9p-like protocol.
* Implement everything as a library first
* Use databases more, and for everything

* System Shell; tcl like language
* Oberon like language
  - Serialization, defined structure layout
  - Reify the stack; coroutines
  - Little/No undefined behaviour
  - 64-bit only
  - Libraries
    - Standard virtual machine
    - Compiler/Linker as a library (can compile to VM or to native)
* Git/Fossil
* Databases (sqlite like DB and a CDB database)
  - Make an sqlite like database and use it everywhere
* Executable format using Sqlite
  - Single binary applications, 'apps'
* Replacements for HTML/CSS/Javascript
  - S-Expressions and Lisp
* VM
  - Small Simple
  - Designed to be run on an FPGA
* Crypto stuff
  -

[Oberon]: http://www.projectoberon.com/ 
[dd]: https://en.wikipedia.org/wiki/Dd_%28Unix%29
[cut]: https://en.wikipedia.org/wiki/Cut_(Unix)
[Pascal]: https://en.wikipedia.org/wiki/Pascal_%28programming_language%29
[C]: https://en.wikipedia.org/wiki/C_(programming_language)
[CDB]: https://cr.yp.to/cdb.html
[sqlite]: https://sqlite.org/index.html