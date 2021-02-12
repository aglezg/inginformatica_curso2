// Celda Lógica

module cl(output wire out, input wire a, b, input wire [1:0] s);

  wire salida_and, salida_or, salida_xor, salida_not; // definicion de variables

  and  and1(salida_and, a, b); // realizamos las operaciones
  or   or1(salida_or, a, b);
  xor  xor1(salida_xor, a, b);
  not not1(salida_not, a);

  mux4_1 mi_mux4(out, salida_and, salida_or, salida_xor, salida_not, s);

endmodule
