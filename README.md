# Low-level System

Low-level system workspace for Autonomous Mecanum Car project.

## Description

Low-level system is designed to control the movement of the Nexus 4WD Mecanum robot. The robot is equipped with four DC motors with encoders and four ultrasonic sensors.

As a microcontroller, the Arduino Diecimila board is used. The system is implemented in C++ using the [PlatformIO](https://platformio.org/) toolset.  
Microcontroller is responsible for:
- receiving commands from the high-level system,
- controlling the motors of the robot accordingly to the received commands,
- applying the PID control to the motors.

### Communication
The system communicates with the high-level system via the serial port. The communication protocol is defined in the `mecanum.proto` file located in the `mecanum-if/protobuf` directory.

**UART communication parameters:**
- Baud rate: 19200
- Data bits: 8
- Parity: None
- Stop bits: 1
- Flow control: None

## Cloning the Repository with Submodules

To clone the repository with submodules, run: 
```bash 
git clone --recurse-submodules git@github.com:autonomous-embedded/low-level-system-4wd-mecanum.git
```

If you forget the `--recurse-submodules` flag during cloning, you can initialize and update submodules manually after cloning:
```bash
# Navigate into the repository's directory
cd low-level-system-4wd-mecanum

# Initialize and update submodules
git submodule init
git submodule update
```

## Repository Structure

The `low-level-system-4wd-mecanum` repository structure is presented below:
```
.
├── bootloader
├── doc
├── include
├── lib
├── mecanum-if
├── platformio.ini
├── README.md
├── src
└── test
```

It contains mainly a [PlatformIO](https://platformio.org/) project, which includes the following files and directories:
- `platformio.ini` - PlatformIO project configuration file
- `src/` - Source code directory,
- `lib/` - Libraries directory (see [README.md](lib/README.md)),
- `include/` - Header files directory,
- `test/` - Test files directory (see [README.md](test/README.md)).

Besides the PlatformIO project files, the repository also contains the following files and directories:
- `bootloader/` - Instruction and required files for burning the bootloader of the Arduino Diecimila in case of bricked board (see [README.md](bootloader/README.md)),
- `docs/` - Documentation directory with files provided by the manufacturer of the Nexus 4WD Mecanum robot,
- `mecanum-if/` - Protocol Buffers submodule directory (see [README.md](mecanum-if/README.md)).

