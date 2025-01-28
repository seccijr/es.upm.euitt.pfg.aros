# AROS Project

The AROS Project is an initiative to develop a scalable communication architecture for distributed embedded devices. The architecture facilitates seamless communication between devices without relying on centralized message coordination systems, such as application servers or message hubs. This approach enables peer-to-peer collaboration, allowing devices to initiate cooperative tasks autonomously.

## Key Objectives

1. **Decentralized Communication**  
   AROS aims to eliminate the need for centralized intermediaries, enabling devices to communicate directly and equally. This ensures robust and flexible collaboration between devices, even in dynamic environments.

2. **Scalability and Adaptability**  
   The architecture supports horizontal scaling, making it capable of accommodating an undefined number of devices. Devices can join or leave the network randomly without disrupting ongoing tasks. This flexibility is particularly suited for scenarios like swarm robotics, where a collective task continues to function efficiently despite the loss or addition of participants.

3. **Environmental Adaptability**  
   AROS is designed to operate in diverse environments without significant setup overhead. Whether there are changes to the hardware, communication medium, or operational conditions, the system can adapt quickly. This ensures its utility in collaborative efforts involving heterogeneous devices in a variety of scenarios.

## Features

This project leverages the Arduino toolchain to develop and manage multiple sketches, handlers, and libraries, implementing core functionality such as:

- **Motor Control:** Modules for line following and turning.
- **Communication:** Wired and wireless communication capabilities.
- **Handlers:** Roles such as token collecting, carrying, and remote control are implemented through modular handlers.
- **Unit Testing:** Includes unit tests (using ArduinoUnit) for validating the system’s functionality.

## Architecture Overview

The project uses CMake to build, configure, and run the Arduino SDK. It supports testing via Arduino hardware (e.g., Arduino UNO) or local execution when applicable.

### Core Components

1. **Handlers**

   - `CarrierHandlerClass`: Manages carrier actions such as moving to meeting points or returning to base.
   - `TokenCollectorHandlerClass`: Implements token collection and manipulates an attached servo arm.
   - `RemoteHandlerClass`: Sends vectors to the communication board using I²C.
   - `FWHandlerClass`: Forwards unknown addresses to appropriate handlers.
   - `EchoHandler` (for testing): Demonstrates message echoing functionality.

2. **Modules**
   - `/comm`: Handles communication via UDP and wired protocols.
   - `/master`: Central logic for role handlers and task coordination.
   - `/motor`: Provides motor control and line-following functionality.
   - `/utility`: Contains common constants, credentials, definitions, and role management utilities.
   - `/test`: Unit tests implemented with ArduinoUnit.

## Building the Project

Follow these steps to build the project using CMake:

1. Create a build directory:

```bash
   mkdir build && cd build
```

2. Configure the project:

```bash
   cmake ..
```

3. Build the project:

```bash
    make
```

4. On Windows, specify a generator (e.g., -G "MinGW Makefiles").

## License

This project is licensed under the MIT License. See the full license text below:

### MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## Disclaimer

Use this software at your own risk. The authors are not liable for any potential damages or misuse.
