# pgdbmanage

=====================================
||| LINUX INSTALL INSTRUCTIONS |||
=====================================

Requires compile/install of TCL & Expect. Below instructions based on these resources:
http://www.linuxfromscratch.org/lfs/view/development/chapter05/tcl.html | 
http://www.linuxfromscratch.org/lfs/view/development/chapter05/expect.html

Download these 2 libraries and extract so that source folders are adjacent:
http://sourceforge.net/projects/tcl/
http://sourceforge.net/projects/expect/

==============================

RUN FROM TCL SOURCE:

./configure --prefix=/usr/local
make
sudo make install
sudo chmod -v u+w /usr/local/lib/libtcl8.6.so
sudo make install-private-headers
sudo ln -sv tclsh8.6 /usr/local/bin/tclsh

==============================

RUN FROM EXPECT SOURCE:

cp -v configure{,.orig}
sed 's:/usr/local/bin:/bin:' configure.orig > configure

./configure --prefix=/usr/local/       \
            --with-tcl=/usr/local/lib \
            --with-tclinclude=/usr/local/include

make
sudo make SCRIPTS="" install
