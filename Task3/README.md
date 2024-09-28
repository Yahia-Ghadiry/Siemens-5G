# Building Code

For building code we need clang++ and use the following: 

```bash
make
```

To use a diffrent compiler change CC in Makefile

After running make the programe name will be program.elf
To change the name of ouput program change TARGET in Makefile


## Usage

```bash
program.elf input_options.txt ouput.txt
```

Replace input_options.txt with options file name.

# Notes

Assuming I and Q take only one byte each
Assuming 14 OFFDM symbols in for each slot (not extended Cyclic Prefix)
Assuming MaxNRB is Accouriding to Spec
