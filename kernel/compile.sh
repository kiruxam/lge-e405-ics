  export ARCH=arm
  export CROSS_COMPILE=arm-none-eabi-
#  make clean
#  make e1open-perf_defconfig
#  make vee3ds-rev_11_defconfig
  make m4dscis-perf_rev11_defconfig
  make > ../log-01-01.txt
#  make menuconfig