// Multiplexor de 4 entradas de un bit

module mux4_1(output reg out, input wire a, b, c, d, input wire [1:0] s);

  always @(a or b or c or d or s)
   
   begin

      case (s)              
        2'b00 : out = a;        // caso 00
        2'b01 : out = b;        // caso 01
        2'b10 : out = c;        // caso 10
        2'b11 : out = d;        // caso 11
        default: out = 'bx;
      endcase

    end

endmodule
