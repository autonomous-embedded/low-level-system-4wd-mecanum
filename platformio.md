# PlatformIO Project

Development of the low-level system was carried out using the [PlatformIO](https://platformio.org/) toolset, which is an open source ecosystem for embedded development. It includes a cross-platform IDE and a unified debugger.

For more information about the PlatformIO project itself, see the [official documentation](https://docs.platformio.org/en/latest/).

## VSCode Integration

We recommend using the [Visual Studio Code](https://code.visualstudio.com/) IDE with the [PlatformIO](https://platformio.org/) extension for development of the low-level system. 

For information about installing the PlatformIO extension, see the [official documentation](https://docs.platformio.org/en/latest/integration/ide/vscode.html).

### Building the Project
1. Open the `low-level-system-4wd-mecanum` directory in the VSCode IDE.
2. Open the PlatformIO sidebar by clicking the PlatformIO icon in the left sidebar.
   - The project should be automatically detected by PlatformIO.
   - If the project is not detected, click the `Open Project` button in the PlatformIO sidebar and select the `low-level-system-4wd-mecanum` directory.
3. Build the project by clicking the `Build` button in the PlatformIO sidebar.
   - The project should build successfully.
   - If the project does not build successfully, check the Build output for errors.
4. Upload the project to the Arduino Diecimila board by clicking the `Upload` button in the PlatformIO sidebar.

> **Note:** If you want to monitor the serial port output of the Arduino Diecimila board, you can use the PlatformIO Monitor by clicking the `Monitor` button in the PlatformIO sidebar.

#### Build options
For a project two build environments  are defined in the `platformio.ini` file:
- diecimilaatmega328-release - Release build environment for the Arduino Diecimila board, which does not support debugging messages via the serial port.
- diecimilaatmega328-debug - Debug build environment for the Arduino Diecimila board, which supports debugging messages via the serial port.

For the development, testing and debugging of the low-level system we recommend using the `diecimilaatmega328-debug` build environment. Although the `diecimilaatmega328-release` build should be used for the final deployment of the low-level system on the Arduino Diecimila board since debugging messages via the serial port can cause serial communication errors and affect the performance of the low-level system.



