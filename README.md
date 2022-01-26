# clad_autodiff_examples
sandbox for testing clad autodiff translator (https://github.com/vgvassilev/clad)

# Install
----------------------------------------------- (also used by kernel slicer)
1. sudo apt-get install llvm-12-dev
2. sudo touch /usr/lib/llvm-12/bin/yaml-bench
3. sudo apt-get install libclang-12-dev

----------------------------------------------- (used only for clad)

4. sudo apt-get install clang-12
5. sudo apt-get install llvm-12-tools
6. sudo bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)" // not sure this is needed
7. sudo -H pip install lit
8. git clone https://github.com/vgvassilev/clad.git clad
9. mkdir build_dir inst; cd build_dir
10. cmake ../clad -DClang_DIR=/usr/lib/llvm-12 -DLLVM_DIR=/usr/lib/llvm-12 -DCMAKE_INSTALL_PREFIX=../inst -DLLVM_EXTERNAL_LIT="`which lit`"
11. make -j 8 && make install
12. result will be located in the folder "inst"
