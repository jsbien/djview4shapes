djview4shapes is a fork of djview4
(http://djvu.sourceforge.net/djview4.html).  Its purpose is to display
the content of common shapes dictionaries contained in DjVu
documents.

The idea to display the common shapes of a document (to facilitate
e.g. transcription and character inventory extraction) and other
suggestions were formulated by Janusz S. Bień. 

English user documentation is provided in the online help, the program
is described in Polish in "Repertuar znaków piśmiennych — problemy i
perspektywy" (https://www.researchgate.net/publication/340342236).

The program was developed by Michał Rudolf using some code of Grzegorz
Chimosz.  The work was supported by the Ministry of Science and Higher
Education's grant no. N N519 38403 (cf.
https://github.com/jsbien/ndt/wiki).

In 2020 a small but important contribution has been made by Alexander
Trufanov. Additionally he provided the essential help to crosscompile
the program for Windows.

The current home of the program is this repository and new issues
should be reported here. There original site https://bitbucket.org/mrudolf/djview-poliqarp is kept because of the open issues, but is no longer maintained.

To compile for Debian GNU/Linux install the build dependencies listed in debian/control, then run

`dpkg-buildpackage -uc -us -b -rfakeroot`

or an equivalent command.

To compile for Windows cf. [Artur Kozak's note](Windows-cross-compile.md).

![djview4shapes: a screenshot](screenshots/djview4shapes_Zaborowski.png?raw=true "Index of abbreviations")
