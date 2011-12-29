LuaTrig
=======

A program to write Age of Empires II triggers in Lua scripting language.

Usage
-----

See the [LuaTrig Wiki](https://github.com/andy-joslin/LuaTrig/wiki) on GitHub for usage instructions.

Credits
-------

The sources for the following programs were immensely helpful in developing LuaTrig:

[AoK Trigger Studio, by DiGiT](http://sourceforge.net/projects/aokts/)

[Trigger Script Editor, by Jatayu](http://aok.heavengames.com/blacksmith/showfile.php?fileid=10278)

Dependencies
------------

These libraries are necessary to compile and develop LuaTrig.

[Swig](http://www.swig.org/)

[wxWidgets](http://wxwidgets.org/)

[zlib](http://zlib.net/)

Operating Systems
-----------------

### Windows ### 
LuaTrig is made for Windows, and will compile and run on Windows.

### Linux ###
To make LuaTrig compile on Linux, mention of resources.rc must be removed from the Makefile. Also, zlib (-lz) must be added to the libs variable in the Makefile.
Once you can get LuaTrig to compile, it will run on Linux.

### Mac ###
LuaTrig will not work on Mac.