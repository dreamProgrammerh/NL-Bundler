# Contributing to NL Bundler

## Development Workflow

```bash
# Clone and build
git clone https://github.com/dreamprogrammerh/nl-bundler
cd nl-bundler
make dev

# Run tests
make test

# Build the bundler itself
make

# Test on a real library
./bin/nlc build libs/arena/v1.0/src -o test.nl
```

## Code Style

- **Indentation**: 4 spaces (no tabs)
- **Line length**: 100 characters max
- **Braces**: Same line for functions
- **Comments**: Use `//` for single line, `/* */` for multi-line
- **Naming**:
  - `camelCase` for functions/variables
  - `PascalCase` for types
  - `UPPER_CASE` for macros

## Adding New Features

1. Create a branch: `git checkout -b feature/name`
2. Add tests in `tests/` directory
3. Update documentation
4. Run `make test` to verify
5. Submit a pull request

## Testing

```bash
# Unit tests
make test-unit

# Integration tests
make test-integration

# Full test suite
make test-all
```

## Release Process

```bash
# Update version
make version VERSION=1.0.0

# Build release
make release

# Create tag
git tag -a v1.0.0 -m "Version 1.0.0"
git push --tags
```

## Code of Conduct

Be excellent to each other. That's it.