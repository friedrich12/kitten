ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- make -j$(nproc)
cp vmlwk.bin ../xphoton/hrdisk2/initrd
cp user/hafnium/hafnium /home/friedy/XPHOTON/xphoton/hrdisk2/initrd/test_app
