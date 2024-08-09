# Etch

Etch is a High level HTTP framework for C. It has no dependencies other than the standard library and pthread

## Platforms

Currently, macOS and Linux are supported

In theory, cygwin should let it run under windows. For a "native" windows port, we 
would need to use `windows.h`'s threading functionality instead 
of pthread, as well as rewrite build scripts for windows.

## Project Structure

- `docs`: Contains documentation files (markdown)
- `etch`: Contains source files for etch
- `examples`: Contains examples on how to use etch
- `include`: Contains public headers for etch. See the doxygen docs for more info
- `scripts`: Contains scripts used to develop etch


## Building

First, clone the git repo
```sh
git clone https://github.com/DitherWither/etchteateapee.git
cd etchteateapee
```

Install cmake, doxygen, and a c compiler toolchain, then run
```sh
scripts/build
```
This will build doxygen docs at `build/html`, and build a shared library

Alternatively, if you would like to just build the project, do this instead
```sh
mkdir build
cd build
cmake ..
cmake --build .
```
### Installing

First, build the project, then run
```sh
cd build
cmake --install . --prefix "/usr"
```

### Contributing

This project uses `clang-format` for code formatting. To format the project, install clang-format, then run
```sh
scripts/fmt
```

Replace `/usr` with the desired install path

## Usage

See the examples folder for usage examples


## TODO

- [ ] Write more examples
- [ ] Write better usage section
- [ ] Document the core module
- [ ] Consider making distro packages or brew packages
- [ ] Add unit and integration tests
- [ ] Add CI
- [ ] Host docs on etch.vardhanpatil.com
- [ ] Load config from env variables
- [ ] Consider making higher level wrappers for databases
