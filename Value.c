/*
 * Value.c
 * Creator: George Ferguson
 * Created: Sun Nov 27 14:08:51 2016
 * Changed: Luba Le Xuan
 * Date: Dec 3, 2016
 * Added arrayValue functions, that prevent from repeating array initiation in main
 */

#include <stdlib.h>
#include <stdio.h>
#include "Value.h"

typedef struct Value {
	bool value;
} Value;

Value** arrayValue3 () {
  Value* x = new_Value(false);
  Value* y = new_Value(false);
  Value* z = new_Value(false);
  Value** xyz = new_Value_array(3);
	xyz[0] = x;
	xyz[1] = y;
	xyz[2] = z;
  return xyz;
}

Value** arrayValue2 () {
  Value* x = new_Value(false);
  Value* y = new_Value(false);
  Value** xy = new_Value_array(2);
	xy[0] = x;
	xy[1] = y;
    return xy;
}

Value* new_Value(bool value) {
	Value* this = (Value*)malloc(sizeof(Value));
	this->value = value;
	return this;
}

Value** new_Value_array(int len) {
	Value** this = (Value**)calloc(sizeof(Value*), len);
	return this;
}

bool Value_getValue(Value* this) {
	return this->value;
}

void Value_setValue(Value* this, bool b) {
	this->value = b;
}

void Value_print(Value* this) {
	printf("0x%lx=%s", this, this->value ? "true" : "false");
}
