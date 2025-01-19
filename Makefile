clean:
	rm -rf build 

configure:
	cmake --preset debug

build:
	cmake --build --preset debug

test:
	cmake --workflow --preset test

test_fresh:
	cmake --workflow --preset test --fresh

.DEFAULT_GOAL := test_fresh
