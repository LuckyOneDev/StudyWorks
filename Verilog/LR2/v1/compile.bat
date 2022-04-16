c:/iverilog/bin/iverilog.exe -o result fullsum.v summator.v testbench.v
c:/iverilog/bin/vvp.exe result -lxt2
C:\iverilog\gtkwave\bin\gtkwave.exe test.vcd
del result test.vcd