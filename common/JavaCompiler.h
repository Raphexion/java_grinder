/**
 *  Java Grinder
 *  Author: Michael Kohn
 *   Email: mike@mikekohn.net
 *     Web: http://www.mikekohn.net/
 * License: GPL
 *
 * Copyright 2014 by Michael Kohn
 *
 */

#ifndef _JAVA_COMPILER_H
#define _JAVA_COMPILER_H

#include "Compiler.h"
#include "Generator.h"
#include "JavaClass.h"

#define GET_PC_INT16(a) ((int16_t)(((uint16_t)bytes[pc+a+0])<<8|bytes[pc+a+1]))
#define GET_PC_UINT16(a) (((uint16_t)bytes[pc+a+0])<<8|bytes[pc+a+1])
#define GET_PC_INT32(a) ((int32_t)((uint32_t)bytes[pc+a+0])<<24| \
                        ((uint32_t)bytes[pc+a+1])<<16|\
                        ((uint32_t)bytes[pc+a+2])<<8|\
                         bytes[pc+a+3])
#define GET_PC_UINT32(a) (((uint32_t)bytes[pc+a+0])<<24| \
                         ((uint32_t)bytes[pc+a+1])<<16|\
                         ((uint32_t)bytes[pc+a+2])<<8|\
                          bytes[pc+a+3])

class JavaCompiler : public Compiler
{
public:
  JavaCompiler();
  virtual ~JavaCompiler();

  virtual int load_class(FILE *in);
  virtual void insert_static_field_defines();
  virtual void init_heap();
  virtual int add_static_initializers();
  virtual int compile_methods(bool do_main);

private:
  void fill_label_map(uint8_t *label_map, int label_map_len, uint8_t *bytes, int code_len, int pc_start);
  int optimize_const(JavaClass *java_class, char *method_name, uint8_t *bytes, int pc, int pc_end, int address, int const_val);
  int array_load(JavaClass *java_class, int constant_id, uint8_t array_type);
  int array_store(JavaClass *java_class, int constant_id, uint8_t array_type);
  int compile_method(JavaClass *java_class, int method_id);

  JavaClass *java_class;
  static uint8_t cond_table[];
};

#endif

