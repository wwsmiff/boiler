# Boiler
A simple commaind-line utility to generate boilerplate code with ease.

### Build
Dependencies:
- A C++ compiler that supports C++20.
```
cmake -S . -B build
cmake --build build
```

### Install
Default install location is ~/.boiler (for linux). Installation currently isn't tested/supported on Windows and MacOS.
```
cmake --install build
```
