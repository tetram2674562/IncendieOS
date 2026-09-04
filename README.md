# ArcticFox OS

A hobby x86 operating system.

## Ultimate goals

- Provide the ability to listen to music
- Play 3D video games !
- Watch youtube 
- Use the cool Arctic Fox web browser !

## Compiling

The resulting ISO file will be located in the root directory of the git repository as `ArcticFox_OS.iso`

You must have docker in order for the build script to work.

Just use the build.sh script !

```
./build.sh
```

You can also do it the old fashioned way using the `install.sh` that will compile the toolchain for you operating system
And then use cmake to build it

Like this: 
```
mkdir build && cd build
```

```
cmake .. && make
```

## Running the OS 

You can either use virtualbox or qemu

(For qemu you can do the following : `qemu-system-i386 ArcticFoxOS.iso`)

## Why ?

I realised I didn't had enough knowledge in low-level programming, so I challenged myself to this _little_ project to improve myself.

## Target Hardware

I wish to support the same specificaions than XP, allowing me to run ArcticFox OS on very old hardware.

## Contributing

As it is a personnal project, I'm not open to contribution. However you can feel free to fork it as long as you mention me ❤️ !

## About AI 

All the code written here is handwritten by myself, there are no AI code. 
