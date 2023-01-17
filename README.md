# Sagetech SDK Public
This is a public release of the Sagetech SDK.

## Configure and Build
The SDK can be cloned with:
```
git clone https://github.com/Sagetech-Avionics/sagetech-mxs-sdk.git
```

The SDK can be configured using the following commands for an x86 Linux environment.
```
mkdir build
cmake -B ./build -G "Unix Makefiles" .
```

Other build configurations can be specified if other toolchains are installed. For example one could use the following to build for an Aarch64 environment.
```
cmake -B ./build/ -G "Unix Makefiles" \
  -DCMAKE_C_COMPILER={PATH_TO_CROSSCOMPILER}/aarch64-none-linux-gnu-gcc \
  -DCMAKE_CXX_COMPILER={PATH_TO_CROSSCOMPILER}/aarch64-none-linux-gnu-g++ \
  .
```

Then run the following to build:
```
cd build
make
```
v1.0 tagged Jan 16th 2023 posted by Riley Barnes
