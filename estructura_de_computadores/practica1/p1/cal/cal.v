// Celda aritmético-lógica

module cal(output wire out, c_out, input wire a, b, l, c_in, input wire [1:0] s);

  wire salida_fa, salida_cl; // declaracion de variables

  fa mifa(c_out, salida_fa, a, b, c_in);
  cl micl(salida_cl, a, b, s);           

  mux2_1 mi_mux21(out, salida_fa, salida_cl, l);

endmodule
