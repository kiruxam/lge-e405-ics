  export ARCH=arm
#  export CROSS_COMPILE=arm-eabi-
  export CROSS_COMPILE=arm-none-eabi-
#  make clean
  make e1brcis-perf_rev11_defconfig
  make > ../01-log-01.txt
#  make menuconfig