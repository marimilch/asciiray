# ASCIIRay

## Preview

https://user-images.githubusercontent.com/52521188/156248341-7c7d56b5-90aa-4d8a-95f4-957db98acce5.mp4

## How to build

### tl;dr
```bash
# Install dependency tingping/ustring. Requires C package manager clib(1).
clib install tingping/ustring

# Compile using native compiler.
cc asciiray.c -o asciiray
```

### Learn More
This little demo relies on C package ``tingping/ustring`` for UTF-8 string manipulation. 
To install it [clib(1)](https://www.clibs.org/) is required - a package manager for C.
You can follow the instructions on the website (it's easy). In macOS you can install clib(1) with 
[brew](https://brew.sh/):
```bash
# Install clib(1) via brew.
brew install clib
```
Once successfully installed you can run the commands in the tl;dr section above to compile
ASCIIRay.

## Usage
Once compiled, in your console type
``./asciiray <width> <height>``
where width and height are unsigned integers and press Enter.
~~160 and 40 is recommended due to least artifacts.~~
The tearing bug has been fixed and any size should work. :)

Enjoy the little demo :).

## Warning
Actually not a raytracer, since it works with the camera matrix.
It only works on UNIX-based systems, sorry. :(

# Thank you
For reading this! Who'd have thought, you'd stumble in here. :)
