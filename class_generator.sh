#!/usr/bin/env bash
##############################################################
#   Usage                                                    #
#   ./class_generator.sh basePath Class1 Class2 Class3       #
##############################################################

cd $1

for i in ${@:2}; do

    echo "#include \"../base.h\"

typedef struct __$i *$i;

$i ${i}_new();

void ${i}_delete($i instance);
" > $i.h;

    echo "#include \"$i.h\"

struct __$i {
};

$i ${i}_new() {
  $i instance = malloc(sizeof(struct __$i));
  return instance;
}

void ${i}_delete($i instance) {
    free(instance);
}
" > $i.c;

done