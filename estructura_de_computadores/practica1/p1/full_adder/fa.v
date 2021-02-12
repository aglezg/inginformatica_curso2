//Full-Adder (operador concatenación '{}')

module fa(output wire cout, sum, input wire a, b, cin);

  assign {cout,sum} = a + b + cin; //operador suma

endmodule
