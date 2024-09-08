
all:
	rm -fr release || true
	conan build . --build=missing -s build_type=Debug
	mkdir -p release/bin
	cp build/bin/* release/

clean:
	rm -fr release
	rm -fr build

