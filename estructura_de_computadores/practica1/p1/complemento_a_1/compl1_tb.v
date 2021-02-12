// Testbench de módulo de complemento a 1

`timescale 1 ns / 10 ps

module compl1_tb;
//declaracion de señales

wire[3:0] test_Sal;
reg[3:0] test_Ent;
reg test_cp1;

//instancia del modulo a testear, con notación de posiciones de argumentos 
compl1 micompl1(test_Sal, test_Ent, test_cp1);

initial
begin
  $monitor("tiempo=%0d Ent=%4b >> Sal=%4b\n", $time, test_Ent, test_Sal);
//  $dumpfile("fa_v1_tb.vcd");
//  $dumpvars;

  $display("cp1 = 0\n");
  test_cp1 = 1'b0;

  test_Ent = 4'b0000;
  #20;
  test_Ent = 4'b0001;
  #20;
  test_Ent = 4'b0010;
  #20;
  test_Ent = 4'b0011;
  #20;
  test_Ent = 4'b0100;
  #20;
  test_Ent = 4'b0101;
  #20;
  test_Ent = 4'b0110;
  #20;
  test_Ent = 4'b0111;
  #20;
  test_Ent = 4'b1000;
  #20;
  test_Ent = 4'b1001;
  #20;
  test_Ent = 4'b1010;
  #20;
  test_Ent = 4'b1011;
  #20;
  test_Ent = 4'b1100;
  #20;
  test_Ent = 4'b1101;
  #20;
  test_Ent = 4'b1110;
  #20;
  test_Ent = 4'b1111;
  #20;

  $display("cp1 = 1\n");
  test_cp1 = 1'b1;

  test_Ent = 4'b0000;
  #20;
  test_Ent = 4'b0001;
  #20;
  test_Ent = 4'b0010;
  #20;
  test_Ent = 4'b0011;
  #20;
  test_Ent = 4'b0100;
  #20;
  test_Ent = 4'b0101;
  #20;
  test_Ent = 4'b0110;
  #20;
  test_Ent = 4'b0111;
  #20;
  test_Ent = 4'b1000;
  #20;
  test_Ent = 4'b1001;
  #20;
  test_Ent = 4'b1010;
  #20;
  test_Ent = 4'b1011;
  #20;
  test_Ent = 4'b1100;
  #20;
  test_Ent = 4'b1101;
  #20;
  test_Ent = 4'b1110;
  #20;
  test_Ent = 4'b1111;
  #20;

  $finish;  //fin simulacion
end
endmodule
