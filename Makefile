default: all

all: libspot-bundle.so

./tpl_src:
	mkdir ./tpl_src && true

./tpl_build: ./tpl_src
	mkdir ./tpl_build || true


./tpl_build/lib/libadiak.a: ./tpl_build ./tpl/adiak/CMakeLists.txt
	cd tpl_src && rm -rf CMakeCache.txt CMakeFiles && cmake -DBUILD_SHARED_LIBS=OFF -DWITH_MPI=ON -DCMAKE_INSTALL_PREFIX=../tpl_build ../tpl/adiak && make -j8 install 

./tpl_build/lib64/libcaliper.so: ./tpl_build ./tpl_build/lib/libadiak.a 
	cd tpl_src && rm -rf CMakeCache.txt CMakeFiles && cmake -DBUILD_SHARED_LIBS=ON -DWITH_MPI=ON -DWITH_KOKKOS=ON -DWITH_KOKKOS_PROFILING=ON -DWITH_ADIAK=ON -DCMAKE_INSTALL_PREFIX=../tpl_build ../tpl/caliper && make -j8 install

curdir=$(PWD)

libspot-bundle.so: spot-bundle.cpp ./tpl_build/lib64/libcaliper.so
	g++ -I./tpl_build/include -L./tpl_build/lib -L./tpl_build/lib64 -Wl,-rpath,$(curdir)/tpl_build/lib64 spot-bundle.cpp -lcaliper -fPIC -shared -o libspot-bundle.so


