# RISC-V Assembly to Binary Converter

This project is a **RISC-V Assembly to Binary Converter** written in C++. It parses assembly language instructions and converts them into their respective machine-level binary code. This tool is useful for students, educators, and developers working with assembly languages or those interested in learning how instructions are encoded at a lower level.

## Features

- **Instruction Types Supported**: 
  - Register-type (R-type) instructions: `ADD`, `SLT`, `SLTU`, `AND`, `OR`, `XOR`, `SLL`, `SRL`, `SUB`, `SRA`
  - Immediate-type (I-type) instructions: `ADDI`, `ORI`, `XORI`, `SLTI`, `ANDI`, `SLLI`, `SRLI`, `SRAI`
  - Load-type (L-type) instructions: `LW`, `LD`, `LH`, `LB`, `LWU`, `LHU`, `LBU`
  - Store-type (S-type) instructions: `SW`, `SD`, `SB`, `SHW`
  - Branch-type (B-type) instructions: `BEQ`, `BNE`, `BLT`, `BGE`
  - Upper Immediate-type (U-type) instructions: `LUI`, `AUIPC`
  - Jump-type (J-type) instructions: `JAL`
  
- **Label Support**: Handles labels and branches, calculating the correct offsets.
- **File Input/Output**: Reads assembly instructions from an input file and writes the corresponding binary instructions to an output file.
- **Error Handling**: Reports errors for unsupported instructions, register out-of-range, immediate value out-of-range, and more.

## Table of Contents

- [Getting Started](#getting-started)
- [Usage](#usage)
- [Instruction Types](#instruction-types)
- [Code Structure](#code-structure)
- [Contributing](#contributing)

## Getting Started

### Prerequisites

- A C++ compiler like G++
- Basic knowledge of assembly language, especially the RISC-V architecture.

### Installation

1. **Clone the repository:**

2. **Compile the code:**
   
3. **Run the converter:**
   Make sure the input assembly file (`input.asm`) is in the same directory or provide a path.

## Usage

1. **Prepare your input assembly file (`input.asm`):**
   Here's an example:
   ```
    add x3, x4, x5
    addi x3, x3, 10
    
    for:
    bne x3, x2, done
    lw x2, 10(x3)
    jal x2, for
    
    done:
    sw x1, 13(x3)
   ```

2. **Run the assembler:**
   Run the compiled binary, and it will automatically process the `input.asm` and generate the `output.bin` file:

3. **View the output:**
   The output binary file (`output.bin`) will contain the binary instructions for your assembly code.

## Instruction Types

This converter handles the following types of RISC-V instructions:

### Register-Type (R-type)

These instructions operate on registers and include operations like `ADD`, `SUB`, `AND`, `OR`, etc.

Example:
```
ADD x12, x13, x14
```

### Immediate-Type (I-type)

Immediate instructions use a constant value (immediate) with registers, like `ADDI`, `XORI`, etc.

Example:
```
ADDI x12, x13, 10
```

### Load-Type (L-type)

Loads data from memory into a register, like `LW`, `LH`, etc.

Example:
```
LW x12, 0(x13)
```

### Store-Type (S-type)

Stores data from a register into memory, like `SW`, `SB`, etc.

Example:
```
SW x12, 0(x13)
```

### Branch-Type (B-type)

Conditional branch instructions, like `BEQ`, `BNE`, etc.

Example:
```
BEQ x12, x13, label
```

### Upper Immediate-Type (U-type)

Upper immediate instructions, `LUI` and `AUIPC`, which load 20-bit immediate values.

Example:
```
LUI x10, 0x00000
```

### Jump-Type (J-type)

Jump and link instructions like `JAL` (jump and link).

Example:
```
JAL x1, label
```

## Code Structure

The project contains several C++ classes to handle different instruction types:

- **`registerType`**: Handles R-type instructions.
- **`immediateType`**: Handles I-type instructions.
- **`loadType`**: Handles L-type instructions.
- **`storeType`**: Handles S-type instructions.
- **`branchType`**: Handles B-type instructions.
- **`jumpType`**: Handles J-type instructions.
- **`upperImmediateType`**: Handles U-type instructions.
- **`convertor`**: The main class that parses and processes the input file, converting assembly instructions to binary.

The `convertor` class reads the assembly code, splits it into parts, identifies instruction types, and converts each instruction into binary using its respective class. The binary result is then written to the output file.

## How the Conversion Works

Each instruction has a specific format, and the conversion process involves:

1. **Opcode**: Each instruction type has a unique opcode.
2. **Registers**: Registers are converted to 5-bit binary strings.
3. **Immediate values**: Immediate values are handled carefully, with checks on their range and correct sign extension.
4. **Labels**: Labels are identified in the first pass, and their positions are stored. In the second pass, they are replaced with appropriate offsets in branch or jump instructions.

## Example

Here’s an example of converting a simple instruction using the tool:

Input (Assembly):
```
ADD x23, x18, x19
```

Output (Binary):
```
00000001001110010000101110110011
```

The tool reads the `input.asm`, processes the instruction, and outputs the binary equivalent into `output.bin`.

## Contributing

Contributions are welcome!! If you find a bug, want to add more instruction support, or improve the code structure feel free to submit a pull request or open an issue
