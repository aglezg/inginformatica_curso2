// Testbench Full-Adder

`timescale 1 ns / 10 ps

module fa_tb;
//declaracion de señales

wire test_cout, test_sum;
reg test_a, test_b, test_cin;

//instancia del modulo a testear, con notación de posiciones de argumentos 
fa mi_fa(test_cout, test_sum, test_a, test_b, test_cin);


initial
begin
  $monitor("Tiempo=%0d:\n> a=%b b=%b cin=%b\n>> carry=%b / sum=%b \n", $time, test_a, test_b, test_cin, test_cout, test_sum);
//  $dumpfile("fa_v1_tb.vcd");
//  $dumpvars;

  //vector de test 0
  test_a = 1'b0;
  test_b = 1'b0;
  test_cin = 1'b0;
  #20;

  test_a = 1'b0;
  test_b = 1'b0;
  test_cin = 1'b1;
  #20;

  test_a = 1'b0;
  test_b = 1'b1;
  test_cin = 1'b0;
  #20;

  test_a = 1'b0;
  test_b = 1'b1;
  test_cin = 1'b1;
  #20;

  test_a = 1'b1;
  test_b = 1'b0;
  test_cin = 1'b0;
  #20;

  test_a = 1'b1;
  test_b = 1'b0;
  test_cin = 1'b1;
  #20;

  test_a = 1'b1;
  test_b = 1'b1;
  test_cin = 1'b0;
  #20;

  test_a = 1'b1;
  test_b = 1'b1;
  test_cin = 1'b1;
  #20;

  $finish;  //fin simulacion
end
endmodule
