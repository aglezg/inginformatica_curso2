// Testbench CL

`timescale 1 ns / 10 ps

module cl_tb;
//declaracion de señales

wire test_output;
reg[1:0] test_s;
reg test_a, test_b;

//instancia del modulo a testear, con notación de posiciones de argumentos 
cl mi_cl(test_output, test_a, test_b, test_s);


initial
begin
  $monitor("tiempo=%0d a=%b b=%b >> output=%b", $time, test_a, test_b, test_output);
//  $dumpfile("fa_v1_tb.vcd");
//  $dumpvars;

  //vector de test 0
  $display("\nPara s=00:\n");
  test_s = 2'b00;

  test_a = 1'b0;
  test_b = 1'b0;
  #20;

  test_a = 1'b0;
  test_b = 1'b1;
  #20;

  test_a = 1'b1;
  test_b = 1'b0;
  #20;

  test_a = 1'b1;
  test_b = 1'b1;
  #20;

  $display("\nPara s=01:\n");
  test_s = 2'b01;

  test_a = 1'b0;
  test_b = 1'b0;
  #20;

  test_a = 1'b0;
  test_b = 1'b1;
  #20;

  test_a = 1'b1;
  test_b = 1'b0;
  #20;

  test_a = 1'b1;
  test_b = 1'b1;
  #20;

  $display("\nPara s=10:\n");
  test_s = 2'b10;

  test_a = 1'b0;
  test_b = 1'b0;
  #20;

  test_a = 1'b0;
  test_b = 1'b1;
  #20;

  test_a = 1'b1;
  test_b = 1'b0;
  #20;

  test_a = 1'b1;
  test_b = 1'b1;
  #20;

  $display("\nPara s=11:\n");
  test_s = 2'b11;

  test_a = 1'b0;
  test_b = 1'b0;
  #20;

  test_a = 1'b0;
  test_b = 1'b1;
  #20;

  test_a = 1'b1;
  test_b = 1'b0;
  #20;

  test_a = 1'b1;
  test_b = 1'b1;
  #20;

  $finish;  //fin simulacion
end
endmodule
