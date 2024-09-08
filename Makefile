
all:
	rm -fr release || true
	conan build . --profile=C++23 --build=missing -s build_type=Debug
	mkdir -p release/bin
	cp build/Debug/src/includer release/

clean:
	rm CMakeUserPresets.json || true
	rm -fr release || true
	rm -fr build || true

