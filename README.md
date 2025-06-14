# File Transmitter

This project implements a simple file transfer system in C, where a sender program sends a specified file over a network to a receiver program. The file is transmitted via TCP, allowing reliable data transfer.

## Table of Contents
- [Features](#features)
- [Requirements](#requirements)
- [Usage](#usage)
- [Known Issues](#known-issues)
- [Example](#example)
- [License](#license)

## Features

- **Send Files**: The sender program can send files over TCP by specifying the file path.
- **Receive Files**: The receiver program listens for incoming file data and writes it to the "Download" folder.
- **(TODO) Cross-Platform Compatibility**: Code is compatible with both Windows and Unix-based systems.

## Requirements

- **C Compiler** (GCC/Clang on Unix, MSVC on Windows)
- **Sockets Library** (WS2_32 on Windows, `<sys/socket.h>` on Unix)
- **Windows-Specific**: `Winsock` initialization (for Windows systems only)

## Usage
 
1. **Compile the Code**:
     ```bash
     make
     ```

2. **Send a File**:
   Start the sender program and specify the path to the file you want to send:
   - On Unix:
     ```bash
     ./sender
     ```
   - On Windows:
     ```bash
     .\sender.exe
     ```

3. **Start the Receiver**:
   Run the receiver program to begin listening for incoming files:
   - On Unix:
     ```bash
     ./receiver
     ```
   - On Windows:
     ```bash
     .\receiver.exe
     ```

## Known Issues

- **Incomplete File Transfers**: Files may arrive with `0` bytes or be partially transferred if there are network issues or improper handling of socket errors.
 
## Example

```plaintext
Enter address: 127.0.0.1
Enter port: 1111
Enter path to file you want to send: C:\Users\without eyes\Pictures\image.png
File was successfully sent!
```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
