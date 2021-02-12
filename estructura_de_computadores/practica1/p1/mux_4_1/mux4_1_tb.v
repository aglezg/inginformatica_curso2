// Testbench MUX4a1

`timescale 1 ns / 10 ps

module mux4_1_tb;
//declaracion de señales

wire test_output;
reg[1:0] test_s;
reg test_a, test_b, test_c, test_d;

//instancia del modulo a testear, con notación de posiciones de argumentos 
mux4_1 mux41(test_output, test_a, test_b, test_c, test_d, test_s);


initial
begin
  $monitor("tiempo=%0d a=%b b=%b c=%b d=%b >> output=%b \n", $time, test_a, test_b, test_c, test_d, test_output);
//  $dumpfile("fa_v1_tb.vcd");
//  $dumpvars;

  //vector de test 0
  $display("Para s=00 \n");
  test_a = 1'b0;
  test_b = 1'b0;
  test_c = 1'b0;
  test_d = 1'b0;
  test_s = 2'b00;
  #20;

  test_a = 1'b0;
  test_b = 1'b0;
  test_c = 1'b0;
  test_d = 1'b1;
  test_s = 2'b00;
  #20;

  test_a = 1'b0;
  test_b = 1'b0;
  test_c = 1'b1;
  test_d = 1'b1;
  test_s = 2'b00;
  #20;

  test_a = 1'b0;
  test_b = 1'b1;
  test_c = 1'b0;
  test_d = 1'b1;
  test_s = 2'b00;
  #20;

  test_a = 1'b0;
  test_b = 1'b1;
  test_c = 1'b1;
  test_d = 1'b1;
  test_s = 2'b00;
  #20;

  test_a = 1'b1;
  test_b = 1'b0;
  test_c = 1'b0;
  test_d = 1'b0;
  test_s = 2'b00;
  #20;

  test_a = 1'b1;
  test_b = 1'b0;
  test_c = 1'b1;
  test_d = 1'b1;
  test_s = 2'b00;
  #20;

  test_a = 1'b1;
  test_b = 1'b1;
  test_c = 1'b1;
  test_d = 1'b1;
  test_s = 2'b00;
  #20;

  //vector de test 1
  $display("Para s=01 \n");
  test_a = 1'b0;
  test_b = 1'b0;
  test_c = 1'b0;
  test_d = 1'b0;
  test_s = 2'b01;
  #20;

  test_a = 1'b0;
  test_b = 1'b0;
  test_c = 1'b0;
  test_d = 1'b1;
  test_s = 2'b01;
  #20;

  test_a = 1'b0;
  test_b = 1'b0;
  test_c = 1'b1;
  test_d = 1'b1;
  test_s = 2'b01;
  #20;

  test_a = 1'b0;
  test_b = 1'b1;
  test_c = 1'b0;
  test_d = 1'b1;
  test_s = 2'b01;
  #20;

  test_a = 1'b0;
  test_b = 1'b1;
  test_c = 1'b1;
  test_d = 1'b1;
  test_s = 2'b01;
  #20;

  test_a = 1'b1;
  test_b = 1'b0;
  test_c = 1'b0;
  test_d = 1'b0;
  test_s = 2'b01;
  #20;

  test_a = 1'b1;
  test_b = 1'b0;
  test_c = 1'b1;
  test_d = 1'b1;
  test_s = 2'b01;
  #20;

  test_a = 1'b1;
  test_b = 1'b1;
  test_c = 1'b1;
  test_d = 1'b1;
  test_s = 2'b01;
  #20;

  //vector de test 2
  $display("Para s=10 \n");
  test_a = 1'b0;
  test_b = 1'b0;
  test_c = 1'b0;
  test_d = 1'b0;
  test_s = 2'b10;
  #20;

  test_a = 1'b0;
  test_b = 1'b0;
  test_c = 1'b0;
  test_d = 1'b1;
  test_s = 2'b10;
  #20;

  test_a = 1'b0;
  test_b = 1'b0;
  test_c = 1'b1;
  test_d = 1'b1;
  test_s = 2'b10;
  #20;

  test_a = 1'b0;
  test_b = 1'b1;
  test_c = 1'b0;
  test_d = 1'b1;
  test_s = 2'b10;
  #20;

  test_a = 1'b0;
  test_b = 1'b1;
  test_c = 1'b1;
  test_d = 1'b1;
  test_s = 2'b10;
  #20;

  test_a = 1'b1;
  test_b = 1'b0;
  test_c = 1'b0;
  test_d = 1'b0;
  test_s = 2'b10;
  #20;

  test_a = 1'b1;
  test_b = 1'b0;
  test_c = 1'b1;
  test_d = 1'b1;
  test_s = 2'b10;
  #20;

  test_a = 1'b1;
  test_b = 1'b1;
  test_c = 1'b1;
  test_d = 1'b1;
  test_s = 2'b10;
  #20;

  //vector de test 3
  $display("Para s=11 \n");
  test_a = 1'b0;
  test_b = 1'b0;
  test_c = 1'b0;
  test_d = 1'b0;
  test_s = 2'b11;
  #20;

  test_a = 1'b0;
  test_b = 1'b0;
  test_c = 1'b0;
  test_d = 1'b1;
  test_s = 2'b11;
  #20;

  test_a = 1'b0;
  test_b = 1'b0;
  test_c = 1'b1;
  test_d = 1'b1;
  test_s = 2'b11;
  #20;

  test_a = 1'b0;
  test_b = 1'b1;
  test_c = 1'b0;
  test_d = 1'b1;
  test_s = 2'b11;
  #20;

  test_a = 1'b0;
  test_b = 1'b1;
  test_c = 1'b1;
  test_d = 1'b1;
  test_s = 2'b11;
  #20;

  test_a = 1'b1;
  test_b = 1'b0;
  test_c = 1'b0;
  test_d = 1'b0;
  test_s = 2'b11;
  #20;

  test_a = 1'b1;
  test_b = 1'b0;
  test_c = 1'b1;
  test_d = 1'b1;
  test_s = 2'b11;
  #20;

  test_a = 1'b1;
  test_b = 1'b1;
  test_c = 1'b1;
  test_d = 1'b1;
  test_s = 2'b11;
  #20;

  $finish;  //fin simulacion
end
endmodule
