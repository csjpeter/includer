
all:
	rm -fr release || true
	conan build . --profile=C++23 --build=missing -s build_type=Debug
	ctest --test-dir build/Debug --output-on-failure --stop-on-failure
	cd build/Debug && make package
	mkdir -p release/bin
	cp build/Debug/src/includer release/bin/
	cp build/Debug/_CPack_Packages/Linux/DEB/includer-1.0.0-Linux.deb release/
	cp build/Debug/_CPack_Packages/Linux/RPM/RPMS/includer-1.0.0-Linux.rpm release/

clean:
	rm CMakeUserPresets.json || true
	rm -fr release || true
	rm -fr build || true
	rm -fr Testing || true

deps:
	sudo apt-get install g++ rpm python3 python3-pip pipx g++12
	pipx install clang-tidy clang-format conan2


