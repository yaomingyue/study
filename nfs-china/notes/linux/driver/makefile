1 将自己的驱动加入到kernel的编译体系中。如将hello.c 放入arch/arm/mach-omap2中，
  方法一：在mach-omap2目录下的Makefile中加入
  obj-y += hello.o
  或者
  obj-m += hello.o
  方法二： 将hello模块加入配置体系
  在Kconfig 中加入
   config OMAP4_PANDA_HELLO
        bool "Panda Board Hello"
        default y
   这样在make menuconfig 时就能看到OMAP4_PANDA_HELLO模块了
在Makefile中加入
obj-$(CONFIG_OMAP4_PANDA_HELLO)     += hello.o

在 arch/arm/config/panda_chipsee_defconfig 中加入
CONFIG_OMAP4_PANDA_HELLO=y

之后  运行
make panda_chipsee_defconfig
make uImage
