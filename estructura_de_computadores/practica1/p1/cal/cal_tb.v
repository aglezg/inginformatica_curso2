// Testbench celda aritmético lógica

`timescale 1 ns / 10 ps

module cal_tb;
//declaracion de señales

wire test_out, test_cout;
reg[1:0] test_s;
reg test_a, test_b, test_l, test_cin;

//instancia del modulo a testear, con notación de posiciones de argumentos 
cal mical(test_out, test_cout, test_a, test_b, test_l, test_cin, test_s);

initial
begin
  $monitor("tiempo=%0d a=%b b=%b cin=%b s=%2b >> out=%b / cout=%b \n", $time, test_a, test_b, test_cin, test_s, test_out, test_cout);
//  $dumpfile("fa_v1_tb.vcd");
//  $dumpvars;

  //vector de test 0
  $display("Para l=1\n");
  test_l = 1'b1;
  test_s = 2'b00;

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
