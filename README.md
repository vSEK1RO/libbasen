# libbasen

c++20 encoding/decoding from arbitrary base

<a href="https://repology.org/project/libbasen/versions">
    <img src="https://repology.org/badge/tiny-repos/libbasen.svg" alt="Packaging status">
</a>
<a href="https://repology.org/project/libbasen/versions">
    <img src="https://repology.org/badge/latest-versions/libbasen.svg" alt="latest packaged version(s)">
</a>

## Contents

- [Installation](#installation)
    - [Package](#package)
    - [Meson](#meson)
- [Documentation](#documentation)
- [Usage](#usage)
- [Contributing](#contributing)

## Installation

### Package

[![Packaging status](https://repology.org/badge/vertical-allrepos/libbasen.svg)](https://repology.org/project/libbasen/versions)

### Meson

For cli tool you should have [argparse](https://github.com/p-ranav/argparse) as make dependency.

```
meson setup build --buildtype=release
cd build
meson install
```

## Documentation

Available [here](https://vsek1ro.github.io/libbasen)

## Usage

libbasen package provides `basen` cli tool. Below are examples of use:
```
echo "hello world" | basen -t hex > encoded.data
basen -t hex -d < encoded.data > decoded.data
echo "arbitrary alphabet" | basen -a "0123ABCD"
```

## Contributing

Main branch is under protection rules, so you should create pull request. After merging will be runned [authors.sh](https://github.com/vSEK1RO/libbasen/blob/main/authors.sh) for adding all contributors usernames and their number of commits to [AUTHORS](https://github.com/vSEK1RO/libbasen/blob/main/AUTHORS) file.

Now we would like to implement the following features:
- Base32
- BCH
- Bech32

For build with with debug flags:
```
meson setup build-dev -Db_coverage=true
cd build-dev
meson compile
```
For build tests (needed gtest package as dependency):
```
meson test
```
For generating coverage:
```
ninja coverage
```

[⬆️ Contents](#contents)
