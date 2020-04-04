# cpp.note

# メモリリーク検出 - Valgrind at Ubuntu 18.04 LTS (2020-04-04)

Valgrind http://www.valgrind.org/downloads/current.html

```
tar xvf valgrind-3.15.0.tar.bz2
cd valgrind-3.15.0
./configure
make
sudo make install
```

To detect.

```
valgrind --leak-check=yes ./your-application arg1 arg2
```

To uninstall

```
make uninstall

find /usr/local/include/valgrind/
rm -fr /usr/local/include/valgrind

find /usr/local/lib/valgrind/
rm -fr /usr/local/lib/valgrind
```
