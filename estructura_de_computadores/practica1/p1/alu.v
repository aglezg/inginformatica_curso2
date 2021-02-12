// Unidad aritmético-lógica (ALU)
// Compilación:  iverilog alu_tb.v  alu.v mux2_4.v  cal/cal.v cal/mux2_1.v  celda_logica/cl.v mux_4_1/mux4_1.v full_adder/fa.v complemento_a_1/compl1.v 

module alu(output wire [3:0] R, output wire zero, carry, sign, input wire[3:0] A, B, input wire [1:0] ALUOp, input wire L);

  wire [3:0] OP1, OP2, OP2_pre;       // Operandos
  wire op1_A, op2_B, cpl;             // Ayuda al calculo de operandos
  wire c_in0, c_out0, c_out1, c_out2; // Cin/cout 's


  // Definición de las funciones lógicas de op1_A, op2_b, cpl y c_in0
  assign op1_A  = ~ALUOp[1] | L;
  assign op2_B  = ~ALUOp[1] | L | ALUOp[0];
  assign cpl    = ~L & ALUOp[0] | ~L & ALUOp[1];
  assign c_in0  = ALUOp[1] | ALUOp[0];


  mux2_4 mimux2_4_1(OP1, 4'b0000, A, op1_A); // Cálculo de OP1
  mux2_4 mimux2_4_2(OP2_pre, A, B, op2_B);
  compl1 compl1_B(OP2, OP2_pre, cpl);        // Cálculo de OP2


  // Instanciación de las 4 celdas aritmético-lógicas
  cal cal0(R[0], c_out0, OP1[0], OP2[0], L, c_in0, ALUOp); 
  cal cal1(R[1], c_out1, OP1[1], OP2[1], L, c_out0, ALUOp);
  cal cal2(R[2], c_out2, OP1[2], OP2[2], L, c_out1, ALUOp);
  cal cal3(R[3], carry,  OP1[3], OP2[3], L, c_out2, ALUOp);

  // Otras señales
  assign zero = ~R[0] & ~R[1] & ~R[2] & ~R[3];
  assign sign = R[3];

endmodule
