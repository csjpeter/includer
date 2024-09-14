
all:
	rm -fr release || true
	conan build . --profile=C++23 --build=missing -s build_type=Debug
	ctest --test-dir build/Debug --output-on-failure --stop-on-failure
	mkdir -p release/bin
	cp build/Debug/src/includer release/bin/

clean:
	rm CMakeUserPresets.json || true
	rm -fr release || true
	rm -fr build || true
	rm -fr Testing || true

