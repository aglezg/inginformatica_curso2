// ULL- Grado en Ingeniería Informática
// Segundo Año - Estructura de Computadores - Turno de Tarde
// Autor: Adrián Glez Galván - alu0101321219@ull.edu.es

// Testbench Microc.v

`timescale 1 ns / 10 ps

module microc_tb;

// Declaracion de señales
reg clk, reset, s_abs, s_inc, s_inm, we3, wez;
reg[2:0] op;
wire[5:0] opcode;
wire z;

// Reloj --> ciclo de 30
always
begin
	clk=1;
	#15;
	clk=0;
	#15;
end

// Reset --> activo 1/3 del ciclo
initial
begin
	reset=1;
	#5;
	reset=0;
end

//30 entre instruccion e instruccion

// Instancia del módulo 
microc MICROC(clk, reset, s_abs, s_inc, s_inm, we3, wez, op, z, opcode);
 
// Simulación
initial
begin
  $monitor("tiempo=%0d >> clk=%b, opcode=%6b \n", $time, clk, opcode);
  $dumpfile("microc_tb.vcd");
  $dumpvars;

  #15;
  // LI R5, 2
  s_inc=1'b1;
  s_abs=1'b0;
  we3=1'b1;
  op=3'b000;
  wez=1'b0;
  s_inm=1'b1;
  #30;
  // ADD R5, R5, R3
  s_inc=1'b1;
  s_abs=1'b0;
  we3=1'b1;
  op=3'b010;
  wez=1'b1;
  s_inm=1'b0;
  #30;
  // LI R9, 2
  s_inc=1'b1;
  s_abs=1'b0;
  we3=1'b1;
  op=3'b000;
  wez=1'b0;
  s_inm=1'b1;
  #30;
  // LI R10, 1
  s_inc=1'b1;
  s_abs=1'b0;
  we3=1'b1;
  op=3'b000;
  wez=1'b0;
  s_inm=1'b1;
  #30;
  // TEST: SUB R3, R9, R3
  s_inc=1'b1;
  s_abs=1'b0;
  we3=1'b1;
  op=3'b011;
  wez=1'b1;
  s_inm=1'b0;
  #30;
  // JZ FIN
  s_inc=1'b1;
  s_abs=z;
  we3=1'b0;
  op=3'b000;
  wez=1'b0;
  s_inm=1'b0;
  #30;
  // ADD R4, R10, R4
  s_inc=1'b1;
  s_abs=1'b0;
  we3=1'b1;
  op=3'b010;
  wez=1'b1;
  s_inm=1'b0;
  #30;
  // JR TEST
  s_inc=1'b0;
  s_abs=1'b0;
  we3=1'b0;
  op=3'b000;
  wez=1'b0;
  s_inm=1'b0;
  #30;
  // TEST: SUB R3, R9, R3
  s_inc=1'b1;
  s_abs=1'b0;
  we3=1'b1;
  op=3'b011;
  wez=1'b1;
  s_inm=1'b0;
  #30;
  // JZ FIN
  s_inc=1'b1;
  s_abs=z;
  we3=1'b0;
  op=3'b000;
  wez=1'b0;
  s_inm=1'b0;
  #30;
  // J FIN
  s_inc=1'b0;
  s_abs=1'b1;
  we3=1'b0;
  op=3'b000;
  wez=1'b0;
  s_inm=1'b1;
  #30;

  $finish;  //fin simulacion
end
endmodule
