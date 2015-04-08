  export ARCH=arm
#  export CROSS_COMPILE=arm-eabi-
  export CROSS_COMPILE=arm-none-eabi-
#  make clean
  make e1brcis-perf_rev11_defconfig
  make > ../`date '+%Y-%m-%d'`-log-`date '+%H-%M'`.txt
#  make menuconfig