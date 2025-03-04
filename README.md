# B (باء) Programming Language

B (باء) is a programming language designed to support Arabic syntax while maintaining full compatibility with K&R C features. It allows developers to write code using Arabic keywords and identifiers while following established C programming patterns.

## Current Status (v0.1.9.5)

The project now supports:

### Core Features
- Basic type system with K&R C compatibility
  - عدد_صحيح (int) - 32-bit integer
  - عدد_حقيقي (float) - 32-bit float
  - حرف (char) - 16-bit UTF-16 character
  - فراغ (void) - No value type

- Core operator system
  - Arithmetic operators (+, -, *, /, %)
  - Comparison operators (==, !=, <, >, <=, >=)
  - Assignment operator (=)
  - Type checking and validation
  - Arabic operator names

- Control Flow Structures
  - إذا/وإلا (if/else)
  - طالما (while)
  - إرجع (return)

- Arabic File Support
  - Native `.ب` extension
  - Full UTF-8 support
  - Arabic file naming
  - Build system integration

For detailed information about Arabic file support, see [Arabic Support Documentation](docs/arabic_support.md).

### Changelog:

**Added:**
- Enhanced parser debug output for better troubleshooting.
- Test files for Arabic program parsing.
- UTF-8 support for Arabic identifiers in the parser.

**Changed:**
- Refactored parser functions for improved error handling.
- Simplified number parsing (temporarily removed decimal support).
- Improved error messages with more context.

**Fixed:**
- Memory leaks in parser error handling.
- Function declaration parsing.
- Identifier parsing for UTF-8 characters.

### Roadmap:

**Completed Features:**
- Core components (AST, Basic Type System, Basic Operators, Memory Management, Basic Error Handling).
- Arabic support (UTF-8 encoding, Basic Arabic identifiers, Basic RTL support, Arabic error messages).
- Documentation (Language specification, Arabic support guide, C comparison, Architecture overview, Component documentation).

**In Progress:**
- Parser Development (Grammar definition, Token handling, Error recovery, Source location tracking).
- Code Generation (LLVM integration planning, Basic code emission, Debug information support).
- Standard Library (Basic I/O functions, String manipulation, Memory management, File operations).

**Short-term Goals (0.2.0):**
- Complete control flow parsing (إذا, وإلا, طالما).
- Restore decimal number parsing.
- Full operator precedence handling.

### Project Structure
```
baa/
├── src/
│   ├── types/       # Type system implementation
│   └── operators/   # Operator system implementation
├── tests/
│   ├── test_types.c    # Type system tests
│   └── test_operators.c # Operator tests
└── docs/
    ├── architecture.md  # System architecture
    ├── components.md    # Component details
    ├── development.md   # Developer guide
    ├── language.md      # Language specification
    ├── arabic_support.md # Arabic support documentation
    └── roadmap.md       # Development roadmap
```

## Building from Source

### Prerequisites
- CMake 3.20 or higher
- K&R C compliant compiler
- Git for version control
- LLVM development libraries
- Unicode support libraries

### Build Steps
```bash
git clone <repository-url>
cd baa
mkdir build && cd build
cmake ..
cmake --build .
```

### Running Tests
```bash
# Build and run type system tests
gcc -o test_types tests/test_types.c src/types/types.c -I./src
./test_types

# Build and run operator tests
gcc -o test_operators tests/test_operators.c src/operators/operators.c src/types/types.c -I./src
./test_operators
```

## Features

### Type Safety
- Strong type checking
- Explicit conversion rules
- Error type for invalid operations
- UTF-16 support for Arabic text

### Operator System
- Type-safe operations
- Arabic operator names
- K&R C operator precedence
- Comprehensive error handling

### Documentation
- Detailed Arabic error messages
- Comprehensive documentation in both English and Arabic
- Examples and usage guides
- Development guidelines

## File Extensions
The Baa programming language supports two file extensions:
- `.ب` - The primary Arabic file extension
- `.baa` - Alternative Latin file extension

### Example Program
```baa
#تضمين <مكتبة_طباعة>

// مثال برنامج بسيط بلغة باء
دالة رئيسية() {
    اطبع("مرحباً بالعالم!").
    إرجع 0.
}
```

## Contributing

We welcome contributions! Please see our [development guide](docs/development.md) for details on:
- Code style and standards
- Testing requirements
- Documentation guidelines
- Pull request process

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

Special thanks to:
- The C language designers for their foundational work
- The Arabic programming community for their support and feedback
- All contributors who have helped shape this project
