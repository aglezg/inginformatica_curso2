// ULL- Grado en Ingeniería Informática
// Segundo Año - Estructura de Computadores - Turno de Tarde
// Autor: Adrián Glez Galván - alu0101321219@ull.edu.es

module microc(input wire clk, reset, s_abs, s_inc, s_inm, we3, wez, input wire [2:0] op, output wire z, output wire [5:0] opcode);
//Microcontrolador sin memoria de datos de un solo ciclo

// Declaración de variables
wire[9:0] entrada_PC, salida_PC, salida_mux_inc, salida_SUM;
wire[15:0] salida_MEMPROG;
wire[7:0] rd1, rd2, wd3, salida_ALU;
wire salida_ZALU;

// MEMPROG, PC, SUM
registro #(10) PC(clk, reset, entrada_PC, salida_PC);
memprog MEMPROG(clk, salida_PC, salida_MEMPROG);
sum SUM(salida_mux_inc, salida_PC, salida_SUM);

// REGFILE, ALU, FFZ
regfile REGFILE(clk, we3, salida_MEMPROG[11:8], salida_MEMPROG[7:4], salida_MEMPROG[3:0], wd3, rd1, rd2);
alu ALU(rd1, rd2, op, salida_ALU, salida_ZALU);
ffd FFZ(clk, reset, salida_ZALU, wez, z);

// MUX's
mux2 #(10) mux_inc(salida_MEMPROG[9:0], 10'b0000000001, s_inc, salida_mux_inc);
mux2 #(10) mux_abs(salida_SUM, salida_MEMPROG[9:0], s_abs, entrada_PC);
mux2 mux_inm(salida_ALU, salida_MEMPROG[11:4], s_inm, wd3);

// Opcode
assign opcode = salida_MEMPROG[15:10];

endmodule
