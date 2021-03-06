/*
 * File: main.c
 * Creator: George Ferguson
 * Created: Mon Nov 28 14:11:17 2016
 * Changed: Luba Le Xuan
 * Date: Dec 3, 2016
 * Added functions for circuits, testing for 2 inputs function, and code in main function 
 * Time-stamp: <Mon Nov 28 14:22:27 EST 2016 ferguson>
 */
#include <stdio.h>
#include <stdlib.h>
#include "Circuit.h"



//for circuit 1 in project. (x AND NOT y) OR (y AND z)
static Circuit* circuit1() {
  Value** xyz = arrayValue3();
  /* xyz is array where
  * xyz[0] = x, xyz[1] = y, xyz[2] = z
  */
  //define gates
  Gate* notY = new_Inverter(xyz[1]);
  Gate* xAndNotY = new_AndGate(xyz[0],Gate_getOutput(notY));
  Gate* yAndZ = new_AndGate(xyz[1],xyz[2]);
  Gate* or = new_OrGate(Gate_getOutput(xAndNotY),Gate_getOutput(yAndZ));
  //make circuit
  
	Value** outputs = new_Value_array(1);
	outputs[0] = Gate_getOutput(or);
	Gate** gates = new_Gate_array(4);
	gates[0] = notY;
	gates[1] = xAndNotY;
	gates[2] = yAndZ;
	gates[3] = or;
	//for (int i = 0; i < gates.size(); i++) Gate_print(gates[i]);
	return  new_Circuit(3, xyz, 1, outputs, 4, gates);
}

//for circuit 2. (x nand not y) nor (y nand z) = not(notx or y or not y or not z)
static Circuit* circuit2() {
	Value** xyz = arrayValue3(); //default array of booleans
    //make circuit
	Gate** gates = new_Gate_array(5); 
	gates[0] = new_Inverter(xyz[0]); //not x
	gates[1] = new_Inverter(xyz[1]); //not y
	gates[2] = new_Inverter(xyz[2]); //not z
	gates[3] = new_Or4Gate(Gate_getOutput(gates[0]),xyz[1],Gate_getOutput(gates[1]),Gate_getOutput(gates[2])); //or4
	gates[4] = new_Inverter(Gate_getOutput(gates[3])); //nor4
	//output last gate
	Value** outputs = new_Value_array(1);
	outputs[0] = Gate_getOutput(gates[4]);

	return new_Circuit(3, xyz, 1, outputs, 5, gates);
}

/*for circuit 3
*  (y and x) or (not x and not y) = (x and y) or not (x or y)
*/
static Circuit* circuit3 () {
  //define gates
  Value** xy = arrayValue2();
  Gate* xAndY = new_AndGate(xy[0],xy[1]);
  Gate* xOrY = new_OrGate(xy[0],xy[1]);
  Gate* notXOrY = new_Inverter(Gate_getOutput(xOrY));
  Gate* or = new_OrGate(Gate_getOutput(xAndY),Gate_getOutput(notXOrY));
  //make circuit
    Value** outputs = new_Value_array(1);
	outputs[0] = Gate_getOutput(or);
	Gate** gates = new_Gate_array(3);
	gates[0] = xAndY;
	gates[1] = xOrY;
	gates[2] = notXOrY;
	gates[3] = or;
	//for (int i = 0; i < gates.size(); i++) Gate_print(gates[i]);
	return  new_Circuit(2, xy, 1, outputs, 4, gates);

}


/*extra credit: one-bit adder circuit. focs 13.10
* for output d: (not x and y and c) or (x and not y and c) or (x and y and not c) or (x and y and c)
* =(y and z) or (x and z) or (x and y)
*/
static Circuit* circuitD() {
  Value** xyz = arrayValue3();
   //define gates
  Gate* xAndY = new_AndGate(xyz[0],xyz[1]);
  Gate* xAndZ = new_AndGate(xyz[0],xyz[2]);
  Gate* yAndZ = new_AndGate(xyz[1],xyz[2]);
  Gate* or = new_Or3Gate(Gate_getOutput(xAndY),Gate_getOutput(yAndZ),Gate_getOutput(xAndZ));
  //make circuit
  
	Value** outputs = new_Value_array(1);
	outputs[0] = Gate_getOutput(or);
	Gate** gates = new_Gate_array(4);
	gates[0] = xAndY;
	gates[1] = xAndZ;
	gates[2] = yAndZ;
	gates[3] = or;
	//for (int i = 0; i < gates.size(); i++) Gate_print(gates[i]);
	return  new_Circuit(3, xyz, 1, outputs, 4, gates);
}

