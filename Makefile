clean:
	rm -rf build 

configure:
	cmake --preset debug

build: configure
	cmake --build --preset debug

test: FORCE
	cmake --workflow --preset test

test_fresh: FORCE
	cmake --workflow --preset test --fresh

FORCE:

.DEFAULT_GOAL := test
