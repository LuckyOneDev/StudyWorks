c:/iverilog/bin/iverilog.exe -o result -g2005-sv ram.sv testbench.sv
c:/iverilog/bin/vvp.exe result -lxt2
C:\iverilog\gtkwave\bin\gtkwave.exe var_dump.vcd
del result var_dump.vcd