/*extra credit: one-bit adder circuit. focs 13.10
* for output z: (not x and not y and c) or (not x and y and not c) or (x and not y and not c) or (x and y and c)
* (not x)(not y)c + (not x)y(not c) + x(not y)(not c) + xyc
*/
static Circuit* circuitZ() {
  Value** xyz = arrayValue3();
   //define gates
  Value* x = xyz[0];
  Value* y = xyz[1];
  Value* c = xyz[2];
  Gate* notX = new_Inverter(x);
  Gate* notY = new_Inverter(y);
  Gate* notC = new_Inverter(c);
  Gate* notXnotYC = new_And3Gate(Gate_getOutput(notX),Gate_getOutput(notY),c); //not x and not y and c
  Gate* notXYnotC = new_And3Gate(Gate_getOutput(notX), y, Gate_getOutput(notC)); //(not x and y and not c)
  Gate* xnotYnotC = new_And3Gate(x, Gate_getOutput(notY),Gate_getOutput(notC)); //(x and not y and not c)
  Gate* xYC = new_And3Gate(x,y,c); //(x and y and c)
  Gate* or4 = new_Or4Gate(Gate_getOutput(notXnotYC),Gate_getOutput(notXYnotC),Gate_getOutput(xnotYnotC),Gate_getOutput(xYC)); //final
  //circuit
	Value** outputs = new_Value_array(1);
	outputs[0] = Gate_getOutput(or4);
	Gate** gates = new_Gate_array(8);
	gates[0] = notX;
	gates[1] = notY;
	gates[2] = notC;
	gates[3] = notXnotYC;
	gates[4] = notXYnotC;
	gates[5] = xnotYnotC;
	gates[6] = xYC;
	gates[7] = or4 ;
	//for (int i = 0; i < gates.size(); i++) Gate_print(gates[i]);
	return  new_Circuit(3, xyz, 1, outputs, 8, gates);
}


static char* b2s(bool b) {
	return b ? "T" : "F";
}

//test for all combos for 3 inputs
static void test3In1OutAll(Circuit* circuit) {
	for (int i = 1; i >= 0; i--) {
		for (int k = 1; k >= 0; k--) {
			for (int l = 1; l >= 0; l--) {
				Circuit_setInput(circuit, 0, (bool) i);
				Circuit_setInput(circuit, 1, (bool) k);
				Circuit_setInput(circuit, 2, (bool) l);
				Circuit_update(circuit);
				bool out0 = Circuit_getOutput(circuit, 0);
				printf("%s %s %s -> %s\n", b2s((bool)i), b2s((bool)k), b2s((bool)l), b2s(out0));
			}
		}
	}	
}

//test for all combos for 2 inputs
static void test2In1OutAll (Circuit* c) {
	for (int i = 1; i >= 0; i--) {
		for (int k = 1; k >= 0; k--) {
			Circuit_setInput(c, 0, (bool) i);
			Circuit_setInput(c, 1, (bool) k);
			Circuit_update(c);
			bool out0 = Circuit_getOutput(c, 0);
			printf("%s %s -> %s\n", b2s((bool)i), b2s((bool)k), b2s(out0));
		}
	}
}



int main(int argc, char **argv) {

	Circuit* c1  = circuit1();//create new circuit
	printf("Testing circuit1 : (x and not y) or (y and z) \n");
	test3In1OutAll(c1);

	Circuit* c2 = circuit2();//create new circuit
	printf("Testing circuit2 : (x nand not y) nor (y nand z) \n");
	test3In1OutAll(c2);

	Circuit* c3 = circuit3();
	printf("Testing circuit3 :  (y and x) or (not x and not y) \n");
	test2In1OutAll(c3);

	Circuit* c4 = circuitD();
	printf("Testing extra credit circuit4 for gate d: \n");
	printf("  (not x and y and c) or (x and not y and c) or (x and y and not c) or (x and y and c) \n");
	test3In1OutAll(c4);

	Circuit* c5 = circuitZ();
	printf("Testing extra credit circuit5 for gate z : \n");
	printf(" (not x and not y and c) or (not x and y and not c) or (x and not y and not c) or (x and y and c) \n");
	test3In1OutAll(c5);

}
