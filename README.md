# Includer Cli Application

## Overview

The includer application is a C++ program designed to process input streams and handle specific commands embedded within the stream. It supports commands for including files, handling template heads and tails, and splitting the stream processing.

## Features

- **Stream Processing**: Reads characters from an input stream and processes them.
- **Command Handling**: Supports commands such as `@include`, `@template_head`, `@tail`, and `@split`.
- **Template Management**: Handles template heads and tails for nested template processing.
- **File Inclusion**: Includes content from other files specified in the stream.

## Dependencies

- run 'make deps'

## Installation

1. Run this command. The plain binary, the debian and rpm packages should be found in directory called release.
    ```sh
    make all
    ```
## Usage

Run includer --help, or view man includer.

```sh
cat input.txt | includer -t tempalte_dir > output.txt
```

## License

BSD-3-Clause

## Author

Peter Csaszar (Császár Péter) - 2024
