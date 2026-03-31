apt install build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo libisl-dev -y
mkdir toolchain
mkdir build-toolchain
export PREFIX="${PWD}/toolchain"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
cd build-toolchain
wget -nc https://ftp.gnu.org/gnu/binutils/binutils-2.46.0.tar.gz
tar -xzvf binutils-2.46.0.tar.gz
mkdir build-binutils
cd build-binutils
../binutils-2.46.0/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install
cd ..
rm -rf build-binutils
wget -nc https://ftp.gnu.org/gnu/gdb/gdb-17.1.tar.gz
tar -xzvf gdb-17.1.tar.gz
mkdir build-gdb
cd build-gdb
../gdb-17.1/configure --target=$TARGET --prefix="$PREFIX" --disable-werror
make all-gdb
make install-gdb
cd ..
rm -rf build-gdb
wget -nc https://ftp.gnu.org/gnu/gcc/gcc-15.2.0/gcc-15.2.0.tar.gz
tar -xzvf gcc-15.2.0.tar.gz
mkdir build-gcc
cd build-gcc
../gcc-15.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers --disable-hosted-libstdcxx
make all-gcc
make all-target-libgcc
make all-target-libstdc++-v3
make install-gcc
make install-target-libgcc
make install-target-libstdc++-v3
cd ..
rm -rf build-gcc
cd ..
rm -rf build-toolchain
