cmd_src/arm/am57xx-evm.dtb = cpp -Wp,-MD,src/arm/.am57xx-evm.dtb.d.pre.tmp -nostdinc -Iinclude -Isrc/arm -Itestcase-data -undef -D__DTS__ -x assembler-with-cpp -o src/arm/.am57xx-evm.dtb.dts.tmp src/arm/am57xx-evm.dts ; dtc -O dtb -o src/arm/am57xx-evm.dtb -b 0 -i src/arm -d src/arm/.am57xx-evm.dtb.d.dtc.tmp src/arm/.am57xx-evm.dtb.dts.tmp ; cat src/arm/.am57xx-evm.dtb.d.pre.tmp src/arm/.am57xx-evm.dtb.d.dtc.tmp > src/arm/.am57xx-evm.dtb.d
am57xx-evm.o: src/arm/am57xx-evm.dts src/arm/am57xx-beagle-x15.dts \
 src/arm/dra74x.dtsi src/arm/dra7.dtsi \
 include/dt-bindings/interrupt-controller/arm-gic.h \
 include/dt-bindings/interrupt-controller/irq.h \
 include/dt-bindings/pinctrl/dra.h src/arm/skeleton.dtsi \
 src/arm/omap5-cpu-thermal.dtsi include/dt-bindings/thermal/thermal.h \
 include/dt-bindings/gpio/gpio.h include/dt-bindings/input/input.h
src/arm/am57xx-evm.dtb: src/arm/.am57xx-evm.dtb.dts.tmp src/arm/dra7xx-clocks.dtsi
