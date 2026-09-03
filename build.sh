sudo docker run --rm -u $(id -u):$(id -g) -v $(pwd):/project tetram26/arcticfox_os_toolchain /bin/bash -c "rm -rf build && mkdir build && cd build && cmake .. && make"
